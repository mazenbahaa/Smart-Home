/*
 * MADC_prg.c
 *
 *  Created on: Jun 26, 2023
 *      Author: Elkhashab
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "ERROR_STATES.h"
#include "MADC_priv.h"
#include "MADC_config.h"
#include "MADC_init.h"
#include <avr/interrupt.h>

u16 gADC_Value = 0;

ErrorState_t MADC_enInit(void)
{
#if ADC_VREF == AVCC
	SET_BIT(ADMUX_REG, REFS0_BIT);
	CLR_BIT(ADMUX_REG, REFS1_BIT);
#elif ADC_VREF == AREF_PIN
	CLR_BIT(ADMUX_REG, REFS0_BIT);
	CLR_BIT(ADMUX_REG, REFS1_BIT);
#elif ADC_VREF == _2V5
	SET_BIT(ADMUX_REG, REFS0_BIT);
	SET_BIT(ADMUX_REG, REFS1_BIT);
#endif

	// To Select Right Adjust
	CLR_BIT(ADMUX_REG, ADLAR_BIT);
#if ADC_PRESCALER_DV == 128
	SET_BIT(ADCSRA_REG, ADPS0_BIT);
	SET_BIT(ADCSRA_REG, ADPS1_BIT);
	SET_BIT(ADCSRA_REG, ADPS2_BIT);
#elif ADC_PRESCALER_DV == 64
	CLR_BIT(ADCSRA_REG, ADPS0_BIT);
	SET_BIT(ADCSRA_REG, ADPS1_BIT);
	SET_BIT(ADCSRA_REG, ADPS2_BIT);
#endif

	// Enable Auto Trigger Mode
	SET_BIT(ADCSRA_REG, ADATE_BIT);

	// Enable ADC Circuit
	SET_BIT(ADCSRA_REG, ADEN_BIT);

	// To Start Conversion
	SET_BIT(ADCSRA_REG, ADSC_BIT);

	// New For ISR
	SET_BIT(ADCSRA_REG, 3); // Enable Interrupt
	ADMUX_REG = ADMUX_REG & 0xE0;
	ADMUX_REG = ADMUX_REG | 0;
}

ErrorState_t MADC_enRead(u8 copy_u8Channel)
{
	u32 Local_u32Counter = 0;
	ADMUX_REG = ADMUX_REG & 0xE0;
	ADMUX_REG = ADMUX_REG | copy_u8Channel;

	while(Local_u32Counter < 2000000)
	{
		Local_u32Counter++;

		if(GET_BIT(ADCSRA_REG, ADIF_BIT) == ADC_CONVERSION_COMPLETE)
		{
			break;
		}
	}
	return ADCVALUE;
}

ISR(ADC_vect)
{
	SET_BIT(ADCSRA_REG, ADSC_BIT);

	// Put ADC Reading in a Global Variable
	gADC_Value = ADCVALUE;
}
