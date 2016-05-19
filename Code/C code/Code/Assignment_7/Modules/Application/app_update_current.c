/*****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: app_update_current.c
*
* PROJECT....: semester project 4
*
* DESCRIPTION: Updates current position by sending the same target package to the FPGA
*
* Change Log:
******************************************************************************
* Date    Id    Change
* YYMMDD
* --------------------
* 190516  RTH    Module created
*
*****************************************************************************/

/***************************** Include files *******************************/
#include <stdint.h>
#include <tm4c123gh6pm.h>
#include "Modules/EMP/emp_type.h"
#include "Tasking/events.h"
#include "UART0/uart0_tx.h"
#include "Application/app_kernel.h"
#include "Tasking/messages.h"
#include "Tasking/tmodel.h"
#include "PT_api/pt_api.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"


/*****************************    Defines    *******************************/


/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/

// Queues
extern xQueueHandle spi_tx_queue;

/*****************************   Functions   *******************************/
void update_task()
{
	// initialize
	update_current_init();

	// run task
	while(1)
	{
		//send target pan coordinate
		pt_api_send_message(ADR_TARGET_POS, SUB_ADR_PAN, get_msg_state(SSM_TARGET_PAN));

		//send target tilt coordinate
		pt_api_send_message(ADR_TARGET_POS, SUB_ADR_TILT, get_msg_state(SSM_TARGET_TILT));
		
		//delay task for 5 msec
		vTaskDelay(1);
	}		
}

void update_current_init()
{
	// setup
}




/****************************** End Of Module *******************************/














