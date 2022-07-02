/******************************************************************************
 *
 * Module: LM35 Sensor
 *
 * File Name: lm35_sensor.h
 *
 * Description: Header file for LM35 Sensor driver
 *
 * Date Created: 3/10/2021
 *
 * Author: Hazem Montasser
 *
 *******************************************************************************/

#ifndef LM35_SENSOR_H_
#define LM35_SENSOR_H_
#include "std_types.h" /*To use uint8, etc...*/
/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define SENSOR_CHANNEL (2)
#define SENSOR_MAX_VOLTAGE (1.5)
#define SENSOR_MAX_TEMPERATURE (150)
#define POLL 0
#define INTERRUPT 1
#define ADC_CONVERSION_MODE POLL

/*******************************************************************************
 *                            Functions Prototypes                             *
 *******************************************************************************/

uint8 LM35_getTemperature(void);

#endif /* LM35_SENSOR_H_ */
