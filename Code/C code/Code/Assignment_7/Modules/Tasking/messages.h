/*****************************************************************************
* University of Southern Denmark
* Embedded C Programming (ECP)
*
* MODULENAME.: messages.h
*
* PROJECT....: Assignment 4
*
* DESCRIPTION: Support message passing
*
* Change Log:
******************************************************************************
* Date    Id    Change
* YYMMDD
* --------------------
* 050128  KA    Module created.
* 040316  DFH   Module updated
*
*****************************************************************************/

#ifndef _ECP_H
  #define _ECP_H

/***************************** Include files *******************************/
#include "Modules/EMP/emp_type.h"
/*****************************    Defines    *******************************/

/*****************************   Constants   *******************************/

/*****************************   Functions   *******************************/
INT8U get_msg_event( INT8U no );
//   Input    : Index for a specific message
//   Output   : Returns the message while erasing it from buffer
//   Function : get a message at a serden place

void put_msg_event( INT8U no, INT8U event );
//   Input    : Index for a specific message
//   Input    : Specify the event by a number
//   Output   : -
//   Function : Set a message event

INT32U get_msg_state( INT8U no );
//   Input    : Index for a specific state
//   Output   : Returns the state withute erasing
//   Function : Get a message state

void put_msg_state( INT8U no, INT32U state );
//   Input    : Index for putting a specific state
//   Input    : Specify the state by a number
//   Output   : -
//   Function : Sets a state

/****************************** End Of Module *******************************/
#endif

