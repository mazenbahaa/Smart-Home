/*
 * MEXTI_prg.c
 *
 *  Created on: Jun 7, 2023
 *      Author: Elkhashab
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "ERROR_STATES.h"
#include "MEXTI_priv.h"
#include "MEXTI_config.h"
#include "MEXTI_int.h"
#include <avr/interrupt.h>

static void (*CallBackArr[3]) (void) = {NULL, NULL, NULL};

ErrorState_t MEXTI_enEnable(InterruptID_t copy_enID, IntTrigger_t copy_enTrig)
{
	// Config Trigger
	ErrorState_t Local_enState = SUCCESS;
	if(copy_enTrig > RAIS_EDGE_TRIG || copy_enTrig < LOW_LEVEL_TRIG)
	{
		Local_enState = OUT_OF_RANG_ERR;
	}
	else
	{
		switch (copy_enID)
		{
		case INT0_ID:
			// Apply Mask
			MCUCR_REG &= INT0_SC_MASK;

			// Insert Value
			MCUCR_REG |= copy_enTrig;
			break;

		case INT1_ID:
			// Apply Mask
			MCUCR_REG &= INT1_SC_MASK;

			// Insert Value
			MCUCR_REG |= copy_enTrig << INT1_SC_SH;
			break;

		case INT2_ID:
			CLR_BIT(MCUCSR_REG, ISC2_BIT);
			MCUCSR_REG |= GET_BIT(copy_enTrig, 0) << ISC2_BIT;
			break;

		default:
			Local_enState = OUT_OF_RANG_ERR;
		}
		// Enable Special Key
		SET_BIT(GICR_REG, copy_enID);
	}

}

ErrorState_t MEXTI_enDisable(InterruptID_t copy_enID)
{
	ErrorState_t Local_enState = SUCCESS;
	if(copy_enID >= INT2_ID && copy_enID <= INT1_ID)
	{
		CLR_BIT(GICR_REG, copy_enID);
	}
	else
	{
		Local_enState = OUT_OF_RANG_ERR;
	}
	return Local_enState;
}

ErrorState_t MEXTI_ensetCallBack(InterruptID_t copy_enID, void (*ptrfn)(void))
{
	ErrorState_t Local_enState = SUCCESS;
	if(ptrfn == NULL)
	{
		Local_enState = NULL_PTR_ERR;
	}
	else
	{
		switch (copy_enID)
		{
		case INT0_ID:
			CallBackArr[0] = ptrfn;
			break;
		case INT1_ID:
			CallBackArr[1] = ptrfn;
			break;
		case INT2_ID:
			CallBackArr[2] = ptrfn;
			break;
		default:
			Local_enState = OUT_OF_RANG_ERR;
			break;
		}
	}
	return Local_enState;
}

ISR(INT0_vect)
{
	if(CallBackArr[0] != NULL)
	{
		CallBackArr[0]();
	}
}

ISR(INT1_vect)
{
	if (CallBackArr[1] != NULL)
	{
		CallBackArr[1]();
	}
}

ISR(INT2_vect)
{
	if (CallBackArr[2] != NULL)
	{
		CallBackArr[2]();
	}
}
