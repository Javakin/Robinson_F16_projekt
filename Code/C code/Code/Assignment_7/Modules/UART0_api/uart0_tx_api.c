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
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"


/*****************************    Defines    *******************************/


/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/

extern xQueueHandle spi_tx_queue;
extern xQueueHandle spi_rx_queue;

/*****************************   Functions   *******************************/

INT8U pt_api_send_message( INT8U adress, INT8U PT, INT16U message)
{
	// 2 adress bit 1 p/t bit and 11 message bits
	// 0 0 a a pt d d d d d  d d d d d d
	INT16U placeholder = message & 0x07FF;
	placeholder |= (PT & 0x0001 << 11);
	placeholder |= ( adress << 12 );

	// send the message via spi_master
	return xQueueSend(spi_tx_queue, &( placeholder ), portMAX_DELAY);
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

void pt_api_recieve_message(INT16U message)
{
	// deal with the recieved message
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



/****************************** End Of Module *******************************/














