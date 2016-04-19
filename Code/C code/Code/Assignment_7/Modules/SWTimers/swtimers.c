/*****************************************************************************
* University of Southern Denmark
* Embedded C Programming (ECP)
*
* MODULENAME.: swtimers.c
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
* 080219  MoH    Module created.
* 040316  DFH    Module updated
*
*****************************************************************************/

/***************************** Include files *******************************/
#include "Modules/EMP/emp_type.h"
#include "Modules/Tasking/events.h"
#include "Modules/Tasking/messages.h"
/*****************************    Defines    *******************************/
#define MAX_SWTIMERS 8

typedef struct timer_descriptor
{
  INT16U timer_value;
  INT8U  event_buffer;
} timer_descriptor;
/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/

timer_descriptor POT[MAX_SWTIMERS];  // Pool of timers

/*****************************   Functions   *******************************/

INT16U swtimer( INT8U no )
{
  return( POT[no].timer_value );
}



void start_swtimer( INT8U no, INT8U event_buffer, INT16U time )
{
  if( no < MAX_SWTIMERS )
  {
    POT[no].timer_value  = time;
    POT[no].event_buffer = event_buffer;
  }
}


void swt_ctrl(void)
{
  INT8U i;

  for( i= 0; i<MAX_SWTIMERS; i++ )
  {
    if( POT[i].timer_value )
    {
	    POT[i].timer_value--;
	    if( !POT[i].timer_value )
	    {
		    put_msg_event( POT[i].event_buffer, TE_TIMEOUT );
	    }
    }
  }
}

void swtimers_init()
{
  INT8U i;

  for( i= 0; i<MAX_SWTIMERS; i++ )
  {
    POT[i].timer_value  = 0;
    POT[i].event_buffer = 0;
  }
}

/****************************** End Of Module *******************************/












