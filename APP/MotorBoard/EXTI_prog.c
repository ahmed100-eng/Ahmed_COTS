#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "defines.h"

#include "EXTI_interface.h"
#include "EXTI_cfg.h"
#include "EXTI_private.h"
#include "EXTI_reg.h"


static FuncPtr EXTI_pfCallBack[3] = {NULL}/*Array of pointers to function to hold ISR callbacks*/;


void EXTI_voidInit(void)
{
	/*implement INT0 sense control configuration*/
#if INT0_SENSE_CTRL == EXTI_u8LOW_LEVEL
	CLR_BIT(MCUCR,MCUCR_ISC00);
	CLR_BIT(MCUCR,MCUCR_ISC01);
#elif INT0_SENSE_CTR == EXTI_u8ON_CHANGE
	SET_BIT(MCUCR,MCUCR_ISC00);
	CLR_BIT(MCUCR,MCUCR_ISC01);
#elif INT0_SENSE_CTRL  ==  EXTI_u8FALLINGEDGE
	CLR_BIT(MCUCR,MCUCR_ISC00);
	SET_BIT(MCUCR,MCUCR_ISC01);
#elif INT0_SENSE_CTRL== EXTI_u8RISINGEDGE
	SET_BIT(MCUCR,MCUCR_ISC01);
	SET_BIT(MCUCR,MCUCR_ISC00);
#else
#error Wrong INT0_SENSE_CTRL configuration option
#endif
	/*implement INT0 intial state configuration*/
#if INT0_INTIAL_STATE == DISABLED
	CLR_BIT(GICR,GICR_INT0);
#elif INT0_INTIAL_STATE == ENABLED
	SET_BIT(GICR,GICR_INT0);
#else
#error wrong INT0_INTIAL_STATE configuration macro
#endif
	/*implement INT1 sense control configuration*/
#if INT1_SENSE_CTRL == EXTI_u8LOW_LEVEL
	CLR_BIT(MCUCR,MCUCR_ISC10);
	CLR_BIT(MCUCR,MCUCR_ISC11);
#elif INT1_SENSE_CTR == EXTI_u8ON_CHANGE
	SET_BIT(MCUCR,MCUCR_ISC10);
	CLR_BIT(MCUCR,MCUCR_ISC11);
#elif INT1_SENSE_CTRL  ==  EXTI_u8FALLINGEDGE
	CLR_BIT(MCUCR,MCUCR_ISC10);
	SET_BIT(MCUCR,MCUCR_ISC11);
#elif INT1_SENSE_CTRL== EXTI_u8RISINGEDGE
	SET_BIT(MCUCR,MCUCR_ISC10);
	SET_BIT(MCUCR,MCUCR_ISC11);
#else
#error Wrong INT1_SENSE_CTRL configuration option
#endif
	/*implement INT1 intial state configuration*/
#if INT1_INTIAL_STATE == DISABLED
	CLR_BIT(GICR,GICR_INT1);
#elif INT1_INTIAL_STATE == ENABLED
	SET_BIT(GICR,GICR_INT1);
#else
#error wrong INT1_INTIAL_STATE configuration macro
#endif
	/*implement INT2 sense control configuration*/
#if INT2_SENSE_CTRL  ==  EXTI_u8FALLINGEDGE
	CLR_BIT(MCUCSR,MCUCSR_ISC2);
#elif INT2_SENSE_CTRL== EXTI_u8RISINGEDGE
	SET_BIT(MCUCSR,MCUCSR_ISC2);
#else
#error Wrong INT2_SENSE_CTRL configuration option
#endif
	/*implement INT2 intial state configuration*/
#if INT2_INTIAL_STATE == DISABLED
	CLR_BIT(GICR,GICR_INT2);
#elif INT2_INTIAL_STATE == ENABLED
	SET_BIT(GICR,GICR_INT2);
#else
#error wrong INT2_INTIAL_STATE configuration macro
#endif

}

uint8 EXTI_u8SenseCtrl(uint8 Copy_u8IntNum,uint8 Copy_u8Sense)
{
    uint8 Local_u8ErrorState=OK;
    switch  (Copy_u8IntNum)
    {
    case EXTI_u8INT0 :
    	switch(Copy_u8Sense)
    	{
    	case EXTI_u8LOW_LEVEL : CLR_BIT(MCUCR,MCUCR_ISC00);CLR_BIT(MCUCR,MCUCR_ISC01);break;
    	case EXTI_u8ON_CHANGE : SET_BIT(MCUCR,MCUCR_ISC00);CLR_BIT(MCUCR,MCUCR_ISC01);break;
    	case EXTI_u8FALLINGEDGE : CLR_BIT(MCUCR,MCUCR_ISC00);SET_BIT(MCUCR,MCUCR_ISC01);break;
    	case EXTI_u8RISINGEDGE : SET_BIT(MCUCR,MCUCR_ISC00);SET_BIT(MCUCR,MCUCR_ISC01);break;
    	default : Local_u8ErrorState=NOK;break;
    	}break;
        case EXTI_u8INT1 :
        	switch(Copy_u8Sense)
        	{
        	case EXTI_u8LOW_LEVEL : CLR_BIT(MCUCR,MCUCR_ISC10);CLR_BIT(MCUCR,MCUCR_ISC11);break;
        	case EXTI_u8ON_CHANGE : SET_BIT(MCUCR,MCUCR_ISC10);CLR_BIT(MCUCR,MCUCR_ISC11);break;
        	case EXTI_u8FALLINGEDGE : CLR_BIT(MCUCR,MCUCR_ISC10);SET_BIT(MCUCR,MCUCR_ISC11);break;
        	case EXTI_u8RISINGEDGE : SET_BIT(MCUCR,MCUCR_ISC10);SET_BIT(MCUCR,MCUCR_ISC11);break;
        	default : Local_u8ErrorState=NOK;break;
    	}break;
    case EXTI_u8INT2 :
    	switch(Copy_u8Sense)
    	{
    	case EXTI_u8FALLINGEDGE : CLR_BIT(MCUCSR,MCUCSR_ISC2);break;
    	case EXTI_u8RISINGEDGE : SET_BIT(MCUCSR,MCUCSR_ISC2);break;
    	default : Local_u8ErrorState=NOK;break;
    	}break;
    default : Local_u8ErrorState=NOK;break;
    }
    return Local_u8ErrorState;
}

uint8 EXTI_u8IntEnable(uint8 Copy_u8IntNum)
{
    uint8 Local_u8ErrorState = OK;
    switch(Copy_u8IntNum)
    {
    case EXTI_u8INT0 : SET_BIT(GICR,GICR_INT0);break;
    case EXTI_u8INT1 : SET_BIT(GICR,GICR_INT1);break;
    case EXTI_u8INT2 : SET_BIT(GICR,GICR_INT2);break;
    default : Local_u8ErrorState=NOK;break;
    }
    return Local_u8ErrorState;
}
uint8 EXTI_u8IntDisable(uint8 Copy_u8IntNum)
{
    uint8 Local_u8ErrorState = OK;
    switch(Copy_u8IntNum)
    {
    case EXTI_u8INT0 : CLR_BIT(GICR,GICR_INT0);break;
    case EXTI_u8INT1 : CLR_BIT(GICR,GICR_INT1);break;
    case EXTI_u8INT2 : CLR_BIT(GICR,GICR_INT2);break;
    default : Local_u8ErrorState=NOK;break;
    }
    return Local_u8ErrorState;
}
uint8 EXTI_u8SetCallBack(uint8 Copy_u8IntNum,FuncPtr Copy_pfFuncPtr)
{
	uint8 Local_u8ErrorState = OK;
	if (Copy_pfFuncPtr != NULL)
	{
		 EXTI_pfCallBack[Copy_u8IntNum]=Copy_pfFuncPtr;
	}
	else
	{
		Local_u8ErrorState=NULL_PTR_ERR;
	}
	return Local_u8ErrorState;
}
void __vector_1 (void) __attribute__((signal));
void __vector_1 (void)
{
	if(EXTI_pfCallBack[EXTI_u8INT0] != NULL)
	{
		EXTI_pfCallBack[EXTI_u8INT0]();
	}

}
void __vector_2 (void) __attribute__((signal));
void __vector_2 (void)
{
	if(EXTI_pfCallBack[EXTI_u8INT1] != NULL)
	{
		EXTI_pfCallBack[EXTI_u8INT1]();
	}

}
void __vector_3 (void) __attribute__((signal));
void __vector_3 (void)
{
	if(EXTI_pfCallBack[EXTI_u8INT2] != NULL)
	{
		EXTI_pfCallBack[EXTI_u8INT2]();
	}

}
