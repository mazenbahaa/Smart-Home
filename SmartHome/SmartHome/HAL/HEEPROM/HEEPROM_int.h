/*
 * HEEPROM_int.h
 *
 *  Created on: Jun 21, 2023
 *      Author: Elkhashab
 */

#ifndef HEEPROM_HEEPROM_INT_H_
#define HEEPROM_HEEPROM_INT_H_

ErrorState_t HEEPROM_enInit();
ErrorState_t HEEPROM_enWriteByte(u16 copy_u16Address, u8 copy_u8Byte);
ErrorState_t HEEPROM_enReadByte(u16 copy_u16Address, u8 *ptrData);

#endif /* HEEPROM_HEEPROM_INT_H_ */
