/*
 * MADC_init.h
 *
 *  Created on: Jun 26, 2023
 *      Author: Elkhashab
 */

#ifndef MADC_MADC_INIT_H_
#define MADC_MADC_INIT_H_

#define ADC_CHANNEL_0	0
#define ADC_CHANNEL_1	1
#define ADC_CHANNEL_2	2
#define ADC_CHANNEL_3	3
#define ADC_CHANNEL_4	4
#define ADC_CHANNEL_5	5
#define ADC_CHANNEL_6	6
#define ADC_CHANNEL_7	7

ErrorState_t MADC_enInit(void);
ErrorState_t MADC_enRead(u8 copy_u8Channel);

#endif /* MADC_MADC_INIT_H_ */
