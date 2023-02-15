/*
 * TWI_interface.h
 *
 *  Created on: Jan 24, 2023
 *      Author: Pc
 */

#ifndef TWI_INTERFACE_H_
#define TWI_INTERFACE_H_

typedef enum
{
	NoError,
	NULLPtrErr,
	StartConditionErr,
	RepStartErr,
	SlaveAddressWithWriteErr,
	SlaveAddressWithReadErr,
	MstrWriteByteWithAckErr,
	MstrReadByteWithAck
}TWI_ErrorState_t;

void TWI_voidMasterInit(uint8 Copy_u8Address);
void TWI_voidSlaveInit(uint8 Copy_u8Address);
TWI_ErrorState_t TWI_SendStartCondition(void);
TWI_ErrorState_t TWI_SendReapeatedStart(void);
TWI_ErrorState_t TWI_SendSlaveAdressWithWrite(uint8 Copy_u8Address);
TWI_ErrorState_t TWI_SendSlaveAdressWithRead(uint8 Copy_u8Address);
TWI_ErrorState_t TWI_MstrWriteDataByte(uint8 Copy_Data);
TWI_ErrorState_t TWI_MstrReadDataByte(uint8 *Copy_Data);
void TWI_voidStopCondition(void);

#endif /* TWI_INTERFACE_H_ */
