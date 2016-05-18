/*****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: spi_master.c
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
#include "EMP/emp_type.h"
#include "UART0/uart0_tx.h"
#include "SPI_master/spi_master.h"
#include "SPI_api/spi_api.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"


/*****************************    Defines    *******************************/

/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/

enum spi_master
{
	SPI_ST_IDLE,
	SPI_ST_SEND,
	SPI_ST_RECEIVE
};

// Queues
extern xQueueHandle spi_rx_queue;
extern xQueueHandle spi_tx_queue;

// debugging
extern xQueueHandle uart0_tx_queue;

// state_memory
INT8U spi_state = SPI_ST_IDLE;

// current bytes operated on
INT16U spi_rx = 0;
INT16U spi_tx = 0;

/*****************************   Functions   *******************************/
void spi_master_task()
{
	// initialise used prots
	spi_master_init();

	// run task
	while(1)
	{
		switch (spi_state)
		{
		case SPI_ST_IDLE:
			// get new message to send
			if (xQueueReceive(spi_tx_queue, &( spi_tx ), portMAX_DELAY) == pdTRUE)
			{
				spi_state = SPI_ST_SEND;
			}
			break;


		case SPI_ST_SEND:
			// send the byte
			spi_rx = spi_send_message(spi_tx);

			spi_state = SPI_ST_RECEIVE;
			break;

		case SPI_ST_RECEIVE:
			spi_api_recieve_message(spi_rx);
			break;

		}
	}
}


void spi_master_init()
{
	// setup port B
	SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOB;

	// Do a dummy read to insert a few cycles after enabling the peripheral.
	__asm("nop");

	// Enable GPIO
	GPIO_PORTB_DEN_R |= (1 << CON_TX) | (1 << CON_RX) | (1 << CON_ATENTION) |
			(1 << CON_CLOCK);

	// set direction
	GPIO_PORTB_DIR_R |= (1 << CON_TX) | (1 << CON_ATENTION)	| (1 << CON_CLOCK);
	GPIO_PORTB_DIR_R &= ~((1 << CON_RX) );

	// set pull-up resistors
	GPIO_PORTB_PUR_R |= (1 << CON_RX);

}


INT16U spi_send_message(INT16U message)
{
	// define signals
	INT8U temp_holder = 0;
	INT16U recieved = 0;

	// clear atention
	GPIO_PORTB_DATA_R &= ~(1 << CON_ATENTION);

	// send byte
	for(INT8U i = NUM_OF_BITS - 1; i >= 0 && i < NUM_OF_BITS ; i--)
	{

		// set bit to transmit
		temp_holder = (GPIO_PORTB_DATA_R & ~(1 << CON_TX));
		temp_holder |= ( (1 && (message & (1 << i) ) ) << CON_TX);
		GPIO_PORTB_DATA_R = temp_holder;

		// clock high
		temp_holder = (1 << CON_CLOCK);
		GPIO_PORTB_DATA_R |=  temp_holder;


		// read data
		temp_holder = 1 && (GPIO_PORTB_DATA_R & (1 << CON_RX));
		recieved |= (temp_holder << i);

		// clock low
		temp_holder = ~(1 << CON_CLOCK);
		GPIO_PORTB_DATA_R &= temp_holder;



	}

	// set atention
	GPIO_PORTB_DATA_R |= (1 << CON_ATENTION);

	return recieved;
}


/****************************** End Of Module *******************************/














