/*****************************************************************************
* University of Southern Denmark
* Embedded C Programming (ECP)
*
* MODULENAME.: events.h
*
* PROJECT....: Assignent 4
*
* DESCRIPTION: Defining all the events used in Assignment 4
*
* Change Log:
******************************************************************************
* Date    Id    Change
* YYMMDD
* --------------------
* 090215  MoH   Module created
* 040316  DFH   Module updated
*
*****************************************************************************/

#ifndef EVENTS_H_
#define EVENTS_H_

/***************************** Include files *******************************/

/*****************************    Defines    *******************************/
// Events.
// -------

// General Events
// --------------
#define GE_NO_EVENT     	0

// Button Events
// -------------
#define BE_SINGLE_PUSH   	1
#define BE_DOUBLE_PUSH 	 	2
#define BE_LONG_PUSH     	3

// Timer Events
// ------------
#define TE_TIMEOUT      	10

// RTC Events
// ----------

#define RTC_TIME_EVENT		20

// Display Events
// --------------

#define DSP_DIGIT_UPDATE 	30

/*****************************   Constants   *******************************/

/*****************************   Functions   *******************************/

/****************************** End Of Module *******************************/
#endif /*EVENTS_H_*/
