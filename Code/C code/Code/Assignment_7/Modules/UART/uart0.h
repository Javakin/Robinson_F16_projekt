/*****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: uart0.h
*
* PROJECT....: Assignment 4
*
* DESCRIPTION: Support UART comunicaiton
*
* Change Log:
******************************************************************************
* Date    Id    Change
* YYMMDD
* --------------------
* 150228  MoH   Module created.
* 040316  DFH	Module opdaget
*
*****************************************************************************/

#ifndef _UART_H
  #define _UART_H

/***************************** Include files *******************************/

/*****************************    Defines    *******************************/

#define RX_FIFO_NOT_EMPTY !(UART0_FR_R & 0x10)

/*****************************   Constants   *******************************/

/*****************************   Functions   *******************************/

extern BOOLEAN uart0_rx_rdy();
//   Input    : -
//   Output   : -
//   Function : Character ready at uart0 RX

extern INT8U uart0_getc();
//   Input    : -
//   Output   : -
//   Function : Get character from uart0 RX

extern BOOLEAN uart0_tx_rdy();
//   Input    : -
//   Output   : -
//   Function : uart0 TX buffer ready

extern void uart0_putc( INT8U );
//   Input    : -
//   Output   : -
//   Function : Put character to uart0 TX

extern void UART0_init( INT32U, INT8U, INT8U, INT8U );
//   Input    : -
//   Output   : -
//   Function : Initialize uart 0

INT32U lcrh_databits( INT8U antal_databits );
//   Input    : number of bits used
//   Output   : bit-values for bit 5 and 6 for LCRH register
//   Function : sets bit 5 and 6 according to the wanted number of data bits.
//  		    5: bit5 = 0, bit6 = 0.
//  		    6: bit5 = 1, bit6 = 0.
// 		        7: bit5 = 0, bit6 = 1.
//   		    8: bit5 = 1, bit6 = 1  (default).
//  		    all other bits are returned = 0


INT32U lcrh_stopbits( INT8U antal_stopbits );
//   Input    : number of decired stop bits
//   Output   : Bit set settings for LCRH register
//   Function : sets bit 3 according to the wanted number of stop bits.
//   		    1 stpobit:  bit3 = 0 (default).
//   		    2 stopbits: bit3 = 1.
//   		    all other bits are returned = 0

INT32U lcrh_parity( INT8U parity );
//   Input    :
//   Output   :
//   Function : sets bit 1, 2 and 7 to the wanted parity.
//   		    'e':  00000110b.
//   		    'o':  00000010b.
//   		    '0':  10000110b.
//   		    '1':  10000010b.
//   		    'n':  00000000b.
//   		     all other bits are returned = 0

void UART0_rx_isr();

void UART0_tx_isr();

void UART0_task(INT8U my_id, INT8U my_state, INT8U my_event, INT8U my_data);

/****************************** End Of Module *******************************/
#endif

