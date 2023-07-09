/*
 * MTIMER1_priv.h
 *
 *  Created on: Jun 13, 2023
 *      Author: Elkhashab
 */

#ifndef MTIMER1_MTIMER1_PRIV_H_
#define MTIMER1_MTIMER1_PRIV_H_

#define TCNT1_REG	(*((volatile u16*)0x4C))
#define ICR1_REG	(*((volatile u16*)0x46))
#define OCR1A_REG	(*((volatile u16*) 0x4A))
#define OCR1B_REG	(*((volatile u16*) 0x48))
#define TCCR1A_REG	(*((volatile u8*)0x4F))
#define TCCR1B_REG	(*((volatile u8*)0x4E))
#define TIMSK_REG	(*((volatile u8*) 0x59))
#define TIFR_REG	(*((volatile u8*) 0x58))

// TCCR1A
#define WGM10_BIT 0
#define WGM11_BIT 1

// TCCR1A
#define CS10_BIT	0
#define CS11_BIT	1
#define CS12_BIT	2

#define WGM12_BIT	3
#define WGM13_BIT	4

#define ICES1_BIT	6	// Edge Select
#define ICNC1_BIT	7	// Noise Canceler

#define MTIMER1_NO_CLK	0
#define MTIMER1_PRESCALER_1	1
#define MTIMER1_PRESCALER_8	2
#define MTIMER1_PRESCALER_64	3
#define MTIMER1_PRESCALER_256	4
#define MTIMER1_PRESCALER_1024	5
#define MTIMER1_EXTCLK_FALL_EDGE	6
#define MTIMER1_EXTCLK_RISE_EDGE	7

#define MTIMER1_CS_MASK	0xF8

// TIMSK_REG
#define TICIE1_BIT	5

#define TOIE1_BIT 2
#define OCIE1A_BIT	4
#define OCIE1B_BIT 	3

#define TOV1_BIT 2
#define OCF1A_BIT 4
#define OCF1B_BIT 3

#endif /* MTIMER1_MTIMER1_PRIV_H_ */
