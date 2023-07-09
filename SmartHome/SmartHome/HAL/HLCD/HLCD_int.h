/*
 * HLED_int.h
 *
 *  Created on: Jun 1, 2023
 *      Author: Elkhashab
 */

#ifndef HLCD_HLCD_INT_H_
#define HLCD_HLCD_INT_H_

ErrorState_t HLCD_enInit(void);
ErrorState_t HLCD_enSendData(u8 copy_u8Data);
ErrorState_t HLCD_enSendCommand(u8 copy_u8Command);
ErrorState_t HLCD_enSendString(const u8 *str);
ErrorState_t HLCD_enClear(void);
ErrorState_t HLCD_enSendIntNum(s32 copy_u32Num);
ErrorState_t HLCD_enGoToXY(u8 copy_u8X, u8 copy_u8Y);
ErrorState_t HLCD_enSendCustomChar(u8 copy_u8CharCode, u8 *ptrPattern);
ErrorState_t HLCD_enDisplayCustomChar(u8 copy_u8CharCode);

#endif /* HLCD_HLCD_INT_H_ */
