/*****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: GPIO
*
* PROJECT....: Assignment_3
*
* DESCRIPTION: See module specification file (.h-file).
*
* Change Log:
*****************************************************************************
* Date    Id    Change
* YYMMDD
* --------------------
*  160226  JA    Module created.
*
*****************************************************************************/

/***************************** Include files *******************************/
#include <stdint.h>
#include <tm4c123gh6pm.h>
#include "Modules/EMP/emp_type.h"
#include "Modules/GPIO/GPIO.h"

/*****************************    Defines    *******************************/

/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/

/*****************************   Functions   *******************************/

 void GPIO_init()
/*****************************************************************************
*   Function : See module specification (.h-file).
*****************************************************************************/
 {
	   // Enable the GPIO port that is used for LCD-display data lines
	   SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOF | SYSCTL_RCGC2_GPIOC | SYSCTL_RCGC2_GPIOD;

	   // Do a dummy read to insert a few cycles after enabling the peripheral.
	   __asm("nop");

	   GPIO_PORTC_DIR_R = 0xF0;
	   GPIO_PORTD_DIR_R = 0x4C;
	   GPIO_PORTF_DIR_R = 0x0E;

	   GPIO_PORTC_DEN_R = 0xF0;
	   GPIO_PORTD_DEN_R = 0x4C;
	   GPIO_PORTF_DEN_R = 0x1E;

	   GPIO_PORTF_PUR_R = 0x10;


 }
/****************************** End Of Module *******************************/
