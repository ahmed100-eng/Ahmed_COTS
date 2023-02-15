/*
 * PWM_prog.c
 *
 *  Created on: ???/???/????
 *      Author: Sayed Abd-Elaziz
 */
#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "defines.h"

#include "GIE_interface.h"
#include "TIMERS_reg.h"
#include "TIMERS_interface.h"
#include "PWM_interface.h"
#include "TIMERS_private.h"

void TIMER1_OVF_Event(void);
void ICU_Process(void);
void ICU_voidTrigger_CFG(ICU_cfg_t Copy_enTriggerCfg);
void Schedul_voidOVF_Event(void);

extern Global_u8Timer1Prescaler;

uint32 TIMER1_u32Read1=0;
uint32 TIMER1_u32Read2=0;
uint32 TIMER1_u32Read3=0;
static uint8 TIMER1_u8OVF_Counter=0;
static uint8  ICU_u8Flag=0;
void (*Schedul_ptFunc)(void)=NULL;
uint16 Schedul_u16PreloadVal=0,Schedul_u16NumberTicks=0;
void PWM_voidSetFrequency_SetDutyCycle(uint32 Copy_u8Freqency,uint8 Copy_u8DutyCycle)
{
	TIMER1_cfg_t Timer1;
	Timer1.CHANNEL=TIMER1_CHANNEL_A;
	Timer1.FASTPWN_MODE=TIMER1_SET_TOP_CLR_COMP;
	Timer1.WFG_MODE=TIMER1_FAST_PWM_ICR1;
	TIMER1_voidInit(&Timer1);

	switch(Global_u8Timer1Prescaler)
	{
	case DIVISION_BY_1 : ICR1=(uint16)(16000000u/((uint32)Copy_u8Freqency));break;
	case DIVISION_BY_8 : ICR1=(uint16)(2000000u/((uint32)Copy_u8Freqency));break;
	case DIVISION_BY_64 : ICR1=(uint16)(250000u/((uint32)Copy_u8Freqency));break;
	case DIVISION_BY_256 : ICR1=(uint16)(62500u/((uint32)Copy_u8Freqency));break;
	case DIVISION_BY_1024 : ICR1=(uint16)(15625u/((uint32)Copy_u8Freqency));break;
	}
	uint16 Local_u16PeriodTime=ICR1;
    OCR1A= (uint16)(((uint32)Local_u16PeriodTime*Copy_u8DutyCycle/100u)-1u);
}

uint8 PWM_u8Measure_Frequency_DutyCycle(uint32 *Copy_u8ON_Time,uint32 *Copy_PeriodTime)
{
	uint8 Local_u8ErrorState=OK;
	uint16 Local_u8TickTime=5u;
	if(Copy_u8ON_Time != NULL && Copy_PeriodTime != NULL)
	{
       TIMER1_cfg_t Timer1;
       Timer1.WFG_MODE=TIMER1_NORMAL_MODE;
       ICU_voidTrigger_CFG(ICU_TriggerSRC_RisingEdge);
       TIMER1_voidInit(&Timer1);
       TIMERS_u8SetCallBack(TIMER1_OVF,&TIMER1_OVF_Event);
       TIMERS_u8SetCallBack(TIMER1_CAPT,ICU_Process);
       TIMERS_void_INT_Enable(TIMER1_OVF);
       TIMERS_void_INT_Enable(TIMER1_CAPT);
       GIE_voidEnable();
   	   while(ICU_u8Flag < 5u);
   	   GIE_voidDisable();
   	   TIMERS_void_INT_Disable(TIMER1_CAPT);
   	   TIMERS_void_INT_Disable(TIMER1_OVF);
       *Copy_u8ON_Time = (TIMER1_u32Read3 - TIMER1_u32Read2) * (uint32)Local_u8TickTime/10u;
       *Copy_PeriodTime = (TIMER1_u32Read2 - TIMER1_u32Read1) * (uint32)Local_u8TickTime/10u;
       if(*Copy_u8ON_Time > *Copy_PeriodTime)
       {
    	   *Copy_u8ON_Time = *Copy_u8ON_Time - *Copy_PeriodTime;
       }
       ICU_u8Flag=0;
       TIMER1_u8OVF_Counter=0;
	}
	else
	{
		Local_u8ErrorState= NULL_PTR_ERR;
	}
	return Local_u8ErrorState;
}
void ICU_voidTrigger_CFG(ICU_cfg_t Copy_enTriggerCfg)
{
	switch(Copy_enTriggerCfg)
	{
	case ICU_TriggerSRC_FallingEdge : CLR_BIT(TCCR1B,TCCR1B_ICES1);break;
	case ICU_TriggerSRC_RisingEdge	: SET_BIT(TCCR1B,TCCR1B_ICES1);break;
	}
}
void TIMER1_OVF_Event(void)
{
	TIMER1_u8OVF_Counter++;
}
void ICU_Process(void)
{

	static uint8 Local_u8Counter=0;
	Local_u8Counter++;

	if(Local_u8Counter == 1)
	{
		TIMER1_u32Read1 = (uint32)ICR1 + ((uint32)TIMER1_u8OVF_Counter * 65536ul);
	}
	else if (Local_u8Counter == 2)
	{
		TIMER1_u32Read2 = (uint32)ICR1 + ((uint32)TIMER1_u8OVF_Counter * 65536ul);
		ICU_voidTrigger_CFG(ICU_TriggerSRC_FallingEdge);
	}
	else if (Local_u8Counter == 3)
	{
		TIMER1_u32Read3 = (uint32)ICR1 + ((uint32)TIMER1_u8OVF_Counter * 65536ul);
		ICU_voidTrigger_CFG(ICU_TriggerSRC_RisingEdge);
		Local_u8Counter=0;
		ICU_u8Flag++;
	}
}
uint8 Schedule_u8Service(uint32 Copy_u32Time_ms,Schedule_t Copy_enPeriodic_Once,void(*Copy_pvCallBackFunc)(void))
{
   uint8 Local_u8ErrorState=OK;
   if(Copy_pvCallBackFunc != NULL)
   {
	   Schedul_ptFunc = Copy_pvCallBackFunc;
	   Schedul_u16NumberTicks = Copy_u32Time_ms ;
	   TIMER1_cfg_t Timer1;
	   Timer1.WFG_MODE = TIMER1_CTC_OCR1A;
	   TIMERS_void_INT_Enable(TIMER1_COMP_CHA);
	   //TIMERS_u8SetCallBack(TIMER1_COMP_CHA,&Schedul_voidOVF_Event);
	   TIMER1_void_Set_CompValue(250u,TIMER1_CHANNEL_A);
	   TIMER1_voidInit(&Timer1);
	   TIMER0_2_Cfg_t Timer0;
	   Timer0.WFG_MODE=CTC;
	   Timer0.CTC_MODE=NORMAL_CTC;
	   TIMER0_void_Set_CompValue(250);
	   TIMERS_void_INT_Enable(TIMER0_COMP);
	   TIMERS_u8SetCallBack(TIMER0_COMP,&Schedul_voidOVF_Event);
	   TIMER0_u8Init(&Timer0);
   }
   else
   {
	   Local_u8ErrorState = NULL_PTR_ERR;
   }
   return Local_u8ErrorState;
}
void Schedul_voidOVF_Event(void)
{
	static uint32 Local_u32Counter=0u;
	Local_u32Counter++;
	if(Local_u32Counter == Schedul_u16NumberTicks)
	{
		TIMERS_void_INT_Disable(TIMER0_COMP);
		Local_u32Counter=0u;
		if(Schedul_ptFunc != NULL)
		{
			Schedul_ptFunc();
		}
	}
}
