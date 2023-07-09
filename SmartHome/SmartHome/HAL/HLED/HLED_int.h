/*
 * HLED_int.h
 *
 *  Created on: May 29, 2023
 *      Author: Elkhashab
 */

#ifndef HLED_HLED_INT_H_
#define HLED_HLED_INT_H_
#include "ERROR_STATES.h"

#define HLED_RED_ID 1
#define HLED_BLUE_ID 2
#define HLED_GRN_ID 3

ErrorState_t HLED_enInit(u8 copy_u8LedId);
ErrorState_t HLED_enSetON(u8 copy_u8LedId);
ErrorState_t HLED_enSetOFF(u8 copy_u8LedId);
ErrorState_t HLED_enToggle(u8 copy_u8LedId);

#endif /* HLED_HLED_INT_H_ */
