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
#include "Tasking/events.h"
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
	KER_ST_IDLE,
	KER_ST_PAR1,
	KER_ST_PAR2

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
			// pull from kernel queue
			if (xQueueReceive(kernel_queue, &( ker_message ), portMAX_DELAY) == pdTRUE)
			{
				switch(ker_message)
				{
				//////////////////////// all 2 parameter instructions   //////////////////////////////
				case GOTO_COORD_EVENT:
					kernel_state = KER_ST_PAR2;
					break;


				//////////////////////// all 1 parameter instructions   //////////////////////////////
				case EN_LIGHT_EVENT:
					/*no break*/
				case SET_HEIGHT_EVENT:
					/*no break*/
				case SET_WIDTH_EVENT:
					/*no break*/
				case SET_LENGTH_EVENT:
					/*no break*/
				case SET_ACC_EVENT:
					/*no break*/
				case SET_VEL_EVENT:
					/*no break*/
				case SET_SCENE_EVENT:
					kernel_state = KER_ST_PAR1;
					break;

				//////////////////////// all 0 parameter instructions   //////////////////////////////
				case CON_CHEK_EVENT:

					break;

				case CAL_INIT_EVENT:

					break;

				case CAL_ACK_EVENT:

					break;

				case STOP_SHOW_EVENT:

					break;

				default:
					// yot done gooft
					while (1);
					break;
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














