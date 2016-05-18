/*****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: uart0_api.c
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
#include "UART0_api/uart0_api.h"
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

void uart0_api_receive_message(INT16U message)
{
	switch(message)
	{
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

	case 'o':
		// connection check
		uart0_api_put_queue(CON_CHEK_EVENT);
		break;


	default:
		// todo: cheak for number input
		break;
	}
}

void uart0_api_put_queue(INT8U event)
{
	// send the event
	xQueueSend(application_queue, &( event ), portMAX_DELAY);
}

/****************************** End Of Module *******************************/














