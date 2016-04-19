/*****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: ps2controller.c
*
* PROJECT....: semester project 4
*
* DESCRIPTION: See module specification file (.h-file).
*
* Change Log:
******************************************************************************
* Date    Id    Change
* YYMMDD
* --------------------
* 090222  MoH   Module created.
*
*****************************************************************************/

/***************************** Include files *******************************/
#include <stdint.h>
#include <tm4c123gh6pm.h>
#include "Modules/EMP/emp_type.h"
#include "Modules/UART0/uart0_tx.h"
#include "Modules/PS2Controller/ps2controller.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

/*****************************    Defines    *******************************/

/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/

// Queues
extern xQueueHandle uart0_tx_queue;

// Semaphores
// reserves uart0_tx_queue, in order to avoid interruptions
extern xSemaphoreHandle uart0_tx_semaphore;


INT8U message[7] = {'a', 'b', '1', 'd', 'e', 'f', '\n'};
INT8U i = 0;

/*****************************   Functions   *******************************/
void ps2controller_task()
{
	// initialise used prots
	ps2controller_init();

	// run task
	while(1)
	{
		// send char to uart0
		xSemaphoreTake( uart0_tx_semaphore, 10 );
			// critical section
			for (i = 0; i<7; i++)
				uart0_putc_tx( message[i] );

		xSemaphoreGive( uart0_tx_semaphore );

	}
}

void ps2controller_init()
{
	// todo: make controller

}



/****************************** End Of Module *******************************/
