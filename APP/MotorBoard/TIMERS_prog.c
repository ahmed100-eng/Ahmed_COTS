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

static void (*TIMERS_pvCallBackFuncArr[8])(void)={NULL};

void TIMER0_voidInit(void)
{
   /*waveform generation mode: Fast PWM*/
	SET_BIT(TCCR0,3);
	SET_BIT(TCCR0,6);
	/*Clear the prescaler bits*/
	TCCR0&=0b11111000;
	/*Select prescaler : division by 64*/
	TCCR0|=DIVISION_BY_64;


	/*set on top ,clear on compare*/
	CLR_BIT(TCCR0,4);
	SET_BIT(TCCR0,5);


}
void TIMER1_voidInit(void)
{
	/*Wave form generation mode : Fast PWM */
	CLR_BIT(TCCR1A,TCCr1A_COM1A0);
	SET_BIT(TCCR1A,TCCr1A_COM1A1);

	/*clear the prescaler bits*/
	TCCR1B &= 0b11111000;
	/*select the prescaler*/
	TCCR1B |= 0b00000010;

	CLR_BIT(TCCR1A,TCCR1A_WGM10);
	SET_BIT(TCCR1A,TCCR1A_WGM11);
	SET_BIT(TCCR1B,TCCR1B_WGM12);
	SET_BIT(TCCR1B,TCCR1B_WGM13);

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
void TIMER0_void_Set_CompValue(uint8 Copy_u8Val)
{
	OCR0=Copy_u8Val;
}
void TIMER1_void_Set_CompValue(uint16 Copy_u16Val,uint16 Copy_u16Val2)
{
	ICR1 =Copy_u16Val;
	OCR1A=Copy_u16Val2;
}
void __vector_10 (void) __attribute__((signal));
void __vector_10 (void)
{
	if(TIMERS_pvCallBackFuncArr[TIMER0_COMP] != NULL)
	{
		TIMERS_pvCallBackFuncArr[TIMER0_COMP]();
	}
}
