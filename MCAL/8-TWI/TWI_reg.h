/*
 * TWI_reg.h
 *
 *  Created on: Jan 24, 2023
 *      Author: Pc
 */

#ifndef TWI_REG_H_
#define TWI_REG_H_


#define TWBR          *((volatile uint8*)0x20)  /*TWI Bit Rate Register*/


#define TWCR          *((volatile uint8*)0x56)  /*TWI Control Register*/
#define TWCR_TWINT    7u    /*TWI interrupt flag*/
#define TWCR_TWEA     6u    /*TWI Enable Acknowledge Bit*/
#define TWCR_TWSTA    5u    /*TWI START Condition Bit*/
#define TWCR_TWSTO    4u    /*TWI STOP Condition Bit*/
#define TWCR_TWWC     3u    /*TWI Write Collision Flag*/
#define TWCR_TWEN     2u    /*TWI Enable Bit*/
#define TWCR_TWIE     0u    /*TWI Interrupt Enable*/

#define TWSR          *((volatile uint8*)0x21)  /*TWI Status Register*/
#define TWSR_TWPS1    1u    /*TWI Prescaler Bit 1*/
#define TWSR_TWPS0    0u    /*TWI Prescaler Bit 0*/

#define TWDR          *((volatile uint8*)0x23)  /*TWI Data Register*/

#define TWAR          *((volatile uint8*)0x22)  /*TWI Slave Address Register*/
#define TWAR_TWGCE    0u    /*TWI General Call Recognition Enable Bit*/


#endif /* TWI_REG_H_ */
