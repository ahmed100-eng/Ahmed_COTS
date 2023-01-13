#include "BIT_MATH.h"
#include "STD_TYPES.h"


#include "DIO_interface.h"
#include "STM_interface.h"
#include <util/delay.h>

/**
 * @brief This function is used for rotating the stepper motor in Clock wise direction
 * @param Copy_pSTMCfg :This parameter is a pointer to struct include the motor pins and port
 * @param Copy_u16Angel: This parameter is for the angle that user want
 * @return
 */

uint8 STM_CW(const Stepper_t* Copy_pSTMCfg,uint16 Copy_u16Angel)
{
   uint8 Local_u8ErrorState=OK;
   uint16 Local_u16Steps=0,Local_u16LoopCounter=0;
   if(Copy_pSTMCfg!=NULL)
   {
	   Local_u16Steps=(uint16)((uint32)Copy_u16Angel*2048ul/360ul);
	   for(Local_u16LoopCounter=0;Local_u16LoopCounter<Local_u16Steps/4;Local_u16LoopCounter++)
	   {
		   DIO_u8SetPinValue(Copy_pSTMCfg->STM_u8Port,Copy_pSTMCfg->STM_u8Pink,DIO_u8PIN_HIGH);
		   DIO_u8SetPinValue(Copy_pSTMCfg->STM_u8Port,Copy_pSTMCfg->STM_u8Yellow,DIO_u8PIN_HIGH);
		   DIO_u8SetPinValue(Copy_pSTMCfg->STM_u8Port,Copy_pSTMCfg->STM_u8Orange,DIO_u8PIN_HIGH);
		   DIO_u8SetPinValue(Copy_pSTMCfg->STM_u8Port,Copy_pSTMCfg->STM_u8Blue,DIO_u8PIN_LOW);
		   _delay_ms(2);
		   DIO_u8SetPinValue(Copy_pSTMCfg->STM_u8Port,Copy_pSTMCfg->STM_u8Blue,DIO_u8PIN_HIGH);
		   DIO_u8SetPinValue(Copy_pSTMCfg->STM_u8Port,Copy_pSTMCfg->STM_u8Yellow,DIO_u8PIN_HIGH);
		   DIO_u8SetPinValue(Copy_pSTMCfg->STM_u8Port,Copy_pSTMCfg->STM_u8Orange,DIO_u8PIN_HIGH);
		   DIO_u8SetPinValue(Copy_pSTMCfg->STM_u8Port,Copy_pSTMCfg->STM_u8Pink,DIO_u8PIN_LOW);
		   _delay_ms(2);
		   DIO_u8SetPinValue(Copy_pSTMCfg->STM_u8Port,Copy_pSTMCfg->STM_u8Blue,DIO_u8PIN_HIGH);
		   DIO_u8SetPinValue(Copy_pSTMCfg->STM_u8Port,Copy_pSTMCfg->STM_u8Pink,DIO_u8PIN_HIGH);
		   DIO_u8SetPinValue(Copy_pSTMCfg->STM_u8Port,Copy_pSTMCfg->STM_u8Orange,DIO_u8PIN_HIGH);
		   DIO_u8SetPinValue(Copy_pSTMCfg->STM_u8Port,Copy_pSTMCfg->STM_u8Yellow,DIO_u8PIN_LOW);
		   _delay_ms(2);
		   DIO_u8SetPinValue(Copy_pSTMCfg->STM_u8Port,Copy_pSTMCfg->STM_u8Blue,DIO_u8PIN_HIGH);
		   DIO_u8SetPinValue(Copy_pSTMCfg->STM_u8Port,Copy_pSTMCfg->STM_u8Pink,DIO_u8PIN_HIGH);
		   DIO_u8SetPinValue(Copy_pSTMCfg->STM_u8Port,Copy_pSTMCfg->STM_u8Yellow,DIO_u8PIN_HIGH);
		   DIO_u8SetPinValue(Copy_pSTMCfg->STM_u8Port,Copy_pSTMCfg->STM_u8Orange,DIO_u8PIN_LOW);
		   _delay_ms(2);

	   }
   }
   else
   {
	   Local_u8ErrorState=NULL_PTR_ERR;
   }
   return Local_u8ErrorState;
}
uint8 STM_CCW(const Stepper_t* Copy_pSTMCfg,uint16 Copy_u16Angel)
{
	   uint8 Local_u8ErrorState=OK;
	   uint16 Local_u16Steps=0,Local_u16LoopCounter=0;
	   if(Copy_pSTMCfg!=NULL)
	   {
		   Local_u16Steps=(uint16)((uint32)Copy_u16Angel*2048ul/360ul);
		   for(Local_u16LoopCounter=0;Local_u16LoopCounter<Local_u16Steps/4;Local_u16LoopCounter++)
		   {
			   DIO_u8SetPinValue(Copy_pSTMCfg->STM_u8Port,Copy_pSTMCfg->STM_u8Pink,DIO_u8PIN_HIGH);
			   DIO_u8SetPinValue(Copy_pSTMCfg->STM_u8Port,Copy_pSTMCfg->STM_u8Yellow,DIO_u8PIN_HIGH);
			   DIO_u8SetPinValue(Copy_pSTMCfg->STM_u8Port,Copy_pSTMCfg->STM_u8Orange,DIO_u8PIN_HIGH);
			   DIO_u8SetPinValue(Copy_pSTMCfg->STM_u8Port,Copy_pSTMCfg->STM_u8Blue,DIO_u8PIN_LOW);
			   _delay_ms(2);
			   DIO_u8SetPinValue(Copy_pSTMCfg->STM_u8Port,Copy_pSTMCfg->STM_u8Blue,DIO_u8PIN_HIGH);
			   DIO_u8SetPinValue(Copy_pSTMCfg->STM_u8Port,Copy_pSTMCfg->STM_u8Yellow,DIO_u8PIN_HIGH);
			   DIO_u8SetPinValue(Copy_pSTMCfg->STM_u8Port,Copy_pSTMCfg->STM_u8Pink,DIO_u8PIN_HIGH);
			   DIO_u8SetPinValue(Copy_pSTMCfg->STM_u8Port,Copy_pSTMCfg->STM_u8Orange,DIO_u8PIN_LOW);
			   _delay_ms(2);
			   DIO_u8SetPinValue(Copy_pSTMCfg->STM_u8Port,Copy_pSTMCfg->STM_u8Blue,DIO_u8PIN_HIGH);
			   DIO_u8SetPinValue(Copy_pSTMCfg->STM_u8Port,Copy_pSTMCfg->STM_u8Pink,DIO_u8PIN_HIGH);
			   DIO_u8SetPinValue(Copy_pSTMCfg->STM_u8Port,Copy_pSTMCfg->STM_u8Orange,DIO_u8PIN_HIGH);
			   DIO_u8SetPinValue(Copy_pSTMCfg->STM_u8Port,Copy_pSTMCfg->STM_u8Yellow,DIO_u8PIN_LOW);
			   _delay_ms(2);
			   DIO_u8SetPinValue(Copy_pSTMCfg->STM_u8Port,Copy_pSTMCfg->STM_u8Blue,DIO_u8PIN_HIGH);
			   DIO_u8SetPinValue(Copy_pSTMCfg->STM_u8Port,Copy_pSTMCfg->STM_u8Orange,DIO_u8PIN_HIGH);
			   DIO_u8SetPinValue(Copy_pSTMCfg->STM_u8Port,Copy_pSTMCfg->STM_u8Yellow,DIO_u8PIN_HIGH);
			   DIO_u8SetPinValue(Copy_pSTMCfg->STM_u8Port,Copy_pSTMCfg->STM_u8Pink,DIO_u8PIN_LOW);
			   _delay_ms(2);

		   }
	   }
	   return Local_u8ErrorState;
}

