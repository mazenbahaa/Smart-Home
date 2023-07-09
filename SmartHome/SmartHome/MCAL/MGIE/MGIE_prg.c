/*
 * MGIE_prg.c
 *
 *  Created on: Jun 7, 2023
 *      Author: Elkhashab
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "ERROR_STATES.h"
#include "MGIE_priv.h"
#include "MGIE_config.h"
#include "MGIE_int.h"

ErrorState_t MGIE_enEnable(void)
{
	// SET_BIT(SREG_REG, I_BIT)
	asm("SEI");
	return SUCCESS;
}

ErrorState_t MGIE_enDiable(void)
{
	// CLR_BIT(SREG_REG, I_BIT)
	asm("CLI");
	return SUCCESS;
}
