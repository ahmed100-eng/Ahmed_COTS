/**************************************************************/
/**************************************************************/
/*********		Author: Ahmed Abdelaziz			*******************/
/*********		File: DCM_interface.h		*******************/
/*********		Version: 1.00				*******************/
/**************************************************************/



#ifndef DCM_INTERFACE_H_
#define DCM_INTERFACE_H_

typedef struct
{
	uint8 DCM_u8SwitchPort;
	uint8 DCM_u8Switch1Pin;
	uint8 DCM_u8Switch2Pin;
	uint8 DCM_u8Switch3Pin;
	uint8 DCM_u8Switch4Pin;
}DCM_cfg;



uint8 DCM_u8CW(DCM_cfg * Copy_pDCMcfg);
uint8 DCM_u8CCW(DCM_cfg * Copy_pDCMcfg);
uint8 DCM_u8Brake(DCM_cfg * Copy_pDCMcfg);


#endif
