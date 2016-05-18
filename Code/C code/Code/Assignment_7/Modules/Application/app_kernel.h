/*****************************************************************************
* University of Southern Denmark
* Embedded C Programming (ECP)
*
* MODULENAME.: kernel.h
*
* PROJECT....: semester project
*
* DESCRIPTION: mannage commadns
*
* Change Log:
******************************************************************************
* Date    Id    Change
* YYMMDD
* --------------------
* 150516  DFH    Module created
*
*****************************************************************************/

#ifndef KERNEL_H_
#define KERNEL_H_

/***************************** Include files *******************************/
#include "Modules/EMP/emp_type.h"

/*****************************    Defines    *******************************/
//scene defines
#define SCENE1			1
#define SCENE2			2
#define SCENE3			3
/*****************************   Constants   *******************************/


/*****************************   Functions   *******************************/


void kernel_task();
//  Input    : -
//  Output   : -
//  Function : read the input from a playstation 2 controller


void kernel_init();
//  Input    : -
//  Output   : -
//  Function : initialuse the gpio's and setup the controller

void ker_idle_func(INT8U opcode);
//  Input    : -
//  Output   : -
//  Function : this function select states depending on the parameter

void ker_execute_func();
//  Input    : -
//  Output   : -
//  Function : this function is executed under the execute state


/****************************** End Of Module *******************************/
#endif











