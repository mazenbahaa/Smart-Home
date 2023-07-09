/*
 * MWDTIMER_prg.c
 *
 *  Created on: Jun 15, 2023
 *      Author: Elkhashab
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "ERROR_STATES.h"
#include "MWDTIMER_priv.h"
#include "MWDTIMER_config.h"
#include "MWDTIMER_int.h"

ErrorState_t MWDTIMER_enEnable(void)
{
	// Set ON WDT
	SET_BIT(WDTCR_REG, WDE_BIT);

	return SUCCESS;
}

ErrorState_t MWDTIMER_enDisable(void)
{
	// Write Logical One to WDTOE and WDE
	WDTCR_REG |= (1 << WDTOE_BIT) | (1 << WDE_BIT);
	// Turn OFF WDT
	WDTCR_REG = 0x00;

	return SUCCESS;
}

ErrorState_t MWDTIMER_enSleep(u8 copy_u8TimeOut)
{
	ErrorState_t Local_enState = SUCCESS;
	if(copy_u8TimeOut >= MWDT_TIMEOUT_16_3_MS && copy_u8TimeOut <= MWDT_TIMEOUT_2_1_S)
	{
		// Step1: Apply Mask
		WDTCR_REG &= MWDT_PRESCALER_MASK;
		// Step2: Insert Value
		WDTCR_REG |= copy_u8TimeOut;
	}
	else
	{
		Local_enState = OUT_OF_RANG_ERR;
	}
	return Local_enState;
}

ErrorState_t MWDTIMER_enRefresh(void)
{
	asm("WDR");
	return SUCCESS;
}
