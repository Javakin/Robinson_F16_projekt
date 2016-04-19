/*****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: rtc.c
*
* PROJECT....: EMP
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
#include "Modules/RTC/rtc.h"
#include "Modules/EMP/emp_type.h"
#include "Modules/LCD/lcd.h"
#include "Modules/Tasking/tmodel.h"
#include "Modules/Tasking/messages.h"
#include "Modules/SWTimers/swtimers.h"
#include "Modules/Tasking/events.h"
#include "RTCS/rtcs.h"

/*****************************    Defines    *******************************/

/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/

INT8U direction = 1;

/*****************************   Functions   *******************************/


void RTC_task(INT8U my_id, INT8U my_state, INT8U event, INT8U data)
/*****************************************************************************
*   Input    : -
*   Output   : -
*   Function : Disable global interrupt
 ******************************************************************************/
{
	if(wait_sem(SEM_TIME_ACCESS, 0))
	{
		INT8U sec = get_msg_state(SSM_RTC_SEC);
		INT8U min = get_msg_state(SSM_RTC_MIN);
		INT8U hour = get_msg_state(SSM_RTC_HOUR);

		switch (my_state) {

		case 0:
			set_state(1);
			wait(100);
			signal( SEM_TIME_ACCESS);
			break;
		case 1:
			sec++;
			if (sec >= 60)
			{
				min++;
				if (min >= 60) {
					hour++;
					if (hour >= 24)
						hour = 0;
					min = 0;
				}
				sec = 0;
			}

			put_msg_state(SSM_RTC_SEC, sec);
			put_msg_state(SSM_RTC_MIN, min);
			put_msg_state(SSM_RTC_HOUR, hour);

			wait(200);
			signal( SEM_TIME_ACCESS);
			signal( SEM_RTC_UPDATED);
			break;
		}
	}
}

/****************************** End Of Module *******************************/
