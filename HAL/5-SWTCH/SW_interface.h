/**************************************************************/
/**************************************************************/
/*********		Author: Ahmed Abdelaziz			*******************/
/*********		File: SW_interface.h		*******************/
/*********		Version: 1.00				*******************/
/**************************************************************/




#ifndef SW_INTERFACE_H_
#define SW_INTERFACE_H_

typedef struct
{
	uint8 SW_u8PullType;
	uint8 SW_u8Port;
	uint8 SW_u8Pin;

}Switch_t;

#define PRESSED     1u
#define RELEASED    0u

uint8 SW_u8State(Switch_t * Copy_pSwitch,uint8 *Copy_pState);

#endif
