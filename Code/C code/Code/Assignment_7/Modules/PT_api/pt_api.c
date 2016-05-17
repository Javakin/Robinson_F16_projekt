/*****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: pt_api.c
*
* PROJECT....: semester project 4
*
* DESCRIPTION: supports an interface betwean the pan & tilt driver and the application
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
#include "PT_api/pt_api.h"
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

INT8U pt_send_message( INT8U adress, INT8U PT, INT16U message)
{
	// 2 adress bit 1 p/t bit and 11 message bits
	// 0 0 a a pt d d d d d  d d d d d d
	INT16U placeholder = message & 0x07FF;
	placeholder |= (PT & 0x0001 << 11);
	placeholder |= ( adress << 12 );

	// send the message via spi_master
	return xQueueSend(spi_tx_queue, &( placeholder ), portMAX_DELAY);
}

INT8U pt_get_adress(INT16U message)
{
	return message >> 12;
}

INT16U pt_get_data(INT16U message)
{
	return message & 0x07FF;
}

INT16U pt_get_pt(INT16U message)
{
	return message & 0x0800;
}

INT8U pt_recieve_message()
{

	INT16U pt_message;
	INT8U status = pdTRUE;

	// wait for the recieved message
	if (xQueueReceive(spi_rx_queue, &( pt_message ), portMAX_DELAY) == pdTRUE)
	{
	// deal with the recieved message
		switch(pt_get_adress(pt_message))
		{
		case ADR_TARGET_POS:
			switch(pt_get_pt(pt_message))
			{
			case SUB_ADR_PAN:
				put_msg_state(SSM_CURRENT_PAN, pt_get_data(pt_message));
				break;

			case SUB_ADR_TILT:
				put_msg_state(SSM_CURRENT_TILT, pt_get_data(pt_message));
				break;
			}
			break;
		}
	}
	return status;
}



/****************************** End Of Module *******************************/














