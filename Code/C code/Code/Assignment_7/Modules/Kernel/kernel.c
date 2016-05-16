/*****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: kernal.c
*
* PROJECT....: semester project 4
*
* DESCRIPTION: manage commands
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
#include "Modules/EMP/emp_type.h"
#include "Modules/UART0/uart0_tx.h"
#include "Modules/Kernel/kernel.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"


/*****************************    Defines    *******************************/


/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/

enum kernel_states
{
	KER_ST_IDLE
};

// Queues
extern xQueueHandle kernel_queue;
extern xQueueHandle spi_tx_queue;


INT8U kernel_state = KER_ST_IDLE;

// for debugging
INT16U ker_message = 0x1001;

/*****************************   Functions   *******************************/
void kernel_task()
{
	// initialise used prots
	kernel_init();

	// run task
	while(1)
	{
		switch (kernel_state)
		{
		case KER_ST_IDLE:
			// send message using spi_tx_queue directly
			for (INT8U i = 0; i < 10; i++){
				if (xQueueSend(spi_tx_queue, &( ker_message ), portMAX_DELAY) == pdTRUE)
				{
					// send suceeded
					__asm("nop");
				}
			}
			break;
		}
	}
}


void kernel_init()
{
	// setup kernel

}




/****************************** End Of Module *******************************/














