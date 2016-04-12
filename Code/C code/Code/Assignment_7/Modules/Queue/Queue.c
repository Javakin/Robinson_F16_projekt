/*****************************************************************************
 * University of Southern Denmark
 * Embedded Programming (EMP)
 *
 * MODULENAME.: Queue.c
 *
 * PROJECT....: Assingment 4
 *
 * DESCRIPTION: See module specification file (.h-file).
 *
 * Change Log:
 ******************************************************************************
 * Date    Id    Change
 * YYMMDD
 * --------------------
 * 160304  JA   Module created
 *
 *****************************************************************************/

/***************************** Include files *******************************/
#include <stdint.h>
#include "Modules/EMP/emp_type.h"
#include "Queue.h"

/*****************************    Defines    *******************************/

/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/

/*****************************   Functions   *******************************/

void queue_init(struct Queue *q) {
	q->start = 0;
	q->mutex = 0;
	q->length = 0;
}

BOOLEAN queue_put(struct Queue *q, QUEUE_TYPE value) {

	BOOLEAN return_state = FALSE;

	if (q->length < QUEUE_SIZE - 1) {
		if ((q->start + q->length) >= QUEUE_SIZE) {
			q->data[(q->start + q->length) % QUEUE_SIZE] = value;
		} else {
			q->data[q->start + q->length] = value;
		}
		return_state = TRUE;
		q->length++;
	}

	return return_state;
}

QUEUE_TYPE queue_get(struct Queue *q) {

	QUEUE_TYPE value = 0;

	if (q->length > 0) {

		value = q->data[q->start];
		q->length--;

		if (q->start == QUEUE_SIZE - 1) {
			q->start = 0;
		} else {
			q->start++;
		}

	}

	return value;
}

QUEUE_TYPE queue_peak(struct Queue *q, QUEUE_TYPE index) {

	QUEUE_TYPE value = 0;

	if(index >= QUEUE_SIZE) index = index % QUEUE_SIZE;

	if(q->start + index >= QUEUE_SIZE) {
		value = q->data[(q->start + index) % QUEUE_SIZE];
	} else {
		value = q->data[q->start + index];
	}

	return value;
}

void queue_lock(struct Queue *q) {
	q->mutex = TRUE;
}

void queue_unlock(struct Queue *q) {
	q->mutex = FALSE;
}

/****************************** End Of Module *******************************/
