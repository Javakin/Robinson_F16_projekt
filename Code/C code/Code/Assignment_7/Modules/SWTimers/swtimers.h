/*****************************************************************************
* University of Southern Denmark
* Embedded C Programming (ECP)
*
* MODULENAME.: swtimers.h
*
* PROJECT....: Assignment 4
*
* DESCRIPTION: Supporting software-timers
*
* Change Log:
******************************************************************************
* Date    Id    Change
* YYMMDD
* --------------------
* 050128  KA    Module created
* 040316  DFH   Module updated
*
*****************************************************************************/

#ifndef _SWTIMERS_H
  #define _SWTIMERS_H

/***************************** Include files *******************************/

/*****************************    Defines    *******************************/
#define TICK_TIME	5		// tick time in milli seconds.

#define MILLISEC(time_in_msec)  time_in_msec / TICK_TIME


/*****************************   Constants   *******************************/

/*****************************   Functions   *******************************/
INT16U swtimer( INT8U );
//   Input    : the Specific timer number
//   Output   : Timer value
//   Function : Returns the timer value

void start_swtimer( INT8U no, INT8U event_buffer, INT16U time );
//   Input    : timer number
//   Input    : Eventbuffer that needs to change when time-out
//   Input    : time/10mSec
//   Output   : -
//   Function : Starts a timer

void swt_ctrl(void);
//   Input    : -
//   Output   : -
//   Function : Update current timers

void swtimers_init(void);
//   Input    : -
//   Output   : -
//   Function : Initiate all timers to zero

/****************************** End Of Module *******************************/
#endif

