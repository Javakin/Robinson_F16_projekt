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
#include <math.h>		//required for conversion to tach


/*****************************    Defines    *******************************/


/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/

extern xQueueHandle spi_tx_queue;
extern xQueueHandle spi_rx_queue;

extern xSemaphoreHandle pt_semaphore;

/*****************************   Functions   *******************************/

INT8U pt_api_send_message_no_conv( INT8U adress, INT8U PT, INT8U ssm_address)
{
	INT16U data_holder = get_msg_state(ssm_address);
	//this api send will ignore conversion, made for the goto_tach instruction
	
	// 2 adress bit 1 p/t bit and 11 message bits
	// 0 0 a a pt d d d d d  d d d d d d
	INT16U placeholder = data_holder & 0x07FF;
	placeholder |= ((PT & 0x0001) << 11);
	placeholder |= ( adress << 12 );

	// send the message via spi_master
	return xQueueSend(spi_tx_queue, &( placeholder ), portMAX_DELAY);
}

INT8U pt_api_send_message( INT8U address, INT8U PT, INT8U ssm_address)
{
	// define variables
	INT16U placeholder;
	INT8U return_val = 0;
	INT16U data_holder;

	if (xSemaphoreTake(pt_semaphore, portMAX_DELAY) == pdTRUE)
	{
		data_holder = get_msg_state(ssm_address);

		// 2 adress bit 1 p/t bit and 11 message bits
		// 0 0 a a pt d d d d d  d d d d d d
		placeholder = data_holder & 0x07FF;
		placeholder |= ((PT & 0x0001) << 11);
		placeholder |= ( address << 12 );
	
		// send the message via spi_master
		return_val = xQueueSend(spi_tx_queue, &( placeholder ), portMAX_DELAY);
	
		xSemaphoreGive(pt_semaphore);
	}

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
	return message & 0x0800;
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

INT16U pt_api_convert_to_tach(INT16U message)
{
	//here we recieve a number from 1 to 10000
	//this must be converted to a tach value depending on constraints
/* 	
	INT16U Height = get_msg_state(SSM_LENGTH);
	INT16U Width = get_msg_state(SSM_WIDTH);
	INT16U Depth = get_msg_state(SSM_DEPTH);

	//restraints in meter for pan and tilt
	INT16U Tac_P_max = atan(Width/Height)*57.3*3*2;
	INT16U Tac_T_max = atan(Depth/Height)*57.3*3*2;


	INT16U Pos_P_surface = Input_P*Width/100;
	INT16U Pos_T_surface = Input_T*Width/100;

	INT16U Pos_P_tac = atan(Pos_P_surface/Height)*57.3*3;
	INT16U Pos_T_tac = atan(Pos_T_surface/Height)*57.3*3;


	 */

	//input = 5000
	//5000 * 7 / 10000  =3,5
	
	
	//atan(3,5/5)*57,3*3
	
	
	
	
	
	
	return 0;
	
}

/****************************** End Of Module *******************************/














