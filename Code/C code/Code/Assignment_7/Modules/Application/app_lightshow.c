/*****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: app_lightshow.c
*
* PROJECT....: semester project 4
*
* DESCRIPTION: manage lightshow
*
* Change Log:
******************************************************************************
* Date    Id    Change
* YYMMDD
* --------------------
* 190516  DFH    Module created
*
*
*****************************************************************************/

/***************************** Include files *******************************/
#include <stdint.h>
#include <tm4c123gh6pm.h>
#include "Modules/EMP/emp_type.h"
#include "Tasking/events.h"
#include "Tasking/messages.h"
#include "Tasking/tmodel.h"
#include "Application/app_lightshow.h"
#include "PT_api/pt_api.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"


/*****************************    Defines    *******************************/


/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/

enum lightshow_states
{
	LIG_ST_IDLE,
	LIG_ST_WAIT,
	LIG_ST_NEW_TARGET
};

// Queues

extern xQueueHandle app_lightshow_queue;

INT8U lightshow_state = LIG_ST_IDLE;

// for debugging
INT8U lig_message;

/*****************************   Functions   *******************************/
void lightshow_task()
{
	// initialise used ports
	lightshow_init();

	// run task
	while(1)
	{
		switch (lightshow_state)
		{
		case LIG_ST_IDLE:
			// pull from lightshow queue to get enable signal
			if (xQueueReceive(app_lightshow_queue, &( lig_message ) ,portMAX_DELAY) == pdTRUE)
			{
				// recieved message
				if(lig_message == RUN_SHOW_EVENT)
				{
					lightshow_state = LIG_ST_NEW_TARGET;
				}
			}
			break;

		case LIG_ST_NEW_TARGET:
			// send a new target

			break;
		}
	}
}

void lightshow_init()
{
	// run initialisation sequence

}

/****************************** End Of Module *******************************/














