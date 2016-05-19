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
* 170516  DFH    Module created
*
*****************************************************************************/

#ifndef SPIMASTER_H_
#define SPIMASTER_H_

/***************************** Include files *******************************/
#include "Modules/EMP/emp_type.h"

/*****************************    Defines    *******************************/

#define CON_RX			5	//MISO 	, L15
#define CON_TX			0	//MOSI 	, K12
#define CON_ATENTION  	1	//SS	, L17
#define CON_CLOCK   	4	//CLK	, M15


// bits send
#define NUM_OF_BITS				14

/*****************************   Constants   *******************************/


/*****************************   Functions   *******************************/


void spi_master_task();
//  Input    : -
//  Output   : -
//  Function : spi super task


void spi_master_init();
//  Input    : -
//  Output   : -
//  Function : initialize spi


INT16U spi_send_message(INT16U message);
//  Input    : message to send
//  Output   : the recieved message
//  Function : send the current message


/****************************** End Of Module *******************************/
#endif












