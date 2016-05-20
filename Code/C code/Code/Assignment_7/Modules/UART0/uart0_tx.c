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
#include <UART0/uart0_tx.h>

#include "FreeRTOS.h"
#include "queue.h"
#include "task.h"
/*****************************    Defines    *******************************/

/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/

extern xQueueHandle uart0_tx_queue;


/*****************************   Functions   *******************************/

BOOLEAN uart0_rdy_tx()
{
  return( UART0_FR_R & UART_FR_TXFE );
}


INT8U uart0_putc_tx( INT8U ch )
{
	return xQueueSend(uart0_tx_queue, &( ch ), portMAX_DELAY);
}


void uart0_tx_task(void *pvParameters)
{
	uart0_init_tx( 19200, 8, 1, 0 );

	INT8U recieve;

	while(1)
	{
		if (!(UART0_FR_R & UART_FR_TXFF))
		{
			// The TX-fifo is not full add one more char from tx_queue
			if( xQueueReceive( uart0_tx_queue, &( recieve ), portMAX_DELAY ) )
			{
				UART0_DR_R = recieve;
			}
		}
	}
}


INT32U lcrh_databits_tx( INT8U antal_databits )
{
  if(( antal_databits < 5 ) || ( antal_databits > 8 ))
	antal_databits = 8;
  return(( (INT32U)antal_databits - 5 ) << 5 );  // Control bit 5-6, WLEN
}


INT32U lcrh_stopbits_tx( INT8U antal_stopbits )
{
  if( antal_stopbits == 2 )
    return( 0x00000008 );  		// return bit 3 = 1
  else
	return( 0x00000000 );		// return all zeros
}


INT32U lcrh_parity_tx( INT8U parity )
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


void uart0_init_tx( INT32U baud_rate, INT8U databits, INT8U stopbits, INT8U parity )
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

  UART0_LCRH_R  = lcrh_databits_tx( databits );
  UART0_LCRH_R += lcrh_stopbits_tx( stopbits );
  UART0_LCRH_R += lcrh_parity_tx( parity );

  uart0_fifos_enable_tx();


  UART0_CTL_R  |= (UART_CTL_UARTEN | UART_CTL_TXE | UART_CTL_RXE );  // Enable UART

}


void uart0_fifos_enable_tx()
{
  UART0_LCRH_R  |= 0x00000010;
}


void uart0_fifos_disable_tx()
{
  UART0_LCRH_R  &= 0xFFFFFFEF;
}




/****************************** End Of Module *******************************/












