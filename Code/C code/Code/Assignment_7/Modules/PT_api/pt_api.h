/*****************************************************************************
* University of Southern Denmark
* Embedded C Programming (ECP)
*
* MODULENAME.: pt_api.h
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
*
*****************************************************************************/

#ifndef PT_API_H_
#define PT_API_H_

/***************************** Include files *******************************/
#include "Modules/EMP/emp_type.h"

/*****************************    Defines    *******************************/


/*****************************   Constants   *******************************/


/*****************************   Functions   *******************************/


INT8U pt_send_message( INT8U adress, INT16U message);
//  Input    : adress used for the message
//			   the message to send
//  Output   : -
//  Function : puts the formatted message in the spi_tx_queue

INT16U pt_recieve_message();
//  Input    : -
//  Output   : the message from the spi_rx_queue
//  Function : retreves the messages from P&T and updates state memory


/****************************** End Of Module *******************************/
#endif












