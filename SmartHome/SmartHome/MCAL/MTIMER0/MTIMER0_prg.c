/*
 * MTIMER0_prg.c
 *
 *  Created on: Jun 11, 2023
 *      Author: Elkhashab
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "ERROR_STATES.h"
#include "MTIMER0_priv.h"
#include "MTIMER0_config.h"
#include "MTIMER0_int.h"
#include "stdlib.h"
#include <avr/interrupt.h>


static void (*CallBackArr[2]) (void) = {NULL, NULL};
static u32 g_u32NumOfOverflows = 0;
static u8 g_u8NumOfRemaningCount = 0;
static u32 g_u32NumOfCompMatches = 0;

ErrorState_t MTIMER0_enInit(void)
{
	// Config Timer Mode
#if(MTIMER0_MODE == MTIMER0_MODE_NORMAL || MTIMER0_MODE == MTIMER0_MODE_CTC || MTIMER0_MODE == MTIMER0_MODE_FAST_PWM || MTIMER0_MODE == MTIMER0_MODE_PHASE_CORRECT_PWM)
	// Step1: Clear bits by Applying Mask
	TCCR0_REG &= MTIMER0_MODE_MASK;
	// Step2: Insert Value
	TCCR0_REG |= MTIMER0_MODE;
#else
#error("Wrong Timer0 Mode")
#endif

	// Config OC0 Wave Generation
#if(MTIMER0_OC0_MODE >= MTIMER_OC0_DISCONNECTED && MTIMER0_OC0_MODE <= MTIMER0_OC0_SH)
	TCCR0_REG &= MTIMER0_OC0_MASK;
	// Step2: Insert Value
	TCCR0_REG |= MTIMER0_OC0_MASK << MTIMER0_OC0_SH;
#else
#error("Wrong Timer0 Mode")
#endif
}

ErrorState_t MTIMER0_enStart(void)
{
#if(MTIMER0_CLK >= MTIMER0_NO_CLK && MTIMER0_CLK <= MTIMER0_EXTCLK_RISE_EDGE )
	// Step1: Clear bits by Applying Mask
	TCCR0_REG &= MTIMER0_CS_MASK;
	// Step2: Insert Value
	TCCR0_REG |= MTIMER0_CLK;
#else()
#error ("Wrong Timer0 Clock")
#endif
}

ErrorState_t MTIMER0_enStop(void)
{
	// Step1: Clear bits by Applying Mask
	TCCR0_REG &= MTIMER0_CS_MASK;
	// Step2: Insert Value
	//TCCR0_REG |= MTIMER0_NO_CLK;
}

ErrorState_t MTIMER0_enSetCallBack(u8 copy_u8IntID, void (*ptrfn) (void))
{
	ErrorState_t Local_enState = SUCCESS;

	if(ptrfn == NULL)
	{
		Local_enState = NULL_PTR_ERR;
	}
	else
	{
		switch (copy_u8IntID)
		{
		case MTIMER0_OVF_INT_ID:
			CallBackArr[0] = ptrfn;
			break;
		case MTIMER0_COM_INT_ID:
			CallBackArr[1] = ptrfn;
			break;
		default:
			Local_enState = OUT_OF_RANG_ERR;
			break;
		}

		// Second Way
		/*
		if(copy_u8IntID == MTIMER0_COM_INT_ID || copy_u8IntID == MTIMER0_OVF_INT_ID)
		{
			CallBackArr[copy_u8IntID] = ptrfn;
		}
		else
		{
			Local_enState = OUT_OF_RANG_ERR;
		}
		*/
	}
	return Local_enState;
}

ErrorState_t MTIMER0_enSetTime(u32 copy_u32DelayMS)
{
	u32 Local_u32Arr[5] = {1, 8, 64, 256, 1024};
	f32 Local_f32TickTime = (f32) Local_u32Arr[MTIMER0_CLK - 1] / FCPU;
	u32 Local_u32TotalNumberOfCounts = (copy_u32DelayMS * 1000) / Local_f32TickTime;
#if(MTIMER0_MODE == MTIMER0_MODE_NORMAL)
	g_u32NumOfOverflows = Local_u32TotalNumberOfCounts / 256;
	g_u8NumOfRemaningCount = Local_u32TotalNumberOfCounts % 256;

	if(g_u8NumOfRemaningCount != 0)
	{
		TCNT0_REG = 256 - g_u8NumOfRemaningCount;
		g_u32NumOfOverflows++;
	}
#elif(MTIMER0_MODE == MTIMER0_MODE_CTC)
	u8 Local_u8OCRValue = 255;
	while(Local_u32TotalNumberOfCounts % Local_u8OCRValue != 0)
	{
		Local_u8OCRValue--;
	}
	OCR0_REG = Local_u8OCRValue;
	g_u32NumOfCompMatches = Local_u32TotalNumberOfCounts / Local_u8OCRValue;
#endif

	return SUCCESS;
}

ErrorState_t MTIMER0_enEnableInt(u8 copy_u8IntID)
{
	ErrorState_t Local_enState = SUCCESS;

	switch (copy_u8IntID)
	{
	case MTIMER0_OVF_INT_ID:
		SET_BIT(TIMSK_REG, TOIE0_BIT);
		break;
	case MTIMER0_COM_INT_ID:
		SET_BIT(TIMSK_REG, OCIE0_BIT);
		break;
	default:
		Local_enState = OUT_OF_RANG_ERR;
		break;
	}

	return Local_enState;
}

ErrorState_t MTIMER0_enDisableInt(u8 copy_u8IntID)
{
	ErrorState_t Local_enState = SUCCESS;

	switch (copy_u8IntID)
	{
	case MTIMER0_OVF_INT_ID:
		CLR_BIT(TIMSK_REG, TOIE0_BIT);
		break;
	case MTIMER0_COM_INT_ID:
		CLR_BIT(TIMSK_REG, OCIE0_BIT);
		break;
	default:
		Local_enState = OUT_OF_RANG_ERR;
		break;
	}

	return Local_enState;
}

ErrorState_t MTIMER0_enSetCompareValue(u8 copy_u8Value)
{
	OCR0_REG = copy_u8Value;

	return SUCCESS;
}


// For PWM
#if(MTIMER0_MODE == MTIMER0_MODE_FAST_PWM)
ErrorState_t MTIMER0_enSetFastPWM(u8 copy_u8Duty)
{
	ErrorState_t Local_enState = SUCCESS;
	if(copy_u8Duty >= 0 && copy_u8Duty <= 100)
	{
#if(MTIMER0_OC0_MODE == MTIMER0_OC0_NONINVERTED)
		OCR0_REG = abs(((copy_u8Duty * 256) / 100) - 1);
#elif(MTIMER0_OC0_MODE == MTIMER0_OC0_INVERTED)
		OCR0_REG = abs(255 - ((copy_u8Duty * 256) / 100));
#else
	#error("Wrong Fast PWM OC0 Mode")
#endif
	}
	else
	{
		Local_enState = OUT_OF_RANG_ERR;
	}
	return SUCCESS;
}

#elif(MTIMER0_MODE == MTIMER0_MODE_PHASE_CORRECT_PWM)
ErrorState_t MTIMER0_enPhaseCorrectPWM(u8 copy_u8Duty)
{
	ErrorState_t Local_enState = SUCCESS;
	if (copy_u8Duty >= 0 && copy_u8Duty <= 100)
	{
#if(MTIMER0_OC0_MODE == MTIMER0_OC0_NONINVERTED)
		OCR0_REG = ((copy_u8Duty * 255) / 100);
#elif(MTIMER0_OC0_MODE == MTIMER0_OC0_INVERTED)
			OCR0_REG = 255 - ((copy_u8Duty * 255) / 100);
	#else
		#error("Wrong PHASE CORRECT PWM OC0 Mode")
	#endif
	}
	else
	{
		Local_enState = OUT_OF_RANG_ERR;
	}
	return SUCCESS;
}
#endif

ISR(TIMER0_OVF_vect)
{
	static u32 Local_u32NumOfCounts = 0;
	Local_u32NumOfCounts++;	// Increment Number of Counts Every Time ISR Happens

	// If Number of Counts Equals to global Required Number of Overflows
	if(Local_u32NumOfCounts == g_u32NumOfOverflows)
	{
		// Preload TCNT with the Fraction Part
		TCNT0_REG = 256 - g_u8NumOfRemaningCount;

		// Take Action
		if (CallBackArr[MTIMER0_OVF_INT_ID] != NULL)
		{
			CallBackArr[MTIMER0_OVF_INT_ID]();
		}

		// Reset the Local Counter for the New Period
		Local_u32NumOfCounts = 0;
	}
}

ISR(TIMER0_COMP_vect)
{
	static u32 Local_u32NumOfCounts = 0;
	Local_u32NumOfCounts++;
	if(Local_u32NumOfCounts == g_u32NumOfCompMatches)
	{
		Local_u32NumOfCounts = 0;
		if (CallBackArr[MTIMER0_COM_INT_ID] != NULL)
		{
			CallBackArr[MTIMER0_COM_INT_ID]();
		}
	}
}
