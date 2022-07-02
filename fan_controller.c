/******************************************************************************
 *
 * Module: DC Motor
 *
 * File Name: fan_controller.c
 *
 * Description: Source file for the application code which controls the fan
 * using LM35 sensor, ADC, DC Motor & LCD drivers
 *
 * Date Created: 6/10/2021
 *
 * Author: Hazem Montasser
 *
 *******************************************************************************/

#include "lcd.h"
#include "adc.h"
#include "lm35_sensor.h"
#include "dc_motor.h"
#include <util/delay.h>

/* Temperature calculated by LM35 driver */
uint16 g_ambient_temperature = 0;

/* Enum for fan state */
typedef enum {
	OFF, ON
} Fan_State;
Fan_State g_fan_state = OFF;

void APP_FAN_processTemp(uint16 temperature) {
	/*To avoid useless function calls as long as the temperature is still in the same range
	 * and to maintain constant voltage at 100% duty cycle*/
	static uint8 flag = 0;

	if (temperature < 30 && flag != 1) {
		flag = 1;
		DcMotor_Rotate(STOP, 0);
		g_fan_state = OFF;
	} else if (temperature >= 30 && temperature < 60 && flag != 2) {
		flag = 2;
		DcMotor_Rotate(CW, 25);
		g_fan_state = ON;
	} else if (temperature >= 60 && temperature < 90 && flag != 3) {
		flag = 3;
		DcMotor_Rotate(CW, 50);
		g_fan_state = ON;
	} else if (temperature >= 90 && temperature < 120 && flag != 4) {
		flag = 4;
		DcMotor_Rotate(CW, 75);
		g_fan_state = ON;
	} else if (temperature >= 120 && flag != 5) {
		flag = 5;
		DcMotor_Rotate(CW, 100);
		g_fan_state = ON;
	}
}
int main(void) {
	/* Initialization*/

	/*ADC configuration struct: Internal 2.56v, pre-scaler = FCPU/8, no auto trigger, no interrupts */
	ADC_ConfigType ADC_CONF = { AINTERNAL, FCPU_8, FALSE, TRUE };
	/* Initialize ADC, LCD & DC motor drivers */
	ADC_init(&ADC_CONF);
	LCD_init();
	DcMotor_Init();
	/* Constant strings on the LCD screen,
	 * casting to const uint8 ptr to remove compiler warnings */
	LCD_displayStringRowColumn(LCD_ROW_0, 3, (const uint8*) "Fan is ");
	LCD_displayStringRowColumn(LCD_ROW_1, 3, (const uint8*) "Temp =    C");

	/*Super loop*/
	for (;;) {

		/* Get current temperature from LM35 Sensor*/
		g_ambient_temperature = LM35_getTemperature();

		/*Process the temperature to determine the motor speed*/
		APP_FAN_processTemp(g_ambient_temperature);

		/* Display fan state on the LCD*/
		LCD_moveCursor(LCD_ROW_0, 11);
		g_fan_state == OFF ?
				LCD_displayString((const uint8*) "OFF") :
				LCD_displayString((const uint8*) "ON ");

		/* Display the temperature on LCD*/
		LCD_moveCursor(LCD_ROW_1, 10);
		if (g_ambient_temperature >= 100) {
			LCD_integerToString(g_ambient_temperature);
		} else {
			LCD_integerToString(g_ambient_temperature);
			LCD_displayCharacter(' ');
		}

		/* Slight delay to avoid simulation lag */
		_delay_ms(5);
	}

}
