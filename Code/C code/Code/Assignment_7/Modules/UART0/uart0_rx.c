/*****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: uart0.c
*
* PROJECT....: semester project
*
* DESCRIPTION: Support UART communication
*
* Change Log:
*****************************************************************************
* Date    Id    Change
* YYMMDD
* --------------------
* 150228  MoH   Module created
* 040316  DFH   Module updated
*
*****************************************************************************/

/***************************** Include files *******************************/
#include <stdint.h>
#include "tm4c123gh6pm.h"
#include <EMP/emp_type.h>
#include "UART0/uart0_rx.h"
#include "UART0_api/uart0_api.h"
#include "FreeRTOS.h"
#include "queue.h"

/*****************************    Defines    *******************************/

/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/
// Queues
extern xQueueHandle uart0_rx_queue;
extern xQueueHandle default_queue;
extern xQueueHandle application_queue;

static xQueueHandle current_queue;

// states
enum uart_rx_states
{
	SEND_STATE,
	CONFIG_STATE
};


// placeholder for the received byte
INT8U uart0_rx_received;

// state holder
INT8U uart0_rx_state = SEND_STATE;


/*****************************   Functions   *******************************/


INT32U lcrh_databits_rx( INT8U antal_databits )
{
  if(( antal_databits < 5 ) || ( antal_databits > 8 ))
	antal_databits = 8;
  return(( (INT32U)antal_databits - 5 ) << 5 );  // Control bit 5-6, WLEN
}

INT32U lcrh_stopbits_rx( INT8U antal_stopbits )
{
  if( antal_stopbits == 2 )
    return( 0x00000008 );  		// return bit 3 = 1
  else
	return( 0x00000000 );		// return all zeros
}

INT32U lcrh_parity_rx( INT8U parity )
{
  INT32U result;

  switch( parity )
  {
    case 'e':
      result = 0x00000006;
      break;
    case 'o':
      result = 0x00000002;
      break;
    case '0':
      result = 0x00000086;
      break;
    case '1':
      result = 0x00000082;
      break;
    case 'n':
    default:
      result = 0x00000000;
  }
  return( result );
}

void uart0_interrupt_enable_rx()
{
	// UART Receive Interrupt Mask - ½ fyldt resultere i interrupt
	UART0_IM_R |= UART_IM_RXIM;

	// UART Receive Time-Out Interrupt Mask
	UART0_IM_R |= 0x40;

	// enable interrrupt for uart0
	NVIC_EN0_R |= 0x00000020;
}

void uart0_fifos_enable_rx()
{
  UART0_LCRH_R  |= 0x00000010;
}

void uart0_fifos_disable_rx()
{
  UART0_LCRH_R  &= 0xFFFFFFEF;
}

void uart0_isr()
{
	while (RX_FIFO_NOT_EMPTY)
	{
		INT8U received = UART0_DR_R;
		xQueueSendFromISR(uart0_rx_queue, &received, NULL);
	}
}

void uart0_init_rx( INT32U baud_rate, INT8U databits, INT8U stopbits, INT8U parity )
{
  INT32U BRD;

  SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOA;					// Enable clock for Port A

  SYSCTL_RCGC1_R |= SYSCTL_RCGC1_UART0;					// Enable clock for UART 0

  GPIO_PORTA_AFSEL_R |= 0x00000003;		// set PA0 og PA1 to alternativ function (uart0)
  GPIO_PORTA_DIR_R   |= 0x00000002;     // set PA1 (uart0 tx) to output
  GPIO_PORTA_DIR_R   &= 0xFFFFFFFE;     // set PA0 (uart0 rx) to input
  GPIO_PORTA_DEN_R   |= 0x00000003;		// enable digital operation of PA0 and PA1
  //GPIO_PORTA_PUR_R   |= 0x00000002;

  BRD = 64000000 / baud_rate;   	// X-sys*64/(16*baudrate) = 16M*4/baudrate
  UART0_IBRD_R = BRD / 64;
  UART0_FBRD_R = BRD & 0x0000003F;

  UART0_LCRH_R  = lcrh_databits_rx( databits );
  UART0_LCRH_R += lcrh_stopbits_rx( stopbits );
  UART0_LCRH_R += lcrh_parity_rx( parity );

  uart0_fifos_enable_rx();
  uart0_interrupt_enable_rx();

  UART0_CTL_R  |= (UART_CTL_UARTEN | UART_CTL_TXE | UART_CTL_RXE );  // Enable UART

  // set the default target_queue for the task to fill the chars
  current_queue = default_queue;
}

void uart0_rx_task()
{
	uart0_init_rx( 19200, 8, 1, 0 );

	while(1)
	{
		switch( uart0_rx_state )
		{
		case SEND_STATE :
			// send char to the receiving queue
			send_state();
			break;


		case CONFIG_STATE :
			// change recieving queue
			config_state();
			break;
		}
	}
}

void send_state()
{
	if( xQueueReceive( uart0_rx_queue, &( uart0_rx_received ), 10 ) )
	{
		if ( uart0_rx_received == CONFIG_CHAR)
		{
			uart0_rx_state = CONFIG_STATE;
		}
		else
		{
			uart0_api_receive_message(uart0_rx_received);
		}
	}
}

void config_state()
{
	if( xQueueReceive( uart0_rx_queue, &( uart0_rx_received ), portMAX_DELAY ) )
	{
		// select the setting
		switch( uart0_rx_received )
		{
		case SET_APPLICATION:
			current_queue = application_queue;
			break;

		default:
			current_queue = application_queue;
			break;
		}

		// back to send state
		uart0_rx_state = SEND_STATE;
	}
}
/****************************** End Of Module *******************************/












