/*
 * HDCMOTOR_prg.c
 *
 *  Created on: Jun 26, 2023
 *      Author: Elkhashab
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "ERROR_STATES.h"
#include "MDIO_int.h"
#include "HDCMOTOR_priv.h"
#include "HDCMOTOR_config.h"
#include "HDCMOTOR_init.h"


ErrorState_t HDCMOTOR_enInit(void)
{
	MDIO_setPinDirection(HDCMOTOR_PIN0, OUTPUT);
	MDIO_setPinDirection(HDCMOTOR_PIN1, OUTPUT);
}

ErrorState_t HDCMOTOR_enOFF(void)
{
	MDIO_voidSetPinValue(HDCMOTOR_PIN0, LOW);
	MDIO_voidSetPinValue(HDCMOTOR_PIN1, LOW);
}

ErrorState_t HDCMOTOR_enCLK_Wise(void)
{
	MDIO_voidSetPinValue(HDCMOTOR_PIN0, LOW);
	MDIO_voidSetPinValue(HDCMOTOR_PIN1, HIGH);
}

ErrorState_t HDCMOTOR_enCLK_Anti_Wise(void)
{
	MDIO_voidSetPinValue(HDCMOTOR_PIN0, HIGH);
	MDIO_voidSetPinValue(HDCMOTOR_PIN1, LOW);
}
