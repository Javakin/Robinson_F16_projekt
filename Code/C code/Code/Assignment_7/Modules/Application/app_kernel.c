/*****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: app_kernel.c
*
* PROJECT....: semester project 4
*
* DESCRIPTION: Gets instructions from the user, and executes them
*
* Change Log:
******************************************************************************
* Date    Id    Change
* YYMMDD
* --------------------
* 150516  DFH    Module created
* 170516  RTH	 Instructions and states implemented
* 180516  DFH	 Rename project
* 190516  RTH	 FPGA packages implemented
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

enum kernel_states
{
	KER_ST_IDLE,
	KER_ST_1PAR1,
	KER_ST_2PAR1,
	KER_ST_2PAR2,
	KER_ST_EXECUTE
};

// Queues
extern xQueueHandle application_queue;
extern xQueueHandle app_lightshow_queue;
extern xQueueHandle spi_tx_queue;

INT8U kernel_state = KER_ST_IDLE;

// for debugging
INT8U ker_message;

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
			if (xQueueReceive(application_queue, &( ker_message ), portMAX_DELAY) == pdTRUE)
			{
				//shared state memory opcode saves here
				put_msg_state(SSM_OPCODE, ker_message);
				
				// decide witch state to moce to
				ker_idle_func(ker_message);
			}
			break;
		

		case KER_ST_1PAR1:
			//case is a 1 parameter instruction, pull from kernel queue to get parameter 1
			if (xQueueReceive(application_queue, &( ker_message ), portMAX_DELAY) == pdTRUE)
			{
				switch(ker_message)
				{
				case USER_VAL_EVENT:
					//shared state memory saves here
					put_msg_state(SSM_PARAM_1, get_msg_state(SSM_USER_VALUE));

					// reset memory
					put_msg_state(SSM_USER_VALUE, 0);

					//execute instruction
					kernel_state = KER_ST_EXECUTE;
					break;
				}
			}
			break;
		
		case KER_ST_2PAR1:
			//case is a 2 parameter instruction, pull from kernel queue to get parameter 1
			if (xQueueReceive(application_queue, &( ker_message ), portMAX_DELAY) == pdTRUE)
			{
				switch(ker_message)
				{
				case USER_VAL_EVENT:
					//shared state memory saves here
					put_msg_state(SSM_PARAM_1, get_msg_state(SSM_USER_VALUE));

					// reset memory
					put_msg_state(SSM_USER_VALUE, 0);

					//get parameter 2
					kernel_state = KER_ST_2PAR2;
					break;
				}
			}
			break;

		case KER_ST_2PAR2:
			//case is a 2 parameter instruction, pull from kernel queue to get parameter 2
			if (xQueueReceive(application_queue, &( ker_message ), portMAX_DELAY) == pdTRUE)
			{
				switch(ker_message)
				{
				case USER_VAL_EVENT:
					//shared state memory 2 saves here
					put_msg_state(SSM_PARAM_2, get_msg_state(SSM_USER_VALUE));

					// reset memory
					put_msg_state(SSM_USER_VALUE, 0);

					//execute instruction
					kernel_state = KER_ST_EXECUTE;

					break;
				}

			}
			break;
			
		case KER_ST_EXECUTE:
			// execute the operand
			ker_execute_func();
			break;
		}
	}
}

void ker_idle_func(INT8U opcode)
{
	switch(ker_message)
	{
	//////////////////////// all 2 parameter instructions   //////////////////////////////
	case GOTO_COORD_EVENT:
		//get parameter 1
		kernel_state = KER_ST_2PAR1;
		break;


	//////////////////////// all 1 parameter instructions   //////////////////////////////

	case SET_HEIGHT_EVENT:
		/*no break*/
	case SET_WIDTH_EVENT:
		/*no break*/
	case SET_DEPTH_EVENT:
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
	case STOP_SHOW_EVENT:
		//execute instruction
		kernel_state = KER_ST_EXECUTE;

	default:
		// you done goofed
		//while (1);
		__asm("nop");
		break;
	}
}

void ker_execute_func()
{
	switch(get_msg_state(SSM_OPCODE))
	{
	//////////////////////// all 2 parameter instructions   //////////////////////////////
	case GOTO_COORD_EVENT:
	
		//save pan coordinate to SSM
		put_msg_state( SSM_TARGET_PAN, get_msg_state(SSM_PARAM_1));

		//save tilt coordinate to SSM
		put_msg_state( SSM_TARGET_TILT, get_msg_state(SSM_PARAM_2));		
	
		//send pan coordinate
		pt_api_send_message(ADR_TARGET_POS, SUB_ADR_PAN, get_msg_state(SSM_TARGET_PAN));

		//send tilt coordinate
		pt_api_send_message(ADR_TARGET_POS, SUB_ADR_TILT, get_msg_state(SSM_TARGET_TILT));

		kernel_state = KER_ST_IDLE;
		break;

	//////////////////////// all 1 parameter instructions   //////////////////////////////
	case EN_FPGA_EVENT:
		//enables or disables FPGA
		put_msg_state(SSM_FPGA_ENABLE, get_msg_state(SSM_PARAM_1));

		//send package to FPGA with enable value, currently does same action on both motors
		pt_api_send_message(ADR_EN_MOTOR, SUB_ADR_TILT, get_msg_state(SSM_FPGA_ENABLE));
		pt_api_send_message(ADR_EN_MOTOR, SUB_ADR_PAN, get_msg_state(SSM_FPGA_ENABLE));
		
		kernel_state = KER_ST_IDLE;
		break;


	case RUN_SHOW_EVENT:
		//send lightshow value to SSM
		put_msg_state(SSM_LIGHTSHOW, get_msg_state(SSM_PARAM_1));

		//Pass lightshow event
		ker_message = RUN_SHOW_EVENT;
		if (xQueueSend(app_lightshow_queue, &(ker_message), portMAX_DELAY) == pdTRUE)
		{
			kernel_state = KER_ST_IDLE;
		}
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

	case SET_DEPTH_EVENT:
		//set length constraint in SSM
		put_msg_state(SSM_DEPTH, get_msg_state(SSM_PARAM_1));
		
		kernel_state = KER_ST_IDLE;
		break;

	case SET_MAX_VEL_PAN_EVENT:
		//set max speed for pan in SSM
		put_msg_state(SSM_MAX_PAN_VEL, get_msg_state(SSM_PARAM_1));

		//send FPGA package, 3 unused bits
		pt_api_send_message(ADR_MAX_SPEED, SUB_ADR_PAN, get_msg_state(SSM_MAX_PAN_VEL));

		kernel_state = KER_ST_IDLE;
		break;

	case SET_MIN_VEL_PAN_EVENT:
		//set min speed for pan in SSM
		put_msg_state(SSM_MIN_PAN_VEL, get_msg_state(SSM_PARAM_1));

		//send FPGA package, 3 unused bits
		pt_api_send_message(ADR_MIN_SPEED, SUB_ADR_PAN, get_msg_state(SSM_MIN_PAN_VEL));
		
		kernel_state = KER_ST_IDLE;
		break;

	case SET_MAX_VEL_TILT_EVENT:
		//set max speed for tilt in SSM
		put_msg_state(SSM_MAX_TILT_VEL, get_msg_state(SSM_PARAM_1));

		//send FPGA package, 3 unused bits
		pt_api_send_message(ADR_MAX_SPEED, SUB_ADR_TILT, get_msg_state(SSM_MAX_TILT_VEL));
		
		kernel_state = KER_ST_IDLE;
		break;

	case SET_MIN_VEL_TILT_EVENT:
		//set min speed for tilt in SSM
		put_msg_state(SSM_MIN_TILT_VEL, get_msg_state(SSM_PARAM_1));

		//send FPGA package, 3 unused bits
		pt_api_send_message(ADR_MIN_SPEED, SUB_ADR_TILT, get_msg_state(SSM_MIN_TILT_VEL));
		
		kernel_state = KER_ST_IDLE;
		break;

	case SET_SCENE_EVENT:
		//updates scene constraints to predefined scene or default (5,5,5)

		switch(get_msg_state(SSM_PARAM_1))
		{
			case SCENE1:
				put_msg_state(SSM_HEIGHT, 5);
				put_msg_state(SSM_WIDTH, 7);
				put_msg_state(SSM_DEPTH, 7);
				break;

			case SCENE2:
				put_msg_state(SSM_HEIGHT, 6);
				put_msg_state(SSM_WIDTH, 14);
				put_msg_state(SSM_DEPTH, 7);
				break;

			case SCENE3:
				put_msg_state(SSM_HEIGHT, 7);
				put_msg_state(SSM_WIDTH, 14);
				put_msg_state(SSM_DEPTH, 10);
				break;

			default:
				put_msg_state(SSM_HEIGHT, 5);
				put_msg_state(SSM_WIDTH, 5);
				put_msg_state(SSM_DEPTH, 5);
				break;
		}

		kernel_state = KER_ST_IDLE;
		break;


	//////////////////////// all 0 parameter instructions   //////////////////////////////
	case STOP_SHOW_EVENT:
		put_msg_state(SSM_LIGHT_ENABLE, 0);

		kernel_state = KER_ST_IDLE;
		break;

	default:
		// you done goofed
		// while (1);
		__asm("nop");
		break;
	}
}

void kernel_init()
{
	// setup kernel
	
	//set SSM constraints for default scene
	put_msg_state(SSM_HEIGHT, 5);
	put_msg_state(SSM_WIDTH, 5);
	put_msg_state(SSM_DEPTH, 5);
	
	//reset target position
	put_msg_state(SSM_TARGET_PAN, CENTER_PAN);	
	put_msg_state(SSM_TARGET_TILT, CENTER_TILT);	

	//reset speed parameters
	//FPGA initializes to the same values as here
	put_msg_state(SSM_MIN_PAN_VEL, 	30);
	put_msg_state(SSM_MAX_PAN_VEL, 	100);
	put_msg_state(SSM_MIN_TILT_VEL, 30);
	put_msg_state(SSM_MAX_TILT_VEL, 100);
	
	//save FPGA enable state
	//FPGA is enabled when the system is started
	put_msg_state(SSM_FPGA_ENABLE, 1);

}




/****************************** End Of Module *******************************/














