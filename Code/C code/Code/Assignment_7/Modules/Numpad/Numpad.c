/*****************************************************************************
 * University of Southern Denmark
 * Embedded Programming (EMP)
 *
 * MODULENAME.: Numpad.h
 *
 * PROJECT....: Assignment_5
 *
 * DESCRIPTION: See module specification file (.h-file).
 *
 * Change Log:
 *****************************************************************************
 * Date    Id    Change
 * YYMMDD
 * --------------------
 *  160311  JA    Module created.
 *
 *****************************************************************************/

/***************************** Include files *******************************/
#include <stdint.h>
#include <tm4c123gh6pm.h>
#include "Modules/EMP/emp_type.h"
#include <Numpad/Numpad.h>
#include <UART/uart0.h>
#include <Queue/Queue.h>
#include <Tasking/tmodel.h>
#include "RTCS/rtcs.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

/*****************************    Defines    *******************************/

/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/

extern struct Queue numpad_input_queue;
extern xQueueHandle GUI_queue;

/*****************************   Functions   *******************************/

 void numpad_init()
/*****************************************************************************
 *   Function : See module specification (.h-file).
 *****************************************************************************/
{
	// Enable the GPIO port that is used for Numpad
	SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOA | SYSCTL_RCGC2_GPIOE;

	// Do a dummy read to insert a few cycles after enabling the peripheral.
	__asm("nop");

	GPIO_PORTA_DIR_R |= (1 << NUMPAD_COLUMN_1) | (1 << NUMPAD_COLUMN_2)
			| (1 << NUMPAD_COLUMN_3);
	GPIO_PORTA_DEN_R |= (1 << NUMPAD_COLUMN_1) | (1 << NUMPAD_COLUMN_2)
			| (1 << NUMPAD_COLUMN_3);

	GPIO_PORTE_DIR_R &= !((1 << NUMPAD_ROW_1) | (1 << NUMPAD_ROW_2)
			| (1 << NUMPAD_ROW_3) | (1 << NUMPAD_ROW_4));
	GPIO_PORTE_DEN_R |= (1 << NUMPAD_ROW_1) | (1 << NUMPAD_ROW_2)
			| (1 << NUMPAD_ROW_3) | (1 << NUMPAD_ROW_4);

}

// void test();
/*****************************************************************************
 *   Function : See module specification (.h-file).
 *****************************************************************************/

void numpad_task(void *pvParameters)
/*****************************************************************************
 *   Input    : -
 *   Output   : -
 *   Function : Disable global interrupt
 ******************************************************************************/
{
	numpad_init();

	while (1) {
		static INT16U button_prev = 0;
		volatile INT16U button_state = 0;
		volatile INT8U temp = 0;
		INT8U btn;

		//Clear column pins and set column 1 high

		GPIO_PORTA_DATA_R &= !((1 << NUMPAD_COLUMN_1) | (1 << NUMPAD_COLUMN_2)
				| (1 << NUMPAD_COLUMN_3));

		GPIO_PORTA_DATA_R |= (1 << NUMPAD_COLUMN_1);

		//Read in the entire row port
		temp = GPIO_PORTE_DATA_R;

		//Clear column pins and set column 2 high
		GPIO_PORTA_DATA_R &= !((1 << NUMPAD_COLUMN_1) | (1 << NUMPAD_COLUMN_2)
				| (1 << NUMPAD_COLUMN_3));

		GPIO_PORTA_DATA_R |= (1 << NUMPAD_COLUMN_2);

		//Mask out all bits that aren't row data
		temp &= (1 << NUMPAD_ROW_1) | (1 << NUMPAD_ROW_2) | (1 << NUMPAD_ROW_3)
				| (1 << NUMPAD_ROW_4);

		button_state = temp;

		//Read in the entire row port
		temp = GPIO_PORTE_DATA_R;

		//Clear column pins and set column 3 high
		GPIO_PORTA_DATA_R &= !((1 << NUMPAD_COLUMN_1) | (1 << NUMPAD_COLUMN_2)
				| (1 << NUMPAD_COLUMN_3));

		GPIO_PORTA_DATA_R |= (1 << NUMPAD_COLUMN_3);

		//Mask out all bits that aren't row data
		temp &= (1 << NUMPAD_ROW_1) | (1 << NUMPAD_ROW_2) | (1 << NUMPAD_ROW_3)
				| (1 << NUMPAD_ROW_4);

		button_state |= (temp << 4);

		//Read in the entire row port
		temp = GPIO_PORTE_DATA_R;

		//Mask out all bits that aren't row data
		temp &= (1 << NUMPAD_ROW_1) | (1 << NUMPAD_ROW_2) | (1 << NUMPAD_ROW_3)
				| (1 << NUMPAD_ROW_4);

		button_state |= (temp << 8);

		if (button_prev != button_state) {
			for (int i = 0; i < 12; i++) {
				if ((button_state & (1 << i)) != (button_prev & (1 << i))) {
					if (button_state & (1 << i)) {
						switch (i) {
						case NUMPAD_ZERO:
							btn = '0';
							uart0_putc('0');
							//put_queue(Q_INPUT,'0',0);
							//queue_put(&numpad_input_queue,'0');
							break;
						case NUMPAD_ONE:
							btn = '1';
							uart0_putc('1');
							//put_queue(Q_INPUT,'1',0);
							//queue_put(&numpad_input_queue,'1');
							break;
						case NUMPAD_TWO:
							btn = '2';
							uart0_putc('2');
							//put_queue(Q_INPUT,'2',0);
							//queue_put(&numpad_input_queue,'2');
							break;
						case NUMPAD_THREE:
							btn = '3';
							uart0_putc('3');
							//put_queue(Q_INPUT,'3',0);
							//queue_put(&numpad_input_queue,'3');
							break;
						case NUMPAD_FOUR:
							btn = '4';
							uart0_putc('4');
							//put_queue(Q_INPUT,'4',0);
							//queue_put(&numpad_input_queue,'4');
							break;
						case NUMPAD_FIVE:
							btn = '5';
							uart0_putc('5');
							//put_queue(Q_INPUT,'5',0);
							//queue_put(&numpad_input_queue,'5');
							break;
						case NUMPAD_SIX:
							btn = '6';
							uart0_putc('6');
							//put_queue(Q_INPUT,'6',0);
							//queue_put(&numpad_input_queue,'6');
							break;
						case NUMPAD_SEVEN:
							btn = '7';
							uart0_putc('7');
							//put_queue(Q_INPUT,'7',0);
							//queue_put(&numpad_input_queue,'7');
							break;
						case NUMPAD_EIGHT:
							btn = '8';
							uart0_putc('8');
							//put_queue(Q_INPUT,'8',0);
							//queue_put(&numpad_input_queue,'8');
							break;
						case NUMPAD_NINE:
							btn = '9';
							uart0_putc('9');
							//put_queue(Q_INPUT,'9',0);
							//queue_put(&numpad_input_queue,'9');
							break;
						case NUMPAD_HASH:
							btn = '#';
							uart0_putc('#');
							//put_queue(Q_INPUT,'#',0);
							//queue_put(&numpad_input_queue,'#');
							break;
						case NUMPAD_STAR:
							btn = '*';
							uart0_putc('*');
							//put_queue(Q_INPUT,'*',0);
							//queue_put(&numpad_input_queue,'*');
							break;
						default:
							break;
						}
						xQueueSend(GUI_queue,&btn,10000);
					}
				}
			}
			button_prev = button_state;
		}
		vTaskDelay(30 / portTICK_RATE_MS);
	}
	//wait( NUMPAD_DEBOUNCE_TIME); //
}

/****************************** End Of Module *******************************/
