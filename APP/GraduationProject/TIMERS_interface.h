/*
 * TIMER0_interface.h
 *
 *  Created on: ???/???/????
 *      Author: Sayed Abd-Elaziz
 */

#ifndef TIMERS_INTERFACE_H_
#define TIMERS_INTERFACE_H_



typedef enum
{
	TIMER0_OVF=0,
	TIMER0_COMP,
	TIMER2_OVF,
	TIMER2_COMP,
	TIMER1_OVF,
	TIMER1_COMP_CHA,
	TIMER1_COMP_CHB,
	TIMER1_CAPT
}TIMERS_Int_Src_t;
typedef enum
{
	NORMAL_MODE=0,
	CTC,
	FAST_PWM,
	PHASE_CORRECT
}TIMER0_2_WFGEN_MODE_t;
typedef enum
{
	NORMAL_CTC=0,
	TOG_COMP,
	CLR_COMP,
	SET_COMP
}TIMER0_2_OC_MODE_t;
typedef enum
{
	NORMAL_PWM=0,
	CLR_TOP_SET_COMP,
	SET_TOP_CLR_COMP
}TIMER0_2_FAST_PWM_MODE_t;
typedef enum
{
	NORMAL_PHCORRECT=0,
	CLR_COMPUP_SET_COMPDOWN,
	SET_COMPUP_CLR_COMPDOWN
}TIMER0_2_PHCORRECT_PWM_MODE_t;

typedef struct
{
   TIMER0_2_WFGEN_MODE_t    WFG_MODE;
   TIMER0_2_OC_MODE_t       CTC_MODE;
   TIMER0_2_FAST_PWM_MODE_t FASTPWM_MODE;
   TIMER0_2_PHCORRECT_PWM_MODE_t  PHCORRECT_MODE;
}TIMER0_2_Cfg_t;
typedef enum
{
	TIMER1_CHANNEL_A=0,
	TIMER1_CHANNEL_B
}TIMER1_CHANNEL_t;
typedef enum
{
   TIMER1_NORMAL_MODE=0,
   TIMER1_PHCRR_8bit,
   TIMER1_PHCRR_9bit,
   TIMER1_PHCRR_10bit,
   TIMER1_CTC_OCR1A,
   TIMER1_FAST_PWM_8bit,
   TIMER1_FAST_PWM_9bit,
   TIMER1_FAST_PWM_10bit,
   TIMER1_PH_FRECRR_OCR1A,
   TIMER1_PH_FRECRR_ICR1,
   TIMER1_PH_CRR_OCR1A,
   TIMER1_PH_CRR_ICR1,
   TIMER1_CTC_ICR1,
   TIMER1_FAST_PWM_ICR1,
   TIMER1_FAST_PWM_OCR1A


}TIMER1_WFGEN_Mode_t;
typedef enum
{
	TIMER1_NORMAL_CTC=0,
	TIMER1_TOG_COMP,
	TIMER1_CLR_COMP,
	TIMER1_SET_COMP
}TIMER1_OC_MODE_t;
typedef enum
{
	TIMER1_NORMAL_PWM=0,
	TIMER1_CLR_TOP_SET_COMP,
	TIMER1_SET_TOP_CLR_COMP
}TIMER1_FAST_PWM_MODE_t;
typedef enum
{
	TIMER1_NORMAL_PHCORRECT=0,
	TIMER1_CLR_COMPUP_SET_COMPDOWN,
	TIMER1_SET_COMPUP_CLR_COMPDOWN
}TIMER1_PHCORRECT_PWM_MODE_t;
typedef struct
{
	TIMER1_WFGEN_Mode_t WFG_MODE;
	TIMER1_OC_MODE_t    CTC_MODE;
	TIMER1_FAST_PWM_MODE_t FASTPWN_MODE;
	TIMER1_PHCORRECT_PWM_MODE_t   PHCORR_MODE;
	TIMER1_CHANNEL_t   CHANNEL;
}TIMER1_cfg_t;
typedef enum
{
	WDT_16ms=0,
	WDT_32ms,
	WDT_65ms,
	WDT_130ms,
	WDT_260ms,
	WDT_520ms,
	WDT_1s,
	WDT_2s
}WDT_TIME_t;
void TIMERS_void_INT_Enable(TIMERS_Int_Src_t Copy_u8INT_Src);
void TIMERS_void_INT_Disable(TIMERS_Int_Src_t Copy_u8INT_Src);

uint8 TIMER0_u8Init(TIMER0_2_Cfg_t *Copy_stCfg);
void TIMER0_voidPreload_Val(uint8 Copy_u8Val);
void TIMER0_void_Set_CompValue(uint8 Copy_u8Val);
void TIMER0_voidSet_CTCMode(TIMER0_2_OC_MODE_t Copy_enMode);
void TIMER0_voidSet_FastPwmMode(TIMER0_2_FAST_PWM_MODE_t Copy_enMode);
void TIMER0_voidSet_PHCorrectMode(TIMER0_2_PHCORRECT_PWM_MODE_t Copy_enMode);

uint8 TIMER2_u8Init(TIMER0_2_Cfg_t *Copy_stCfg);
void TIMER2_voidPreload_Val(uint8 Copy_u8Val);
void TIMER2_void_Set_CompValue(uint8 Copy_u8Val);
void TIMER2_voidSet_CTCMode(TIMER0_2_OC_MODE_t Copy_enMode);
void TIMER2_voidSet_FastPwmMode(TIMER0_2_FAST_PWM_MODE_t Copy_enMode);
void TIMER2_voidSet_PHCorrectMode(TIMER0_2_PHCORRECT_PWM_MODE_t Copy_enMode);

uint8 TIMER1_voidInit(TIMER1_cfg_t *Copy_stCfg_Data);
void TIMER1_voidSet_CTCMode(TIMER1_OC_MODE_t Copy_enMode,TIMER1_CHANNEL_t Copy_enChannel);
void TIMER1_voidSet_FastPwmMode(TIMER1_FAST_PWM_MODE_t Copy_enMode,TIMER1_CHANNEL_t Copy_enChannel);
void TIMER1_voidSet_PHCorrectMode(TIMER1_PHCORRECT_PWM_MODE_t Copy_enMode,TIMER1_CHANNEL_t Copy_enChannel);

void TIMER1_void_Set_CompValue(uint16 Copy_u16Val,TIMER1_CHANNEL_t Copy_enChannel);
void TIMER1_voidPreload_Val(uint16 Copy_u16Val);
void TIMER1_voidSet_TopVal(uint16 Copy_u16Val,TIMER1_WFGEN_Mode_t Copy_enMode);
uint8 TIMERS_u8SetCallBack(TIMERS_Int_Src_t Copy_TmrIntSource,void(*Copy_pvCallBackFunc)(void));

void WDT_voidSetTime(WDT_TIME_t Copy_enTime);
void WDT_voidEnable();
void WDT_voidDisable();
#endif
