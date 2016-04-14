/*****************************************************************************
* University of Southern Denmark
* Embedded C Programming (ECP)
*
* MODULENAME.: leds.c
*
* PROJECT....: ECP
*
* DESCRIPTION: See module specification file (.h-file).
*
* Change Log:
******************************************************************************
* Date    Id    Change
* YYMMDD
* --------------------
* 050128  KA    Module created.
*
*****************************************************************************/

/***************************** Include files *******************************/

#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "EMP/emp_type.h"
#include "EMP/glob_def.h"
#include "FreeRTOS.h"
#include "Task.h"
#include "queue.h"
#include "semphr.h"
#include "systick.h"
#include "status_led.h"


// ------------------------
#include "Modules/LCD/lcd.h"
#include "Modules/GPIO/GPIO.h"
#include "Numpad/Numpad.h"
#include "UART/uart0.h"
#include "LCD/lcd.h"
#include "GPIO/GPIO.h"
#include "GUI/gui.h"
#include "PS2Controller/ps2controller.h"

/*****************************    Defines    *******************************/
#define USERTASK_STACK_SIZE configMINIMAL_STACK_SIZE
#define IDLE_PRIO 0
#define LOW_PRIO  1
#define MED_PRIO  2
#define HIGH_PRIO 3

/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/
volatile INT16S ticks;
xQueueHandle uart0_rx_queue;
xQueueHandle LCD_image_queue;
xQueueHandle GUI_queue;
xQueueHandle LCD_char_queue;

/*****************************   Functions   *******************************/


static void setupHardware(void)
{
  // TODO: Put hardware configuration and initialisation in here

  // Warning: If you do not initialize the hardware clock, the timings will be inaccurate
  SysTick_init();
  GPIO_init();
  UART0_init( 19200, 8, 1, 0 );
}

int main(void)
{
	// Perform all init functions
	setupHardware();


	// Create all queues
	uart0_rx_queue = 	xQueueCreate(128,sizeof(char));
	LCD_image_queue = 	xQueueCreate(3, sizeof(INT8U[36]));
	LCD_char_queue = 	xQueueCreate(16, sizeof(INT8U));
	GUI_queue = 		xQueueCreate(16, sizeof(INT8U));


	// Variable used to check if all tasks has been created correcty
	portBASE_TYPE return_value = pdTRUE;


	// Start the tasks defined within this file
	return_value &= xTaskCreate( status_led_task, ( signed portCHAR * ) "Status_led", USERTASK_STACK_SIZE, NULL, LOW_PRIO, NULL );
	//return_value &= xTaskCreate( LCD_task, ( signed portCHAR * ) "LCD", USERTASK_STACK_SIZE, NULL, LOW_PRIO, NULL );
	//return_value &= xTaskCreate( numpad_task, ( signed portCHAR * ) "Numpad", USERTASK_STACK_SIZE, NULL, LOW_PRIO, NULL );
	//return_value &= xTaskCreate( gui_task, ( signed portCHAR * ) "GUI", USERTASK_STACK_SIZE, NULL, LOW_PRIO, NULL );

	// testing task
	return_value &= xTaskCreate( ps2controller_task, ( signed portCHAR * ) "ps2controller_task", USERTASK_STACK_SIZE, NULL, LOW_PRIO, NULL );

	// Test if all tasks started sucessfully
	if (return_value != pdTRUE)
	{
		// failed to start all tasks
		GPIO_PORTD_DATA_R &= 0xBF;  // Turn on status LED.
		while(1);  // cold not create one or more tasks.
	}


	// Start the scheduler.
	vTaskStartScheduler();


	// Will only get here if there was insufficient memory to create the idle task.

  return 1;
}
