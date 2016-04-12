/*****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: Numpad.h
*
* PROJECT....: Assignment_5
*
* DESCRIPTION: 
*
* Change Log:
******************************************************************************
* Date    Id    Change
* YYMMDD
* --------------------
* 160311 JA    Module created.
*
*****************************************************************************/

#ifndef NUMPAD
	#define NUMPAD

/***************************** Include files *******************************/

/*****************************    Defines    *******************************/

#define NUMPAD_COLUMN_1 4
#define NUMPAD_COLUMN_2	3
#define NUMPAD_COLUMN_3	2

#define NUMPAD_ROW_1 3
#define NUMPAD_ROW_2 2
#define NUMPAD_ROW_3 1
#define NUMPAD_ROW_4 0

#define NUMPAD_ZERO	 4
#define NUMPAD_ONE 	 3
#define NUMPAD_TWO 	 7
#define NUMPAD_THREE 11
#define NUMPAD_FOUR  2
#define NUMPAD_FIVE  6
#define NUMPAD_SIX   10
#define NUMPAD_SEVEN 1
#define NUMPAD_EIGHT 5
#define NUMPAD_NINE  9
#define NUMPAD_HASH  8
#define NUMPAD_STAR  0


#define NUMPAD_DEBOUNCE_TIME 6 //About 30ms since the tick is 5ms

/********************** External declaration of Variables ******************/

/*****************************   Constants   *******************************/

/*************************  Function interfaces ****************************/

//Test Function
/*****************************************************************************
*   Input    : -
*   Output   : -
*   Function : Test function
******************************************************************************/

void numpad_init();
/*****************************************************************************
*   Input    : -
*   Output   : -
*   Function : Initializes the Numpad
******************************************************************************/

void numpad_task(void *pvParameters);

/****************************** End Of Module *******************************/

#endif
