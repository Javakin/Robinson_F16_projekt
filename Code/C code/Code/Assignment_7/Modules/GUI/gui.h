/*****************************************************************************
* University of Southern Denmark
* Embedded C Programming (ECP)
*
* MODULENAME.: gui.h
*
* PROJECT....: Assignment 7
*
* DESCRIPTION: Offers services for the display layer
*
* Change Log:
******************************************************************************
* Date    Id    Change
* YYMMDD
* --------------------
* 050128  KA    Module created
*
*****************************************************************************/

#ifndef GUI_H_
#define GUI_H_

/***************************** Include files *******************************/
#include "Modules/EMP/emp_type.h"
//#include <String.h>
/*****************************    Defines    *******************************/

#define WELCOME_MSG		0
#define COMMAND_PROMPT 	1
#define ERROR_MSG 		2
#define TIME_PROMPT		3
#define CURRENT_TIME	4
#define POT_PROMPT		5
#define POT_VALUE		6

// Indexes for image array
#define CURRENT_POS		32

#define NEXT_POS		35

/*****************************   Constants   *******************************/


/*****************************   Functions   *******************************/

void gui_task(void *pvParameters);

void set_image(INT8U image);

/****************************** End Of Module *******************************/
#endif /* GUI_H_ */
