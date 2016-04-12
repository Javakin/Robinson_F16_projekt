/*****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: display.c
*
* PROJECT....: Assignment 4
*
* DESCRIPTION: Uses the services to perform the desired output
*
* Change Log:
******************************************************************************
* Date    Id    Change
* YYMMDD
* --------------------
* 090222  MoH   Module created.
* 040316  DFH   Module update
*
*
*****************************************************************************/

/***************************** Include files *******************************/
#include <stdint.h>
#include <tm4c123gh6pm.h>
#include "Modules/EMP/emp_type.h"
#include "Modules/LCD/lcd.h"
#include "Modules/Tasking/tmodel.h"
#include "Modules/Tasking/messages.h"
#include "Modules/SWTimers/swtimers.h"
#include "Modules/Tasking/events.h"
#include "Modules/Display/display.h"
#include <Queue/Queue.h>

/*****************************    Defines    *******************************/

/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/
extern struct Queue display_lcd_queue;

enum display_states
{
	INITIAL_STATE,
	ENTER_COMMAND,
	ENTER_TIME,
	SHOW_CLOCK,
	ERROR_CMD,
	ERROR_TIME
};

INT8U iterator = 0;

/*****************************   Functions   *******************************/

void display_task( INT8U my_id, INT8U my_state, INT8U my_event, INT8U data )
{
	INT8U event = get_msg_event(SEB_PRINT);

	switch (my_state)
	{
	case INITIAL_STATE:
		//command_msg();
		write_cmd(LCD_CMD_CLEAR_SCREEN);
		write_cmd(LCD_CMD_DISPLAY_ON);
		set_state( SHOW_CLOCK );  // default state

	case ENTER_COMMAND:

		if(event)
		{
			switch(event)
			{
				case '*':
					write_cmd(LCD_CMD_CLEAR_SCREEN);
					command_msg();
					break;

				case '#':
					set_state( ENTER_TIME );
					write_cmd(LCD_CMD_CLEAR_SCREEN);
					time_prompt();
					break;

				case '?':
					set_state( ERROR_CMD );
					write_cmd(LCD_CMD_CLEAR_SCREEN);
					error_msg();
					wait( 300 );
					break;

				case '¤':
					set_state( SHOW_CLOCK );
					write_cmd(LCD_CMD_CLEAR_SCREEN);
					write_cmd(LCD_CMD_DISPLAY_ON);
					show_clock();
					break;

				default:
					write_data(event);
					break;
			}
		}
		break;

	case SHOW_CLOCK:

		show_clock();
		wait_sem(SEM_RTC_UPDATED, 0);

		if(event == '*')
		{
			set_state( ENTER_COMMAND );
			write_cmd(LCD_CMD_CLEAR_SCREEN);
			command_msg();
		}

		break;

	case ENTER_TIME:

		if(event)
		{
			switch(event)
			{
				case '#':
					set_state( SHOW_CLOCK );
					write_cmd(LCD_CMD_CLEAR_SCREEN);
					write_cmd(LCD_CMD_DISPLAY_ON);
					iterator = 0;
					break;

				case '*':
					set_state( ENTER_COMMAND );
					write_cmd(LCD_CMD_CLEAR_SCREEN);
					command_msg();
					break;

				case '?':
					set_state( ERROR_TIME );
					write_cmd(LCD_CMD_CLEAR_SCREEN);
					error_msg();
					iterator = 0;
					wait( 300 );
					break;

				default:
					write_data(event);
					if(iterator == 1 || iterator == 3)
						write_cmd(LCD_CMD_CURSOR_SHIFT_R);
					iterator++;
					break;
			}

		}
		break;

	case ERROR_CMD:
		set_state( ENTER_COMMAND );
		write_cmd(LCD_CMD_CLEAR_SCREEN);
		command_msg();
		break;

	case ERROR_TIME:
		set_state( ENTER_TIME );
		write_cmd(LCD_CMD_CLEAR_SCREEN);
		time_prompt();
		break;


	default:
		// you dun goofed
		break;
	}
}

void error_msg()
{
	set_cursor(1,0);
	INT8U besked[13]= {'I','n','v','a','l','i','d',' ','i','n','p','u','t'};
	run_sequence(besked,13);

	set_cursor(2,1);
	INT8U besked2[12]= {'T','r','y',' ','a','g','a','i','n','.','.','.'};
	run_sequence(besked2,12);
}



void command_msg()
{
	set_cursor(0,0);
	INT8U besked[14]= {'E','n','t','e','r',' ','c','o','m','m','a','n','d',':'};
	run_sequence(besked,14);

	set_cursor(0,1);
	write_cmd(LCD_CMD_BLINK_ON);
}

void time_prompt()
{
	INT8U besked[13]= {'S','e','t',' ','t','h','e',' ','t','i','m','e',':'};
	set_cursor(0,0);

	run_sequence(besked,13);

	set_cursor(4,1);

	INT8U besked2[8]= {'h','h',':','m','m',':','s','s'};
	run_sequence(besked2,8);
	set_cursor(4,1);
	write_cmd(LCD_CMD_BLINK_ON);
}

void show_clock()
{
	// setup

	INT8U sec = get_msg_state(SSM_RTC_SEC);
	INT8U min = get_msg_state(SSM_RTC_MIN);
	INT8U hour = get_msg_state(SSM_RTC_HOUR);
	INT8U colon = ':';

	if( sec & 0x01)
		colon = ' ';

	set_cursor(4,0);

	write_data(hour / 10 + '0');
	write_data(hour % 10 + '0');

	write_data(colon);

	write_data(min / 10 + '0');
	write_data(min % 10 + '0');

	write_data(colon);

	write_data(sec / 10 + '0');
	write_data(sec % 10 + '0');
	set_cursor(4,0);

	wait_sem(SEM_RTC_UPDATED, 0);

}

void set_cursor(INT8U x, INT8U y)
{
	  INT8U pos;

	  pos = y*0x40 + x;
	  pos |= 0x80;

	  write_cmd(pos);
}

void write_data(INT8U data)
{
	put_queue(Q_LCD,DATA_MODE,0);
	put_queue(Q_LCD,data,0);
}

void write_cmd(INT8U cmd)
{
	put_queue(Q_LCD,CMD_MODE,0);
	put_queue(Q_LCD,cmd,0);
}

void run_sequence(INT8U array[], INT8U size)
{
	for(int i = 0; i < size; i++)
	{
		write_data(array[i]);
	}
}
/****************************** End Of Module *******************************/
