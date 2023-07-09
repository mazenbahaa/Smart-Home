/*
 * HLCD_prg.c
 *
 *  Created on: Jun 1, 2023
 *      Author: Elkhashab
 */

#include "STD_TYPES.h"
#include "ERROR_STATES.h"
#include "BIT_MATH.h"
#include "MDIO_int.h"
#include "HLCD_priv.h"
#include "HLCD_config.h"
#include "HLCD_int.h"
#include <avr/delay.h>

ErrorState_t HLCD_enInit(void)
{
	// Set Direction for pins as Output

	MDIO_setPinDirection(HLCD_RS_PIN, OUTPUT);
	MDIO_setPinDirection(HLCD_EN_PIN, OUTPUT);

	MDIO_setPinDirection(HLCD_D7_PIN, OUTPUT);
	MDIO_setPinDirection(HLCD_D6_PIN, OUTPUT);
	MDIO_setPinDirection(HLCD_D5_PIN, OUTPUT);
	MDIO_setPinDirection(HLCD_D4_PIN, OUTPUT);

#if(HLCD_MODE == _8BIT_)
	MDIO_setPinDirection(HLCD_D3_PIN, OUTPUT);
	MDIO_setPinDirection(HLCD_D2_PIN, OUTPUT);
	MDIO_setPinDirection(HLCD_D1_PIN, OUTPUT);
	MDIO_setPinDirection(HLCD_D0_PIN, OUTPUT);

	_delay_ms(35);
	HLCD_enSendCommand(HLCD_FUNCTION_SET_8BIT_2LINES_5X7);

#elif(HLCD_MODE == _4BIT_)
	_delay_ms(35);
	//Send 0010
	MDIO_voidSetPinValue(HLCD_EN_PIN, LOW);
	MDIO_voidSetPinValue(HLCD_D7_PIN, 0);
	MDIO_voidSetPinValue(HLCD_D6_PIN, 0);
	MDIO_voidSetPinValue(HLCD_D5_PIN, 1);
	MDIO_voidSetPinValue(HLCD_D4_PIN, 0);

	MDIO_voidSetPinValue(HLCD_EN_PIN, HIGH);
	_delay_ms(1);
	MDIO_voidSetPinValue(HLCD_EN_PIN, LOW);
	_delay_ms(30);

	HLCD_enSendCommand(HLCD_FUNCTION_SET_4BIT_2LINES_5X7);
#endif

	// Perform Rest Initialization Sequence
	HLCD_enSendCommand(HLCD_DISPLAY_ON_CURSOR_ON_BLINK_OFF);
	HLCD_enSendCommand(HLCD_CLEAR);
	HLCD_enSendCommand(HLCD_ENTRY_MODE_SET_INC_NO_SHIFT);
}

ErrorState_t HLCD_enSendData(u8 copy_u8Data)
{
	MDIO_voidSetPinValue(HLCD_RS_PIN, HIGH);
	// Send Data as a Byte to NLatch
	HLCD_voidNLatch(copy_u8Data);

	return SUCCESS;
}

ErrorState_t HLCD_enSendCommand(u8 copy_u8Command)
{
	MDIO_voidSetPinValue(HLCD_RS_PIN, LOW);
	// Send Command as a Byte to NLatch
	HLCD_voidNLatch(copy_u8Command);

	return SUCCESS;
}

ErrorState_t HLCD_enSendString(const u8 *str)
{
	while(*str != '\0')
	{
		HLCD_enSendData(*str);
		str++;
	}
	return SUCCESS;
}

ErrorState_t HLCD_enClear(void)
{
	HLCD_enSendCommand(HLCD_CLEAR);
}

ErrorState_t HLCD_enSendIntNum(s32 copy_u32Num)
{
	u8 IntArr[10] = {0};
	s8 i = 0;
	if(copy_u32Num == 0)
	{
		HLCD_enSendData('0');
	}
	else if(copy_u32Num < 0)
	{
		HLCD_enSendData('-');
		copy_u32Num *= -1;
	}
	while(copy_u32Num > 0)
	{
		IntArr[i] = copy_u32Num % 10;
		copy_u32Num = copy_u32Num / 10;
		i++;
	}
	i--;
	while(i >= 0)
	{
		HLCD_enSendData(IntArr[i] + '0');
		i--;
	}

	return SUCCESS;
}

ErrorState_t HLCD_enGoToXY(u8 copy_u8X, u8 copy_u8Y)
{
	if(copy_u8X == 0)
	{
		HLCD_enSendCommand(HLCD_FIRST_COL | copy_u8Y);
	}
	else if(copy_u8X == 1)
	{
		HLCD_enSendCommand(HLCD_SECOND_COL | copy_u8Y);
	}
}

ErrorState_t HLCD_enSendCustomChar(u8 copy_u8CharCode, u8 *ptrPattern)
{
	HLCD_enSendCommand(copy_u8CharCode + HLCD_SET_CGRAM_ADDRESS);
	u8 i;

	for(i = 0; i <= 8; i++)
	{
		HLCD_enSendData(ptrPattern[i]);
	}

}

ErrorState_t HLCD_enDisplayCustomChar(u8 copy_u8CharCode)
{
	HLCD_enSendData(copy_u8CharCode);
}

static void HLCD_voidNLatch (u8 copy_u8Byte)
{
	u8 i;

#if(HLCD_MODE == _8BIT_)
	u8 LCdPinsArr[] = {HLCD_D0_PIN, HLCD_D1_PIN, HLCD_D2_PIN, HLCD_D3_PIN,
				 	 	 	 HLCD_D4_PIN, HLCD_D5_PIN, HLCD_D6_PIN, HLCD_D7_PIN};
	//MDIO_voidSetPinValue(HLCD_D0_PIN, GET_BIT(copy_u8Byte, 0));
	MDIO_voidSetPinValue(HLCD_EN_PIN, LOW);
	for(i = 0; i <= 7; i++)
	{
		MDIO_voidSetPinValue(LCdPinsArr[i], GET_BIT(copy_u8Byte, i));
	}
		MDIO_voidSetPinValue(HLCD_EN_PIN, HIGH);
		_delay_ms(1);
		MDIO_voidSetPinValue(HLCD_EN_PIN, LOW);
		_delay_ms(30);

#elif(HLCD_MODE == _4BIT_)
	u8 LCdPinsArr[] = { HLCD_D4_PIN, HLCD_D5_PIN, HLCD_D6_PIN, HLCD_D7_PIN };
	MDIO_voidSetPinValue(HLCD_EN_PIN, LOW);

	for (i = 0; i <= 3; i++)
	{
		MDIO_voidSetPinValue(LCdPinsArr[i], GET_BIT(copy_u8Byte, i + 4));
	}

	MDIO_voidSetPinValue(HLCD_EN_PIN, HIGH);
	_delay_ms(1);
	MDIO_voidSetPinValue(HLCD_EN_PIN, LOW);
	_delay_ms(30);

	// Send Lower 4 bits
	//MDIO_voidSetPinValue(HLCD_EN_PIN, LOW);

	for (i = 0; i <= 3; i++)
	{
		MDIO_voidSetPinValue(LCdPinsArr[i], GET_BIT(copy_u8Byte, i));
	}

	MDIO_voidSetPinValue(HLCD_EN_PIN, HIGH);
	_delay_ms(1);
	MDIO_voidSetPinValue(HLCD_EN_PIN, LOW);
	_delay_ms(30);
#else
	#error ("Wrong LCD Mode");
#endif
}

