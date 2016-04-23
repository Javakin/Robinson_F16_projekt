/*****************************************************************************
* University of Southern Denmark
* Embedded C Programming (ECP)
*
* MODULENAME.: PS2Controller.h
*
* PROJECT....: semester project
*
* DESCRIPTION: suppots the playstation 2 controller
*
* Change Log:
******************************************************************************
* Date    Id    Change
* YYMMDD
* --------------------
* 050128  KA    Module created
*
*****************************************************************************/

#ifndef PS2CONTROLLER_H_
#define PS2CONTROLLER_H_

/***************************** Include files *******************************/
#include "Modules/EMP/emp_type.h"

/*****************************    Defines    *******************************/

#define CON_RX			6	// brown wire
#define CON_TX			1	// orange wire
#define CON_ATENTION    3   // yellow wire
#define CON_CLOCK    	7   // blue wire
#define CON_ACK    		5   // green wire


/*****************************   Constants   *******************************/


/*****************************   Functions   *******************************/


void ps2controller_task();
//  Input    : -
//  Output   : -
//  Function : read the input from a playstation 2 controller


void ps2controller_init();
//  Input    : -
//  Output   : -
//  Function : initialuse the gpio's and setup the controller

void send_data();
//  Input    : -
//  Output   : -
//  Function : debugging tool to send data via uart0_tx

void send_byte();
//  Input    : -
//  Output   : -
//  Function : debugging tool to send data via uart0_tx

/****************************** End Of Module *******************************/
#endif












