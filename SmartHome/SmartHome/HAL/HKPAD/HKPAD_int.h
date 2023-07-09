/*
 * HKPAD_int.h
 *
 *  Created on: May 31, 2023
 *      Author: Elkhashab
 */

#ifndef HKPAD_HKPAD_INT_H_
#define HKPAD_HKPAD_INT_H_

#define HKPAD_NO_PRESSED_KEY 0xFF

typedef enum
{
	KP_PRESSED = 0,
	KP_RELEASED = 1,
	KP_HOLDING = 2
}StateMachine;

ErrorState_t HKPAD_enInit(void);
ErrorState_t HKPAD_enGetPressKey(u8 *ptrKey);

#endif /* HKPAD_HKPAD_INT_H_ */
