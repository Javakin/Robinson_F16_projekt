/*****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: kernel.c
*
* PROJECT....: semester project 4
*
* DESCRIPTION: Gets instructions from the console, and executes said instructions
*
* Change Log:
******************************************************************************
* Date    Id    Change
* YYMMDD
* --------------------
* 150516  DFH    Module created
* 170516  RTH	 Instructions and states implemented
*
*****************************************************************************/

/***************************** Include files *******************************/
#include <stdint.h>
#include <tm4c123gh6pm.h>
#include "Modules/EMP/emp_type.h"
#include "Tasking/events.h"
#include "UART0/uart0_tx.h"
#include "Kernel/kernel.h"
#include "Tasking/messages.h"
#include "Tasking/tmodel.h"
#include "PT_api/pt_api.h"
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
				put_msg_state(SSM_OPCODE, ker_message);
				
				switch(ker_message)
				{
				//////////////////////// all 2 parameter instructions   //////////////////////////////
				case GOTO_COORD_EVENT:
					//get parameter 1
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
				case SET_MAX_VEL_PAN_EVENT:
					/*no break*/
				case SET_MIN_VEL_PAN_EVENT:
					/*no break*/
				case SET_MAX_VEL_TILT_EVENT:
					/*no break*/
				case SET_MIN_VEL_TILT_EVENT:
					/*no break*/

				case SET_SCENE_EVENT:
					//get parameter 1
					kernel_state = KER_ST_1PAR1;
					break;

				//////////////////////// all 0 parameter instructions   //////////////////////////////
				case CON_CHEK_EVENT:
					/*no break*/
				case STOP_SHOW_EVENT:
					//execute instruction
					kernel_state = KER_ST_EXECUTE;
					
				default:
					// you done goofed
					while (1);
					break;
				}
			}
			break;
		

		case KER_ST_1PAR1:
			//case is a 1 parameter instruction, pull from kernel queue to get parameter 1
			if (xQueueReceive(kernel_queue, &( ker_message ), portMAX_DELAY) == pdTRUE)
			{
				//shared state memory 2 saves here
				put_msg_state(SSM_PARAM_1, ker_message);
				//execute instruction
				kernel_state = KER_ST_EXECUTE;
			}
			break;
		
		case KER_ST_2PAR1:
			//case is a 2 parameter instruction, pull from kernel queue to get parameter 1
			if (xQueueReceive(kernel_queue, &( ker_message ), portMAX_DELAY) == pdTRUE)
			{
				//shared state memory 2 saves here
				put_msg_state(SSM_PARAM_1, ker_message);
				//get parameter 2
				kernel_state = KER_ST_2PAR2;
			}
			break;

		case KER_ST_2PAR2:
			//case is a 2 parameter instruction, pull from kernel queue to get parameter 2
			if (xQueueReceive(kernel_queue, &( ker_message ), portMAX_DELAY) == pdTRUE)
			{
				//shared state memory 2 saves here
				put_msg_state(SSM_PARAM_2, ker_message);
				//execute instruction
				kernel_state = KER_ST_EXECUTE;
			}
			break;
			
		case KER_ST_EXECUTE:
				
				switch(get_msg_state(SSM_OPCODE))
				{
				//////////////////////// all 2 parameter instructions   //////////////////////////////
				case GOTO_COORD_EVENT:
					//send pan coordinate
					pt_send_message(ADR_TARGET_POS, SUB_ADR_PAN, get_msg_state(SSM_PARAM_1));
					//save pan coordinate to SSM
					put_msg_state( SSM_TARGET_PAN, get_msg_state(SSM_PARAM_1));

					//send tilt coordinate
					pt_send_message(ADR_TARGET_POS, SUB_ADR_TILT, get_msg_state(SSM_PARAM_2));
					//save tilt coordinate to SSM
					put_msg_state( SSM_TARGET_TILT, get_msg_state(SSM_PARAM_2));
					
					kernel_state = KER_ST_IDLE;
					break;

				//////////////////////// all 1 parameter instructions   //////////////////////////////
				case EN_FPGA_EVENT:
					//enables or disables FPGA
					put_msg_state(SSM_FPGA_ENABLE, get_msg_state(SSM_PARAM_1));
									
					kernel_state = KER_ST_IDLE;
					break;
				
				
				case EN_LIGHT_EVENT:
					//send lightshow value to SSM
					put_msg_state(SSM_LIGHTSHOW, get_msg_state(SSM_PARAM_1));

					//enable lightshow
					put_msg_state(SSM_LIGHT_ENABLE, 1);
					
					kernel_state = KER_ST_IDLE;
					break;

				case SET_HEIGHT_EVENT:
					//set height constraint in SSM
					put_msg_state(SSM_HEIGHT, get_msg_state(SSM_PARAM_1));

					kernel_state = KER_ST_IDLE;
					break;

				case SET_WIDTH_EVENT:
					//set width constraint in SSM
					put_msg_state(SSM_WIDTH, get_msg_state(SSM_PARAM_1));
									
					kernel_state = KER_ST_IDLE;
					break;

				case SET_LENGTH_EVENT:
					//set length constraint in SSM
					put_msg_state(SSM_LENGTH, get_msg_state(SSM_PARAM_1));
					kernel_state = KER_ST_IDLE;
					break;

				case SET_MAX_VEL_PAN_EVENT:
					//set max speed for pan in SSM
					put_msg_state(SSM_MAX_PAN_VEL, get_msg_state(SSM_PARAM_1));
					
					kernel_state = KER_ST_IDLE;
					break;
					
				case SET_MIN_VEL_PAN_EVENT:
					//set min speed for pan in SSM
					put_msg_state(SSM_MIN_PAN_VEL, get_msg_state(SSM_PARAM_1));
					
					kernel_state = KER_ST_IDLE;
					break;
					
				case SET_MAX_VEL_TILT_EVENT:
					//set max speed for tilt in SSM
					put_msg_state(SSM_MAX_TILT_VEL, get_msg_state(SSM_PARAM_1));
														
					kernel_state = KER_ST_IDLE;
					break;
					
				case SET_MIN_VEL_TILT_EVENT:
					//set min speed for tilt in SSM
					put_msg_state(SSM_MIN_TILT_VEL, get_msg_state(SSM_PARAM_1));
														
					kernel_state = KER_ST_IDLE;
					break;	
					
				case SET_SCENE_EVENT:
					//updates scene constraints to predefined scene or default (5,5,5)
					
					switch(get_msg_state(SSM_PARAM_1))
					{
						case SCENE1:
							put_msg_state(SSM_HEIGHT, 5);
							put_msg_state(SSM_WIDTH, 7);
							put_msg_state(SSM_LENGTH, 7);
							break;
							
						case SCENE2:
							put_msg_state(SSM_HEIGHT, 6);
							put_msg_state(SSM_WIDTH, 14);
							put_msg_state(SSM_LENGTH, 7);
							break;
							
						case SCENE3:
							put_msg_state(SSM_HEIGHT, 7);
							put_msg_state(SSM_WIDTH, 14);
							put_msg_state(SSM_LENGTH, 10);
							break;
							
						default:
							put_msg_state(SSM_HEIGHT, 5);
							put_msg_state(SSM_WIDTH, 5);
							put_msg_state(SSM_LENGTH, 5);
							break;
					}
					
					kernel_state = KER_ST_IDLE;
					break;
					

				//////////////////////// all 0 parameter instructions   //////////////////////////////
				case CON_CHEK_EVENT:
					//ping microcontroller for connection

					//ping FPGA for connection
					
					//TODO
					kernel_state = KER_ST_IDLE;
					break;
										
				case STOP_SHOW_EVENT:
					put_msg_state(SSM_LIGHT_ENABLE, 0);
				
					kernel_state = KER_ST_IDLE;
					break;
					
				default:
					// you done goofed
					while (1);
					break;
				}
		}
	}
}


void kernel_init()
{
	// setup kernel
	
	//set SSM constraints for default scene
	put_msg_state(SSM_HEIGHT, 5);
	put_msg_state(SSM_WIDTH, 5);
	put_msg_state(SSM_LENGTH, 5);
	
	//reset target position
	put_msg_state(SSM_LENGTH, 5);	
}




/****************************** End Of Module *******************************/














