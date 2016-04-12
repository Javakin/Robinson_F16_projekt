/*****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: uart0.c
*
* PROJECT....: Assignment 4
*
* DESCRIPTION: Support UART comunicaiton
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
#include <UART/uart0.h>
#include <Tasking/tmodel.h>
#include <Tasking/messages.h>
#include <Queue/Queue.h>
#include <RTCS/rtcs.h>
#include "FreeRTOS.h"
#include "queue.h"
/*****************************    Defines    *******************************/

/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/
//extern struct Queue uart0_rx_queue;
extern xQueueHandle uart0_rx_queue;
extern xQueueHandle LCD_image_queue;
extern xQueueHandle LCD_char_queue;

/*****************************   Functions   *******************************/


INT32U lcrh_databits( INT8U antal_databits )
{
  if(( antal_databits < 5 ) || ( antal_databits > 8 ))
	antal_databits = 8;
  return(( (INT32U)antal_databits - 5 ) << 5 );  // Control bit 5-6, WLEN
}

INT32U lcrh_stopbits( INT8U antal_stopbits )
{
  if( antal_stopbits == 2 )
    return( 0x00000008 );  		// return bit 3 = 1
  else
	return( 0x00000000 );		// return all zeros
}

INT32U lcrh_parity( INT8U parity )
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

void uart0_interrupt_enable()
{
	UART0_IM_R |= UART_IM_RXIM;
	UART0_IM_R |= 0x40;

	NVIC_EN0_R = 0x00000020;
}

void uart0_interrupt_disable()
{

}

void uart0_fifos_enable()
{
  UART0_LCRH_R  |= 0x00000020;
}

void uart0_fifos_disable()
{
  UART0_LCRH_R  &= 0xFFFFFFEF;
}

extern BOOLEAN uart0_rx_rdy()
{
  return( UART0_FR_R & UART_FR_RXFF );
}

extern INT8U uart0_getc()
{
  return ( UART0_DR_R );
}

extern BOOLEAN uart0_tx_rdy()
{
  return( UART0_FR_R & UART_FR_TXFE );
}

extern void uart0_putc( INT8U ch )
{
  UART0_DR_R = ch;
}

void UART0_tx_isr()
{

}

void UART0_rx_isr()
{
	do
	{
		//put_queue(Q_INPUT,received,0);
		//queue_put(&uart0_rx_queue, UART0_DR_R);
//		xQueueSendFromISR(LCD_image_queue, &image, NULL);
//
		INT8U received = UART0_DR_R;
//		xQueueSendFromISR(LCD_char_queue, &received, NULL);
	} while (RX_FIFO_NOT_EMPTY);
}

void UART0_task(INT8U my_id, INT8U my_state, INT8U my_event, INT8U my_data)
{
	UART0_init( 19200, 8, 1, 0 );
	while(1)
	{

	}
}

extern void UART0_init( INT32U baud_rate, INT8U databits, INT8U stopbits, INT8U parity )
{
  INT32U BRD;

  #ifndef E_PORTA
  #define E_PORTA
  SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOA;					// Enable clock for Port A
  #endif

  #ifndef E_UART0
  #define E_UART0
  SYSCTL_RCGC1_R |= SYSCTL_RCGC1_UART0;					// Enable clock for UART 0
  #endif

  GPIO_PORTA_AFSEL_R |= 0x00000003;		// set PA0 og PA1 to alternativ function (uart0)
  GPIO_PORTA_DIR_R   |= 0x00000002;     // set PA1 (uart0 tx) to output
  GPIO_PORTA_DIR_R   &= 0xFFFFFFFE;     // set PA0 (uart0 rx) to input
  GPIO_PORTA_DEN_R   |= 0x00000003;		// enable digital operation of PA0 and PA1
  //GPIO_PORTA_PUR_R   |= 0x00000002;

  BRD = 64000000 / baud_rate;   	// X-sys*64/(16*baudrate) = 16M*4/baudrate
  UART0_IBRD_R = BRD / 64;
  UART0_FBRD_R = BRD & 0x0000003F;

  UART0_LCRH_R  = lcrh_databits( databits );
  UART0_LCRH_R += lcrh_stopbits( stopbits );
  UART0_LCRH_R += lcrh_parity( parity );

  uart0_fifos_enable();
  uart0_interrupt_enable();

  UART0_CTL_R  |= (UART_CTL_UARTEN | UART_CTL_TXE | UART_CTL_RXE );  // Enable UART

}

/****************************** End Of Module *******************************/












