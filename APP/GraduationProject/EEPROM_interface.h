/*
 * EEPROM_interface.h
 *
 *  Created on: Jan 24, 2023
 *      Author: Pc
 */

#ifndef EEPROM_INTERFACE_H_
#define EEPROM_INTERFACE_H_

uint8 EEPROM_voidWriteDataByte(uint16 Copy_u16LocAddress,uint8 Copy_u8DataByte);
uint8 EEPROM_voidReadDataByte(uint16 Copy_u16LocAddress,uint8 *Copy_u8DataByte);

#endif /* EEPROM_INTERFACE_H_ */
