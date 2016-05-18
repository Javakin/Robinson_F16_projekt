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
#include "Tasking/tmodel.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"


/*****************************    Defines    *******************************/


/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/

extern xQueueHandle kernel_queue;
extern xQueueHandle uart0_tx_queue;

/*****************************   Functions   *******************************/

void uart0_api_receive_message(INT16U message)
{
	switch(message)
	{
	case 'g':
		// goto coordinat

		break;

	case 'f':
		// enable FPGA event
		break;

	case 'l':
		// enable lightshow

		break;

	case 'h':
		// set hight

		break;

	case 'w':
		// set width

		break;

	case 'd':
		// set depth

		break;

	case 'p':
		// set min velocity pan

		break;

	case 'P':
		// set max velocity pan

		break;

	case 't':
		// set min velocity tilt

		break;

	case 'T':
		// set max velocity tilt

		break;

	case 's':
		// set scene

		break;

	case 'c':
		// stop lightshow

		break;

	case 'o':
		// connection check

		break;


	default:
		// todo: cheak for number input
		break;
	}
}


/****************************** End Of Module *******************************/














