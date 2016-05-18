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
	case CHAR_a:
		break;

	case CHAR_b:
		break;

	case CHAR_c:
		break;

	case CHAR_e:
		break;
	}
}


/****************************** End Of Module *******************************/














