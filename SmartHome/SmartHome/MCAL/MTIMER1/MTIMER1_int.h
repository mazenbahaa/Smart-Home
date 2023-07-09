/*
 * MTIMER1_int.h
 *
 *  Created on: Jun 13, 2023
 *      Author: Elkhashab
 */

#ifndef MTIMER1_MTIMER1_INT_H_
#define MTIMER1_MTIMER1_INT_H_

#define MTIMER1_ICU_FALL_EDGE_TRIG	0
#define MTIMER1_ICU_RISE_EDGE_TRIG	1

#define MTIMER1_OVF_INT_ID 0
#define MTIMER1_COM_INT_ID 1

ErrorState_t MTIMER1_enInit(void);	// Time Mode
ErrorState_t MTIMER1_enStart(void);	// Clock
ErrorState_t MTIMER1_enStop(void);
ErrorState_t MTIMER1_enSetCallBack(void (*ptrfn) (void));
ErrorState_t MTIMER1_enEnableInt(void);
ErrorState_t MTIMER1_enDisableInt(void);


ErrorState_t MTIMER1_ICU_enInit(void);	// Config 1st Trigger to ISR
ErrorState_t MTIMER1_ICU_enEnableInt(void);
ErrorState_t MTIMER1_ICU_enDisableInt(void);
ErrorState_t MTIMER1_ICU_enSetCallBack(void (*ptrfn) (void));
ErrorState_t MTIMER1_ICU_enRead(volatile u16 *ptrReadValue);
ErrorState_t MTIMER1_ICU_enSetTrigger(u8 copy_u8Trigg);

#endif /* MTIMER1_MTIMER1_INT_H_ */
