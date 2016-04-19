/*****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: uart0_tx.h
*
* PROJECT....: Assignment 4
*
* DESCRIPTION: Support uart0_tx comunicaiton
*
* Change Log:
******************************************************************************
* Date    Id    Change
* YYMMDD
* --------------------
* 150228  MoH   Module created.
* 040316  DFH	Module opdaget
* 150416  DFH	Module splittet up in Rx and Tx
*
*****************************************************************************/

#ifndef _UART0_TX_H
  #define _UART0_TX_H

/***************************** Include files *******************************/

/*****************************    Defines    *******************************/

/*****************************   Constants   *******************************/

/*****************************   Functions   *******************************/


BOOLEAN uart0_rdy_tx();
//   Input    : -
//   Output   : -
//   Function : uart0 TX buffer ready


INT8U uart0_putc_tx( INT8U ch );
//   Input    : the char to send
//   Output   : 1 if suceded, 0 if failed (time oute)
//   Function : Put character in the uart0_TX_queue


void uart0_tx_task(void *pvParameters);
//   Input    : -
//   Output   : -
//   Function : transmit the content in uart0_tx_queue


INT32U lcrh_databits_tx( INT8U antal_databits );
//   Input    : number of bits used
//   Output   : bit-values for bit 5 and 6 for LCRH register
//   Function : sets bit 5 and 6 according to the wanted number of data bits.
//  		    5: bit5 = 0, bit6 = 0.
//  		    6: bit5 = 1, bit6 = 0.
// 		        7: bit5 = 0, bit6 = 1.
//   		    8: bit5 = 1, bit6 = 1  (default).
//  		    all other bits are returned = 0


INT32U lcrh_stopbits_tx( INT8U antal_stopbits );
//   Input    : number of decired stop bits
//   Output   : Bit set settings for LCRH register
//   Function : sets bit 3 according to the wanted number of stop bits.
//   		    1 stpobit:  bit3 = 0 (default).
//   		    2 stopbits: bit3 = 1.
//   		    all other bits are returned = 0


INT32U lcrh_parity_tx( INT8U parity );
//   Input    :
//   Output   :
//   Function : sets bit 1, 2 and 7 to the wanted parity.
//   		    'e':  00000110b.
//   		    'o':  00000010b.
//   		    '0':  10000110b.
//   		    '1':  10000010b.
//   		    'n':  00000000b.
//   		     all other bits are returned = 0


void uart0_init_tx( INT32U baud_rate, INT8U databits, INT8U stopbits, INT8U parity);
//   Input    : -
//   Output   : -
//   Function : Initialize uart 0


void uart0_fifos_enable_tx();
//   Input    : -
//   Output   : -
//   Function : enable fifo


void uart0_fifos_disable_tx();
//   Input    : -
//   Output   : -
//   Function : disable fifo


/****************************** End Of Module *******************************/
#endif

