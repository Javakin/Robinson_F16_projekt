/*****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: rtcs.h
*
* PROJECT....: EMP
*
* DESCRIPTION: Test.
*
* Change Log:
******************************************************************************
* Date    Id    Change
* YYMMDD
* --------------------
* 150303  MoH   Module created.
*
*****************************************************************************/

#ifndef _RTCS_H
  #define _RTCS_H

/***************************** Include files *******************************/

/*****************************    Defines    *******************************/
typedef unsigned char  			HANDLE;		// HANDLE: Task diagram element ID
typedef unsigned char           SEM;        //

#define MAX_TASKS	   16
#define MAX_QUEUES     16
#define MAX_SEMAPHORES 64		// The first 2xMAX_QUEUES are reserved for the queues.

#define USER_TASK      1
#define USER_QUEUE     0
#define USER_SEM       2*MAX_QUEUES

#define TASK_IDLE               0
#define TASK_READY              1
#define TASK_WAIT_FOR_TIMEOUT   2
#define TASK_WAIT_FOR_SEMAPHORE 4

#define QUEUE_SIZE   128

#define EVENT_NONE    0
#define EVENT_TIMEOUT 1
#define EVENT_SIGNAL  2

#define WAIT_FOREVER  0

#define SYS_TASK	 128

#define ERROR_TASK  0xFF		// Task error
/*****************************   Constants   *******************************/

/*****************************   Functions   *******************************/
extern void set_event( INT8U new_event );

extern void set_state( INT8U );
/*****************************************************************************
*   Input    : new_state
*   Output   : -
*   Function : Test function
******************************************************************************/
extern void wait( INT16U );
/*****************************************************************************
*   Input    : Timeout
*   Output   : -
*   Function : Test function
******************************************************************************/

extern BOOLEAN wait_sem( INT8U, INT16U );
/*****************************************************************************
*   Input    : Semaphore
*   		   Timeout
*   Output   : TRUE if READY
*   		   FALSE if WAITING
*   Function : Wait for semaphore
******************************************************************************/

extern void signal( INT8U );
/*****************************************************************************
*   Input    : Semaphore
*   Output   : -
*   Function : Test function
******************************************************************************/

INT8S open_queue( INT8U );
/*****************************************************************************
*   Input    : Queue name
*   		   Handle to queue
*   		   -1 if queue is not opend
*   Output   : TRUE if READY
*   		   FALSE if WAITING
*   Function : Open queue
******************************************************************************/

BOOLEAN put_queue( INT8U, INT8U, INT16U );
/*****************************************************************************
*   Input    : Semaphore
*   		   Timeout
*   Output   : TRUE if data produced
*   		   FALSE if waiting for space in queue
*   Function : produce data to queue
******************************************************************************/

BOOLEAN get_queue( INT8U, INT8U*, INT16U );
/*****************************************************************************
*   Input    : handle to queue
*   		   Pointer to databuffer
*   		   Timeout
*   Output   : TRUE if data consumen
*   		   FALSE if waiting for data
*   Function : consume data from queue
******************************************************************************/

extern HANDLE start_task( INT8U, void (*tf)(INT8U, INT8U, INT8U, INT8U) );
extern INT8U RTCS_init();
void schedule();

/****************************** End Of Module *******************************/
#endif

