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
#define CON_ATENTION  	3   // yellow wire
#define CON_CLOCK   	7   // blue wire
#define CON_ACK    		5   // green wire

// super states
#define IDLE_STATE			0
#define SEND_MESSAGE_STATE	1
#define SET_ATEN_STATE		2
#define CLR_ATEN_STATE		3
#define SEND_BYTE_STATE		4
#define ACK_WAIT_STATE		5
#define ACK_RECEIVED_STATE	6

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

INT8U send_message();
//  Input    : -
//  Output   : 1 if don sending bytes, 0 if not
//  Function : send the message

void idle_func();
//  Input    : -
//  Output   : -
//  Function : fill the message buffer with new pull

void ps2_isr();
//  Input    : -
//  Output   : -
//  Function : set acknowledge when recieved

INT8U ack_wait();
//  Input    : -
//  Output   : the new message_state
//  Function : test if the ack has arrived afteer 5 ms

void send_byte();
//  Input    : -
//  Output   : the new byte_state
//  Function : send the current_byte


/****************************** End Of Module *******************************/
#endif












