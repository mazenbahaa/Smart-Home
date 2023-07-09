/*
 * HEEPROM_prg.c
 *
 *  Created on: Jun 21, 2023
 *      Author: Elkhashab
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "ERROR_STATES.h"
#include "MIIC_int.h"
#include "HEEPROM_priv.h"
#include "HEEPROM_config.h"
#include "HEEPROM_int.h"

ErrorState_t HEEPROM_enInit()
{
	MIIC_enInit();

	return SUCCESS;
}

ErrorState_t HEEPROM_enWriteByte(u16 copy_u16Address, u8 copy_u8Byte)
{
	u8 Status;

	// Send Start
	MIIC_enSendStart();

	// Check Status
	MIIC_enReadStatus(&Status);
	if(Status != MTWI_MR_START_SUCCESS)
	{
		return FALIUR;
	}

	// Send Address 1010 + A10 A9 A8 + W
	u8 _3MSB = (u8) (copy_u16Address & 0x0700) >> 7;
	MIIC_enSendByte(_3MSB | 0xA0);

	// Check Status
	MIIC_enReadStatus(&Status);
	if (Status != MTWI_MT_SLA_W_ACK)
	{
		return FALIUR;
	}

	// Send Rest of Byte Address as Data A7 .... A0
	MIIC_enSendByte((u8) copy_u16Address);

	// Check Status
	MIIC_enReadStatus(&Status);
	if (Status != MTWI_MT_DATA_ACK)
	{
		return FALIUR;
	}

	// Send Byte to be Written
	MIIC_enSendByte(copy_u8Byte);

	// Check Status
	MIIC_enReadStatus(&Status);
	if (Status != MTWI_MT_DATA_ACK)
	{
		return FALIUR;
	}

	// Send Stop
	MIIC_enSendStop();

	return SUCCESS;
}

ErrorState_t HEEPROM_enReadByte(u16 copy_u16Address, u8 *ptrData)
{
	u8 Status;

	// Send Start
	MIIC_enSendStart();

	// Check Status
	MIIC_enReadStatus(&Status);
	if (Status != MTWI_MR_START_SUCCESS)
	{
		return FALIUR;
	}

	// Send Address 1010 + A10 A9 A8 + W
	u8 _3MSB = (u8) (copy_u16Address & 0x0700) >> 7;
	MIIC_enSendByte(_3MSB | 0xA0);

	// Check Status
	MIIC_enReadStatus(&Status);
	if (Status != MTWI_MT_SLA_W_ACK)
	{
		return FALIUR;
	}

	// Send Rest of Byte Address as Data A7 .... A0
	MIIC_enSendByte((u8) copy_u16Address);

	// Check Status
	MIIC_enReadStatus(&Status);
	if (Status != MTWI_MT_DATA_ACK)
	{
		return FALIUR;
	}

	// Send Repeated
	MIIC_enSendStart();

	// Check Status
	MIIC_enReadStatus(&Status);
	if(Status != MTWI_MR_REPEATED_START_SUCCESS)
	{
		return FALIUR;
	}

	// Send Address 1010 + 000 + R
	MIIC_enSendByte(0xA0 | 0x01);

	// Check Status
	MIIC_enReadStatus(&Status);
	if(Status != MTWI_MR_SLA_R_ACK)
	{
		return FALIUR;
	}

	// Read
	MIIC_enReceiverByteACK(ptrData);

	// Check Status
	MIIC_enReadStatus(&Status);
	if (Status != MTWI_MR_DATA_ACK)
	{
		return FALIUR;
	}

	// Send Stop
	MIIC_enSendStop();

	return SUCCESS;
}
