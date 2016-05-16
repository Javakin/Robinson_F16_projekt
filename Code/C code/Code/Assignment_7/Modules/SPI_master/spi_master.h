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

#define CON_RX			5
#define CON_TX			0
#define CON_ATENTION  	1
#define CON_CLOCK   	4


// bits send
#define NUM_OF_BITS				16

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


INT16U spi_send_message(INT16U message);
//  Input    : message to send
//  Output   : the recieved message
//  Function : send the current message


/****************************** End Of Module *******************************/
#endif












