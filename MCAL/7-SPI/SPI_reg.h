/*
 * SPI_reg.h
 *
 *  Created on: Jan 17, 2023
 *      Author: Pc
 */

#ifndef SPI_REG_H_
#define SPI_REG_H_


#define SPCR              *((volatile uint8*)0x2d)
#define SPCR_SPIE         7u
#define SPCR_SPE          6u
#define SPCR_DORD         5u
#define SPCR_MSTR         4u
#define SPCR_CPOL         3u
#define SPCR_CPHA         2u
#define SPCR_SPR1         1u
#define SPCR_SPR0         0u


#define SPSR              *((volatile uint8*)0x2e)
#define SPSR_SPIF         7u
#define SPSR_WCOL         6u
#define SPSR_SPI2X        0u

#define SPDR              *((volatile uint8*)0x2f)





#endif /* SPI_REG_H_ */
