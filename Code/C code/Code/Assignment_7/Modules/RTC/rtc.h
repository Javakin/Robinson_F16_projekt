/*****************************************************************************
* University of Southern Denmark
* Embedded C Programming (ECP)
*
* MODULENAME.: rtc.h
*
* PROJECT....: ECP
*
* DESCRIPTION: Test.
*
* Change Log:
******************************************************************************
* Date    Id    Change
* YYMMDD
* --------------------
* 050128  KA    Module created.
*
*****************************************************************************/

#ifndef _RTC_H
  #define _RTC_H

/***************************** Include files *******************************/
#include "Modules/EMP/emp_type.h"
/*****************************    Defines    *******************************/

#define RS_AUTO 	1
#define RS_MAN 		2

// Time Defines
// ------------

#define HOURS_12				172800
#define HOURS_24				345600

#define CYCLE_TIME				HOURS_24

/*****************************   Constants   *******************************/

/*****************************   Functions   *******************************/

void RTC_init();

void RTC_task(INT8U my_id, INT8U my_state, INT8U event, INT8U data);


/****************************** End Of Module *******************************/
#endif /* RTC_H_ */
