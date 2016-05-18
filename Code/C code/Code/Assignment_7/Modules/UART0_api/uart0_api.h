/*****************************************************************************
* University of Southern Denmark
* Embedded C Programming (ECP)
*
* MODULENAME.: uart0_rx_api.h
*
* PROJECT....: semester project
*
* DESCRIPTION: supports an interface for using the application_queue
*
* Change Log:
******************************************************************************
* Date    Id    Change
* YYMMDD
* --------------------
* 180516  DFH    Module created
*
*****************************************************************************/

#ifndef UART0_API_H_
#define UART0_API_H_

/***************************** Include files *******************************/
#include "Modules/EMP/emp_type.h"

/*****************************    Defines    *******************************/


/*****************************   Constants   *******************************/


/*****************************   Functions   *******************************/

void uart0_api_receive_message(INT16U message);
//  Input    : the message received from user
//  Output   : -
//  Function : hanles the input from user

void uart0_api_transmit(INT8U message);
//  Input    : the message to send to user
//  Output   : -
//  Function : hanles the output from user

void uart0_api_put_queue(INT8U event);
//  Input    : the event to send
//  Output   : -
//  Function : sends events to the application queue

/****************************** End Of Module *******************************/
#endif












