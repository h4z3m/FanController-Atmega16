/******************************************************************************
 *
 * Module: ADC
 *
 * File Name: adc.c
 *
 * Description: Source file for ADC driver
 *
 * Date Created: 2/10/2021
 *
 * Author: Hazem Montasser
 *
 *******************************************************************************/

#include "adc.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include "common_macros.h"

/*******************************************************************************
 *                          Global Variables                                   *
 *******************************************************************************/
volatile uint16 g_ADC_conversionResult = 0;
static volatile void (*g_ADC_callBackNotif)(void) = NULL_PTR;

/*******************************************************************************
 *                          ISR's Definitions                                  *
 *******************************************************************************/

ISR(ADC_vect) {
	if (g_ADC_callBackNotif != NULL_PTR) {
		(*g_ADC_callBackNotif)();
	}
	g_ADC_conversionResult = ADC;
}

/*******************************************************************************
 *                          Functions Definitions                              *
 *******************************************************************************/

void ADC_init(ADC_ConfigType *ADC_Config) {
	ADMUX = 0x00;

	/* Configure ADC Vref */
	ADMUX = (ADMUX & 0x3F) | (((ADC_Config->Vref) & 0x03) << 6);

	/* ADC Enable */
	SET_BIT(ADCSRA, ADEN);

	/* Enable/disable ADC interrupt */
	ADCSRA = (ADCSRA & 0xF7) | ((ADC_Config->InterruptEnable) << ADIE);

	/* Set pre-scaler */
	ADCSRA = (ADCSRA & 0xF8) | ((ADC_Config->Prescaler) & 0x07);

	/* Enable/disable auto trigger*/
	ADC_Config->AutoTrigger ? SET_BIT(ADCSRA, ADATE) : CLEAR_BIT(ADCSRA, ADATE);
}

uint16 ADC_readChannel_poll(uint8 a_channelNumber) {

	/*Insert first 3 bits in channel number in ADMUX*/
	ADMUX = (ADMUX & ADC_MODE) | (a_channelNumber & 0x07);

	/* Start conversion */
	SET_BIT(ADCSRA, ADSC);

	while (BIT_IS_CLEAR(ADCSRA, ADIF)) {
		/*Poll for ADIF flag = 1*/
	}

	/*Clear ADC interrupt flag by writing 1 to the bit*/
	SET_BIT(ADCSRA, ADIF);

	/* Return conversion result from ADC register*/
	g_ADC_conversionResult = ADC;
	return ADC;
}

void ADC_readChannel_interrupt(uint8 a_channelNumber) {
	/*Insert first 3 bits in channel number in ADMUX*/
	ADMUX = (ADMUX & ADC_MODE) | (a_channelNumber & 0x07);

	/* Start conversion */
	SET_BIT(ADCSRA, ADSC);
}

uint16 ADC_returnADC(void) {
	return ADC;
}

void ADC_setCallbackNotification(void (*a_Callback_Ptr)(void)) {
	g_ADC_callBackNotif = a_Callback_Ptr;
}

void ADC_DeInit(void) {
	ADMUX = 0;
	ADCSRA = 0;
	ADC = 0;
}

