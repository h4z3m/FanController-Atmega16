/******************************************************************************
 *
 * Module: DC Motor
 *
 * File Name: dc_motor.c
 *
 * Description: Source file for DC Motor driver
 *
 * Date Created: 6/10/2021
 *
 * Author: Hazem Montasser
 *
 *******************************************************************************/

#include "dc_motor.h"
#include "common_macros.h"
#include <avr/io.h>

/*******************************************************************************
 *                          Global Variables                                   *
 *******************************************************************************/
volatile uint8 g_DCMotor_current_speed = 0;
/*******************************************************************************
 *                          Functions Definitions                              *
 *******************************************************************************/

void PWM_Timer0_Start(uint8 duty_cycle) {
	TCNT0=0;
	TCCR0 = 0;
	/*
	 * WGM0:1 = 1 ---> Fast PWM mode
	 * COM01  = 1 ---> Non-inverting PWM mode
	 * CS01   = 1 ---> Pre-scaler = FCPU/8
	 *
	 * */
	OCR0 = (uint8) (((float) duty_cycle / 100.0) * (TIMER0_TOP_VALUE));
	TCCR0 = (1 << WGM00) | (1 << WGM01) | (1 << COM01) | (1 << CS01);
}
void DcMotor_Init(void) {
	/* Setup control pins */
	GPIO_setupPinDirection(DCMOTOR_PORT_PWM, DCMOTOR_ENA_PIN, PIN_OUTPUT);
	GPIO_setupPinDirection(DCMOTOR_PORT_CTRL, DCMOTOR_IN1_PIN, PIN_OUTPUT);
	GPIO_setupPinDirection(DCMOTOR_PORT_CTRL, DCMOTOR_IN2_PIN, PIN_OUTPUT);
	/* Turn off motor initially */
	GPIO_writePin(DCMOTOR_PORT_PWM, DCMOTOR_ENA_PIN, LOGIC_LOW);
	GPIO_writePin(DCMOTOR_PORT_CTRL, DCMOTOR_IN1_PIN, LOGIC_LOW);
	GPIO_writePin(DCMOTOR_PORT_CTRL, DCMOTOR_IN2_PIN, LOGIC_LOW);
}

void DcMotor_Rotate(DcMotor_State state, uint8 speed) {
	/* Calculate duty cycle: 0-100 %*/
	uint8 duty_cycle = ((float) speed / DCMOTOR_MAX_SPEED) * 100;
	/* Set rotation direction on IN1, IN2 pins*/
	GPIO_writePin(DCMOTOR_PORT_CTRL, DCMOTOR_IN1_PIN, (state & 0x01) >> 0);
	GPIO_writePin(DCMOTOR_PORT_CTRL, DCMOTOR_IN2_PIN, (state & 0x02) >> 1);
	g_DCMotor_current_speed = speed;
	/* Generate PWM signal */
	PWM_Timer0_Start(duty_cycle);
}
