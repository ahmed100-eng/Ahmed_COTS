/**************************************************************/
/**************************************************************/
/*********		Author: Amgad Samir			*******************/
/*********		File: PORT_interface.h		*******************/
/*********		Version: 1.00				*******************/
/**************************************************************/
/**************************************************************/


#include "STD_TYPES.h"

#include "DIO_interface.h"


#include "KPD_cfg.h"
#include "KPD_interface.h"
#include "KPD_private.h"


/*required: All row pins are input pulledup, all coulmn pins are output high*/
uint8 KPD_GetPressedKey(void)
{
	uint8 Local_u8PressedKey= KPD_u8NO_PRESSED_KEY_VAL;
	uint8 Local_u8RowCounter, Local_u8ColCounter, Local_u8KeyState;
    static uint8 Local_u8ColArr[KPD_u8COL_NUM]={KPD_u8COL1_PIN,KPD_u8COL2_PIN,KPD_u8COL3_PIN,KPD_u8COL4_PIN};
    static uint8 Local_u8RowArr[KPD_u8ROW_NUM]={KPD_u8ROW1_PIN,KPD_u8ROW2_PIN,KPD_u8ROW3_PIN,KPD_u8ROW4_PIN};
    static uint8 Local_u8KpPDArr[KPD_u8ROW_NUM][KPD_u8COL_NUM]= KPD_u8BUTTON_ARR;


	/*Activate column pins and read the rows*/
	for(Local_u8ColCounter=0;Local_u8ColCounter<KPD_u8COL_NUM;Local_u8ColCounter++)
	{
		/*Activate the current column*/
		DIO_u8SetPinValue(KPD_u8COLPORT,Local_u8ColArr[Local_u8ColCounter],DIO_u8PIN_LOW);

		for(Local_u8RowCounter=0;Local_u8RowCounter<KPD_u8ROW_NUM;Local_u8RowCounter++)
		{
			/*Read the current row*/
			DIO_u8GetPinValue(KPD_u8ROWPORT,Local_u8RowArr[Local_u8RowCounter],&Local_u8KeyState);
			if(Local_u8KeyState == DIO_u8PIN_LOW)
			{
				Local_u8PressedKey= Local_u8KpPDArr[Local_u8RowCounter][Local_u8ColCounter];

				while(Local_u8KeyState==DIO_u8PIN_LOW)
				{
					DIO_u8GetPinValue(KPD_u8ROWPORT,Local_u8RowArr[Local_u8RowCounter],&Local_u8KeyState);
				}
				return Local_u8PressedKey;
			}

		}
		DIO_u8SetPinValue(KPD_u8COLPORT,Local_u8ColArr[Local_u8ColCounter],DIO_u8PIN_HIGH);

	}

	return Local_u8PressedKey;
}
