/*
 * MEXTI_priv.h
 *
 *  Created on: Jun 7, 2023
 *      Author: Elkhashab
 */

#ifndef MEXTI_MEXTI_PRIV_H_
#define MEXTI_MEXTI_PRIV_H_

#define MCUCR_REG	(*((volatile u8*)0x55)) // ISC INT0, INT1
#define MCUCSR_REG	(*((volatile u8*)0x54)) // ISC INT2
#define GICR_REG	(*((volatile u8*)0x5B)) // PIEs = special Enable
#define GIFR_REG	(*((volatile u8*)0x5A)) // PIFs = Flags

//MCUCR_REG
#define ISC00_BIT 0
#define ISC01_BIT 1
#define ISC10_BIT 2
#define ISC11_BIT 3

//MCUCSR_REG
#define ISC2_BIT 6

//GICR_REG
#define INT2_BIT 5
#define INT0_BIT 6
#define INT1_BIT 7

//GIFR_REG

#define INT1_SC_SH	2
#define INT0_SC_MASK	0b11111100
#define INT1_SC_MASK	0b11110011

#endif /* MEXTI_MEXTI_PRIV_H_ */
