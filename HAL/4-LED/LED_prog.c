/**************************************************************/
/**************************************************************/
/*********		Author: Ahmed Abdelaziz			*******************/
/*********		File: LED_prog.c		*******************/
/*********		Version: 1.00				*******************/
/**************************************************************/


#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "DIO_interface.h"
#include "LED_private.h"

#include "LED_interface.h"

void LED_voidLedOn(uint8 Copy_u8Port,uint8 Copy_u8Pin,uint8 Copy_u8ConnectionType)
{
	if (Copy_u8ConnectionType==SinkConnecton)
	{
       DIO_u8SetPinValue(Copy_u8Port,Copy_u8Pin,DIO_u8PIN_LOW);
	}
	else if (Copy_u8ConnectionType==SourceConnection)
	{
		DIO_u8SetPinValue(Copy_u8Port,Copy_u8Pin,DIO_u8PIN_HIGH);
	}
}

void LED_voidLedOff(uint8 Copy_u8Port,uint8 Copy_u8Pin,uint8 Copy_u8ConnectionType)
{
	if (Copy_u8ConnectionType==SinkConnecton)
	{
       DIO_u8SetPinValue(Copy_u8Port,Copy_u8Pin,DIO_u8PIN_HIGH);
	}
	else if (Copy_u8ConnectionType==SourceConnection)
	{
		DIO_u8SetPinValue(Copy_u8Port,Copy_u8Pin,DIO_u8PIN_LOW);
	}
}
void LED_voidLedToggle(uint8 Copy_u8Port,uint8 Copy_u8Pin)
{
	DIO_u8TogglePinValue(Copy_u8Port,Copy_u8Pin);
}
