/*****************************************************************************
* University of Southern Denmark
* Embedded C Programming (ECP)
*
* MODULENAME.: spi_api.h
*
* PROJECT....: semester project
*
* DESCRIPTION: supports an interface for using the message_queues
*
* Change Log:
******************************************************************************
* Date    Id    Change
* YYMMDD
* --------------------
* 150516  DFH    Module created
*
*****************************************************************************/

#ifndef SPI_API_H_
#define SPI_API_H_

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


INT8U spi_api_send_message( INT8U adress, INT8U PT, INT16U message);
//  Input    : adress used for the message
//			   the message to send
//  Output   : -
//  Function : puts the formatted message in the spi_tx_queue

void spi_api_recieve_message(INT16U message);
//  Input    : the message to update the ssm
//  Output   : -
//  Function : retreves the messages from P&T and updates state memory

INT8U spi_api_get_adress(INT16U message);
//  Input    : the recieved message
//  Output   : the adress from the message
//  Function : retreves the messages adress

INT16U spi_api_get_data(INT16U message);
//  Input    : the recieved message
//  Output   : the data from the message
//  Function : retreves the messages data

INT16U spi_api_get_pt(INT16U message);
//  Input    : the recieved message
//  Output   : the p/t bit from the message
//  Function : retreves the messages p/t bit


/****************************** End Of Module *******************************/
#endif












