/******************************************************************************
 *
 * Module: DC Motor
 *
 * File Name: dc_motor.h
 *
 * Description: Header file for DC Motor driver
 *
 * Date Created: 6/10/2021
 *
 * Author: Hazem Montasser
 *
 *******************************************************************************/

#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_
#include "std_types.h"	/* To use uint8, etc...*/
#include "gpio.h"		/* For port & pins definitions */

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define DCMOTOR_MAX_SPEED 100		/* Max speed for the motor, max allowed value = 255 */
#define DCMOTOR_PORT_PWM PORTB_ID	/* Port which has ENA connected: MUST HAVE AN OC PIN */
#define DCMOTOR_PORT_CTRL PORTB_ID	/* Port which has IN1&IN2 connected */

#define DCMOTOR_IN1_PIN	PIN1_ID
#define DCMOTOR_IN2_PIN PIN2_ID
#define DCMOTOR_ENA_PIN PIN3_ID

#define TIMER0_TOP_VALUE (0xFF)

/******************************************************************************
 *                      External Variables                                    *
 *******************************************************************************/

extern volatile uint8 g_DCMotor_current_speed;

/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/

/* Enum for H-Bridge modes: Stop rotation, clockwise & anti-clockwise */
typedef enum {
	STOP, /*00*/
	CW, /*01*/
	ACW /*10*/
} DcMotor_State;

/*******************************************************************************
 *                     			 Functions Prototypes                          *
 *******************************************************************************/

/******************************************************************************
 *
 * Function Name: DcMotor_Init
 *
 * Description:  Initializing function for the output pins of the motor:
 * 					ENA,IN1,IN2.
 * Args: void
 * Returns: void
 *******************************************************************************/
void DcMotor_Init(void);

/******************************************************************************
 *
 * Function Name: DcMotor_Rotate
 *
 * Description:  Changes motor direction & speed by using Timer0 PWM.
 *
 * Args:
 *
 * 		[in] -DcMotor_State state
 * 		Enum type for the motor state.
 * 			 -uint8 speed
 *		Motor speed, max speed specified in header file.
 * 		[out] N/A
 *
 * Returns: void
 *
 *******************************************************************************/
void DcMotor_Rotate(DcMotor_State state, uint8 speed);

#endif /* DC_MOTOR_H_ */
