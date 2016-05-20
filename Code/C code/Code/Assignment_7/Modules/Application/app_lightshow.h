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
#define MIN_DISTANCE	20
#define CENTER_PAN		540
#define CENTER_TILT		540

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

void set_coord(INT16U pan, INT16U tilt);
//  Input    : -
//  Output   : -
//  Function : send the coordinat to the pt_api

/****************************** End Of Module *******************************/
#endif












