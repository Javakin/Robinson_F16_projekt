/*****************************************************************************
* University of Southern Denmark
* Embedded C Programming (ECP)
*
* MODULENAME.: spi_master.h
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

#ifndef SPIMASTER_H_
#define SPIMASTER_H_

/***************************** Include files *******************************/
#include "Modules/EMP/emp_type.h"

/*****************************    Defines    *******************************/

#define CON_RX			3	// brown wire
#define CON_TX			7	// orange wire
#define CON_ATENTION  	1   // yellow wire
#define CON_CLOCK   	4   // blue wire
#define CON_ACK    		2   // green wire

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


void spi_master_task();
//  Input    : -
//  Output   : -
//  Function : read the input from a playstation 2 controller


void spi_master_init();
//  Input    : -
//  Output   : -
//  Function : initialuse the gpio's and setup the controller

INT8U spi_send_message();
//  Input    : -
//  Output   : 1 if don sending bytes, 0 if not
//  Function : send the message

void spi_idle_func();
//  Input    : -
//  Output   : -
//  Function : fill the message buffer with new pull

INT8U spi_ack_wait();
//  Input    : -
//  Output   : the new message_state
//  Function : test if the ack has arrived afteer 5 ms

void spi_send_byte();
//  Input    : -
//  Output   : the new byte_state
//  Function : send the current_byte


/****************************** End Of Module *******************************/
#endif











