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
#include "semphr.h"


// ------------------------
#include "Modules/LCD/lcd.h"
#include "Modules/GPIO/GPIO.h"
#include "Numpad/Numpad.h"
#include "UART0/uart0_tx.h"
#include "UART0/uart0_rx.h"
#include "LCD/lcd.h"
//#include "GPIO/GPIO.h"
//#include "GUI/gui.h"
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
// Queues
xQueueHandle uart0_rx_queue;
xQueueHandle uart0_tx_queue;

xQueueHandle LCD_image_queue;
xQueueHandle GUI_queue;
xQueueHandle LCD_char_queue;

// semaphores
xSemaphoreHandle uart0_tx_semaphore;

/*****************************   Functions   *******************************/


static void setupHardware(void)
{
  // put inits here
  SysTick_init();

}

int main(void)
{
	// Perform all init functions
	setupHardware();


	// Create all queues
	uart0_rx_queue = 	xQueueCreate(128,sizeof(INT8U));
	uart0_tx_queue = 	xQueueCreate(128,sizeof(INT8U));

	LCD_image_queue = 	xQueueCreate(3, sizeof(INT8U[36]));
	LCD_char_queue = 	xQueueCreate(16, sizeof(INT8U));
	GUI_queue = 		xQueueCreate(16, sizeof(INT8U));

	// create all semaphores
	uart0_tx_semaphore = xSemaphoreCreateMutex();

	// Variable used to check if all tasks has been created correcty
	portBASE_TYPE return_value = pdTRUE;


	// Start the tasks defined within this file
	return_value &= xTaskCreate( status_led_task, ( signed portCHAR * ) "Status_led", USERTASK_STACK_SIZE, NULL, LOW_PRIO, NULL );


	// uart0 tasks
	return_value &= xTaskCreate( uart0_rx_task, ( signed portCHAR *) "uart0_rx_task", USERTASK_STACK_SIZE, NULL, LOW_PRIO, NULL);
	return_value &= xTaskCreate( uart0_tx_task, ( signed portCHAR *) "uart0_tx_task", USERTASK_STACK_SIZE, NULL, LOW_PRIO, NULL);


	// ps2controller
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