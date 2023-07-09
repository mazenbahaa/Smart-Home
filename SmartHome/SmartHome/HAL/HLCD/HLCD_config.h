/*
 * HLCD_config.h
 *
 *  Created on: Jun 1, 2023
 *      Author: Elkhashab
 */

#ifndef HLCD_HLCD_CONFIG_H_
#define HLCD_HLCD_CONFIG_H_

/*
 * Choose _4BIT_ OR _8BIT_
 */

#define HLCD_MODE _4BIT_

#define HLCD_RS_PIN	PA1
#define HLCD_EN_PIN	PA2
#define HLCD_RW_PIN

#define HLCD_D4_PIN PA3
#define HLCD_D5_PIN	PA4
#define HLCD_D6_PIN PA5
#define HLCD_D7_PIN PA6

#if(HLCD_MODE == _8BIT_)
#define HLCD_D0_PIN	PB0
#define HLCD_D1_PIN	PB1
#define HLCD_D2_PIN	PB2
#define HLCD_D3_PIN	PB3
#endif

/*
 *  Special Character Config
 */
#define CHAR_M_AR_CODE	{0x00, 0x00, 0x00, 0x1F, 0x05, 0x07, 0x00, 0x00}
#define CHAR_AZE_AR_CODE	{0x02, 0x0A, 0x02, 0x0B, 0x08, 0x18, 0x00, 0x00}
#define CHAR_N_AR_CODE	{0x00, 0x04, 0x00, 0x0A, 0x0A, 0x0E, 0x00, 0x00}

#endif /* HLCD_HLCD_CONFIG_H_ */
