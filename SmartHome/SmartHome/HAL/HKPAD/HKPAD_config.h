/*
 * HKPAD_config.h
 *
 *  Created on: May 31, 2023
 *      Author: Elkhashab
 */

#ifndef HKPAD_HKPAD_CONFIG_H_
#define HKPAD_HKPAD_CONFIG_H_

/*
 * Please Configure Pins for Keypad:
 *
 */

#define HKPAD_R0_PIN PB4
#define HKPAD_R1_PIN PB5
#define HKPAD_R2_PIN PB6
#define HKPAD_R3_PIN PB7

#define HKPAD_C0_PIN PD2
#define HKPAD_C1_PIN PD3
#define HKPAD_C2_PIN PD4
#define HKPAD_C3_PIN PD5

#define KIT_TYPE REAL_KIT

/*
 * Here you can Choose Keypad Mapping
 */

// Normal KeyPad
//#define HKYPAD_KEYS {{1,2,3,4},{5,6,7,8},{9,10,11,12},{13,14,15,16}}

// Calculator KeyPad
//#define HKYPAD_KEYS {{1,2,3,'+'},{5,6,7,'-'},{9,10,11,'*'},{13,14,15,'/'}}

// Smart Home Project
#define HKYPAD_KEYS {{1,2,3,4},{5,6,7,8},{9,10,11,12},{13,14,'ON','OFF'}}

#endif /* HKPAD_HKPAD_CONFIG_H_ */
