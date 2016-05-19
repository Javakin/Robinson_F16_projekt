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
* 190516  RTH	 Corrected comments
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
//  Function : super task for the kernel, runs 5 states


void kernel_init();
//  Input    : -
//  Output   : -
//  Function : initializes the kernel

void ker_idle_func(INT8U opcode);
//  Input    : -
//  Output   : -
//  Function : function to find amount of parameters an instruction takes

void ker_execute_func();
//  Input    : -
//  Output   : -
//  Function : function to run instruction when all parameters are found


/****************************** End Of Module *******************************/
#endif












