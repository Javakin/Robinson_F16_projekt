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
#include "Modules/EMP/emp_type.h"
#include "Modules/UART0/uart0_tx.h"
#include "Modules/SPI_master/spi_master.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"


/*****************************    Defines    *******************************/

//#define CON_RX	1 && (CONTROLLER_RX & (1 << CON_RX))


/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/

// Queues
extern xQueueHandle uart0_tx_queue;

// instructions
INT16U inst[4] = {0x5A5A, 0x5A5A, 0x5A5A, 0x5A5A};

// testing of recieving queues
xQueueHandle command_queue;



INT8U state = IDLE_STATE;
INT8U message_state = ACK_RECEIVED_STATE;

INT8U ack_received = 0;


// current bytes operated on
INT16U spi_current_byte_rx = 0;
INT16U spi_current_byte_tx = 0;

/*****************************   Functions   *******************************/
void spi_master_task()
{
	// initialise used prots
	spi_master_init();

	// run task
	while(1)
	{
		switch (state)
		{
		case IDLE_STATE:
			// fill buffer with new pull
			spi_idle_func();
			state = CLR_ATEN_STATE;
			break;

		case SET_ATEN_STATE:
			// set atention
			GPIO_PORTB_DATA_R |= (1 << CON_ATENTION);
			uart0_putc_tx( '\n' );
			state = IDLE_STATE;
			break;

		case CLR_ATEN_STATE:
			// clear atention
			GPIO_PORTB_DATA_R &= ~(1 << CON_ATENTION);
			state = ACK_RECEIVED_STATE;
			break;

		case SEND_BYTE_STATE:
			spi_send_byte();
			state = ACK_WAIT_STATE;
			break;

		case ACK_WAIT_STATE:
			state = spi_ack_wait();
			break;

		case ACK_RECEIVED_STATE:
			if(xQueueReceive(command_queue, &( spi_current_byte_tx ), 2 ) == pdTRUE)
				// new byte to sende
				state = SEND_BYTE_STATE;
			else
				// queue enpty set aten_state
				state = SET_ATEN_STATE;
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
			(1 << CON_CLOCK) | (1 << CON_ACK);

	// set direction
	GPIO_PORTB_DIR_R |= (1 << CON_TX) | (1 << CON_ATENTION)	| (1 << CON_CLOCK);
	GPIO_PORTB_DIR_R &= ~((1 << CON_RX) | (1 << CON_ACK));

	// set pull-up resistors
	GPIO_PORTB_PUR_R |= (1 << CON_RX) | (1 << CON_ACK);

	// setup af interrupt for prot A
	//NVIC_EN0_R |= 0x0000002;

	// interrupt masking
	//GPIO_PORTB_IM_R |= (1 << CON_ACK);

	// set interrupt event
	//GPIO_PORTB_IEV_R |= (1 << CON_ACK);

	// setup queues
	command_queue = xQueueCreate(32, sizeof(INT16U));
}


void spi_idle_func()
{
	// fyld buffer
	for (INT8U i = 0; i < 13; i++)
	{
		xQueueSend(command_queue, &( inst[i] ), 1);
	}
}


INT8U spi_ack_wait()
{
	INT8U message = SEND_BYTE_STATE;
	//vTaskDelay(1);

	// test if ack has arriveds
	//if (ack_received)
	//{
		// send suceded
		message = ACK_RECEIVED_STATE;
		//ack_received = 0;

		// send byte to screeen
		for (INT8U i = 0; i < 16; i++)
			uart0_putc_tx( ((spi_current_byte_rx & (1 << i)) && 1) + '0' );
	//}

	return message;
}


void spi_send_byte()
{
	INT8U test = 0;
	spi_current_byte_rx = 0;
	// send byte
	for(INT8U i = 0; i < 13; i++)
	{
		// clock low
		// set bit to transmit
		test = (GPIO_PORTB_DATA_R & ~(1 << CON_TX));
		test |= ( (1 && (spi_current_byte_tx & (1 << i) ) ) << CON_TX);
		GPIO_PORTB_DATA_R = test;

		test = ~(1 << CON_CLOCK);
		GPIO_PORTB_DATA_R &= test;

		// clock high
		// read data
		test = 1 && (GPIO_PORTB_DATA_R & (1 << CON_RX));
		spi_current_byte_rx |= (test << i);

		test = (1 << CON_CLOCK);
		GPIO_PORTB_DATA_R |=  test;

	}
}


/****************************** End Of Module *******************************/














