/*
 * PWM_interface.h
 *
 *  Created on: ???/???/????
 *      Author: Sayed Abd-Elaziz
 */

#ifndef PWM_INTERFACE_H_
#define PWM_INTERFACE_H_

typedef enum
{
	ICU_TriggerSRC_FallingEdge=0,
	ICU_TriggerSRC_RisingEdge
}ICU_cfg_t;

typedef enum
{
	Periodic=0,
	Once
}Schedule_t;

void PWM_voidSetFrequency_SetDutyCycle(uint32 Copy_u8Freqency,uint8 Copy_u8DutyCycle);
uint8 PWM_u8Measure_Frequency_DutyCycle(uint32 *Copy_u8ON_Time,uint32 *Copy_PeriodTime);
uint8 Schedule_u8Service(uint32 Copy_u32Time_ms,Schedule_t Copy_enPeriodic_Once,void(*Copy_pvCallBackFunc)(void));

#endif /* PWM_INTERFACE_H_ */
