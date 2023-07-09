/*
 * MWDTIMER_priv.h
 *
 *  Created on: Jun 15, 2023
 *      Author: Elkhashab
 */

#ifndef MWDTIMER_MWDTIMER_PRIV_H_
#define MWDTIMER_MWDTIMER_PRIV_H_

#define WDTCR_REG (*((volatile u8*)0x41))

#define WDP0_BIT	0
#define WDP1_BIT	1
#define WDP3_BIT	2

#define WDE_BIT	3	// Watch Dog Enable
#define WDTOE_BIT	4	// Watch Dog Turn OFF Enable

#define MWDT_PRESCALER_MASK 0xF8

#endif /* MWDTIMER_MWDTIMER_PRIV_H_ */
