/*
 * HTEMPREATURE_init.h
 *
 *  Created on: Jun 26, 2023
 *      Author: Elkhashab
 */

#ifndef HTEMPERATURE_HTEMPREATURE_INIT_H_
#define HTEMPERATURE_HTEMPREATURE_INIT_H_

ErrorState_t HTEMPREATURE_enInit(void);
ErrorState_t HTEMPREATURE_enRead(u16 *copy_u16Ptr);

#endif /* HTEMPERATURE_HTEMPREATURE_INIT_H_ */
