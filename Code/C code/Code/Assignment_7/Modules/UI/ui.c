/*****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: ui.c
*
* PROJECT....: Assignment 4
*
* DESCRIPTION: Support UART comunicaiton
*
* Change Log:
*****************************************************************************
* Date    Id    Change
* YYMMDD
* --------------------
* 150228  MoH   Module created
* 040316  DFH   Module updated
*
*****************************************************************************/

/***************************** Include files *******************************/
#include <stdint.h>
#include "tm4c123gh6pm.h"
#include <EMP/emp_type.h>
#include <UART/uart0.h>
#include <Tasking/tmodel.h>
#include <Queue/Queue.h>
#include <Tasking/messages.h>
#include <Tasking/events.h>
#include <RTCS/rtcs.h>
#include "ui.h"
/*****************************    Defines    *******************************/

/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/

enum ui_states
{
	WAIT,
	DECODING,
	SET_TIME,
	UPDATE_TIME,
	INITIAL_STATE
};

INT8U cmd_array[3][16] = {
		{'1','2'},
		{'2','2'},
		{'1','1'}
};

INT8U input_iterator = 0;

INT8U current_input[16];

extern INT8U current_task;

/*****************************   Functions   *******************************/

void ui_task(INT8U my_id, INT8U my_state, INT8U my_event, INT8U my_data)
{
	INT8U received; //queue_get(&numpad_input_queue);
	if(get_queue(Q_INPUT,&received,0) || my_event)
	{
		//put_msg_event(SEB_PRINT, received);
		switch(my_state)
		{
//			case INITIAL_STATE:
//				set_state( WAIT );
//				wait( 100 );
//				break;

			case WAIT:
				if(received == '*')
				{
					set_state( DECODING );
					put_msg_event(SEB_PRINT, received);
				}
				break;

			case DECODING:
				if(input_iterator > 15)
				{
					reset_input();
					put_msg_event(SEB_PRINT, '?');
				}

				current_input[input_iterator++] = received;
				switch(received)
				{
					case '#':
						current_input[input_iterator - 1] = 0;
						INT8U cmd = find_command();
						switch(cmd)
						{
							case 0:
								reset_input();
								put_msg_event(SEB_PRINT, '#');
								set_state( SET_TIME );
								break;

							case 1:
								reset_input();
								put_msg_event(SEB_PRINT, '¤');
								set_state( WAIT );
								break;

							default:
								reset_input();
								put_msg_event(SEB_PRINT, '?');
						}
						break;

					case '*':
						reset_input();
						put_msg_event(SEB_PRINT, '*');
						break;

					default:
						put_msg_event(SEB_PRINT, received);
						break;
				}
				break;

			case SET_TIME:
				set_time(&received);
				break;

			case UPDATE_TIME:
				update_time();
				set_state( WAIT );
				reset_input();
				put_msg_event(SEB_PRINT, '#');
				set_event( EVENT_NONE );
				break;

			default:
				break;
		}
	}
}

void reset_input()
{
	input_iterator = 0;

	for(int i = 0; i < 16; i++)
	{
		current_input[i] = 0;
	}
}

INT8U find_command()
{
	INT8S result = -1;

	for(int i = 0; i < 3; i++)
	{
		for(int j = 0; j < 16; j++)
		{
			if(cmd_array[i][j] != current_input[j])
				break;

			if(j == 15)
				result = i;
		}

		if( result >= 0)
			break;
	}
	return( result );
}

void set_time(INT8U *character)

{
	if(*character == '*')
	{
		put_msg_event(SEB_PRINT, '*');
		reset_input();
		set_state( DECODING );
	}
	else
	{
		switch(input_iterator)
		{
			case 0:
				if(*character - '0' < 3 && *character - '0' >= 0)
				{
					put_msg_event(SEB_PRINT, *character);
					current_input[input_iterator++] = *character;
				}
				else
				{
					put_msg_event(SEB_PRINT, '?');
					reset_input();
				}
				break;

			case 1:
				if ( *character - '0' < 4 && *character - '0' >= 0 )
				{
					put_msg_event(SEB_PRINT, *character);
					current_input[input_iterator++] = *character;
				}
				else if ( *character - '0' < 10 && *character - '0' >= 0 && current_input[0] - '0' < 2 )
				{
					put_msg_event(SEB_PRINT, *character);
					current_input[input_iterator++] = *character;
				}
				else
				{
					put_msg_event(SEB_PRINT, '?');
					reset_input();
				}
				break;

			case 2:
				if ( *character - '0' < 6 && *character - '0' >= 0 )
				{
					put_msg_event(SEB_PRINT, *character);
					current_input[input_iterator++] = *character;
				}
				else
				{
					put_msg_event(SEB_PRINT, '?');
					reset_input();
				}
				break;

			case 3:
				if ( *character - '0' < 10 && *character - '0' >= 0 )
				{
					put_msg_event(SEB_PRINT, *character);
					current_input[input_iterator++] = *character;
				}
				else
				{
					put_msg_event(SEB_PRINT, '?');
					reset_input();
				}
				break;

			case 4:
				if ( *character - '0' < 6 && *character - '0' >= 0 )
				{
					put_msg_event(SEB_PRINT, *character);
					current_input[input_iterator++] = *character;
				}
				else
				{
					put_msg_event(SEB_PRINT, '?');
					reset_input();
				}
				break;

			case 5:
				if ( *character - '0' < 10 && *character - '0' >= 0 )
				{
					put_msg_event(SEB_PRINT, *character);
					current_input[input_iterator++] = *character;
				}
				else
				{
					put_msg_event(SEB_PRINT, '?');
					reset_input();
				}
				break;

			default:
				//wait_sem(SEM_TIME_ACCESS, 0);
				//set_state( UPDATE_TIME );
				if(*character == '#')
				{
					if(wait_sem(SEM_TIME_ACCESS, 0))
					{
						put_msg_event(SEB_PRINT, *character);
						update_time();
						set_state( WAIT );
						signal( SEM_TIME_ACCESS );
					}
					else
						set_state( UPDATE_TIME );
				}
				break;
		}
	}
}

void update_time()
{
	INT8U hour = (current_input[0] - '0') * 10  + (current_input[1] - '0');
	INT8U min = (current_input[2] - '0') * 10 + (current_input[3] - '0');
	INT8U sec = (current_input[4] - '0') * 10 + (current_input[5] - '0');

	put_msg_state(SSM_RTC_HOUR, hour);
	put_msg_state(SSM_RTC_MIN, min);
	put_msg_state(SSM_RTC_SEC, sec);

	//signal( SEM_TIME_ACCESS);
	signal( SEM_RTC_UPDATED);

	reset_input();
}
/****************************** End Of Module *******************************/


