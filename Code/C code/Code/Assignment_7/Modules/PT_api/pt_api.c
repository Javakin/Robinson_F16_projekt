/*****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: spi_api.c
*
* PROJECT....: semester project 4
*
* DESCRIPTION: supports an interface for using the message_queues
*
* Change Log:
******************************************************************************
* Date    Id    Change
* YYMMDD
* --------------------
* 150516  DFH    Module created
*
*****************************************************************************/

/***************************** Include files *******************************/
#include <stdint.h>
#include <tm4c123gh6pm.h>
#include "EMP/emp_type.h"
#include "PT_api/PT_api.h"
#include "Tasking/messages.h"
#include "Tasking/tmodel.h"
#include "Tasking/events.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"



/*****************************    Defines    *******************************/


/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/

extern xQueueHandle spi_tx_queue;
extern xQueueHandle spi_rx_queue;

//extern xSemaphoreHandle pt_semaphore;


/*****************************   Functions   *******************************/


INT8U pt_api_send_message( INT8U address, INT8U PT, INT8U ssm_address)
{
	// define variables
	INT16U placeholder;
	INT8U return_val = 0;
	INT16U data_holder;

	data_holder = get_msg_state(ssm_address);

	// convert the relative number to tacks
	if (address == ADR_TARGET_POS)
	{
		// desable preemption or interrupt
		//taskENTER_CRITICAL();

		//message = pt_api_convert_to_tach(PT, 5000);
		//pt_api_convert_to_tach(PT, 2000);

		//taskEXIT_CRITICAL();
	}

	// 2 adress bit 1 p/t bit and 11 message bits
	// 0 0 a a pt d d d d d  d d d d d d
	placeholder = data_holder & 0x07FF;
	placeholder |= ((PT & 0x0001) << 11);
	placeholder |= ( address << 12 );

	// send the message via spi_master
	return_val = xQueueSend(spi_tx_queue, &( placeholder ), portMAX_DELAY);


	return return_val;
}

INT8U pt_api_get_adress(INT16U message)
{
	return message >> 12;
}

INT16U pt_api_get_data(INT16U message)
{
	return message & 0x07FF;
}

INT16U pt_api_get_pt(INT16U message)
{
	return 1 & (message >> 11);
}

void pt_api_receive_message(INT16U message)
{
	// deal with the received message
	switch(pt_api_get_adress(message))
	{
	case ADR_TARGET_POS:
		switch(pt_api_get_pt(message))
		{
		case SUB_ADR_PAN:
			put_msg_state(SSM_CURRENT_PAN, pt_api_get_data(message));
			break;

		case SUB_ADR_TILT:
			put_msg_state(SSM_CURRENT_TILT, pt_api_get_data(message));
			break;
		}
		break;
	}
}

INT16U pt_api_convert_to_tach(INT8U PT, INT16U message)
{
	// define variables
	FP64 pos = message - 5000;
	FP64 span;
	FP64 height = get_msg_state(SSM_HEIGHT)*1000;

	// get the value for plant
	if (PT == SUB_ADR_PAN)
		span = get_msg_state(SSM_WIDTH)*1000;
	if (PT == SUB_ADR_TILT)
		span = get_msg_state(SSM_DEPTH)*1000;

	// perform calculation
	FP64 a = span/10000;
	a *= pos;

	FP64 Tak = 1080/(2*3.1415);

	Tak = pt_api_atan(a/height);

	Tak = pt_api_atan(1);
	Tak = pt_api_atan(0.5);

	Tak += 540;

	INT16S ret_val = Tak;

	return ret_val;
}

FP64 pt_api_atan(FP64 value)
{
	//initiate values
	FP64 result = 0;
	FP64 sub_result;

	for (INT8U i = 1; i < 4; i++)
	{
		// reset sub result
		sub_result = value;

		// z power
		for(INT8U j = 1; j < (i*2 - 1); j++)
			sub_result *= value;

		// divide
		sub_result /= (i*2 - 1);

		// append part
		if (i % 2)
			result += sub_result;
		else
			result -= sub_result;
	}

	return result;
}

INT8U pt_api_set_coord(INT16U pan, INT16U tilt)
{
	INT8U ret_val = pdTRUE;

	// send a new pan target
	ret_val &= put_msg_state(SSM_TARGET_PAN, pan);
	ret_val &= pt_api_send_message(ADR_TARGET_POS, SUB_ADR_PAN, SSM_TARGET_PAN);

	// send a new tilt target
	ret_val &= put_msg_state(SSM_TARGET_TILT, tilt);
	ret_val &= pt_api_send_message(ADR_TARGET_POS, SUB_ADR_TILT, SSM_TARGET_TILT);

	return ret_val;
}


/****************************** End Of Module *******************************/














