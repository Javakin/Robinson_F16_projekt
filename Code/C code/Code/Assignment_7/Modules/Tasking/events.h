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

// pure events
#define CON_CHEK_EVENT		0
#define GOTO_COORD_EVENT	2
#define RUN_SHOW_EVENT		3
#define STOP_SHOW_EVENT		4
#define EN_FPGA_EVENT		5

// read value events
#define SET_HEIGHT_EVENT		10
#define SET_WIDTH_EVENT			11
#define SET_DEPTH_EVENT			12
#define SET_SCENE_EVENT			13

#define SET_MAX_VEL_PAN_EVENT	20
#define SET_MIN_VEL_PAN_EVENT	21
#define SET_MAX_VEL_TILT_EVENT	22
#define SET_MIN_VEL_TILT_EVENT	23

#define UPDATE_POS_EVENT		30



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
