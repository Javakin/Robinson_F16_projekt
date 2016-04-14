/*****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: ps2controller.c
*
* PROJECT....: semester project 4
*
* DESCRIPTION: See module specification file (.h-file).
*
* Change Log:
******************************************************************************
* Date    Id    Change
* YYMMDD
* --------------------
* 090222  MoH   Module created.
*
*****************************************************************************/

/***************************** Include files *******************************/
#include <stdint.h>
#include <tm4c123gh6pm.h>
#include "Modules/EMP/emp_type.h"
#include "Modules/UART/uart0.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

/*****************************    Defines    *******************************/

/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/

extern xQueueHandle uart0_rx_queue;


/*****************************   Functions   *******************************/
void ps2controller_task()
{
	while(1)
	{
		uart0_putc('c');
	}
}


/****************************** End Of Module *******************************/
