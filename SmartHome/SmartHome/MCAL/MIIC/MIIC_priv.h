/*
 * MIIC_priv.h
 *
 *  Created on: Jun 21, 2023
 *      Author: Elkhashab
 */

#ifndef MIIC_MIIC_PRIV_H_
#define MIIC_MIIC_PRIV_H_

#define	TWCR_REG	(*((volatile u8*)0x56))	// Control Register
#define TWDR_REG	(*((volatile u8*)0x23))	// Data Register
#define TWAR_REG	(*((volatile u8*)0x22))	// Slave Address Register
#define TWSR_REG	(*((volatile u8*)0x21))	// Status Register
#define TWBR_REG	(*((volatile u8*)0x20)) // Bit Rate Register

// TWCR_REG
#define TWINT_BIT	7	// Interrupt Flag
#define TWEA_BIT	6	// TWI Enable Acknowledge Bit
#define TWSTA_BIT	5	// To Send Start Condition
#define TWSTO_BIT	4	// To Send Stop Condition
#define TWWC_BIT	3	// Write Collision Flag
#define TWEN_BIT	2	// TWI Enable
#define TWIE_BIT	0	// TWI Interrupt Enable

// TWSR_REG
#define TWPS1_BIT	1	// Prescelar Bit 1
#define TWPS0_BIT	0	// Prescelar Bit 0

// TWAR_REG
#define TWGCE_BIT	0	// Disable / Enable General Call Recognition

#define MTWI_STATUS_MASK	0xF8	// 0b11111000

#endif /* MIIC_MIIC_PRIV_H_ */
