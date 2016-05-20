/*****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: uart0_api.c
*
* PROJECT....: semester project 4
*
* DESCRIPTION: supports an interface to use the message_queues
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
#include "UART0_api/uart0_api.h"
#include "UART0/uart0_tx.h"
#include "Tasking/messages.h"
#include "Tasking/events.h"
#include "Tasking/tmodel.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"


/*****************************    Defines    *******************************/


/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/

extern xQueueHandle application_queue;
extern xQueueHandle uart0_tx_queue;



/*****************************   Functions   *******************************/

void uart0_api_receive_message(INT8U message)
{
	uart0_api_send_message(message);

	switch(message)
	{
	case '\n':
		/*no break*/
	case '/':
		// enter has been pressed
		uart0_api_put_queue(USER_VAL_EVENT);
		break;

	case 'g':
		// goto coordinat
		uart0_api_put_queue(GOTO_COORD_EVENT);
		break;

	case 'f':
		// enable FPGA event
		uart0_api_put_queue(EN_FPGA_EVENT);
		break;

	case 'l':
		// enable lightshow
		uart0_api_put_queue(RUN_SHOW_EVENT);
		break;

	case 'h':
		// set hight
		uart0_api_put_queue(SET_HEIGHT_EVENT);
		break;

	case 'w':
		// set width
		uart0_api_put_queue(SET_WIDTH_EVENT);
		break;

	case 'd':
		// set depth
		uart0_api_put_queue(SET_DEPTH_EVENT);
		break;

	case 'p':
		// set min velocity pan
		uart0_api_put_queue(SET_MIN_VEL_PAN_EVENT);
		break;

	case 'P':
		// set max velocity pan
		uart0_api_put_queue(SET_MAX_VEL_PAN_EVENT);
		break;

	case 't':
		// set min velocity tilt
		uart0_api_put_queue(SET_MIN_VEL_TILT_EVENT);
		break;

	case 'T':
		// set max velocity tilt
		uart0_api_put_queue(SET_MAX_VEL_TILT_EVENT);
		break;

	case 's':
		// set scene
		uart0_api_put_queue(SET_SCENE_EVENT);
		break;

	case 'c':
		// stop lightshow
		uart0_api_put_queue(STOP_SHOW_EVENT);
		break;


	default:
		// cheak for number input
		if ( (message >= '0') && (message <= '9') &&  get_msg_state(SSM_USER_VALUE) < 1000000)
		{
			// a number has been pressed
			INT32U number = get_msg_state(SSM_USER_VALUE);
			number *= 10;
			number += message - '0';

			// update SSM if no owerflow has occoerd
			put_msg_state(SSM_USER_VALUE, number);

		}

		break;
	}
}

void uart0_api_put_queue(INT8U event)
{
	// send the event
	xQueueSend(application_queue, &( event ), portMAX_DELAY);
}

void uart0_api_send_message(INT8U message)
{
	// send the entire message via the uart0_tx_queue
	uart0_putc_tx(message);
}
/****************************** End Of Module *******************************/














