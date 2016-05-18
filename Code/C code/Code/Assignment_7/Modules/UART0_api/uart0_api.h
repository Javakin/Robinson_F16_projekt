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

#define CHAR_a   'a'
#define CHAR_b   'b'
#define CHAR_c   'c'
#define CHAR_d   'd'
#define CHAR_e   'e'
#define CHAR_f   'f'
#define CHAR_g   'g'
#define CHAR_h   'h'
#define CHAR_i   'i'



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

/****************************** End Of Module *******************************/
#endif












