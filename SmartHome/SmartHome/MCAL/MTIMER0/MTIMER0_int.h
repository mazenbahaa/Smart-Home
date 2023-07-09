/*
 * MTIMER0_int.h
 *
 *  Created on: Jun 11, 2023
 *      Author: Elkhashab
 */

#ifndef MTIMER0_MTIMER0_INT_H_
#define MTIMER0_MTIMER0_INT_H_

//Prebuild Config

#define MTIMER0_OVF_INT_ID 0
#define MTIMER0_COM_INT_ID 1

ErrorState_t MTIMER0_enInit(void);
ErrorState_t MTIMER0_enStart(void);
ErrorState_t MTIMER0_enStop(void);
ErrorState_t MTIMER0_enSetCallBack(u8 copy_u8IntID, void (*ptrfn) (void));
ErrorState_t MTIMER0_enSetTime(u32 copy_u32DelayMS); // Same As _delay_ms
ErrorState_t MTIMER0_enEnableInt(u8 copy_u8IntID);
ErrorState_t MTIMER0_enDisableInt(u8 copy_u8IntID);
ErrorState_t MTIMER0_enSetCompareValue(u8 copy_u8Value);

// For PWM
#if(MTIMER0_MODE == MTIMER0_MODE_FAST_PWM)
ErrorState_t MTIMER0_enSetFastPWM(u8 copy_u8Duty);
#endif

#if(MTIMER0_MODE == MTIMER0_MODE_PHASE_CORRECT_PWM)
ErrorState_t MTIMER0_enPhaseCorrectPWM(u8 copy_u8Duty);
#endif

#endif /* MTIMER0_MTIMER0_INT_H_ */
