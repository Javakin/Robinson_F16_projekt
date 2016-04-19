/*****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: Queue.c
*
* PROJECT....: Assingment 4
*
* DESCRIPTION: Module for implementing queues
*
* Change Log:
******************************************************************************
* Date    Id    Change
* YYMMDD
* --------------------
* 160304  JA   Module created
*
*****************************************************************************/

#ifndef ASSIGNMENT_5_MODULES_QUEUE_QUEUE_H_
#define ASSIGNMENT_5_MODULES_QUEUE_QUEUE_H_

/***************************** Include files *******************************/
#include <EMP/emp_type.h>
#include <EMP/glob_def.h>
#include <RTCS/rtcs.h>

/*****************************    Defines    *******************************/
//#define QUEUE_SIZE 64
#define QUEUE_TYPE INT8U

/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/

struct Queue {
	QUEUE_TYPE data[QUEUE_SIZE];
	QUEUE_TYPE start;
	QUEUE_TYPE length;
	BOOLEAN mutex;
};

/*****************************   Functions   *******************************/

void queue_init(struct Queue *q);

BOOLEAN queue_put(struct Queue *q, QUEUE_TYPE value);
 //   Input    : A pointer to the queue to work on and the value to put into the queue
 //   Output   : A bool which represents if the operation was succesful. False means the queue is full
 //   Function : This function puts the value into the queue. Returns false if queue is full

QUEUE_TYPE queue_get(struct Queue *q);
 //   Input    : A pointer to the queue to work on
 //   Output   : The first value in the queue
 //   Function : Returns the first value in the queue and removes it

QUEUE_TYPE queue_peak(struct Queue *q, QUEUE_TYPE index);
 //   Input    : A pointer to the queue to work on and the index to peak
 //   Output   : The value of the peaked index
 //   Function : Peaks a value at the supplied index. It is indexed from the start value. Does not remove value from queue.

void queue_lock(struct Queue *q);
 //   Input    : A pointer to the queue to work on
 //   Output   :
 //   Function : Locks the queues mutex

void queue_unlock(struct Queue *q);
 //   Input    : A pointer to the queue to work on
 //   Output   :
 //   Function : Unlocks the queues mutex

/****************************** End Of Module *******************************/

#endif /* ASSIGNMENT_5_MODULES_QUEUE_QUEUE_H_ */
