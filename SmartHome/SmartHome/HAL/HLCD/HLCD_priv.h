/*
 * HLCD_priv.h
 *
 *  Created on: Jun 1, 2023
 *      Author: Elkhashab
 */

#ifndef HLCD_HLCD_PRIV_H_
#define HLCD_HLCD_PRIV_H_

#define _4BIT_ 0
#define _8BIT_ 1

static void HLCD_voidNLatch (u8 copy_u8Byte);

#define HLCD_CLEAR 0x01
#define HLCD_FUNCTION_SET_8BIT_2LINES_5X7 0x38
#define HLCD_FUNCTION_SET_4BIT_2LINES_5X7 0x28

#define HLCD_DISPLAY_ON_CURSOR_ON_BLINK_OFF 0x0E
#define HLCD_ENTRY_MODE_SET_INC_NO_SHIFT 0x06

#define HLCD_SET_CGRAM_ADDRESS 0x40

#define HLCD_FIRST_COL	0x80
#define HLCD_SECOND_COL	0xC0

#endif /* HLCD_HLCD_PRIV_H_ */
