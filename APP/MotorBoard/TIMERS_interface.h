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
	TIMER0_COMP
}TIMERS_Int_Src_t;


void TIMER0_voidInit(void);

void TIMER1_voidInit(void);

void TIMER0_void_Set_CompValue(uint8 Copy_u8Val);

void TIMER1_void_Set_CompValue(uint16 Copy_u16Val,uint16 Copy_u16Val2);


uint8 TIMERS_u8SetCallBack(TIMERS_Int_Src_t Copy_TmrIntSource,void(*Copy_pvCallBackFunc)(void));


#endif
