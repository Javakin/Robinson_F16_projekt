/*****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: lcd.c
*
* PROJECT....: EMP
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
#include "Modules/LCD/lcd.h"
#include "Modules/Tasking/tmodel.h"
#include "Modules/Tasking/messages.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

/*****************************    Defines    *******************************/

/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/

extern xQueueHandle uart0_rx_queue;
extern xQueueHandle LCD_image_queue;
extern xQueueHandle LCD_char_queue;

enum lcd_states {
	 WAIT,
	 NEW_IMAGE,
	 DIRECT_INPUT
};

INT8U lcd_state = 0;

/*****************************   Functions   *******************************/

INT8U index_conv(INT8U index)
{
	INT8U result = 0;
	if(index > 15)
	{
		result |= 0x40;
		result += (index - 16);
	}
	else
		result = index;

	return result;
}

void LCD_init()
{
	vTaskDelay(100 / portTICK_RATE_MS);

	INT8U init_sequence[12] = {0x30, 0x30, 0x30, 0x20, 0x20, 0x80, 0x00, 0xC0, 0x00, 0x60, 0x00, 0x10};

	// inisiation sequence
	INT8U i = 0;
	for (i = 0; i < 12; i++)
	{
		GPIO_PORTC_DATA_R = init_sequence[i];
		LCD_Flash_Enable_Pin();

		vTaskDelay(10 / portTICK_RATE_MS);
	}
}

void LCD_Flash_Enable_Pin()
{
	LCD_ENABLE_PIN_HIGH;
	LCD_ENABLE_PIN_LOW;
}

void LCD_Write(INT8U data, INT8U mode) {
	INT8U low_nibble = (data & 0x0F);
	INT8U high_nibble = ((data & 0xF0) >> 4);

	if (mode) {
		LCD_SET_DATA_MODE;
	} else {
		LCD_SET_CMD_MODE;
	}

	GPIO_PORTC_DATA_R &= 0x0F;
	GPIO_PORTC_DATA_R |= (high_nibble << 4);
	LCD_Flash_Enable_Pin();

	vTaskDelay(1 / portTICK_RATE_MS);
	// Maybe some wait time?

	GPIO_PORTC_DATA_R &= 0x0F;
	GPIO_PORTC_DATA_R |= (low_nibble << 4);
	LCD_Flash_Enable_Pin();
	// send ready event
}

void LCD_Set_Cursor(INT8U address)
{
	if(address < 128)
		LCD_Write( address | 0x80 , CMD_MODE);
}

void LCD_task(void *pvParameters)
{
	LCD_init();

	INT8U received[36];

	while (1)
	{
		if (xQueueReceive(LCD_image_queue, &received, 10000))
		{
			for (int i = received[35]; i < 36; i++)
			{
				vTaskDelay(5 / portTICK_RATE_MS);
				switch (i) {
								case 0:
									LCD_Set_Cursor(0x00);
									vTaskDelay(5 / portTICK_RATE_MS);
									LCD_Write(received[i], DATA_MODE);
									vTaskDelay(5 / portTICK_RATE_MS);
									break;

								case 32:
									LCD_Set_Cursor(index_conv(received[i]));
									vTaskDelay(5 / portTICK_RATE_MS);
									break;

								case 33:
									if (received[i])
										LCD_Write(LCD_CMD_CURSOR_ON, CMD_MODE);
									vTaskDelay(5 / portTICK_RATE_MS);
									break;

								case 34:
									if (received[i])
										LCD_Write(LCD_CMD_BLINK_ON, CMD_MODE);
									else
										LCD_Write(LCD_CMD_DISPLAY_ON, CMD_MODE);
									vTaskDelay(5 / portTICK_RATE_MS);
									break;

								case 35:
									break;

								case 16:
									LCD_Set_Cursor(0x40);
									vTaskDelay(5 / portTICK_RATE_MS);
									// no break here!

								default:
									LCD_Write(received[i], DATA_MODE);
									vTaskDelay(5 / portTICK_RATE_MS);
									break;
				}
			}
		}
	}
}

/****************************** End Of Module *******************************/
