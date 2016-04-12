/*****************************************************************************
* University of Southern Denmark
* Embedded C Programming (ECP)
*
* MODULENAME.: tmodel.h
*
* PROJECT....: ECP
*
* DESCRIPTION: Defines the elemtn of the task model..
*
* Change Log:
******************************************************************************
* Date    Id    Change
* YYMMDD
* --------------------
* 101004  MoH   Module created.
*
*****************************************************************************/

#ifndef _TMODEL_H_
#define _TMODEL_H_

#include "RTCS/rtcs.h"

// Tasks.
// ------
#define TASK_ADC				10
#define TASK_SW_TIMERS 			11
#define TASK_MAIN 				12
#define TASK_BUTTON 			13
#define TASK_DREH		 		14
#define TASK_DISPLAY			15
#define TASK_LCD 				16
#define TASK_RTC				17
#define TASK_UART0				18
#define TASK_UI					19
#define TASK_NUMPAD				20

// Interrupt Service Routines.
// ---------------------------
#define ISR_TIMER 21

// Shared State Memory.
// --------------------
#define SSM_RTC_SEC				31
#define SSM_RTC_MIN				32
#define SSM_RTC_HOUR			33

// Shared Event Buffer.
// --------------------
#define SEB_UART_RX				40
#define SEB_PRINT				41

// Semaphores.
// -----------
#define SEM_LCD          		USER_SEM
#define SEM_RTC_UPDATED  		USER_SEM+1
#define SEM_TIME_ACCESS			USER_SEM+2

// Display to LCD task Shared Event Buffer
// ---------------------------------------
#define SEB_CMD_LCD			50 //
#define SEB_DATA_LCD		51
#define SEB_TO_LCD			52
#define SEB_DIGIT_UPDATE	53

// RTC Event Buffer
// ----------------
#define SEB_TO_RTC			54


#define Q_INPUT				USER_QUEUE
#define Q_LCD				USER_QUEUE+1

#endif /* _TMODEL_H_ */
