/*****************************************************************************
* University of Southern Denmark
* Embedded C Programming (ECP)
*
* MODULENAME.: messages.c
*
* PROJECT....: Assignment 4
*
* DESCRIPTION:  Support message passing.
*
* Change Log:
******************************************************************************
* Date    Id    Change
* YYMMDD
* --------------------
* 080219  MoH    Module created.
* 040316  DFH    Module updated
*
*****************************************************************************/

/***************************** Include files *******************************/
#include "Modules/EMP/emp_type.h"
#include "FreeRTOS.h"
#include "semphr.h"
/*****************************    Defines    *******************************/
#define MAX_MSG 64

/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/

INT8U   msg_event[MAX_MSG];
INT32U  msg_state[MAX_MSG];

extern xSemaphoreHandle ssm_semaphor;
/*****************************   Functions   *******************************/

INT8U get_msg_event( INT8U address )
{
	INT8U result = 0;

	if ( address < MAX_MSG )
	{
		if ( msg_event[address] )
		{

			result = msg_event[address];
			msg_event[address] = 0;
		}
	}
	return (result);
}

void put_msg_event( INT8U address, INT8U event )
{

	if ( address < MAX_MSG )
		msg_event[address] = event;
}

INT32U get_msg_state( INT8U address )
{
	INT32U result = 0;

	if ( address < MAX_MSG )
	{
		if( xSemaphoreTake( ssm_semaphore, portMAX_DELAY) == pdTRUE )
		{
		// critical section
		result = msg_state[address];

		xSemaphoreGive( ssm_semaphore );
		}
	}
	return (result);
}

INT8U put_msg_state( INT8U address, INT32U state )
{
	INT8U status = 0;

	if ( address < MAX_MSG )
		if( xSemaphoreTake( ssm_semaphore, portMAX_DELAY) == pdTRUE )
		{
		// critical section
		msg_state[address] = state;

		status = pdTRUE;
		xSemaphoreGive( ssm_semaphore );
		}
	return status;
}







