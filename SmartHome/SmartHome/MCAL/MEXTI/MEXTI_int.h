/*
 * MEXTI_int.h
 *
 *  Created on: Jun 7, 2023
 *      Author: Elkhashab
 */

#ifndef MEXTI_MEXTI_INT_H_
#define MEXTI_MEXTI_INT_H_

typedef enum
{
	LOW_LEVEL_TRIG = 0,
	ANY_CHANGE_TRIG = 1,
	FALL_EDGE_TRIG = 2,
	RAIS_EDGE_TRIG = 3
}IntTrigger_t;

typedef enum
{
	INT0_ID = 6,
	INT1_ID = 7,
	INT2_ID = 5
}InterruptID_t;

ErrorState_t MEXTI_enEnable(InterruptID_t copy_enID, IntTrigger_t copy_enTrig); // Set ON Enable, Config Sense Control
ErrorState_t MEXTI_enDisable(InterruptID_t copy_enID); //Set OFF

ErrorState_t MEXTI_ensetCallBack(InterruptID_t copy_enID, void (*ptrfn)(void));

#endif /* MEXTI_MEXTI_INT_H_ */
