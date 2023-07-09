/*
 * HKPAD_prg.h
 *
 *  Created on: May 31, 2023
 *      Author: Elkhashab
 */

#include <avr/delay.h>
#include "STD_TYPES.h"
#include "ERROR_STATES.h"
#include "MDIO_int.h"
#include "HKPAD_priv.h"
#include "HKPAD_config.h"
#include "HKPAD_int.h"

ErrorState_t HKPAD_enInit(void)
{
	// Config Rows to be Output
	MDIO_setPinDirection(HKPAD_R0_PIN, OUTPUT);
	MDIO_setPinDirection(HKPAD_R1_PIN, OUTPUT);
	MDIO_setPinDirection(HKPAD_R2_PIN, OUTPUT);
	MDIO_setPinDirection(HKPAD_R3_PIN, OUTPUT);

	// Config Cols to be Input
	MDIO_setPinDirection(HKPAD_C0_PIN, INPUT);
	MDIO_setPinDirection(HKPAD_C1_PIN, INPUT);
	MDIO_setPinDirection(HKPAD_C2_PIN, INPUT);
	MDIO_setPinDirection(HKPAD_C3_PIN, INPUT);

	// Initialize Output (Rows) High
	MDIO_voidSetPinValue(HKPAD_R0_PIN, HIGH);
	MDIO_voidSetPinValue(HKPAD_R1_PIN, HIGH);
	MDIO_voidSetPinValue(HKPAD_R2_PIN, HIGH);
	MDIO_voidSetPinValue(HKPAD_R3_PIN, HIGH);

	// Activate Internal Pull up with Cols
#if(KIT_TYPE == SIM_KIT)
	MDIO_voidSetPinValue(HKPAD_C0_PIN, HIGH);
	MDIO_voidSetPinValue(HKPAD_C1_PIN, HIGH);
	MDIO_voidSetPinValue(HKPAD_C2_PIN, HIGH);
	MDIO_voidSetPinValue(HKPAD_C3_PIN, HIGH);
#endif

	return SUCCESS;
}

ErrorState_t HKPAD_enGetPressKey(u8 *ptrKey)
{
	u8 Local_u8PressedKey = HKPAD_NO_PRESSED_KEY;
	u8 Local_u8PinRead;
	u8 row_indx;
	u8 col_indx;
	u8 flag = 0;

	u8 Local_u8ArrKeys[4][4] = HKYPAD_KEYS;
	u8 rowArr[] = {HKPAD_R0_PIN, HKPAD_R1_PIN, HKPAD_R2_PIN, HKPAD_R3_PIN};
	u8 colArr[] = {HKPAD_C0_PIN, HKPAD_C1_PIN, HKPAD_C2_PIN, HKPAD_C3_PIN};

	for(row_indx = 0 ; row_indx <= 3 && flag == 0; row_indx++)
	{
		// Output 0 (Ground) on Row
		MDIO_voidSetPinValue(rowArr[row_indx], LOW);
		for(col_indx = 0; col_indx <= 3 && flag == 0; col_indx++)
		{
			MDIO_voidgetPinValue(colArr[col_indx], &Local_u8PinRead);
			if (Local_u8PinRead == HKPAD_KEY_PRESSED)
			{
				_delay_ms(50);
				MDIO_voidgetPinValue(colArr[col_indx], &Local_u8PinRead);
				if (Local_u8PinRead == HKPAD_KEY_PRESSED)
				{
					if (Local_u8PinRead == HKPAD_KEY_PRESSED)
					{
						MDIO_voidgetPinValue(colArr[col_indx], &Local_u8PinRead);

					}
					Local_u8PressedKey = Local_u8ArrKeys[row_indx][col_indx];
					flag = 1;
				}
				else
				{

				}
			}
			else
			{

			}
		}

		// Output 1 (High) on Row (Deactivate)
		MDIO_voidSetPinValue(rowArr[row_indx], HIGH);
	}
	*ptrKey = Local_u8PressedKey;
	return SUCCESS;
}
