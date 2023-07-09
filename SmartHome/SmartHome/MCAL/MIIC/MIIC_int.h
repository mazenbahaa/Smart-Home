/*
 * MIIC_int.h
 *
 *  Created on: Jun 21, 2023
 *      Author: Elkhashab
 */

#ifndef MIIC_MIIC_INT_H_
#define MIIC_MIIC_INT_H_

/*
 * Master Mode
 */
// MT Status Codes
#define MTWI_MT_START_SUCCESS	0x08
#define MTWI_MT_REPEATED_START_SUCCESS	0x10
#define MTWI_MT_SLA_W_ACK	0x18
#define MTWI_MT_SLA_W_NOACK	0x20
#define MTWI_MT_DATA_ACK	0x28
#define MTWI_MT_DATA_NOACK	0x30
#define MTWI_MT_ARBITRATION_LOST	0x38

// MR Status Codes
#define MTWI_MR_START_SUCCESS	0x08
#define MTWI_MR_REPEATED_START_SUCCESS	0x10
#define MTWI_MR_SLA_R_ACK	0x40
#define MTWI_MR_SLA_R_NOACK	0x48
#define MTWI_MR_DATA_ACK	0x50
#define MTWI_MR_DATA_NOACK	0x58
#define MTWI_MR_ARBITRATION_LOST	0x38

ErrorState_t MIIC_enInit(void);
ErrorState_t MIIC_enSendStart(void);
ErrorState_t MIIC_enSendStop(void);
ErrorState_t MIIC_enSendByte(u8 copy_u8data);	// Master Transmitter
ErrorState_t MIIC_enReceiverByteACK(u8 *ptrReceiveData);		// Master Receiver
ErrorState_t MIIC_enReceiverByteNoACK(u8 *ptrReceiveData);	// Master Receiver
ErrorState_t MIIC_enReadStatus(u8 *ptrStatusValue);

#endif /* MIIC_MIIC_INT_H_ */
