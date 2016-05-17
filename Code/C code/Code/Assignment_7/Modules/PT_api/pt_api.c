/*****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: pt_api.c
*
* PROJECT....: semester project 4
*
* DESCRIPTION: supports an interface betwean the pan & tilt driver and the application
*
* Change Log:
******************************************************************************
* Date    Id    Change
* YYMMDD
* --------------------
* 150516  DFH    Module created
*
*****************************************************************************/

/***************************** Include files *******************************/
#include <stdint.h>
#include <tm4c123gh6pm.h>
#include "Modules/EMP/emp_type.h"
#include "Modules/UART0/uart0_tx.h"
#include "Modules/PT_api/pt_api.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"


/*****************************    Defines    *******************************/


/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/

extern xQueueHandle spi_tx_queue;

/*****************************   Functions   *******************************/

INT8U pt_send_message( INT8U adress, INT16U message)
{
	// 2 adress bit and 14 message bits
	// a a m m m m m m  m m m m m m m m

	INT16U placeholder = message & 0x3FFF;
	placeholder |= ( adress << 14 );

	return xQueueSend(spi_tx_queue, &( placeholder ), portMAX_DELAY);
}


INT16U pt_recieve_message()
{
	return 0;
}



/****************************** End Of Module *******************************/














