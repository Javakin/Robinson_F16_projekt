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

// sub adresses
#define SUB_ADR_PAN		0
#define SUB_ADR_TILT	1

// adresses
#define ADR_TARGET_POS	0
#define ADR_MAX_SPEED	1
#define ADR_MIN_SPEED	2
#define ADR_EN_MOTOR	3

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












