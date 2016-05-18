/*****************************************************************************
* University of Southern Denmark
* Embedded C Programming (ECP)
*
* MODULENAME.: tmodel.h
*
* PROJECT....: ECP
*
* DESCRIPTION: Defines the elemtn of the task model..
*
* Change Log:
******************************************************************************
* Date    Id    Change
* YYMMDD
* --------------------
* 101004  MoH   Module created.
*
*****************************************************************************/

#ifndef _TMODEL_H_
#define _TMODEL_H_

// position parameters
#define SSM_CURRENT_PAN		0
#define SSM_CURRENT_TILT	1
#define SSM_TARGET_PAN		2
#define SSM_TARGET_TILT		3

//scene dimentions
#define SSM_HEIGHT			10
#define SSM_WIDTH			11
#define SSM_DEPTH			12

// instructions
#define SSM_OPCODE			20
#define SSM_PARAM_1			21
#define SSM_PARAM_2			22

// movement constraints
#define SSM_MIN_PAN_VEL		30
#define SSM_MAX_PAN_VEL		31
#define SSM_MIN_TILT_VEL	32
#define SSM_MAX_TILT_VEL	33


// system enables
#define SSM_FPGA_ENABLE		40
#define SSM_LIGHT_ENABLE	41
#define SSM_JOYSTICK_ENABLE 42


// lightshow
#define SSM_LIGHTSHOW		50




#endif /* _TMODEL_H_ */
