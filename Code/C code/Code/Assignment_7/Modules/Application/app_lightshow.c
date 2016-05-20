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
#define SHOW_POINT1		4
#define SHOW_POINT2		2
#define SHOW_POINT3		2


/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/

enum lightshow_states
{
	LIG_ST_IDLE,
	LIG_ST_WAIT_PAN,
	LIG_ST_WAIT_TILT,
	LIG_ST_NEW_TARGET
};

// Queues

extern xQueueHandle app_lightshow_queue;

INT8U lightshow_state = LIG_ST_IDLE;

// for debugging
INT8U lig_message;
INT8U n = 0;

INT16S	target_pos;
INT16S	current_pos;

//0 - 10 000
//INT16U show1[4][2] = { { 1000, 1000 }, { 1000, 9000}, { 9000, 9000}, { 9000, 1000}};
//
INT16U show1[SHOW_POINT1][2] = { { 400, 400 }, { 400, 680}, { 680, 680}, { 680, 400}};
INT16U show2[SHOW_POINT2][2] = { { 400, 400 }, { 680, 680}};
INT16U show3[SHOW_POINT3][2] = { { 400, 680 }, { 680, 400}};

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
			if (xQueueReceive(app_lightshow_queue, &( lig_message ), portMAX_DELAY) == pdTRUE)
			{
				// recieved message
				if(lig_message == RUN_SHOW_EVENT)
				{
					lightshow_state = LIG_ST_NEW_TARGET;
				}
			}
			break;

		case LIG_ST_NEW_TARGET:
			switch (get_msg_state(SSM_LIGHTSHOW))
			{
				case 1:
					// show 1
					if(	pt_api_set_coord(show1[n][0], show1[n][1]))
						lightshow_state = LIG_ST_WAIT_PAN;
					n = (n + 1) % SHOW_POINT1;
					break;

				case 2:
					// show 2
					if(pt_api_set_coord(show2[n][0], show2[n][1]))
						lightshow_state = LIG_ST_WAIT_PAN;
					n = (n + 1) % SHOW_POINT2;
					break;

				case 3:
					// show 3
					if(pt_api_set_coord(show3[n][0], show3[n][1]))
						lightshow_state = LIG_ST_WAIT_PAN;
					n = (n + 1) % SHOW_POINT3;
					break;
			}
			break;

		case LIG_ST_WAIT_PAN:
			if(xQueueReceive(app_lightshow_queue, &( lig_message ), 1) == pdTRUE)
			{
				// message recieved
				if (lig_message ==  STOP_SHOW_EVENT)
				{
					pt_api_set_coord(CENTER_PAN, CENTER_TILT);
					lightshow_state = LIG_ST_IDLE;
				}
			}
			else
			{
				// wait for system to reach system
				target_pos = get_msg_state(SSM_TARGET_PAN);
				current_pos = get_msg_state(SSM_CURRENT_PAN);

				if (((target_pos - current_pos) < MIN_DISTANCE) && ((target_pos - current_pos) > - MIN_DISTANCE))
				{
					lightshow_state = LIG_ST_WAIT_TILT;
				}
			}
			break;

		case LIG_ST_WAIT_TILT:
			if(xQueueReceive(app_lightshow_queue, &( lig_message ), 1) == pdTRUE)
			{
				// message recieved
				if (lig_message ==  STOP_SHOW_EVENT)
				{
					pt_api_set_coord(CENTER_PAN, CENTER_TILT);
					lightshow_state = LIG_ST_IDLE;
				}
			}
			else
			{
				// wait for system to reach system
				target_pos = get_msg_state(SSM_TARGET_TILT);
				current_pos = get_msg_state(SSM_CURRENT_TILT);

				if (((target_pos - current_pos) < MIN_DISTANCE) && ((target_pos - current_pos) > - MIN_DISTANCE))
				{
					lightshow_state = LIG_ST_NEW_TARGET;
				}
			}
			break;

		}
	}
}

void lightshow_init()
{
	// run initialisation sequence

}

/****************************** End Of Module *******************************/














