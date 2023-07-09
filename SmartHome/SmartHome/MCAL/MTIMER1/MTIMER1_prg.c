/*
 * MTIMER1_prg.c
 *
 *  Created on: Jun 13, 2023
 *      Author: Elkhashab
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "ERROR_STATES.h"
#include "MTIMER1_config.h"
#include "MTIMER1_priv.h"
#include "MTIMER1_int.h"
#include <avr/interrupt.h>

static void (*CallBackPTR) (void) = NULL;

static void (*g_ICU_CallBackPTR) (void) = NULL;

ErrorState_t MTIMER1_enInit(void)
{
	// Choose Mode to be Normal Mode
	CLR_BIT(TCCR1A_REG, WGM10_BIT);
	CLR_BIT(TCCR1A_REG, WGM11_BIT);

	CLR_BIT(TCCR1B_REG, WGM12_BIT);
	CLR_BIT(TCCR1B_REG, WGM13_BIT);
}

ErrorState_t MTIMER1_enStart(void)
{
#if(MTIMER1_CLK >= MTIMER1_NO_CLK && MTIMER1_CLK <= MTIMER1_EXTCLK_RISE_EDGE )
	// Step1: Clear bits by Applying Mask
	TCCR1B_REG &= MTIMER1_CS_MASK;
	// Step2: Insert Value
	TCCR1B_REG |= MTIMER1_CLK;
#else
#error ("Wrong Timer1 Clock")
#endif
}

ErrorState_t MTIMER1_enStop(void)
{
	// Step1: Clear bits by Applying Mask
	TCCR1B_REG &= MTIMER1_CS_MASK;
	// Step2: Insert Value
	//TCCR1B_REG |= MTIMER1_NO_CLK;
}

ErrorState_t MTIMER1_enSetCallBack(void (*ptrfn) (void))
{
	ErrorState_t Local_enState = SUCCESS;

	if (ptrfn == NULL)
	{
		Local_enState = NULL_PTR_ERR;
	}
	else
	{
		CallBackPTR = ptrfn;
	}
}

ErrorState_t MTIMER1_enEnableInt(void)
{
	ErrorState_t Local_enState = SUCCESS;

	SET_BIT(TIMSK_REG, TOIE1_BIT);

	return Local_enState;
}

ErrorState_t MTIMER1_enDisableInt(void)
{
	ErrorState_t Local_enState = SUCCESS;

	CLR_BIT(TIMSK_REG, TOIE1_BIT);

	return Local_enState;
}


ErrorState_t MTIMER1_ICU_enInit(void)
{
	MTIMER1_ICU_enSetTrigger(MTIMER1_ICU_RISE_EDGE_TRIG);
}

ErrorState_t MTIMER1_ICU_enEnableInt(void)
{
	SET_BIT(TIMSK_REG, TICIE1_BIT);
}

ErrorState_t MTIMER1_ICU_enDisableInt(void)
{
	CLR_BIT(TIMSK_REG, TICIE1_BIT);
}

ErrorState_t MTIMER1_ICU_enSetCallBack(void (*ptrfn) (void))
{
	ErrorState_t Local_enState = SUCCESS;
	if(ptrfn != NULL)
	{
		g_ICU_CallBackPTR = ptrfn;
	}
	else
	{
		Local_enState = NULL_PTR_ERR;
	}
	return Local_enState;
}

ErrorState_t MTIMER1_ICU_enRead(volatile u16 *ptrReadValue)
{
	ErrorState_t Local_enState = SUCCESS;

	if(ptrReadValue != NULL)
	{
		*ptrReadValue = ICR1_REG;
	}
	else
	{
		Local_enState = NULL_PTR_ERR;
	}
	return Local_enState;
}

ErrorState_t MTIMER1_ICU_enSetTrigger(u8 copy_u8Trigg)
{
	ErrorState_t Local_enState = SUCCESS;

	switch(copy_u8Trigg)
	{
	case MTIMER1_ICU_FALL_EDGE_TRIG:
		CLR_BIT(TCCR1B_REG, ICES1_BIT);
		break;
	case MTIMER1_ICU_RISE_EDGE_TRIG:
		SET_BIT(TCCR1B_REG, ICES1_BIT);
		break;
	default:
		Local_enState = OUT_OF_RANG_ERR;
		break;
	}
	return Local_enState;
}


ISR(TIMER1_CAPT_vect)
{
	if(g_ICU_CallBackPTR != NULL)
	{
		g_ICU_CallBackPTR(); // Call Function in Higher Layer
	}
}


ISR(TIMER1_OVF_vect)
{
	if(CallBackPTR != NULL)
	{
		CallBackPTR();
	}
}

