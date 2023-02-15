/*
 * TIMER0_prog.c
 *
 *  Created on: ???/???/????
 *      Author: Sayed Abd-Elaziz
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "defines.h"

#include "TIMERS_interface.h"
#include "TIMERS_private.h"
#include "TIMERS_reg.h"
#include "TIMERS_cfg.h"
static void (*TIMERS_pvCallBackFuncArr[8])(void)={NULL};
uint8 Global_u8Timer1Prescaler=0;
uint8 TIMER0_u8Init(TIMER0_2_Cfg_t *Copy_stCfg)
{
	uint8 Local_u8Error_State=OK;
	if(Copy_stCfg!=NULL)
	{
		/*Select the wave form generation mode*/
		switch(Copy_stCfg->WFG_MODE)
		{
		case NORMAL_MODE : CLR_BIT(TCCR0,TCCR0_WGM00);CLR_BIT(TCCR0,TCCR0_COM01);break;/*Normal Mode configuration*/
		case CTC : CLR_BIT(TCCR0,TCCR0_WGM00);SET_BIT(TCCR0,TCCR0_COM01);break;/*CTC Mode configuration*/
		case FAST_PWM : SET_BIT(TCCR0,TCCR0_WGM00);SET_BIT(TCCR0,TCCR0_COM01);break;/*Fast PWM configuration*/
		case PHASE_CORRECT : SET_BIT(TCCR0,TCCR0_WGM00);CLR_BIT(TCCR0,TCCR0_COM01);break;/*Phase correct Mode configuration*/
		}
		/*configure the CTC mode */
		if(Copy_stCfg->WFG_MODE==CTC)
		{
           switch(Copy_stCfg->CTC_MODE)
           {
           case NORMAL_CTC : CLR_BIT(TCCR0,TCCR0_COM00);CLR_BIT(TCCR0,TCCR0_COM01);break; /*disconnect the pin*/
           case TOG_COMP   : SET_BIT(TCCR0,TCCR0_COM00);CLR_BIT(TCCR0,TCCR0_COM01);break; /*toggle the pin on Compare match*/
           case CLR_COMP   : CLR_BIT(TCCR0,TCCR0_COM00);SET_BIT(TCCR0,TCCR0_COM01);break; /*Clear the pin on Compare match*/
           case SET_COMP   : SET_BIT(TCCR0,TCCR0_COM00);SET_BIT(TCCR0,TCCR0_COM01);break; /*set the pin on Compare match*/
           }
		}
		else if (Copy_stCfg->WFG_MODE==FAST_PWM)
		{
          switch(Copy_stCfg->FASTPWM_MODE)
          {
          case NORMAL_PWM : CLR_BIT(TCCR0,TCCR0_COM00);CLR_BIT(TCCR0,TCCR0_COM01);break; /*disconnect the pin*/
          case SET_TOP_CLR_COMP   : CLR_BIT(TCCR0,TCCR0_COM00);SET_BIT(TCCR0,TCCR0_COM01);break; /*Clear the pin on Compare match set on top*/
          case CLR_TOP_SET_COMP   : SET_BIT(TCCR0,TCCR0_COM00);SET_BIT(TCCR0,TCCR0_COM01);break; /*set the pin on Compare match clear on top*/
          }
		}
		else if (Copy_stCfg->WFG_MODE==PHASE_CORRECT)
		{
          switch(Copy_stCfg->PHCORRECT_MODE)
          {
          case NORMAL_PWM : CLR_BIT(TCCR0,TCCR0_COM00);CLR_BIT(TCCR0,TCCR0_COM01);break; /*disconnect the pin*/
          case CLR_COMPUP_SET_COMPDOWN   : CLR_BIT(TCCR0,TCCR0_COM00);SET_BIT(TCCR0,TCCR0_COM01);break; /*Clear the pin on Compare match up counting set on compare match down counting*/
          case SET_COMPUP_CLR_COMPDOWN   : SET_BIT(TCCR0,TCCR0_COM00);SET_BIT(TCCR0,TCCR0_COM01);break; /*Clear the pin on Compare match down counting set on compare match up counting*/
          }
		}
		/*configure the presacler value*/
		TCCR0&=PRESCALERMASK;       /*Clear the prescaler bits*/
		TCCR0|=TIMER0_u8PRESCALER; 	   /*Select prescaler */
	}
	else
	{
		Local_u8Error_State=NULL_PTR_ERR;
	}
    return Local_u8Error_State;
}
void TIMER0_voidPreload_Val(uint8 Copy_u8Val)
{
	TCNT0=Copy_u8Val;
}
void TIMER0_void_Set_CompValue(uint8 Copy_u8Val)
{
	OCR0=Copy_u8Val;
}
void TIMER0_voidSet_CTCMode(TIMER0_2_OC_MODE_t Copy_enMode)
{
	switch(Copy_enMode)
	{
    case NORMAL_CTC : CLR_BIT(TCCR0,TCCR0_COM00);CLR_BIT(TCCR0,TCCR0_COM01);break; /*disconnect the pin*/
    case TOG_COMP   : SET_BIT(TCCR0,TCCR0_COM00);CLR_BIT(TCCR0,TCCR0_COM01);break; /*toggle the pin on Compare match*/
    case CLR_COMP   : CLR_BIT(TCCR0,TCCR0_COM00);SET_BIT(TCCR0,TCCR0_COM01);break; /*Clear the pin on Compare match*/
    case SET_COMP   : SET_BIT(TCCR0,TCCR0_COM00);SET_BIT(TCCR0,TCCR0_COM01);break; /*set the pin on Compare match*/
	}
}
void TIMER0_voidSet_FastPwmMode(TIMER0_2_FAST_PWM_MODE_t Copy_enMode)
{
	switch(Copy_enMode)
	{
    case NORMAL_PWM : CLR_BIT(TCCR0,TCCR0_COM00);CLR_BIT(TCCR0,TCCR0_COM01);break; /*disconnect the pin*/
    case SET_TOP_CLR_COMP   : CLR_BIT(TCCR0,TCCR0_COM00);SET_BIT(TCCR0,TCCR0_COM01);break; /*Clear the pin on Compare match set on top*/
    case CLR_TOP_SET_COMP   : SET_BIT(TCCR0,TCCR0_COM00);SET_BIT(TCCR0,TCCR0_COM01);break; /*set the pin on Compare match clear on top*/
	}
}
void TIMER0_voidSet_PHCorrectMode(TIMER0_2_PHCORRECT_PWM_MODE_t Copy_enMode)
{
	switch(Copy_enMode)
	{
    case NORMAL_PWM : CLR_BIT(TCCR0,TCCR0_COM00);CLR_BIT(TCCR0,TCCR0_COM01);break; /*disconnect the pin*/
    case CLR_COMPUP_SET_COMPDOWN   : CLR_BIT(TCCR0,TCCR0_COM00);SET_BIT(TCCR0,TCCR0_COM01);break; /*Clear the pin on Compare match up counting set on compare match down counting*/
    case SET_COMPUP_CLR_COMPDOWN   : SET_BIT(TCCR0,TCCR0_COM00);SET_BIT(TCCR0,TCCR0_COM01);break; /*Clear the pin on Compare match down counting set on compare match up counting*/
	}
}
uint8 TIMER2_u8Init(TIMER0_2_Cfg_t *Copy_stCfg)
{
	uint8 Local_u8Error_State=OK;
	if(Copy_stCfg!=NULL)
	{
		/*Select the wave form generation mode*/
		switch(Copy_stCfg->WFG_MODE)
		{
		case NORMAL_MODE : CLR_BIT(TCCR2,TCCR2_WGM20);CLR_BIT(TCCR2,TCCR2_WGM21);break;/*Normal Mode configuration*/
		case CTC : CLR_BIT(TCCR2,TCCR2_WGM20);SET_BIT(TCCR2,TCCR2_WGM21);break;/*CTC Mode configuration*/
		case FAST_PWM : SET_BIT(TCCR2,TCCR2_WGM20);SET_BIT(TCCR2,TCCR2_WGM21);break;/*Fast PWM configuration*/
		case PHASE_CORRECT : SET_BIT(TCCR2,TCCR2_WGM20);CLR_BIT(TCCR2,TCCR2_WGM21);break;/*Phase correct Mode configuration*/
		}
		/*configure the CTC mode */
		if(Copy_stCfg->WFG_MODE==CTC)
		{
           switch(Copy_stCfg->CTC_MODE)
           {
           case NORMAL_CTC : CLR_BIT(TCCR2,TCCR2_COM20);CLR_BIT(TCCR2,TCCR2_COM21);break; /*disconnect the pin*/
           case TOG_COMP   : SET_BIT(TCCR2,TCCR2_COM20);CLR_BIT(TCCR2,TCCR2_COM21);break; /*toggle the pin on Compare match*/
           case CLR_COMP   : CLR_BIT(TCCR2,TCCR2_COM20);SET_BIT(TCCR2,TCCR2_COM21);break; /*Clear the pin on Compare match*/
           case SET_COMP   : SET_BIT(TCCR2,TCCR2_COM20);SET_BIT(TCCR2,TCCR2_COM21);break; /*set the pin on Compare match*/
           }
		}
		else if (Copy_stCfg->WFG_MODE==FAST_PWM)
		{
          switch(Copy_stCfg->FASTPWM_MODE)
          {
          case NORMAL_PWM : CLR_BIT(TCCR2,TCCR2_COM20);CLR_BIT(TCCR2,TCCR2_COM21);break; /*disconnect the pin*/
          case SET_TOP_CLR_COMP   : CLR_BIT(TCCR2,TCCR2_COM20);SET_BIT(TCCR2,TCCR2_COM21);break; /*Clear the pin on Compare match set on top*/
          case CLR_TOP_SET_COMP   : SET_BIT(TCCR2,TCCR2_COM20);SET_BIT(TCCR2,TCCR2_COM21);break; /*set the pin on Compare match clear on top*/
          }
		}
		else if (Copy_stCfg->WFG_MODE==PHASE_CORRECT)
		{
          switch(Copy_stCfg->PHCORRECT_MODE)
          {
          case NORMAL_PWM : CLR_BIT(TCCR2,TCCR0_COM00);CLR_BIT(TCCR2,TCCR2_COM21);break; /*disconnect the pin*/
          case CLR_COMPUP_SET_COMPDOWN   : CLR_BIT(TCCR2,TCCR2_COM20);SET_BIT(TCCR2,TCCR2_COM21);break; /*Clear the pin on Compare match up counting set on compare match down counting*/
          case SET_COMPUP_CLR_COMPDOWN   : SET_BIT(TCCR2,TCCR2_COM20);SET_BIT(TCCR2,TCCR2_COM21);break; /*Clear the pin on Compare match down counting set on compare match up counting*/
          }
		}
		/*configure the presacler value*/
		TCCR2&=PRESCALERMASK;       /*Clear the prescaler bits*/
		TCCR2|=TIMER2_u8PRESCALER; 	   /*Select prescaler */
	}
	else
	{
		Local_u8Error_State=NULL_PTR_ERR;
	}
    return Local_u8Error_State;
}
void TIMER2_voidPreload_Val(uint8 Copy_u8Val)
{
	TCNT2=Copy_u8Val;

}
void TIMER2_void_Set_CompValue(uint8 Copy_u8Val)
{
	OCR2=Copy_u8Val;

}
void TIMER2_voidSet_CTCMode(TIMER0_2_OC_MODE_t Copy_enMode)
{
	switch(Copy_enMode)
	{
    case NORMAL_CTC : CLR_BIT(TCCR2,TCCR2_COM20);CLR_BIT(TCCR2,TCCR2_COM21);break; /*disconnect the pin*/
    case TOG_COMP   : SET_BIT(TCCR2,TCCR2_COM20);CLR_BIT(TCCR2,TCCR2_COM21);break; /*toggle the pin on Compare match*/
    case CLR_COMP   : CLR_BIT(TCCR2,TCCR2_COM20);SET_BIT(TCCR2,TCCR2_COM21);break; /*Clear the pin on Compare match*/
    case SET_COMP   : SET_BIT(TCCR2,TCCR2_COM20);SET_BIT(TCCR2,TCCR2_COM21);break; /*set the pin on Compare match*/
	}
}
void TIMER2_voidSet_FastPwmMode(TIMER0_2_FAST_PWM_MODE_t Copy_enMode)
{
	switch(Copy_enMode)
	{
    case NORMAL_PWM : CLR_BIT(TCCR0,TCCR2_COM20);CLR_BIT(TCCR2,TCCR2_COM21);break; /*disconnect the pin*/
    case SET_TOP_CLR_COMP   : CLR_BIT(TCCR2,TCCR2_COM20);SET_BIT(TCCR2,TCCR2_COM21);break; /*Clear the pin on Compare match set on top*/
    case CLR_TOP_SET_COMP   : SET_BIT(TCCR2,TCCR2_COM20);SET_BIT(TCCR2,TCCR2_COM21);break; /*set the pin on Compare match clear on top*/
	}
}
void TIMER2_voidSet_PHCorrectMode(TIMER0_2_PHCORRECT_PWM_MODE_t Copy_enMode)
{
	switch(Copy_enMode)
	{
    case NORMAL_PWM : CLR_BIT(TCCR2,TCCR2_COM20);CLR_BIT(TCCR2,TCCR2_COM21);break; /*disconnect the pin*/
    case CLR_COMPUP_SET_COMPDOWN   : CLR_BIT(TCCR2,TCCR2_COM20);SET_BIT(TCCR2,TCCR2_COM21);break; /*Clear the pin on Compare match up counting set on compare match down counting*/
    case SET_COMPUP_CLR_COMPDOWN   : SET_BIT(TCCR2,TCCR2_COM20);SET_BIT(TCCR2,TCCR2_COM21);break; /*Clear the pin on Compare match down counting set on compare match up counting*/
	}
}
uint8 TIMER1_voidInit(TIMER1_cfg_t *Copy_stCfg_Data)
{
	uint8 Local_u8ErrorState=OK;
	if(Copy_stCfg_Data != NULL)
	{
		/*Wave form generation mode selection */
       switch(Copy_stCfg_Data->WFG_MODE)
       {
       case TIMER1_NORMAL_MODE :
       {
    	   CLR_BIT(TCCR1A,TCCR1A_WGM10);
    	   CLR_BIT(TCCR1A,TCCR1A_WGM11);
    	   CLR_BIT(TCCR1B,TCCR1B_WGM12);
    	   CLR_BIT(TCCR1B,TCCR1B_WGM13);
       }break;
       case TIMER1_PHCRR_8bit :
       {
    	   SET_BIT(TCCR1A,TCCR1A_WGM10);
    	   CLR_BIT(TCCR1A,TCCR1A_WGM11);
    	   CLR_BIT(TCCR1B,TCCR1B_WGM12);
    	   CLR_BIT(TCCR1B,TCCR1B_WGM13);
       }break;
       case TIMER1_PHCRR_9bit :
       {
       	   CLR_BIT(TCCR1A,TCCR1A_WGM10);
           SET_BIT(TCCR1A,TCCR1A_WGM11);
           CLR_BIT(TCCR1B,TCCR1B_WGM12);
           CLR_BIT(TCCR1B,TCCR1B_WGM13);
       }break;
       case TIMER1_PHCRR_10bit :
       {
       	   SET_BIT(TCCR1A,TCCR1A_WGM10);
           SET_BIT(TCCR1A,TCCR1A_WGM11);
           CLR_BIT(TCCR1B,TCCR1B_WGM12);
           CLR_BIT(TCCR1B,TCCR1B_WGM13);
       }break;
       case TIMER1_CTC_OCR1A :
       {
       	   CLR_BIT(TCCR1A,TCCR1A_WGM10);
           CLR_BIT(TCCR1A,TCCR1A_WGM11);
           SET_BIT(TCCR1B,TCCR1B_WGM12);
           CLR_BIT(TCCR1B,TCCR1B_WGM13);
       }break;
       case TIMER1_FAST_PWM_8bit :
       {
       	   SET_BIT(TCCR1A,TCCR1A_WGM10);
           CLR_BIT(TCCR1A,TCCR1A_WGM11);
           SET_BIT(TCCR1B,TCCR1B_WGM12);
           CLR_BIT(TCCR1B,TCCR1B_WGM13);
       }break;
       case TIMER1_FAST_PWM_9bit :
       {
       	   CLR_BIT(TCCR1A,TCCR1A_WGM10);
           SET_BIT(TCCR1A,TCCR1A_WGM11);
           SET_BIT(TCCR1B,TCCR1B_WGM12);
           CLR_BIT(TCCR1B,TCCR1B_WGM13);
       }break;
       case TIMER1_FAST_PWM_10bit :
       {
       	   SET_BIT(TCCR1A,TCCR1A_WGM10);
           SET_BIT(TCCR1A,TCCR1A_WGM11);
           SET_BIT(TCCR1B,TCCR1B_WGM12);
           CLR_BIT(TCCR1B,TCCR1B_WGM13);
       }break;
       case TIMER1_PH_FRECRR_ICR1 :
       {
    	   CLR_BIT(TCCR1A,TCCR1A_WGM10);
    	   CLR_BIT(TCCR1A,TCCR1A_WGM11);
    	   CLR_BIT(TCCR1B,TCCR1B_WGM12);
    	   SET_BIT(TCCR1B,TCCR1B_WGM13);
       }break;
       case TIMER1_PH_FRECRR_OCR1A :
       {
    	   SET_BIT(TCCR1A,TCCR1A_WGM10);
    	   CLR_BIT(TCCR1A,TCCR1A_WGM11);
    	   CLR_BIT(TCCR1B,TCCR1B_WGM12);
    	   SET_BIT(TCCR1B,TCCR1B_WGM13);
       }break;
       case TIMER1_PH_CRR_ICR1 :
       {
    	   CLR_BIT(TCCR1A,TCCR1A_WGM10);
    	   SET_BIT(TCCR1A,TCCR1A_WGM11);
    	   CLR_BIT(TCCR1B,TCCR1B_WGM12);
    	   SET_BIT(TCCR1B,TCCR1B_WGM13);
       }break;
       case TIMER1_PH_CRR_OCR1A :
       {
    	   SET_BIT(TCCR1A,TCCR1A_WGM10);
    	   SET_BIT(TCCR1A,TCCR1A_WGM11);
    	   CLR_BIT(TCCR1B,TCCR1B_WGM12);
    	   SET_BIT(TCCR1B,TCCR1B_WGM13);
       }break;
       case TIMER1_CTC_ICR1 :
       {
    	   CLR_BIT(TCCR1A,TCCR1A_WGM10);
    	   CLR_BIT(TCCR1A,TCCR1A_WGM11);
    	   SET_BIT(TCCR1B,TCCR1B_WGM12);
    	   SET_BIT(TCCR1B,TCCR1B_WGM13);
       }break;
       case TIMER1_FAST_PWM_ICR1 :
       {
    	   CLR_BIT(TCCR1A,TCCR1A_WGM10);
    	   SET_BIT(TCCR1A,TCCR1A_WGM11);
    	   SET_BIT(TCCR1B,TCCR1B_WGM12);
    	   SET_BIT(TCCR1B,TCCR1B_WGM13);
       }break;
       case TIMER1_FAST_PWM_OCR1A :
       {
    	   SET_BIT(TCCR1A,TCCR1A_WGM10);
    	   SET_BIT(TCCR1A,TCCR1A_WGM11);
    	   SET_BIT(TCCR1B,TCCR1B_WGM12);
    	   SET_BIT(TCCR1B,TCCR1B_WGM13);
       }break;
       }
       if(Copy_stCfg_Data->WFG_MODE== TIMER1_NORMAL_MODE)
       {
		   CLR_BIT(TCCR1A,TCCR1A_COM1A0);
		   CLR_BIT(TCCR1A,TCCR1A_COM1A1);
		   CLR_BIT(TCCR1A,TCCR1A_COM1B0);
		   CLR_BIT(TCCR1A,TCCR1A_COM1B1);
       }
       else if(Copy_stCfg_Data->WFG_MODE==TIMER1_CTC_ICR1 || Copy_stCfg_Data->WFG_MODE==TIMER1_CTC_OCR1A)
       {
    	   switch(Copy_stCfg_Data->CTC_MODE)
    	   {
    	   case TIMER1_NORMAL_CTC :  /*Disconnect the Pins OC1A,OC1B*/
    	   {
    		   if (Copy_stCfg_Data->CHANNEL==TIMER1_CHANNEL_A)
    		   {
        		   CLR_BIT(TCCR1A,TCCR1A_COM1A0);
        		   CLR_BIT(TCCR1A,TCCR1A_COM1A1);
    		   }
    		   else if(Copy_stCfg_Data->CHANNEL==TIMER1_CHANNEL_B)
    		   {
        		   CLR_BIT(TCCR1A,TCCR1A_COM1B0);
        		   CLR_BIT(TCCR1A,TCCR1A_COM1B1);
    		   }
    	   }break;
    	   case TIMER1_TOG_COMP :   /*Toggle the Pins OC1A,OC1B*/
    	   {
    		   if(Copy_stCfg_Data->CHANNEL==TIMER1_CHANNEL_A)
    		   {
        		   SET_BIT(TCCR1A,TCCR1A_COM1A0);
        		   CLR_BIT(TCCR1A,TCCR1A_COM1A1);
    		   }
    		   else if(Copy_stCfg_Data->CHANNEL==TIMER1_CHANNEL_B)
    		   {
        		   SET_BIT(TCCR1A,TCCR1A_COM1B0);
        		   CLR_BIT(TCCR1A,TCCR1A_COM1B1);
    		   }
    	   }break;
    	   case TIMER1_CLR_COMP :   /*Clear the Pins OC1A,OC1B*/
    	   {
    		   if(Copy_stCfg_Data->CHANNEL==TIMER1_CHANNEL_A)
    		   {
        		   CLR_BIT(TCCR1A,TCCR1A_COM1A0);
        		   SET_BIT(TCCR1A,TCCR1A_COM1A1);
    		   }
    		   else if(Copy_stCfg_Data->CHANNEL==TIMER1_CHANNEL_B)
    		   {
        		   CLR_BIT(TCCR1A,TCCR1A_COM1B0);
        		   SET_BIT(TCCR1A,TCCR1A_COM1B1);
    		   }
    	   }break;
    	   case TIMER1_SET_COMP :   /*Set the Pins OC1A,OC1B*/
    	   {
    		   if(Copy_stCfg_Data->CHANNEL==TIMER1_CHANNEL_A)
    		   {
        		   SET_BIT(TCCR1A,TCCR1A_COM1A0);
        		   SET_BIT(TCCR1A,TCCR1A_COM1A1);
    		   }
    		   else if(Copy_stCfg_Data->CHANNEL==TIMER1_CHANNEL_B)
    		   {
        		   SET_BIT(TCCR1A,TCCR1A_COM1B0);
        		   SET_BIT(TCCR1A,TCCR1A_COM1B1);
    		   }
    	   }break;
    	   }
       }
       else if(Copy_stCfg_Data->WFG_MODE==TIMER1_FAST_PWM_10bit || Copy_stCfg_Data->WFG_MODE==TIMER1_FAST_PWM_8bit || Copy_stCfg_Data->WFG_MODE==TIMER1_FAST_PWM_9bit ||Copy_stCfg_Data->WFG_MODE==TIMER1_FAST_PWM_ICR1 ||Copy_stCfg_Data->WFG_MODE==TIMER1_FAST_PWM_OCR1A
    		   )
       {
          switch(Copy_stCfg_Data->FASTPWN_MODE)
          {
          case TIMER1_NORMAL_PWM :
          {
        	 if(Copy_stCfg_Data->CHANNEL==TIMER1_CHANNEL_A)
        	 {
       		     CLR_BIT(TCCR1A,TCCR1A_COM1A0);
       		     CLR_BIT(TCCR1A,TCCR1A_COM1A1);
        	 }
        	 else if(Copy_stCfg_Data->CHANNEL==TIMER1_CHANNEL_B)
        	 {
       		     CLR_BIT(TCCR1A,TCCR1A_COM1B0);
       		     CLR_BIT(TCCR1A,TCCR1A_COM1B1);
        	 }
          }break;
          case TIMER1_SET_TOP_CLR_COMP :
          {
           if(Copy_stCfg_Data->CHANNEL==TIMER1_CHANNEL_A)
           {
       		   CLR_BIT(TCCR1A,TCCR1A_COM1A0);
       		   SET_BIT(TCCR1A,TCCR1A_COM1A1);
           }
           else if(Copy_stCfg_Data->CHANNEL==TIMER1_CHANNEL_B)
           {
       		   CLR_BIT(TCCR1A,TCCR1A_COM1B0);
       		   SET_BIT(TCCR1A,TCCR1A_COM1B1);
           }
          }break;
          case TIMER1_CLR_TOP_SET_COMP :
          {
           if(Copy_stCfg_Data->CHANNEL==TIMER1_CHANNEL_A)
           {
       		   SET_BIT(TCCR1A,TCCR1A_COM1A0);
       		   SET_BIT(TCCR1A,TCCR1A_COM1A1);
           }
           else if(Copy_stCfg_Data->CHANNEL==TIMER1_CHANNEL_B)
           {
       		   SET_BIT(TCCR1A,TCCR1A_COM1B0);
       		   SET_BIT(TCCR1A,TCCR1A_COM1B1);
           }
          }break;
          }
       }
       else
       {
           switch(Copy_stCfg_Data->PHCORR_MODE)
           {
           case TIMER1_NORMAL_PHCORRECT :
           {
        	   if(Copy_stCfg_Data->CHANNEL==TIMER1_CHANNEL_A)
        	   {
       		     CLR_BIT(TCCR1A,TCCR1A_COM1A0);
       		     CLR_BIT(TCCR1A,TCCR1A_COM1A1);
        	   }
        	   else if(Copy_stCfg_Data->CHANNEL==TIMER1_CHANNEL_B)
        	   {
       		     CLR_BIT(TCCR1A,TCCR1A_COM1B0);
       		     CLR_BIT(TCCR1A,TCCR1A_COM1B1);
        	   }
           }break;
           case TIMER1_CLR_COMPUP_SET_COMPDOWN :
           {
        	   if(Copy_stCfg_Data->CHANNEL==TIMER1_CHANNEL_A)
        	   {
           		   CLR_BIT(TCCR1A,TCCR1A_COM1A0);
           		   SET_BIT(TCCR1A,TCCR1A_COM1A1);
        	   }
        	   else if(Copy_stCfg_Data->CHANNEL==TIMER1_CHANNEL_B)
        	   {
           		   CLR_BIT(TCCR1A,TCCR1A_COM1B0);
           		   SET_BIT(TCCR1A,TCCR1A_COM1B1);
        	   }
           }break;
           case TIMER1_SET_COMPUP_CLR_COMPDOWN :
           {
        	   if(Copy_stCfg_Data->CHANNEL==TIMER1_CHANNEL_A)
        	   {
           		   SET_BIT(TCCR1A,TCCR1A_COM1A0);
           		   SET_BIT(TCCR1A,TCCR1A_COM1A1);
        	   }
        	   else if(Copy_stCfg_Data->CHANNEL==TIMER1_CHANNEL_B)
        	   {
           		   SET_BIT(TCCR1A,TCCR1A_COM1B0);
           		   SET_BIT(TCCR1A,TCCR1A_COM1B1);
        	   }
           }break;
           }
       }
   	/*clear the prescaler bits*/
   	TCCR1B &= PRESCALERMASK;
   	/*select the prescaler*/
   	TCCR1B |= TIMER1_u8PRESCALER;
   	Global_u8Timer1Prescaler=TIMER1_u8PRESCALER;
	}
	else
	{
		Local_u8ErrorState=NULL_PTR_ERR;
	}
    return Local_u8ErrorState;
}
void TIMER1_voidSet_CTCMode(TIMER1_OC_MODE_t Copy_enMode,TIMER1_CHANNEL_t Copy_enChannel)
{
	   switch(Copy_enMode)
	   {
	   case TIMER1_NORMAL_CTC :  /*Disconnect the Pins OC1A,OC1B*/
	   {
	    	if(Copy_enChannel == TIMER1_CHANNEL_A)
	    	{
			     CLR_BIT(TCCR1A,TCCR1A_COM1A0);
			     CLR_BIT(TCCR1A,TCCR1A_COM1A1);
	    	}
	    	else if (Copy_enChannel == TIMER1_CHANNEL_B)
	    	{
			     CLR_BIT(TCCR1A,TCCR1A_COM1B0);
			     CLR_BIT(TCCR1A,TCCR1A_COM1B1);
	    	}
	   }break;
	   case TIMER1_TOG_COMP :   /*Toggle the Pins OC1A,OC1B*/
	   {
		   if(Copy_enChannel == TIMER1_CHANNEL_A)
		   {
			   SET_BIT(TCCR1A,TCCR1A_COM1A0);
			   CLR_BIT(TCCR1A,TCCR1A_COM1A1);
		   }
		   else if(Copy_enChannel == TIMER1_CHANNEL_B)
		   {
			   SET_BIT(TCCR1A,TCCR1A_COM1B0);
			   CLR_BIT(TCCR1A,TCCR1A_COM1B1);
		   }
	   }break;
	   case TIMER1_CLR_COMP :   /*Clear the Pins OC1A,OC1B*/
	   {
	    	if(Copy_enChannel == TIMER1_CHANNEL_A)
	    	{
	 		   CLR_BIT(TCCR1A,TCCR1A_COM1A0);
	 		   SET_BIT(TCCR1A,TCCR1A_COM1A1);
	    	}
	    	else if(Copy_enChannel == TIMER1_CHANNEL_B)
	    	{
	 		   CLR_BIT(TCCR1A,TCCR1A_COM1B0);
	 		   SET_BIT(TCCR1A,TCCR1A_COM1B1);
	    	}
	   }break;
	   case TIMER1_SET_COMP :   /*Set the Pins OC1A,OC1B*/
	   {
	    	if(Copy_enChannel == TIMER1_CHANNEL_A)
	    	{
	 		   SET_BIT(TCCR1A,TCCR1A_COM1A0);
	 		   SET_BIT(TCCR1A,TCCR1A_COM1A1);
	    	}
	    	else if(Copy_enChannel == TIMER1_CHANNEL_B)
	    	{
	 		   SET_BIT(TCCR1A,TCCR1A_COM1B0);
	 		   SET_BIT(TCCR1A,TCCR1A_COM1B1);
	    	}
	   }break;
	   }
}
void TIMER1_voidSet_FastPwmMode(TIMER1_FAST_PWM_MODE_t Copy_enMode,TIMER1_CHANNEL_t Copy_enChannel)
{
    switch(Copy_enMode)
    {
    case TIMER1_NORMAL_PWM :
    {
    	if(Copy_enChannel == TIMER1_CHANNEL_A)
    	{
		     CLR_BIT(TCCR1A,TCCR1A_COM1A0);
		     CLR_BIT(TCCR1A,TCCR1A_COM1A1);
    	}
    	else if (Copy_enChannel == TIMER1_CHANNEL_B)
    	{
		     CLR_BIT(TCCR1A,TCCR1A_COM1B0);
		     CLR_BIT(TCCR1A,TCCR1A_COM1B1);
    	}
    }break;
    case TIMER1_CLR_TOP_SET_COMP :
    {
    	if(Copy_enChannel == TIMER1_CHANNEL_A)
    	{
 		   CLR_BIT(TCCR1A,TCCR1A_COM1A0);
 		   SET_BIT(TCCR1A,TCCR1A_COM1A1);
    	}
    	else if(Copy_enChannel == TIMER1_CHANNEL_B)
    	{
 		   CLR_BIT(TCCR1A,TCCR1A_COM1B0);
 		   SET_BIT(TCCR1A,TCCR1A_COM1B1);
    	}
    }break;
    case TIMER1_SET_TOP_CLR_COMP :
    {
    	if(Copy_enChannel == TIMER1_CHANNEL_A)
    	{
 		   SET_BIT(TCCR1A,TCCR1A_COM1A0);
 		   SET_BIT(TCCR1A,TCCR1A_COM1A1);
    	}
    	else if(Copy_enChannel == TIMER1_CHANNEL_B)
    	{
 		   SET_BIT(TCCR1A,TCCR1A_COM1B0);
 		   SET_BIT(TCCR1A,TCCR1A_COM1B1);
    	}
    }break;
    }
}
void TIMER1_voidSet_PHCorrectMode(TIMER1_PHCORRECT_PWM_MODE_t Copy_enMode,TIMER1_CHANNEL_t Copy_enChannel)
{
    switch(Copy_enMode)
    {
    case TIMER1_NORMAL_PHCORRECT :
    {
    	if(Copy_enChannel == TIMER1_CHANNEL_A)
    	{
		     CLR_BIT(TCCR1A,TCCR1A_COM1A0);
		     CLR_BIT(TCCR1A,TCCR1A_COM1A1);
    	}
    	else if (Copy_enChannel == TIMER1_CHANNEL_B)
    	{
		     CLR_BIT(TCCR1A,TCCR1A_COM1B0);
		     CLR_BIT(TCCR1A,TCCR1A_COM1B1);
    }break;
    case TIMER1_CLR_COMPUP_SET_COMPDOWN :
    {
    	if(Copy_enChannel == TIMER1_CHANNEL_A)
    	{
 		   CLR_BIT(TCCR1A,TCCR1A_COM1A0);
 		   SET_BIT(TCCR1A,TCCR1A_COM1A1);
    	}
    	else if(Copy_enChannel == TIMER1_CHANNEL_B)
    	{
 		   CLR_BIT(TCCR1A,TCCR1A_COM1B0);
 		   SET_BIT(TCCR1A,TCCR1A_COM1B1);
    	}
    }break;
    case TIMER1_SET_COMPUP_CLR_COMPDOWN :
    {
    	if(Copy_enChannel == TIMER1_CHANNEL_A)
    	{
 		   SET_BIT(TCCR1A,TCCR1A_COM1A0);
 		   SET_BIT(TCCR1A,TCCR1A_COM1A1);
    	}
    	else if(Copy_enChannel == TIMER1_CHANNEL_B)
    	{
 		   SET_BIT(TCCR1A,TCCR1A_COM1B0);
 		   SET_BIT(TCCR1A,TCCR1A_COM1B1);
    	}
    }break;
    }
  }
}
void TIMERS_void_INT_Enable(TIMERS_Int_Src_t Copy_u8INT_Src)
{
	switch(Copy_u8INT_Src)
	{
	case TIMER0_OVF  : SET_BIT(TIMSK,TIMSK_TOIE0);break;
	case TIMER0_COMP : SET_BIT(TIMSK,TIMSK_OCIE0);break;
	case TIMER2_OVF  : SET_BIT(TIMSK,TIMSK_TOIE2);break;
	case TIMER2_COMP : SET_BIT(TIMSK,TIMSK_OCIE2);break;
	case TIMER1_OVF  : SET_BIT(TIMSK,TIMSK_TOIE1);break;
	case TIMER1_COMP_CHA : SET_BIT(TIMSK,TIMSK_OCIE1A);break;
	case TIMER1_COMP_CHB : SET_BIT(TIMSK,TIMSK_OCIE1B);break;
	case TIMER1_CAPT : SET_BIT(TIMSK,TIMSK_TICIE1);break;
	}
}
void TIMERS_void_INT_Disable(TIMERS_Int_Src_t Copy_u8INT_Src)
{
	switch(Copy_u8INT_Src)
	{
	case TIMER0_OVF  : CLR_BIT(TIMSK,TIMSK_TOIE0);break;
	case TIMER0_COMP : CLR_BIT(TIMSK,TIMSK_OCIE0);break;
	case TIMER2_OVF  : CLR_BIT(TIMSK,TIMSK_TOIE2);break;
	case TIMER2_COMP : CLR_BIT(TIMSK,TIMSK_OCIE2);break;
	case TIMER1_OVF  : CLR_BIT(TIMSK,TIMSK_TOIE1);break;
	case TIMER1_COMP_CHA : CLR_BIT(TIMSK,TIMSK_OCIE1A);break;
	case TIMER1_COMP_CHB : CLR_BIT(TIMSK,TIMSK_OCIE1B);break;
	case TIMER1_CAPT : CLR_BIT(TIMSK,TIMSK_TICIE1);break;
	}
}
uint8 TIMERS_u8SetCallBack(TIMERS_Int_Src_t Copy_TmrIntSource,void(*Copy_pvCallBackFunc)(void))
{
    uint8 Local_u8Errorstate= OK;
    if(Copy_pvCallBackFunc!=NULL)
    {
        TIMERS_pvCallBackFuncArr[Copy_TmrIntSource]=Copy_pvCallBackFunc;
    }
    else
    {
    	Local_u8Errorstate=NOK;

    }

    return Local_u8Errorstate;
}
void TIMER1_voidPreload_Val(uint16 Copy_u16Val)
{
	TCNT1=Copy_u16Val;
}
void TIMER1_void_Set_CompValue(uint16 Copy_u16Val,TIMER1_CHANNEL_t Copy_enChannel)
{
	if(Copy_enChannel == TIMER1_CHANNEL_A)
	{
		OCR1A=Copy_u16Val;
	}
	else if(Copy_enChannel == TIMER1_CHANNEL_B)
	{
		OCR1B=Copy_u16Val;
	}
}
void TIMER1_voidSet_TopVal(uint16 Copy_u16Val,TIMER1_WFGEN_Mode_t Copy_enMode)
{
   switch(Copy_enMode)
   {
   case TIMER1_CTC_ICR1 : ICR1=Copy_u16Val;break;
   case TIMER1_CTC_OCR1A : OCR1A=Copy_u16Val;break;
   case TIMER1_FAST_PWM_ICR1 : ICR1=Copy_u16Val;break;
   case TIMER1_FAST_PWM_OCR1A :OCR1A=Copy_u16Val;break;
   case TIMER1_PH_CRR_ICR1 : ICR1=Copy_u16Val;break;
   case TIMER1_PH_CRR_OCR1A : OCR1A=Copy_u16Val;break;
   case TIMER1_PH_FRECRR_ICR1 : ICR1=Copy_u16Val;break;
   case TIMER1_PH_FRECRR_OCR1A : OCR1A=Copy_u16Val;break;
   }
}
void WDT_voidSetTime(WDT_TIME_t Copy_enTime)
{
   WDTCR = 0x00;
   WDTCR = Copy_enTime;
}
void WDT_voidEnable()
{
	WDTCR |= 1<<WDTCR_WDE;
}
void WDT_voidDisable()
{
	WDTCR = (1<<WDTCR_WDTOE) | (1<<WDTCR_WDE);
	WDTCR=0x00;
}
void __vector_10 (void) __attribute__((signal));
void __vector_10 (void)
{
	if(TIMERS_pvCallBackFuncArr[TIMER0_COMP] != NULL)
	{
		TIMERS_pvCallBackFuncArr[TIMER0_COMP]();
	}
}
void __vector_11 (void) __attribute__((signal));
void __vector_11 (void)
{
	if(TIMERS_pvCallBackFuncArr[TIMER0_OVF] != NULL)
	{
		TIMERS_pvCallBackFuncArr[TIMER0_OVF]();
	}
}
void __vector_8 (void) __attribute__((signal));
void __vector_8 (void)
{
	if(TIMERS_pvCallBackFuncArr[TIMER1_COMP_CHB] != NULL)
	{
		TIMERS_pvCallBackFuncArr[TIMER1_COMP_CHB]();
	}
}
void __vector_7 (void) __attribute__((signal));
void __vector_7 (void)
{
	if(TIMERS_pvCallBackFuncArr[TIMER1_COMP_CHA] != NULL)
	{
		TIMERS_pvCallBackFuncArr[TIMER1_COMP_CHA]();
	}
}
void __vector_4 (void) __attribute__((signal));
void __vector_4 (void)
{
	if(TIMERS_pvCallBackFuncArr[TIMER2_COMP] != NULL)
	{
		TIMERS_pvCallBackFuncArr[TIMER2_COMP]();
	}
}
void __vector_5 (void) __attribute__((signal));
void __vector_5 (void)
{
	if(TIMERS_pvCallBackFuncArr[TIMER2_OVF] != NULL)
	{
		TIMERS_pvCallBackFuncArr[TIMER2_OVF]();
	}
}
void __vector_6 (void) __attribute__((signal));
void __vector_6 (void)
{
	if(TIMERS_pvCallBackFuncArr[TIMER1_CAPT] != NULL)
	{
		TIMERS_pvCallBackFuncArr[TIMER1_CAPT]();
	}
}
void __vector_9 (void) __attribute__((signal));
void __vector_9 (void)
{
	if(TIMERS_pvCallBackFuncArr[TIMER1_OVF] != NULL)
	{
		TIMERS_pvCallBackFuncArr[TIMER1_OVF]();
	}
}
