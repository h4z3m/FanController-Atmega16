/******************************************************************************
 *
 * Module: LM35 Sensor
 *
 * File Name: lm35_sensor.c
 *
 * Description: Source file for LM35 Sensor driver
 *
 * Date Created: 3/10/2021
 *
 * Author: Hazem Montasser
 *
 *******************************************************************************/

#include "lm35_sensor.h"
#include "adc.h"
#include "util/delay.h"
uint8 LM35_getTemperature(void) {
	uint8 temp = 0;
#if (ADC_CONVERSION_MODE==POLL)
	uint16 ADC_out = ADC_readChannel_poll(SENSOR_CHANNEL);
	/* Delay slightly to allow ADC conversion to complete */
	_delay_ms(10);
	temp = (uint8) (((uint32) ADC_out * SENSOR_MAX_TEMPERATURE
			* ADC_REF_VOLT_VALUE) / (ADC_MAXIMUM_VALUE * SENSOR_MAX_VOLTAGE));

#elif (ADC_CONVERSION_MODE==INTERRUPT)
	ADC_readChannel_interrupt(SENSOR_CHANNEL);
	/* Delay slightly to allow ADC conversion to complete */
	_delay_ms(10);
	temp = (uint8) (((uint32) g_ADC_conversionResult * SENSOR_MAX_TEMPERATURE
			* ADC_REF_VOLT_VALUE) / (ADC_MAXIMUM_VALUE * SENSOR_MAX_VOLTAGE));

#endif
	return temp;
}

