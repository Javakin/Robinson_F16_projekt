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
	KER_ST_1PAR1,
	KER_ST_2PAR1,
	KER_ST_2PAR2,
	KER_ST_EXECUTE

};

// Queues
extern xQueueHandle kernel_queue;
extern xQueueHandle spi_tx_queue;

INT8U shared_state_variable_1;  //opcode
INT8U shared_state_variable_2;	//parameter 1
INT8U shared_state_variable_3;	//parameter 2


INT8U kernel_state = KER_ST_IDLE;

// for debugging
INT16U ker_message = 0x1001;

/*****************************   Functions   *******************************/
void kernel_task()
{
	// initialise used ports
	kernel_init();

	// run task
	while(1)
	{
		switch (kernel_state)
		{
		case KER_ST_IDLE:
			// pull from kernel queue to get opcode
			if (xQueueReceive(kernel_queue, &( ker_message ), portMAX_DELAY) == pdTRUE)
			{
				//shared state memory 1 saves here
				shared_state_variable_1 = ker_message;
				
				switch(ker_message)
				{
				//////////////////////// all 2 parameter instructions   //////////////////////////////
				case GOTO_COORD_EVENT:
					kernel_state = KER_ST_2PAR1;
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
					kernel_state = KER_ST_1PAR1;
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
					// you done goofed
					while (1);
					break;
				}

			}
			break;
		
		//case is a 1 parameter instruction, pull from kernel to get parameter 1
		case KER_ST_1PAR1:
			if (xQueueReceive(kernel_queue, &( ker_message ), portMAX_DELAY) == pdTRUE)
			{
				//shared state memory 2 saves here
				shared_state_variable_2 = ker_message;
				//kernel_state = KER_ST_IDLE;
				//Run instruction
				
			}

			break;
		
		
		//case is a 2 parameter instruction, pull from kernel to get parameter 1
		case KER_ST_2PAR1:
			if (xQueueReceive(kernel_queue, &( ker_message ), portMAX_DELAY) == pdTRUE)
			{
				//shared state memory 2 saves here
				shared_state_variable_2 = ker_message;
				kernel_state = KER_ST_2PAR2;

				
			}
			break;
		}
		
		//case is a 2 parameter instruction, pull from kernel to get parameter 2
		case KER_ST_2PAR2:
			if (xQueueReceive(kernel_queue, &( ker_message ), portMAX_DELAY) == pdTRUE)
			{
				//shared state memory 2 saves here
				shared_state_variable_2 = ker_message;
				//kernel_state = KER_ST_PAR1;
				//set state to run instruction
			}
			break;
			
		case KER_ST_EXECUTE:
			
	}
}


void kernel_init()
{
	// setup kernel

}




/****************************** End Of Module *******************************/














