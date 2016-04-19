/*****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: systick.h
*
* PROJECT....: EMP Assignment 3
*
* DESCRIPTION: Implements systick functionality
*
* Change Log:
******************************************************************************
* Date    Id    Change
* YYMMDD
* --------------------
* 160226  JA    Module created.
* 040316  DFH   Module updated
*
*****************************************************************************/

#ifndef SYS_TICK
	#define SYS_TICK

/***************************** Include files *******************************/
#include <stdint.h>
#include <tm4c123gh6pm.h>
#include "Modules/EMP/emp_type.h"

/*****************************    Defines    *******************************/
#define FCPU 16000000	//In hertz
#define TIMEOUT 5		//In ms
#define SYSTICK_RELOAD_VALUE ((TIMEOUT * FCPU)/1000)-1
#if (SYSTICK_RELOAD_VALUE > 0xFFFFFF)
	#error "Systick Reload Value Too High!"
#endif

#if (SYSTICK_RELOAD_VALUE <= 0)
	#error "Systick Reload Value Is Zero Or Below And Won't Have An Effect!"
#endif

// Missing definitions in tm4c123gh6pm.h file
#define NVIC_INT_CTRL_PEND_SYST   0x04000000  // Pend a systick int
#define NVIC_INT_CTRL_UNPEND_SYST 0x02000000  // Unpend a systick int

#define SYSTICK_PRIORITY    0x7E

/********************** External declaration of Variables ******************/
extern volatile INT16S ticks;
/*****************************   Constants   *******************************/

/*************************  Function interfaces ****************************/
void SysTick_Handler(void);
//   Input    : -
//   Output   : -
//   Function : Interrupt function for systick interrupt

void enable_global_int(void);
//   Input    : -
//   Output   : -
//   Function : Enables global interrupts

void disable_global_int(void);
//   Input    : -
//   Output   : -
//   Function : Disables global interrupts

void SysTick_init(void);
//   Input    : -
//   Output   : -
//   Function : Initialises the systick counter

/****************************** End Of Module *******************************/

#endif
