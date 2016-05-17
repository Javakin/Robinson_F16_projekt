/*****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: spi_master.c
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
* 170516  DFH   Module created
*
*****************************************************************************/

/***************************** Include files *******************************/
#include <stdint.h>
#include <tm4c123gh6pm.h>
#include "Modules/EMP/emp_type.h"
#include "UART0/uart0_tx.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"


/*****************************    Defines    *******************************/

/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/

enum user_input
{
	UI_ST_IDLE
};

// Queues
extern xQueueHandle user_input_queue;

// debugging
extern xQueueHandle uart0_tx_queue;

// state_memory
INT8U ui_state = UI_ST_IDLE;

// messages
INT8U ui_receive = 0;

/*****************************   Functions   *******************************/
void user_input_task()
{
	// initialise used prots
	user_input_init();

	// run task
	while(1)
	{
		switch (ui_state)
		{
		case UI_ST_IDLE:
			// get new message to send
			if (xQueueReceive(user_input_queue, &( ui_receive ), portMAX_DELAY) == pdTRUE)
			{
				// do code
			}
			break;

		}
	}
}


void user_input_init()
{
	// setup task

}





/****************************** End Of Module *******************************/














