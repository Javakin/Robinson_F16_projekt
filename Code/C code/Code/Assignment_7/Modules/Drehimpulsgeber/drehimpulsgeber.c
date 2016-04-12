/*****************************************************************************
 * University of Southern Denmark
 * Embedded Programming (EMP)
 *
 * MODULENAME.: drehimpulsgeber.c
 *
 * PROJECT....: EMP
 *
 * DESCRIPTION: driver for the drehimpulsgeber
 *
 * Change Log:
 *****************************************************************************
 * Date    Id    Change
 * YYMMDD
 * --------------------
 * 180316	DFH 	module created
 *
 *****************************************************************************/

/***************************** Include files *******************************/
#include <stdint.h>
#include <EMP/emp_type.h>
#include <tm4c123gh6pm.h>
#include <UART/uart0.h>

/*****************************    Defines    *******************************/
#define DREHIMPULSGEBER_A		5
#define DREHIMPULSGEBER_B		6
#define DREHIMPULSGEBER_PUSH	7

#define DREH_A					1 && (GPIO_PORTA_DATA_R & (1 << DREHIMPULSGEBER_A))
#define DREH_B					1 && (GPIO_PORTA_DATA_R & (1 << DREHIMPULSGEBER_B))
#define DREH_PUSH				1 && (GPIO_PORTA_DATA_R & (1 << DREHIMPULSGEBER_PUSH))

#define CCW 					0
#define CW						1

/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/

/*****************************   Functions   *******************************/
void dreh_init(void) {
	// Enable the GPIO port that is used for Numpad
	SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOA;

	// Do a dummy read to insert a few cycles after enabling the peripheral.
	__asm("nop");

	// Set direcction
	GPIO_PORTA_DIR_R &= ~((1 << DREHIMPULSGEBER_A) | (1 << DREHIMPULSGEBER_B)
			| (1 << DREHIMPULSGEBER_PUSH));

	// digital enable
	GPIO_PORTA_DEN_R |= (1 << DREHIMPULSGEBER_A) | (1 << DREHIMPULSGEBER_B)
			| (1 << DREHIMPULSGEBER_PUSH);

	// setup af interrupt for prot A
	//NVIC_EN0_R |= 0x0000001;

	// interrupt masking
	//GPIO_PORTA_IM_R |= (1 << DREHIMPULSGEBER_A) | (1 << DREHIMPULSGEBER_B);

	// set interrupt event for DREHIMPULSGEBER_A to rising eadges
	//GPIO_PORTA_IEV_R |= (1 << DREHIMPULSGEBER_A) | (1 << DREHIMPULSGEBER_B);
}

/*
 void dreh_isr() {
 static INT8S enc_states[] = { 0, -1, 1, 0, 1, 0, 0, -1, -1, 0, 0, 1, 0, 1,
 -1, 0 };
 static INT8U old_ab = 0;

 INT8U A = DREH_A;
 INT8U B = DREH_B;

 old_ab <<= 2;
 old_ab |= ((A << 1) | B);

 INT8S val = enc_states[(old_ab & 0x0F)];

 if (val == 1) {
 uart0_putc('R');
 } else if (val == -1) {
 uart0_putc('L');
 }

 // swich toggle eadge

 if (GPIO_PORTA_MIS_R & (1 << DREHIMPULSGEBER_A)) {
 GPIO_PORTA_IEV_R ^= (1 << DREHIMPULSGEBER_A);
 } else if (GPIO_PORTA_MIS_R & (1 << DREHIMPULSGEBER_B)) {
 GPIO_PORTA_IEV_R ^= (1 << DREHIMPULSGEBER_B);
 }

 // reset interruptflag
 GPIO_PORTA_ICR_R |= (1 << DREHIMPULSGEBER_A) | (1 << DREHIMPULSGEBER_B);
 }
 */

void dreh_task(INT8U my_id, INT8U my_state, INT8U event, INT8U data)
{
	static INT8S enc_states[] = { 0, -1, 1, 0, 1, 0, 0, -1, -1, 0, 0, 1, 0, 1, -1, 0 };
	static INT8U old_ab = 0;
	static INT8U countTwo = 0;

	old_ab <<= 2;
	old_ab |= (((DREH_A) << 1) | (DREH_B));

	INT8S val = enc_states[(old_ab & 0x0F)];

	if (val != 0)
	{
		if (countTwo)
		{
			if (val == 1)
			{
				uart0_putc('R');
			}
			else if (val == -1)
			{
				uart0_putc('L');
			}
			countTwo = 0;
		}
		else
		{
			countTwo++;
		}
	}
}

/****************************** End Of Module *******************************/

