/*****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: uart0_rx.h
*
* PROJECT....: Assignment 4
*
* DESCRIPTION: Support uart0_rx comunicaiton
*
* Change Log:
******************************************************************************
* Date    Id    Change
* YYMMDD
* --------------------
* 150228  MoH   Module created.
* 040316  DFH	Module opdaget
* 150416  DFH 	Module splittet up in RX and TX
*
*****************************************************************************/

#ifndef _UART0_RX_H
  #define _UART0_RX_H

/***************************** Include files *******************************/

/*****************************    Defines    *******************************/

#define RX_FIFO_NOT_EMPTY !(UART0_FR_R & 0x10)

// states
#define SEND_STATE		0
#define CONFIG_STATE	1

// settings
#define CONFIG_CHAR		'<'
#define SET_PS2CON		'p'


/*****************************   Constants   *******************************/

/*****************************   Functions   *******************************/
void uart0_interrupt_enable_rx();
//   Input    : -
//   Output   : -
//   Function : Enable interrupt for uart0


void uart0_isr_rx();
//   Input    : -
//   Output   : -
//   Function : put char in uart0_rx_queue


void uart0_rx_task();
//   Input    : -
//   Output   : -
//   Function : distribute chars to the corresponding task



INT32U lcrh_databits_rx( INT8U antal_databits );
//   Input    : number of bits used
//   Output   : bit-values for bit 5 and 6 for LCRH register
//   Function : sets bit 5 and 6 according to the wanted number of data bits.
//  		    5: bit5 = 0, bit6 = 0.
//  		    6: bit5 = 1, bit6 = 0.
// 		        7: bit5 = 0, bit6 = 1.
//   		    8: bit5 = 1, bit6 = 1  (default).
//  		    all other bits are returned = 0


INT32U lcrh_stopbits_rx( INT8U antal_stopbits );
//   Input    : number of decired stop bits
//   Output   : Bit set settings for LCRH register
//   Function : sets bit 3 according to the wanted number of stop bits.
//   		    1 stpobit:  bit3 = 0 (default).
//   		    2 stopbits: bit3 = 1.
//   		    all other bits are returned = 0


INT32U lcrh_parity_rx( INT8U parity );
//   Input    :
//   Output   :
//   Function : sets bit 1, 2 and 7 to the wanted parity.
//   		    'e':  00000110b.
//   		    'o':  00000010b.
//   		    '0':  10000110b.
//   		    '1':  10000010b.
//   		    'n':  00000000b.
//   		     all other bits are returned = 0


void uart0_fifos_disable_rx();
//   Input    : -
//   Output   : -
//   Function : disable fifo buffer


void uart0_fifos_enable_rx();
//   Input    : -
//   Output   : -
//   Function : enable fifo buffer


void uart0_init_rx( INT32U, INT8U, INT8U, INT8U );
//   Input    : -
//   Output   : -
//   Function : Initialize uart 0

void send_state();
//   Input    : -
//   Output   : -
//   Function : send char to the receiving queue

void config_state();
//   Input    : -
//   Output   : -
//   Function : change the recieving queue

/****************************** End Of Module *******************************/
#endif

