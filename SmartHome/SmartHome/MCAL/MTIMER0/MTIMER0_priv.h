/*
 * MTIMER0_priv.h
 *
 *  Created on: Jun 11, 2023
 *      Author: Elkhashab
 */

#ifndef MTIMER0_MTIMER0_PRIV_H_
#define MTIMER0_MTIMER0_PRIV_H_

#define TCCR0_REG	(*((volatile u8*) 0x53))
#define TCNT0_REG	(*((volatile u8*) 0x52))
#define OCR0_REG	(*((volatile u8*) 0x5C))
#define TIMSK_REG	(*((volatile u8*) 0x59))
#define TIFR_REG	(*((volatile u8*) 0x58))

// TCCR0_REG

#define CS00_BIT	0
#define CS01_BIT	1
#define CS02_BIT	2

#define WGM01_BIT	3

#define COM00_BIT	4
#define COM01_BIT	5

#define WGM00_BIT	6

#define FOC0_BIT	7

// TIMSK_REG

#define TOIE0_BIT 0
#define OCIE0_BIT 1

// TIFR_REG

#define TOV0_BIT 0
#define OCF0_BIT 1

#define MTIMER0_CS_MASK	0xF8

#define MTIMER0_NO_CLK	0
#define MTIMER0_PRESCALER_1	1
#define MTIMER0_PRESCALER_8	2
#define MTIMER0_PRESCALER_64	3
#define MTIMER0_PRESCALER_256	4
#define MTIMER0_PRESCALER_1024	5
#define MTIMER0_EXTCLK_FALL_EDGE	6
#define MTIMER0_EXTCLK_RISE_EDGE	7

#define MTIMER0_MODE_MASK 0xB7

#define MTIMER0_MODE_NORMAL 0x00
#define MTIMER0_MODE_CTC	0x08
#define MTIMER0_MODE_FAST_PWM	0x48
#define MTIMER0_MODE_PHASE_CORRECT_PWM	0x40

#define MTIMER0_OC0_MASK 0xCF

#define  MTIMER_OC0_DISCONNECTED	0
#define  MTIMER_OC0_TOGGLER	1
#define  MTIMER_OC0_CLEAR	2
#define  MTIMER_OC0_SET	3

#define MTIMER0_OC0_SH 4

// For PWM
#define MTIMER0_OC0_NONINVERTED	2
#define MTIMER0_OC0_INVERTED	3

#endif /* MTIMER0_MTIMER0_PRIV_H_ */
