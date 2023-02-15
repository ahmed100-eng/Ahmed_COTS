#include "STD_TYPES.h"
#include "defines.h"
#include <util/delay.h>

#include "TWI_interface.h"

#include "EEPROM_interface.h"
#include "EEPROM_cfg.h"
#include "EEPROM_priv.h"

uint8 EEPROM_voidWriteDataByte(uint16 Copy_u16LocAddress,uint8 Copy_u8DataByte)
{
	uint8 Local_u8ErrorState = OK;

	if(Copy_u16LocAddress <= EEPROM_MAX_ADDRESS)
	{
       uint8 Local_u8AddressPacket = EEPROM_FIXED_ADDRESS | (EEPROM_A2_CONNECTION<<2u | (uint8)((Copy_u16LocAddress)>>8u));
       TWI_SendStartCondition();

       /*Send the address packet with the fixed address and the A2 connection*/
       TWI_SendSlaveAdressWithWrite(Local_u8AddressPacket);

       /*Send a data packet with the least 8 bits of the location address*/
       TWI_MstrWriteDataByte((uint8) Copy_u16LocAddress);

       /*Send a data packet to the location address*/
       TWI_MstrWriteDataByte(Copy_u8DataByte);

       TWI_voidStopCondition();

       /*wait for 10ms for EEPROM write cycle*/
       _delay_ms(10);
	}
	else
	{
		Local_u8ErrorState = NOK;
	}

	return Local_u8ErrorState;
}
uint8 EEPROM_voidReadDataByte(uint16 Copy_u16LocAddress,uint8 *Copy_u8DataByte)
{
	uint8 Local_u8ErrorState= OK;


	if(Copy_u8DataByte != NULL)
	{
		if(Copy_u16LocAddress <= EEPROM_MAX_ADDRESS)
		{
	       uint8 Local_u8AddressPacket = EEPROM_FIXED_ADDRESS | (EEPROM_A2_CONNECTION<<2u | (uint8)((Copy_u16LocAddress)>>8u));
	       TWI_SendStartCondition();

	       /*Send the address packet with the fixed address and the A2 connection*/
           TWI_SendSlaveAdressWithWrite(Local_u8AddressPacket);

           /*Send a data packet with the least 8 bits of the location address*/
           TWI_MstrWriteDataByte((uint8) Copy_u16LocAddress);

           /*Send Repeated Start to read data*/
           TWI_SendReapeatedStart();

           /*Send Slave Address with read*/
           TWI_SendSlaveAdressWithRead(Local_u8AddressPacket);


           /*Read a data packet from the location address*/
           TWI_MstrReadDataByte(Copy_u8DataByte);

           TWI_voidStopCondition();
		}
		else
		{
			Local_u8ErrorState = NOK;
		}
	}
	else
	{
		Local_u8ErrorState = NULL_PTR_ERR;
	}

	return Local_u8ErrorState;
}
