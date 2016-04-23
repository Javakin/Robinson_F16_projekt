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
#include "Modules/UART0/uart0_tx.h"
#include "Modules/PS2Controller/ps2controller.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

/*****************************    Defines    *******************************/



/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/

// Queues
extern xQueueHandle uart0_tx_queue;
extern xQueueHandle ps2con_queue;
extern xQueueHandle default_queue;
// testing of recieving queues
xQueueHandle command_queue;


// Semaphores
// reserves uart0_tx_queue, in order to avoid interruptions
extern xSemaphoreHandle uart0_tx_semaphore;


INT8U message[7] = {'a', 'b', '1', 'd', 'e', 'f', '\n'};
INT8U test = 0;


// receive variable
INT8U receive;

// digital pulling sequence
INT8U poll_once[5] = {0x01, 0x42, 0x00, 0xFF, 0xFF};
INT8U current_state = 0;

/*****************************   Functions   *******************************/
void ps2controller_task()
{
	// initialise used prots
	ps2controller_init();

	// run task
	while(1)
	{
		// clear atention
		GPIO_PORTB_DATA_R &= !(1 << CON_ATENTION);
		vTaskDelay(1);

		// send message
		for(INT8U byte = 0; byte < 5; byte++)
		{
			// send current byte
			for(INT8U bit = 0; bit < 8; bit++)
			{
				// send the transmitted bit
				GPIO_PORTB_DATA_R &= !(1 << CON_TX);
				GPIO_PORTB_DATA_R |= ( (1 && (poll_once[byte] & (1 << bit) ) ) << CON_TX);

				// read the recieved bit
				receive = '0';
				test = GPIO_PORTB_DATA_R;
				if (test & (1 << CON_RX))
					receive = '1';
				uart0_putc_tx( receive );


				// clock signal
				GPIO_PORTB_DATA_R &= !(1 << CON_CLOCK);
				vTaskDelay(1);
				GPIO_PORTB_DATA_R |=  (1 << CON_CLOCK);
				vTaskDelay(1);
			}

			// wait for acknowledge (delay for 5 µsec)
			vTaskDelay(1);
		}

		// set atention
		GPIO_PORTB_DATA_R |= (1 << CON_ATENTION);
		uart0_putc_tx( '\n' );
		vTaskDelay(1);
	}
}

void ps2controller_init()
{
	// setup port B
	SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOB;

	// Do a dummy read to insert a few cycles after enabling the peripheral.
	__asm("nop");

	// Enable GPIO
	GPIO_PORTB_DEN_R |= (1 << CON_TX) | (1 << CON_RX) | (1 << CON_ATENTION) |
			(1 << CON_CLOCK) | (1 << CON_ACK);

	// set direction
	GPIO_PORTB_DIR_R |= (1 << CON_TX) | (1 << CON_ATENTION)	| (1 << CON_CLOCK);
	GPIO_PORTB_DIR_R &= !((1 << CON_RX) | (1 << CON_ACK));

	// set pull-up resistors
	GPIO_PORTB_PUR_R |= (CON_ACK) | (CON_ATENTION);

	// todo: run initialising sequence



}

void send_byte()
{
	// send the bit
}

void digital_setup()
{
	// todo: setup digital sequence
}

void send_data()
{
	xSemaphoreTake( uart0_tx_semaphore, 10 );
		// critical section
		for (INT8U i = 0; i < 7; i++ )
			uart0_putc_tx( message[i] );

	xSemaphoreGive( uart0_tx_semaphore );
}

/****************************** End Of Module *******************************/
