/*****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: gui.c
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
#include "EMP/emp_type.h"
#include "Modules/LCD/lcd.h"
#include "Modules/Tasking/tmodel.h"
#include "Modules/Tasking/messages.h"
#include "GUI/gui.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

/*****************************    Defines    *******************************/

/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/

INT8U image_buffer[7][36] = {
		{'W','e','l','c','o','m','e','!',' ','P','r','e','s','s',' ',' ',
		 '"','*','"',' ','f','o','r',' ','m','e','n','u','G',' ',' ',' ',
		 0x00,0,0,0 },

		{'E','n','t','e','r',' ','C','o','m','m','a','n','d',':',' ',' ',
		 ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
		 0x10,0,1,0 },

		{'I','n','v','a','l','i','d',' ','I','n','p','u','t',' ',' ',' ',
		 ' ',' ','T','r','y',' ','A','g','a','i','n','.','.','.',' ',' ',
		 0x00,0,0,0 },

		{'S','e','t',' ','t','h','e',' ','T','i','m','e',':',' ',' ',' ',
		 ' ',' ',' ',' ','h','h',':','m','m',':','s','s',' ',' ',' ',' ',
	     0x14,0,1,0 },

		{'C','u','r','r','e','n','t',' ','T','i','m','e',':',' ',' ',' ',
		 ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
		 0x14,0,0,0 },

		{'A','d','j','u','s','t',' ','Y','o','u','r',' ','K','n','o','b',
		 ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
		 0x14,0,0,0 },

		{'K','n','o','b',' ','V','a','l','u','e',':',' ',' ',' ',' ',' ',
		 ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
		 0x14,0,0,0 }
};

INT8U current_image[36];

extern xQueueHandle GUI_queue;
extern xQueueHandle LCD_image_queue;

enum gui_states {
	INIT,
	ENTER_COMMAND,
	ERROR,
	SET_TIME,
	SHOW_TIME
};

/*****************************   Functions   *******************************/

void gui_task(void *pvParameters)
{
	INT8U received;
	INT8U gui_state = INIT;

	set_image(WELCOME_MSG);
	xQueueSend(LCD_image_queue,&current_image,10000);
	while (1) {
		if (xQueueReceive(GUI_queue, &received, 10000))
		{
			switch (gui_state)
			{
			case INIT:

				if (received == '*')
				{
					set_image(COMMAND_PROMPT);
					xQueueSend(LCD_image_queue,&current_image,10000);
					gui_state = ENTER_COMMAND;
					current_image[NEXT_POS] = current_image[CURRENT_POS] + 1;
				}
				break;

			case ENTER_COMMAND:
				if(received == '#')
				{
					gui_state = ERROR;
					set_image(ERROR_MSG);
					xQueueSend(LCD_image_queue,&current_image,10000);
				}

				else if(current_image[NEXT_POS] < 32)
				{
					current_image[current_image[NEXT_POS]] = received;
					current_image[CURRENT_POS]++;
					xQueueSend(LCD_image_queue,&current_image,10000);
					current_image[NEXT_POS]++;
				}
				break;

			case ERROR:
				//xQueueSend(LCD_image_queue,&current_image,10000);
				break;

			case SET_TIME:
				break;

			case SHOW_TIME:
				break;

			default:
				break;
			}
		}
	}
}

void set_image(INT8U image)
{
	for(int i = 0; i < 36; i++)
	{
		current_image[i] = image_buffer[image][i];
	}
}
/****************************** End Of Module *******************************/
