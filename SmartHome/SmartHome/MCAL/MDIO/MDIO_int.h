/*
 * MDIO_int.h
 *
 *  Created on: May 28, 2023
 *      Author: Elkhashab
 */

#ifndef MDIO_MDIO_INT_H_
#define MDIO_MDIO_INT_H_

typedef enum{
	PA0 = 10,
	PA1 = 11,
	PA2 = 12,
	PA3 = 13,
	PA4 = 14,
	PA5 = 15,
	PA6 = 16,
	PA7 = 17,

	PB0 = 20,
	PB1 = 21,
	PB2 = 22,
	PB3 = 23,
	PB4 = 24,
	PB5 = 25,
	PB6 = 26,
	PB7 = 27,

	PC0 = 30,
	PC1 = 31,
	PC2 = 32,
	PC3 = 33,
	PC4 = 34,
	PC5 = 35,
	PC6 = 36,
	PC7 = 37,

	PD0 = 40,
	PD1 = 41,
	PD2 = 42,
	PD3 = 43,
	PD4 = 44,
	PD5 = 45,
	PD6 = 46,
	PD7 = 47

}Pin_t;

typedef enum{
	INPUT = 0,
	OUTPUT = 1
}Direction_t;

typedef enum{
	HIGH = 1,
	LOW = 0
}Value_t;

typedef enum{
	PORTA = 1,
	PORTB = 2,
	PORTC = 3,
	PORTD = 4
}Port_t;

void MDIO_setPinDirection(Pin_t copy_enpin, Direction_t copy_enDirection);
void MDIO_voidSetPinValue(Pin_t copy_enpin, Value_t copy_enValue);
void MDIO_voidSetPortValue(Port_t copy_enPort, u8 copy_u8Value);
void MDIO_voidgetPinValue(Pin_t copy_enpin, Value_t * ptrValue);
void MDIO_voidTogglePinValue(Pin_t copy_enpin);
void MDIO_voidGetPortValue(Port_t copy_enPort, u8 *ptrValue);

#endif /* MDIO_MDIO_INT_H_ */
