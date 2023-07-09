/*
 * MIIC_prg.c
 *
 *  Created on: Jun 21, 2023
 *      Author: Elkhashab
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "ERROR_STATES.h"
#include "MIIC_priv.h"
#include "MIIC_config.h"
#include "MIIC_int.h"

ErrorState_t MIIC_enInit(void)
{
	// Speed = 400 KHZ at FCPU = 8 MHZ, Prescaler = 1
	// Config Speed -> 400 KHZ	(TWBR Register, Prescaler Bits)
	CLR_BIT(TWSR_REG, TWPS0_BIT);
	CLR_BIT(TWSR_REG, TWPS1_BIT);

	TWBR_REG = 0x02;

	// Enable TWI (Turn ON)
	SET_BIT(TWCR_REG, TWEN_BIT);
}

ErrorState_t MIIC_enSendStart(void)
{
	// Clear Flag + Set Start Bit + Enable TWI
	TWCR_REG = (1 << TWINT_BIT) | (1 << TWSTA_BIT) | (1 << TWEN_BIT);

	// Wait Until Operation is Done
	while(!(TWCR_REG & (1 << TWINT_BIT)));

	return SUCCESS;
}

ErrorState_t MIIC_enSendStop(void)
{
	TWCR_REG = (1 << TWINT_BIT) | (1 << TWEN_BIT) | (1 << TWSTO_BIT);

	return SUCCESS;
}

ErrorState_t MIIC_enSendByte(u8 copy_u8data)
{
	// Load Data Into Data Register
	TWDR_REG = copy_u8data;

	// Clear Flag + Set Enable
	TWCR_REG = (1 << TWINT_BIT) | (1 << TWEN_BIT);

	// Wait Until Operation is Done
	while (!(TWCR_REG & (1 << TWINT_BIT)));

	return SUCCESS;
}

ErrorState_t MIIC_enReceiverByteACK(u8 *ptrReceiveData)
{
	// Clear Flag + Set Enable + Set ACK Bit
	TWCR_REG = (1 << TWINT_BIT) | (1 << TWEN_BIT) | (1 << TWEA_BIT);

	// Wait Until Operation is Done
	while (!(TWCR_REG & (1 << TWINT_BIT)));

	// Load Received Byte Into Pointer
	*ptrReceiveData = TWDR_REG;

	return SUCCESS;
}

ErrorState_t MIIC_enReceiverByteNoACK(u8 *ptrReceiveData)
{
	// Clear Flag + Set Enable + Set ACK Bit
	TWCR_REG = (1 << TWINT_BIT) | (1 << TWEN_BIT);

	// Wait Until Operation is Done
	while (!(TWCR_REG & (1 << TWINT_BIT)));

	// Load Received Byte Into Pointer
	*ptrReceiveData = TWDR_REG;

	return SUCCESS;
}

ErrorState_t MIIC_enReadStatus(u8 *ptrStatusValue)
{
	// Apply Mask on Status Register and Return Status Code
	*ptrStatusValue = TWSR_REG & MTWI_STATUS_MASK;

	return SUCCESS;
}
