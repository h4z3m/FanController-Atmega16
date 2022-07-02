/******************************************************************************
 *
 * Module: ADC
 *
 * File Name: adc.h
 *
 * Description: Header file for ADC driver
 *
 * Date Created: 2/10/2021
 *
 * Author: Hazem Montasser
 *
 *******************************************************************************/

#ifndef ADC_H_
#define ADC_H_

#include "std_types.h" /*To use uint8, etc...*/

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define ADC_MODE_00000 (0xE0) /* ADC0 single-ended input MUX mode*/
#define ADC_MODE_00001 (0xE1) /* ADC1 single-ended input MUX mode*/
#define ADC_MODE_00010 (0xE2) /* ADC2 single-ended input MUX mode*/
#define ADC_MODE_00011 (0xE3) /* ADC3 single-ended input MUX mode*/
#define ADC_MODE_00100 (0xE4) /* ADC4 single-ended input MUX mode*/
#define ADC_MODE_00101 (0xE5) /* ADC5 single-ended input MUX mode*/
#define ADC_MODE_00110 (0xE6) /* ADC6 single-ended input MUX mode*/
#define ADC_MODE_00111 (0xE7) /* ADC7 single-ended input MUX mode*/

#define ADC_MODE_01000 (0xE8) /* ADC0, ADC0 Differential input MUX mode 10x*/
#define ADC_MODE_01001 (0xE9) /* ADC1, ADC0 Differential input MUX mode 10x*/
#define ADC_MODE_01010 (0xEA) /* ADC0, ADC0 Differential input MUX mode 200x*/
#define ADC_MODE_01011 (0xEB) /* ADC1, ADC0 Differential input MUX mode 200x*/
#define ADC_MODE_01100 (0xEC) /* ADC2, ADC2 Differential input MUX mode 10x*/
#define ADC_MODE_01101 (0xED) /* ADC3, ADC2 Differential input MUX mode 10x*/
#define ADC_MODE_01110 (0xEE) /* ADC2, ADC2 Differential input MUX mode 200x*/
#define ADC_MODE_01111 (0xEF) /* ADC3, ADC2 Differential input MUX mode 200x*/

#define ADC_MODE_10000 (0xF0) /* ADC0, ADC1 Differential input MUX mode*/
#define ADC_MODE_10001 (0xF1) /* ADC1, ADC1 Differential input MUX mode*/
#define ADC_MODE_10010 (0xF2) /* ADC2, ADC1 Differential input MUX mode*/
#define ADC_MODE_10011 (0xF3) /* ADC3, ADC1 Differential input MUX mode*/
#define ADC_MODE_10100 (0xF4) /* ADC4, ADC1 Differential input MUX mode*/
#define ADC_MODE_10101 (0xF5) /* ADC5, ADC1 Differential input MUX mode*/
#define ADC_MODE_10110 (0xF6) /* ADC6, ADC1 Differential input MUX mode*/
#define ADC_MODE_10111 (0xF7) /* ADC7, ADC1 Differential input MUX mode*/
#define ADC_MODE_11000 (0xF8) /* ADC0, ADC2 Differential input MUX mode*/
#define ADC_MODE_11001 (0xF9) /* ADC1, ADC2 Differential input MUX mode*/
#define ADC_MODE_11010 (0xFA) /* ADC2, ADC2 Differential input MUX mode*/
#define ADC_MODE_11011 (0xFB) /* ADC3, ADC2 Differential input MUX mode*/
#define ADC_MODE_11100 (0xFC) /* ADC4, ADC2 Differential input MUX mode*/

#define ADC_MODE ADC_MODE_00000 /* Select from the above modes here. */

#define ADC_MAXIMUM_VALUE (1023)
#define ADC_REF_VOLT_VALUE (2.56)
/******************************************************************************
 *                      External Variables                                    *
 *******************************************************************************/

extern volatile uint16 g_ADC_conversionResult; /* Contains ADC conversion result */

/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/

/* Enum for ADC voltage input */
typedef enum {
	AREF, /* From AREF PIN */
	AVCC, /* Shares AVCC   */
	AINTERNAL = 3 /* Internal 2.56v*/
} ADC_Voltage;

/*Enum for ADC pre-scaler, ADC frequency input must be 50-200KHz*/
typedef enum {
	FCPU_2_, FCPU_2, FCPU_4, FCPU_8, FCPU_16, FCPU_32, FCPU_64, FCPU_128
} ADC_Clock;

/******************************************************************************
 *
 * Structure Name: ADC_ConfigType
 *
 * Structure Description:  Structure responsible for holding ADC initialization
 * variables which will be passed to ADC_init() function.
 *
 *******************************************************************************/
typedef struct {
	ADC_Voltage Vref;
	ADC_Clock Prescaler;
	boolean AutoTrigger;
	boolean InterruptEnable;
} ADC_ConfigType;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/******************************************************************************
 *
 * Function Name: ADC_init
 *
 * Description:  Function responsible for initializing ADC module with the
 * specified configurations passed to ADC_Config struct.
 *
 * Args:
 *
 * 		[in] ADC_ConfigType *a_ADC_Config
 * 			Contains Vref, Pre-scaler & interrupt enable settings
 * 		[out] N/A
 *
 * Returns: void
 *
 *******************************************************************************/
void ADC_init(ADC_ConfigType *ADC_Config);

/******************************************************************************
 *
 * Function Name: ADC_readChannel_poll
 *
 * Description: Starts conversion on the given channel number and polls
 * until conversion is fully complete then returns the ADC register result while
 * clearing the ADIF flag.
 *
 * Args:
 *
 * 		[in] uint8 a_channelNumber
 *			Channel number for the ADC (must be 0-7)
 * 		[out] N/A
 *
 * Returns: uint16
 *
 *******************************************************************************/
uint16 ADC_readChannel_poll(uint8 a_channelNumber);

/******************************************************************************
 *
 * Function Name: ADC_readChannel_interrupt
 *
 * Description:  Starts conversion on the given channel number.
 * Only use with interrupt enabled and expect ADC output on g_ADC_conversionResult.
 *
 * Args:
 *
 * 		[in] uint8 a_channelNumber
 *			Channel number for the ADC (must be 0-7)
 * 		[out] N/A
 *
 * Returns: void
 *
 *******************************************************************************/
void ADC_readChannel_interrupt(uint8 a_channelNumber);

/******************************************************************************
 *
 * Function Name: ADC_returnADC
 *
 * Description:  Returns ADC register conversion result.
 *
 * Args: void
 *
 * Returns: uint16
 *******************************************************************************/
uint16 ADC_returnADC(void);

/******************************************************************************
 *
 * Function Name: ADC_setCallbackNotification
 *
 * Description:  Sets the callback notification function to be called when/if
 * an ADC interrupt occurs.
 *
 * Args:
 *
 * 		[in] void (*a_Callback_Ptr)(void)
 * 			Pointer to the input callback function.
 * 		[out] N/A
 *
 * Returns: void
 *
 *******************************************************************************/
void ADC_setCallbackNotification(void (*a_ptrToCallback)(void));

/******************************************************************************
 *
 * Function Name: ADC_DeInit
 *
 * Description:  Disables the ADC module and resets its related registers.
 *
 * Args: void
 *
 * Returns: void
 *******************************************************************************/
void ADC_DeInit(void);

#endif /* ADC_H_ */
