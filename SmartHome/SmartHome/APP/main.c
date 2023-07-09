/*
 * main.c
 *
 *  Created on: Jun 26, 2023
 *      Author: Elkhashab
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "ERROR_STATES.h"
#include "MDIO_int.h"
#include "MADC_init.h"
#include "MGIE_int.h"
#include "MTIMER0_int.h"
#include "MTIMER1_int.h"
#include "HTEMPREATURE_init.h"
#include "HLED_int.h"
#include "HLCD_int.h"
#include "HKPAD_int.h"
#include "HEEPROM_int.h"
#include <avr/delay.h>

// UltraSonic Sector
#define MAX_LEN	65353

volatile u16 g_Reading1 = 0;
volatile u16 g_Reading2 = 0;

volatile u16 g_Reading1_X = 0;
volatile u16 g_Reading2_Y = 0;

typedef enum
{
	STATE1 = 1, STATE2 = 2, STATE3 = 3
}StateMachine_Type;

static volatile StateMachine_Type g_State = STATE1;

volatile u8 g_OVFCount = 0;

void ICU_HW(void);
void OVF_INT(void);

void main(void)
{
	HLCD_enInit();
	HKPAD_enInit();
	HEEPROM_enInit();
	HLED_enInit(HLED_GRN_ID);
	HRELAY_enInit();
	HTEMPREATURE_enInit();
	HDCMOTOR_enInit();

	// UltraSonic Sector

	MDIO_setPinDirection(PD6, INPUT);
	MDIO_setPinDirection(PC5, OUTPUT);

	MTIMER0_enInit();
	MTIMER0_enPhaseCorrectPWM(0);
	MTIMER0_enStart();

	MTIMER1_enInit();
	MTIMER1_ICU_enInit();
	MTIMER1_ICU_enEnableInt();
	MTIMER1_ICU_enSetCallBack(ICU_HW);

	MTIMER1_enSetCallBack(OVF_INT);

	MTIMER1_enStart();

	MGIE_enEnable();

	MDIO_voidSetPinValue(PC5, HIGH);
	_delay_us(10);
	MDIO_voidSetPinValue(PC5, LOW);

	while (g_State != STATE3);

	u32 TimeTicks = ((u32) g_Reading2 + ((u32) g_Reading2_Y * MAX_LEN)) - ((u32) g_Reading1 + ((u32) g_Reading1_X * MAX_LEN));
	TimeTicks = g_Reading2 - g_Reading1;
	f32 TickTime = 1024 / 16; // Micro Sec
	f32 Time = (TimeTicks * TickTime) / 1000000.0;
	u32 Distance = ceil(34300 * (Time / 2));

	while (g_State != STATE3);

	// Store Data in EEPROM
	u8 ReadData[4];
	u8 i;
	u8 Pass [4] = {1, 2, 3, 4};

	for (i = 0; i <= 4; i++)
	{
		HEEPROM_enWriteByte(i, Pass[i]);
		_delay_ms(100);
	}

	HEEPROM_enReadByte(0, &ReadData[0]);
	_delay_ms(100);
	HEEPROM_enReadByte(1, &ReadData[1]);
	_delay_ms(100);
	HEEPROM_enReadByte(2, &ReadData[2]);
	_delay_ms(100);
	HEEPROM_enReadByte(3, &ReadData[3]);
	_delay_ms(100);



	while (1) {
		/*
		HLCD_enSendString("Distance = ");
		HLCD_enGoToXY(1, 0);
		HLCD_enSendIntNum(Distance);
		_delay_ms(1000);
		HLCD_enClear();
		*/

		// Project Section

		// Temperature Sector

		u16 Temper;

		HTEMPREATURE_enRead(&Temper);
		if(Temper <= 25)
		{
			HDCMOTOR_enOFF();
		}
		else if(Temper > 25)
		{
			HDCMOTOR_enCLK_Wise();
			MTIMER0_enPhaseCorrectPWM(50);
			_delay_ms(1000);
		}
		else if(Temper >= 30)
		{
			HDCMOTOR_enCLK_Wise();
			MTIMER0_enPhaseCorrectPWM(100);
			_delay_ms(1000);
		}

		// Authentication Sector

		u8 Key = HKPAD_NO_PRESSED_KEY;
		u8 CheckPass[4];
		u8 Counter = 0;
		u8 i;

		if(Distance >= 0 && Distance <= 15)
		{
			HLCD_enGoToXY(1, 0);
			HLCD_enSendString('Enter Password');
			HKPAD_enGetPressKey(&Key);

			if(&Key == Pass[0] && &Key == Pass[1] && &Key == Pass[2] && &Key == Pass[3])
			{
				HLCD_enClear();
				HLCD_enGoToXY(1, 0);
				HLCD_enSendString("Hello Ahmed");

				HRELAY_enOnce();

				if(&Key == 'ON')
				{
					HLED_enSetON(HLED_GRN_ID);
				}
				if(&Key == 'OFF')
				{
					HLED_enSetOFF(HLED_GRN_ID);
				}
			}
			else
			{
				for(i = 0; i <= 3 ; i++)
				{
					HLCD_enClear();
					HLCD_enGoToXY(1, 0);
					HLCD_enSendString("Wrong Password");
					if (&Key == Pass[0] && &Key == Pass[1] && &Key == Pass[2] && &Key == Pass[3])
					{

						HLCD_enClear();
						HLCD_enSendString("Hello Ahmed");
						_delay_ms(500);
						HLCD_enClear();

					}
				}
				_delay_ms(2000);
			}
		}
		else
		{
			HLCD_enSendString('Out Of Range');
		}
	}


}

void ICU_HW(void)
{
	if(g_State == STATE1)
	{
		MTIMER1_ICU_enRead(&g_Reading1);
		g_Reading1_X = g_OVFCount;
		MTIMER1_ICU_enSetTrigger(MTIMER1_ICU_FALL_EDGE_TRIG);
		g_State = STATE2;
	}
	else if(g_State == STATE2)
	{
		MTIMER1_ICU_enRead(&g_Reading2);
		g_Reading2_Y = g_OVFCount;
		g_State = STATE3;
		MTIMER1_ICU_enSetTrigger(MTIMER1_ICU_RISE_EDGE_TRIG);

		MTIMER1_enStop();
		MTIMER1_ICU_enDisableInt();
	}
}

void OVF_INT(void)
{
	g_OVFCount++;
}
