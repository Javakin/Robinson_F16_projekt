/*****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: drehimpulsgeber.h
*
* PROJECT....: assignment 6
*
* DESCRIPTION: driver for the drehimpulsgeber
*
* Change Log:
******************************************************************************
* Date    Id    Change
* YYMMDD
* --------------------
* 180316	DFH 	module created
*
*****************************************************************************/

#ifndef _DREHIMPULSGEBER_H
  #define _DREHIMPULSGEBER_H

/***************************** Include files *******************************/

/*****************************    Defines    *******************************/

/********************** External declaration of Variables ******************/

/*****************************   Constants   *******************************/

/*************************  Function interfaces ****************************/

void dreh_init(void);
//	Input    : -
//  Output   : -
//  Function : init the drehimpuslgeber

void dreh_isr();
//	Input    : -
//  Output   : -
//  Function : interrrupt rutine for interrupt prot A

void dreh_task(INT8U my_id, INT8U my_state, INT8U event, INT8U data);
//	Input    : -
//  Output   : -
//  Function : manages the task

/****************************** End Of Module *******************************/
#endif

