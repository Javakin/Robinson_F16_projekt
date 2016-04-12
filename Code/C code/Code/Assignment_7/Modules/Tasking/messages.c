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
/*****************************    Defines    *******************************/
#define MAX_MSG 64

/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/

INT8U   msg_event[MAX_MSG];
INT32U   msg_state[MAX_MSG];

/*****************************   Functions   *******************************/

INT8U get_msg_event( INT8U no )
{
	INT8U result = 0;

	if ( no < MAX_MSG )
	{
		if ( msg_event[no] )
		{
			result = msg_event[no];
			msg_event[no] = 0;
		}
	}
	return (result);
}

void put_msg_event( INT8U no, INT8U event )
{
	if ( no < MAX_MSG )
		msg_event[no] = event;
}

INT32U get_msg_state( INT8U no )
{
	INT32U result = 0;

	if ( no < MAX_MSG )
	{
		result = msg_state[no];
	}
	return (result);
}

void put_msg_state( INT8U no, INT32U state )
{
	if ( no < MAX_MSG )
		msg_state[no] = state;
}







