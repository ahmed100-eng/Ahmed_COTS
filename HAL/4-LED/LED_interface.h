/**************************************************************/
/**************************************************************/
/*********		Author: Ahmed Abdelaziz			*******************/
/*********		File: LED_interface.h			*******************/
/*********		Version: 1.00				*******************/
/**************************************************************/


#ifndef LED_INTERFACE_H_
#define LED_INTERFACE_H_

void LED_voidLedOn(uint8 Copy_u8Port,uint8 Copy_u8Pin,uint8 Copy_u8ConnectionType);

void LED_voidLedOff(uint8 Copy_u8Port,uint8 Copy_u8Pin,uint8 Copy_u8ConnectionType);

void LED_voidLedToggle(uint8 Copy_u8Port,uint8 Copy_u8Pin);


#endif

