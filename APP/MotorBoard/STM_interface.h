




#ifndef STM_INTERFACE_H_
#define STM_INTERFACE_H_

typedef struct
{
	uint8 STM_u8Port;
	uint8 STM_u8Blue;
	uint8 STM_u8Pink;
	uint8 STM_u8Yellow;
	uint8 STM_u8Orange;

}Stepper_t;




uint8 STM_CW(const Stepper_t* Copy_pSTMCfg,uint16 Copy_u16Angel);
uint8 STM_CCW(const Stepper_t* Copy_pSTMCfg,uint16 Copy_u16Angel);

extern Stepper_t Stepper_One;

#endif


