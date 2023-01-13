/**************************************************************/
/**************************************************************/
/*********		Author: Ahmed Abdelaziz			*******************/
/*********		File: DCM_prog.c		*******************/
/*********		Version: 1.00				*******************/
/**************************************************************/

#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "DIO_interface.h"
#include "DCM_private.h"

#include "DCM_interface.h"


uint8 DCM_u8CW(DCM_cfg * Copy_pDCMcfg)
{
    uint8 Local_u8ErrorState=OK;
    if(Copy_pDCMcfg!=NULL)
    {
    	DIO_u8SetPinValue(Copy_pDCMcfg->DCM_u8SwitchPort,Copy_pDCMcfg->DCM_u8Switch1Pin,DIO_u8PIN_LOW);
        DIO_u8SetPinValue(Copy_pDCMcfg->DCM_u8SwitchPort,Copy_pDCMcfg->DCM_u8Switch2Pin,DIO_u8PIN_LOW);
        DIO_u8SetPinValue(Copy_pDCMcfg->DCM_u8SwitchPort,Copy_pDCMcfg->DCM_u8Switch3Pin,DIO_u8PIN_LOW);
        DIO_u8SetPinValue(Copy_pDCMcfg->DCM_u8SwitchPort,Copy_pDCMcfg->DCM_u8Switch4Pin,DIO_u8PIN_LOW);

        DIO_u8SetPinValue(Copy_pDCMcfg->DCM_u8SwitchPort,Copy_pDCMcfg->DCM_u8Switch1Pin,DIO_u8PIN_HIGH);
        DIO_u8SetPinValue(Copy_pDCMcfg->DCM_u8SwitchPort,Copy_pDCMcfg->DCM_u8Switch4Pin,DIO_u8PIN_HIGH);
    }
    else
    {
    	Local_u8ErrorState=NULL_PTR_ERR;

    }
    return Local_u8ErrorState;
}

uint8 DCM_u8CCW(DCM_cfg * Copy_pDCMcfg)
{
    uint8 Local_u8ErrorState=OK;
    if(Copy_pDCMcfg!=NULL)
    {
    	   DIO_u8SetPinValue(Copy_pDCMcfg->DCM_u8SwitchPort,Copy_pDCMcfg->DCM_u8Switch1Pin,DIO_u8PIN_LOW);
    	   DIO_u8SetPinValue(Copy_pDCMcfg->DCM_u8SwitchPort,Copy_pDCMcfg->DCM_u8Switch2Pin,DIO_u8PIN_LOW);
    	   DIO_u8SetPinValue(Copy_pDCMcfg->DCM_u8SwitchPort,Copy_pDCMcfg->DCM_u8Switch3Pin,DIO_u8PIN_LOW);
    	   DIO_u8SetPinValue(Copy_pDCMcfg->DCM_u8SwitchPort,Copy_pDCMcfg->DCM_u8Switch4Pin,DIO_u8PIN_LOW);

    	   DIO_u8SetPinValue(Copy_pDCMcfg->DCM_u8SwitchPort,Copy_pDCMcfg->DCM_u8Switch2Pin,DIO_u8PIN_HIGH);
    	   DIO_u8SetPinValue(Copy_pDCMcfg->DCM_u8SwitchPort,Copy_pDCMcfg->DCM_u8Switch3Pin,DIO_u8PIN_HIGH);
    }
    else
    {
    	Local_u8ErrorState=NULL_PTR_ERR;

    }
    return Local_u8ErrorState;


}

uint8 DCM_u8Brake(DCM_cfg * Copy_pDCMcfg)
{
    uint8 Local_u8ErrorState=OK;
    if(Copy_pDCMcfg!=NULL)
    {
        DIO_u8SetPinValue(Copy_pDCMcfg->DCM_u8SwitchPort,Copy_pDCMcfg->DCM_u8Switch1Pin,DIO_u8PIN_LOW);
        DIO_u8SetPinValue(Copy_pDCMcfg->DCM_u8SwitchPort,Copy_pDCMcfg->DCM_u8Switch2Pin,DIO_u8PIN_LOW);
        DIO_u8SetPinValue(Copy_pDCMcfg->DCM_u8SwitchPort,Copy_pDCMcfg->DCM_u8Switch3Pin,DIO_u8PIN_LOW);
        DIO_u8SetPinValue(Copy_pDCMcfg->DCM_u8SwitchPort,Copy_pDCMcfg->DCM_u8Switch4Pin,DIO_u8PIN_LOW);
#if SW_BRAKECIRCUIT  ==  ENABLE
        DIO_u8SetPinValue(Copy_pDCMcfg->DCM_u8SwitchPort,Copy_pDCMcfg->DCM_u8Switch3Pin,DIO_u8PIN_HIGH);
        DIO_u8SetPinValue(Copy_pDCMcfg->DCM_u8SwitchPort,Copy_pDCMcfg->DCM_u8Switch4Pin,DIO_u8PIN_HIGH);
#endif
    }
    else
    {
    	Local_u8ErrorState=NULL_PTR_ERR;

    }
    return Local_u8ErrorState;


}
