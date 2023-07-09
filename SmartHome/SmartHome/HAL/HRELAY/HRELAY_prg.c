/*
 * HRELAY_prg.c
 *
 *  Created on: Jun 26, 2023
 *      Author: Elkhashab
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "ERROR_STATES.h"
#include "MDIO_int.h"
#include "HRELAY_priv.h"
#include "HRELAY_config.h"
#include "HRELAY_init.h"
#include <avr/delay.h>

ErrorState_t HRELAY_enInit(void)
{
	MDIO_setPinDirection(HRELAY_1_PIN, OUTPUT);
	MDIO_setPinDirection(HRELAY_2_PIN, OUTPUT);
}

ErrorState_t HRELAY_enON(void)
{
	MDIO_voidSetPinValue(HRELAY_1_PIN, HIGH);
	MDIO_voidSetPinValue(HRELAY_2_PIN, HIGH);
}

ErrorState_t HRELAY_enOFF(void)
{
	MDIO_voidSetPinValue(HRELAY_1_PIN, LOW);
	MDIO_voidSetPinValue(HRELAY_2_PIN, LOW);
}

ErrorState_t HRELAY_enOnce(void)
{
	MDIO_voidTogglePinValue(HRELAY_1_PIN);
	_delay_ms(100);

	/*
	MDIO_voidTogglePinValue(HRELAY_2_PIN);
	_delay_ms(100);
	*/
}
