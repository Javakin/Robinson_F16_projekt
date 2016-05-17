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

#define CON_CHEK_EVENT		0
#define CAL_INIT_EVENT		1
#define CAL_ACK_EVENT		2
#define EN_LIGHT_EVENT		3
#define SET_HEIGHT_EVENT	4
#define SET_WIDTH_EVENT		5
#define SET_LENGTH_EVENT	6
#define SET_ACC_EVENT		7
#define SET_VEL_EVENT		8
#define SET_SCENE_EVENT		9
#define GOTO_COORD_EVENT	10
#define RUN_SHOW_EVENT		11
#define STOP_SHOW_EVENT		12



// General Events
// --------------
#define GE_NO_EVENT     	0


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