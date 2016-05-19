/*****************************************************************************
* University of Southern Denmark
* Embedded C Programming (ECP)
*
* MODULENAME.: app_lightshow.h
*
* PROJECT....: semester project
*
* DESCRIPTION: mannage lightshow
*
* Change Log:
******************************************************************************
* Date    Id    Change
* YYMMDD
* --------------------
* 190516  DFH    Module created
*
*****************************************************************************/

#ifndef LIGHTSHOW_H_
#define LIGHTSHOW_H_

/***************************** Include files *******************************/
#include "Modules/EMP/emp_type.h"

/*****************************    Defines    *******************************/
#define MIN_DISTANCE	200


/*****************************   Constants   *******************************/


/*****************************   Functions   *******************************/


void lightshow_task();
//  Input    : -
//  Output   : -
//  Function : super task for the lightshow


void lightshow_init();
//  Input    : -
//  Output   : -
//  Function : initializes the lightshow



/****************************** End Of Module *******************************/
#endif












