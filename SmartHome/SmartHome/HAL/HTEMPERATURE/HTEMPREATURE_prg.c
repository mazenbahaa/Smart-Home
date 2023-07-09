/*
 * HTEMPREATURE_prg.c
 *
 *  Created on: Jun 26, 2023
 *      Author: Elkhashab
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "ERROR_STATES.h"
#include "HTEMPREATURE_priv.h"
#include "HTEMPREATURE_config.h"
#include "HTEMPREATURE_init.h"

extern u16 gADC_Value;

ErrorState_t HTEMPREATURE_enInit(void)
{
	MADC_enInit();
}

ErrorState_t HTEMPREATURE_enRead(u16 *copy_u16Ptr)
{
	// for Interrupt
	static u16 prev = 0;

	if(prev !=  gADC_Value)
	{
		prev = gADC_Value;
		*copy_u16Ptr = ((u32)gADC_Value * 500 ) / 1023;
	}
}
