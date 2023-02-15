
#include "defines.h"
#include "BIT_MATH.h"
#include "STD_TYPES.h"

#include "TWI_interface.h"
#include "TWI_cfg.h"
#include "TWI_private.h"
#include "TWI_reg.h"


void TWI_voidMasterInit(uint8 Copy_u8Address)
{
    if(Copy_u8Address != 0u)
    {
    	/*SET Mode Address*/
    	TWAR = Copy_u8Address << 1u;
    }
    /*CPU frequency = 16MHz*/
    CLR_BIT(TWSR,TWSR_TWPS0);
    CLR_BIT(TWSR,TWSR_TWPS1);
    TWBR =12u;
    /*Enable acknowledge*/
    SET_BIT(TWCR,TWCR_TWEA);
    SET_BIT(TWCR,TWCR_TWEN);
}
void TWI_voidSlaveInit(uint8 Copy_u8Address)
{
	   if(Copy_u8Address != 0u)
	    {
	    	/*SET Mode Address*/
	    	TWAR = Copy_u8Address << 1u;
	    }

	    SET_BIT(TWCR,TWCR_TWEN);
}
TWI_ErrorState_t TWI_SendStartCondition(void)
{
	TWI_ErrorState_t Local_Error = NoError;

	/*Set Start condition bit*/
	SET_BIT(TWCR,TWCR_TWSTA);
	/*Clear interrupt flag to enable previous action to happen*/
	SET_BIT(TWCR,TWCR_TWINT);

	/*wait until the previous action finishes and the interrupt flag is raised again*/
	while ((GET_BIT(TWCR,TWCR_TWINT)) == 0);

	if((TWSR & STATUS_BITS_MASK) != START_ACK)
	{
		Local_Error=StartConditionErr;
	}
	else
	{

	}
	return Local_Error;
}
TWI_ErrorState_t TWI_SendReapeatedStart(void)
{
	TWI_ErrorState_t Local_Error = NoError;

	/*Set Start condition bit*/
	SET_BIT(TWCR,TWCR_TWSTA);
	/*Clear interrupt flag to enable previous action to happen*/
	SET_BIT(TWCR,TWCR_TWINT);

	/*wait until the previous action finishes and the interrupt flag is raised again*/
	while ((GET_BIT(TWCR,TWCR_TWINT)) == 0);

	/*Check the status of the bus*/
	if((TWSR & STATUS_BITS_MASK) != REP_START_ACK)
	{
		Local_Error=RepStartErr;
	}
	else
	{

	}
	return Local_Error;
}
TWI_ErrorState_t TWI_SendSlaveAdressWithWrite(uint8 Copy_u8Address)
{
	TWI_ErrorState_t Local_Error = NoError;
    /*Set the slave adress into the data register*/
    TWDR=Copy_u8Address << 1u;

    /*Clear bit 0 for request*/
    CLR_BIT(TWDR,0u);
    /*Clear the start condition*/
    CLR_BIT(TWCR,TWCR_TWSTA);

	/*Clear interrupt flag to enable previous action to happen*/
	SET_BIT(TWCR,TWCR_TWINT);

	/*wait until the previous action finishes and the interrupt flag is raised again*/
	while ((GET_BIT(TWCR,TWCR_TWINT)) == 0);

	/*Check the status of the bus*/
	if((TWSR & STATUS_BITS_MASK) != SLAVE_ADD_AND_WR_ACK)
	{
		Local_Error=SlaveAddressWithWriteErr;
	}
	else
	{

	}
	return Local_Error;

}
TWI_ErrorState_t TWI_SendSlaveAdressWithRead(uint8 Copy_u8Address)
{
	TWI_ErrorState_t Local_Error = NoError;


    /*Set the slave address into the data register*/
    TWDR=Copy_u8Address << 1u;

    /*Set bit 0 for request*/
    SET_BIT(TWDR,0u);
    /*Clear the start condition*/
    CLR_BIT(TWCR,TWCR_TWSTA);

	/*Clear interrupt flag to enable previous action to happen*/
	SET_BIT(TWCR,TWCR_TWINT);

	/*wait until the previous action finishes and the interrupt flag is raised again*/
	while ((GET_BIT(TWCR,TWCR_TWINT)) == 0);

	/*Check the status of the bus*/
	if((TWSR & STATUS_BITS_MASK) != SLAVE_ADD_AND_RD_ACK)
	{
		Local_Error=SlaveAddressWithReadErr;
	}
	else
	{

	}

	return Local_Error;
}
TWI_ErrorState_t TWI_MstrWriteDataByte(uint8 Copy_Data)
{
	TWI_ErrorState_t Local_Error = NoError;

	/*Put the data byte on the bus*/
    TWDR = Copy_Data;


	/*Clear interrupt flag to enable previous action to happen*/
	SET_BIT(TWCR,TWCR_TWINT);

	/*wait until the previous action finishes and the interrupt flag is raised again*/
	while ((GET_BIT(TWCR,TWCR_TWINT)) == 0);

	/*Check the status of the bus*/
	if((TWSR & STATUS_BITS_MASK) != MSTR_WR_BYTE_ACK)
	{
		Local_Error=MstrWriteByteWithAckErr;
	}
	else
	{

	}

	return Local_Error;
}
TWI_ErrorState_t TWI_MstrReadDataByte(uint8 *Copy_Data)
{
	TWI_ErrorState_t Local_Error = NoError;

	if(Copy_Data != NULL)
	{
		/*Clear interrupt flag to enable Slave to send data*/
		SET_BIT(TWCR,TWCR_TWINT);
		/*wait until the slave writing finishes and the interrupt flag is raised again*/
		while ((GET_BIT(TWCR,TWCR_TWINT)) == 0);

		/*Check the status of the bus*/
		if((TWSR & STATUS_BITS_MASK) != MSTR_RD_BYTE_WITH_ACK)
		{
			Local_Error=MstrReadByteWithAck;
		}
		else
		{
			/*Read the data sent from slave*/
           *Copy_Data = TWDR;
		}

	}
	else
	{
		Local_Error = NULLPtrErr;
	}


	return Local_Error;
}
void TWI_voidStopCondition(void)
{
	/*Set the stop condition bit */
    SET_BIT(TWCR,TWCR_TWSTO);
	/*Clear interrupt flag to enable previous action to happen*/
	SET_BIT(TWCR,TWCR_TWINT);
}

