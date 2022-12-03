/**************************************************************/
/**************************************************************/
/*********		Author: Ahmed Abdelaziz			*******************/
/*********		File: SW_prog.c		*******************/
/*********		Version: 1.00				*******************/
/**************************************************************/
#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "DIO_interface.h"
#include "SW_private.h"
#include "SW_interface.h"






uint8 SW_u8State(Switch_t * Copy_pSwitch,uint8 *Copy_pState)
{
   uint8 Local_u8ErrorState=OK;
   uint8 Local_u8Switchvalue;
   if(Copy_pSwitch!=NULL && Copy_pState!=NULL)
   {
	  if (Copy_pSwitch->SW_u8PullType==PULLUP)
	  {
         DIO_u8GetPinValue(Copy_pSwitch->SW_u8Port,Copy_pSwitch->SW_u8Pin,&Local_u8Switchvalue);
         if(Local_u8Switchvalue==DIO_u8PIN_LOW)
         {
        	 while(Local_u8Switchvalue==DIO_u8PIN_LOW)
             {
        		 DIO_u8GetPinValue(Copy_pSwitch->SW_u8Port,Copy_pSwitch->SW_u8Pin,&Local_u8Switchvalue);
           	 }

        	 *Copy_pState=PRESSED;

         }
         else if(Local_u8Switchvalue==DIO_u8PIN_HIGH)
         {
        	 *Copy_pState= RELEASED;
         }
	  }
	  else if (Copy_pSwitch->SW_u8PullType==PULLDOWN)
	  {
	     DIO_u8GetPinValue(Copy_pSwitch->SW_u8Port,Copy_pSwitch->SW_u8Pin,&Local_u8Switchvalue);
	     if(Local_u8Switchvalue==DIO_u8PIN_HIGH)
	      {
        	 while(Local_u8Switchvalue==DIO_u8PIN_HIGH)
             {
        		 DIO_u8GetPinValue(Copy_pSwitch->SW_u8Port,Copy_pSwitch->SW_u8Pin,&Local_u8Switchvalue);
           	 }

	      	*Copy_pState=PRESSED;

	      }
	      else if(Local_u8Switchvalue==DIO_u8PIN_LOW)
	      {
	      	 *Copy_pState= RELEASED;
	      }
	  }
   }
   else
   {
	   Local_u8ErrorState=NULL_PTR_ERR;
   }
   return Local_u8ErrorState;
}
