/*
 * MWDTIMER_int.h
 *
 *  Created on: Jun 15, 2023
 *      Author: Elkhashab
 */

#ifndef MWDTIMER_MWDTIMER_INT_H_
#define MWDTIMER_MWDTIMER_INT_H_

#define MWDT_TIMEOUT_16_3_MS	0
#define MWDT_TIMEOUT_32_5_MS	1
#define MWDT_TIMEOUT_65_MS	2

#define MWDT_TIMEOUT_0_13_S	3
#define MWDT_TIMEOUT_0_26_S	4
#define MWDT_TIMEOUT_0_52_S	5
#define MWDT_TIMEOUT_1_S	6
#define MWDT_TIMEOUT_2_1_S	7

ErrorState_t MWDTIMER_enEnable(void);
ErrorState_t MWDTIMER_enDisable(void);
ErrorState_t MWDTIMER_enSleep(u8 copy_u8TimeOut);
ErrorState_t MWDTIMER_enRefresh(void);

#endif /* MWDTIMER_MWDTIMER_INT_H_ */
