/*
 * MDIO_prg.c
 *
 *  Created on: May 28, 2023
 *      Author: Elkhashab
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "MDIO_priv.h"
#include "MDIO_config.h"
#include "MDIO_int.h"

void MDIO_setPinDirection(Pin_t copy_enpin, Direction_t copy_enDirection){
	u32 Local_u8port = copy_enpin / 10;
	u32 Local_u8pin = copy_enpin % 10;

	switch(Local_u8port)
	{
	case PORTA:
		switch(copy_enDirection)
		{
		case INPUT:
			CLR_BIT(DDRA_REG, Local_u8pin);
			break;
		case OUTPUT:
			SET_BIT(DDRA_REG, Local_u8pin);
			break;
		default:
			break;
		}

		break;
	case PORTB:
		switch(copy_enDirection)
		{
		case INPUT:
			CLR_BIT(DDRB_REG, Local_u8pin);
			break;
		case OUTPUT:
			SET_BIT(DDRB_REG, Local_u8pin);
			break;
		default:
			break;
		}
		break;
	case PORTC:
		switch(copy_enDirection)
		{
		case INPUT:
			CLR_BIT(DDRC_REG, Local_u8pin);
			break;
		case OUTPUT:
			SET_BIT(DDRC_REG, Local_u8pin);
			break;
		default:
			break;
		}
		break;
	case PORTD:
		switch(copy_enDirection)
		{
		case INPUT:
			CLR_BIT(DDRD_REG, Local_u8pin);
			break;
		case OUTPUT:
			SET_BIT(DDRD_REG, Local_u8pin);
			break;
		default:
			break;
		}
		break;
	}
}

void MDIO_voidSetPinValue(Pin_t copy_enpin, Value_t copy_enValue){
	u32 Local_u8port = copy_enpin / 10;
	u32 Local_u8pin = copy_enpin % 10;
	switch(Local_u8port)
	{
	case PORTA:
		switch(copy_enValue)
		{
		case LOW:
			CLR_BIT(PORTA_REG, Local_u8pin);
			break;
		case HIGH:
			SET_BIT(PORTA_REG, Local_u8pin);
			break;
		default:
			break;
		}
		break;
	case PORTB:
		switch(copy_enValue)
		{
		case LOW:
			CLR_BIT(PORTB_REG, Local_u8pin);
			break;
		case HIGH:
			SET_BIT(PORTB_REG, Local_u8pin);
			break;
		default:
			break;
		}
		break;
	case PORTC:
		switch(copy_enValue)
		{
		case LOW:
			CLR_BIT(PORTC_REG, Local_u8pin);
			break;
		case HIGH:
			SET_BIT(PORTC_REG, Local_u8pin);
			break;
		default:
			break;
		}
		break;
	case PORTD:
		switch(copy_enValue)
		{
		case LOW:
			CLR_BIT(PORTD_REG, Local_u8pin);
			break;
		case HIGH:
			SET_BIT(PORTD_REG, Local_u8pin);
			break;
		default:
			break;
		}
		break;
	}
}

void MDIO_voidSetPortValue(Port_t copy_enPort, u8 copy_u8Value){
	switch(copy_enPort)
	{
	case PORTA:
		PORTA_REG = copy_u8Value;
		break;
	case PORTB:
		PORTB_REG = copy_u8Value;
		break;
	case PORTC:
		PORTC_REG = copy_u8Value;
		break;
	case PORTD:
		PORTD_REG = copy_u8Value;
		break;
	default:
		break;
	}
}

void MDIO_voidgetPinValue(Pin_t copy_enpin, Value_t * ptrValue){
	u32 Local_u8port = copy_enpin / 10;
	u32 Local_u8pin = copy_enpin % 10;

	switch(Local_u8port)
	{
	case PORTA:
		*ptrValue = GET_BIT(PINA_REG, Local_u8pin);
		break;
	case PORTB:
		*ptrValue = GET_BIT(PINB_REG, Local_u8pin);
		break;
	case PORTC:
		*ptrValue = GET_BIT(PINC_REG, Local_u8pin);
		break;
	case PORTD:
		*ptrValue = GET_BIT(PIND_REG, Local_u8pin);
		break;
	default:
		// Report Error
		break;
	}
}

void MDIO_voidTogglePinValue(Pin_t copy_enpin)
{
	u32 Local_u8port = copy_enpin / 10;
	u32 Local_u8pin = copy_enpin % 10;

	switch(Local_u8port)
	{
	case PORTA:
		 TOG_BIT(PORTA_REG, Local_u8pin);
		break;
	case PORTB:
		TOG_BIT(PORTB_REG, Local_u8pin);
		break;
	case PORTC:
		TOG_BIT(PORTC_REG, Local_u8pin);
		break;
	case PORTD:
		TOG_BIT(PORTD_REG, Local_u8pin);
		break;
	default:
		// Report Error
		break;
	}
}
void MDIO_voidGetPortValue(Port_t copy_enPort, u8 *ptrPortValue)
{
		switch(copy_enPort)
		{
		case PORTA:
			*ptrPortValue = PINA_REG;
			break;
		case PORTB:
			*ptrPortValue = PINB_REG;
			break;
		case PORTC:
			*ptrPortValue = PINC_REG;
			break;
		case PORTD:
			*ptrPortValue = PIND_REG;
			break;
		default:
			// Report Error
			break;
		}
}

