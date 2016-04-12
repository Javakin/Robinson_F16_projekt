/*****************************************************************************
* University of Southern Denmark
* Embedded C Programming (ECP)
*
* MODULENAME.: display.h
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
* 050128  KA    Module created.
* 040316  DFH   Mudule update
*
*****************************************************************************/

#ifndef DISPLAY_H_
#define DISPLAY_H_

/***************************** Include files *******************************/
#include "Modules/EMP/emp_type.h"

/*****************************    Defines    *******************************/


// LCD Commands

#define LCD_CMD_CLEAR_SCREEN 		0x01
#define LCD_CMD_RETURN_HOME			0x02
#define LCD_CMD_DISPLAY_OFF			0x08
#define LCD_CMD_DISPLAY_ON			0x0C
#define LCD_CMD_BLINK_ON			0x0D
#define LCD_CMD_CURSOR_ON			0x0E
#define LCD_CMD_C_B_ON				0x0F
#define LCD_CMD_ENTRY_MODE_L		0x04
#define LCD_CMD_ENTRY_MODE_L_S		0x05
#define LCD_CMD_ENTRY_MODE_R		0x06
#define LCD_CMD_ENTRY_MODE_R_S		0x07
#define LCD_CMD_CURSOR_SHIFT_L 		0x10
#define LCD_CMD_CURSOR_SHIFT_R		0x14
#define LCD_CMD_DISPLAY_SHIFT_L		0x18
#define LCD_CMD_DISPLAY_SHIFT_R		0x1C

/*****************************   Constants   *******************************/


/*****************************   Functions   *******************************/

void display_task( INT8U my_id, INT8U my_state, INT8U event, INT8U data );
//   Input    : Task number
//   Output   : -
//   Function : Manage LCD commands to make the correct output

void command_msg();
//   Input    : -
//   Output   : -
//   Function : Display startup message on LCD screen

void time_prompt();

void error_msg();

void show_clock();
//   Input    : -
//   Output   : -
//   Function : display the time in the center of the LCD

void set_cursor(INT8U x, INT8U y);

void write_data(INT8U data);

void write_cmd(INT8U cmd);

void run_sequence(INT8U array[], INT8U size);

/****************************** End Of Module *******************************/
#endif /* DISPLAY_H_ */











