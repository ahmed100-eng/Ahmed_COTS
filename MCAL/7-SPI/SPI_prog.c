/*
 * SPI_prog.c
 *
 *  Created on: Jan 17, 2023
 *      Author: Pc
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "defines.h"


#include "SPI_reg.h"
#include "SPI_private.h"
#include "SPI_cfg.h"
#include "SPI_interface.h"
#include "SPI_reg.h"


void SPI_Init(void)
{
   /*configure the SPI Mode*/
#if SPI_MODE  ==   SPI_MASTER
	SET_BIT(SPCR,SPCR_MSTR);    /*Master select*/
#elif SPI_MODE  ==   SPI_SLAVE
	CLR_BIT(SPCR,SPCR_MSTR);   /*Slave select*/
#else #error Wrong SPI Mode configuration
#endif
	/*configure the idle state*/
#if SPI_IDLE_STATE  ==  SPI_IDLE_HIGH  /*Idle state is High*/
	SET_BIT(SPCR,SPCR_CPOL);
#elif SPI_IDLE_STATE  ==  SPI_IDLE_LOW /*Idle state is low*/
	CLR_BIT(SPCR,SPCR_CPOL);
#else #error wrong idle State configuration
#endif
   /*configure the clock phase*/
#if SPI_CLOCK_PHASE   ==   SETUP_FIRST
	SET_BIT(SPCR,SPCR_CPHA);  /*Setup first*/
#elif SPI_CLOCK_PHASE   ==   SAMPLE_FIRST
	CLR_BIT(SPCR,SPCR_CPHA); /*Sample first*/
#else #error Wrong clock phase configuration
#endif
	/*configure the clock speed prescaler*/
#if SPI_PRESCALER   ==   DIVISION_BY_2
	CLR_BIT(SPCR,SPCR_SPR0);
	CLR_BIT(SPCR,SPCR_SPR1);
	SET_BIT(SPSR,SPSR_SPI2X);
#elif SPI_PRESCALER   ==   DIVISION_BY_4
	CLR_BIT(SPCR,SPCR_SPR0);
	CLR_BIT(SPCR,SPCR_SPR1);
	CLR_BIT(SPSR,SPSR_SPI2X);
#elif SPI_PRESCALER   ==   DIVISION_BY_8
	SET_BIT(SPCR,SPCR_SPR0);
	CLR_BIT(SPCR,SPCR_SPR1);
	SET_BIT(SPSR,SPSR_SPI2X);
#elif SPI_PRESCALER   ==   DIVISION_BY_16
	SET_BIT(SPCR,SPCR_SPR0);
	CLR_BIT(SPCR,SPCR_SPR1);
	CLR_BIT(SPSR,SPSR_SPI2X);
#elif SPI_PRESCALER   ==   DIVISION_BY_32
	CLR_BIT(SPCR,SPCR_SPR0);
	SET_BIT(SPCR,SPCR_SPR1);
	SET_BIT(SPSR,SPSR_SPI2X);
#elif SPI_PRESCALER   ==   DIVISION_BY_64
	CLR_BIT(SPCR,SPCR_SPR0);
	SET_BIT(SPCR,SPCR_SPR1);
	CLR_BIT(SPSR,SPSR_SPI2X);
#elif SPI_PRESCALER   ==   DIVISION_BY_128
	SET_BIT(SPCR,SPCR_SPR0);
	SET_BIT(SPCR,SPCR_SPR1);
	CLR_BIT(SPSR,SPSR_SPI2X);
#else #error Wrong presacaller configuration
#endif
/*configure the Interrupt flag*/
#if  SPI_INT_ENABLE    ==   ENABLED
     SET_BIT(SPCR,SPCR_SPIE);
#elif SPI_INT_ENABLE    ==   DISABLED
     CLR_BIT(SPCR,SPCR_SPIE);
#else #error wrong interrupt configuration
#endif
     /*configure the Data order direction*/
#if SPI_DATA_DIRECTION   ==   SPI_DATA_LSB
     SET_BIT(SPCR,SPCR_DORD);
#elif SPI_DATA_DIRECTION   ==   SPI_DATA_MSB
     CLR_BIT(SPCR,SPCR_DORD);
#else #error wrong Data order configuration
#endif
     /*configure the SPI ENABEL */
#if SPI_ENABLE    ==    ENABLED
     SET_BIT(SPCR,SPCR_SPE);
#elif SPI_ENABLE    ==    DISABLED
     CLR_BIT(SPCR,SPCR_SPE);
#else #error wrong Enabel configuration
#endif

}
uint8 SPI_u8SEND_RECIEVE(Copy_u8Data)
{
	uint8 Local_u8RecievedData;
	SPDR=Copy_u8Data;
	while((GET_BIT(SPSR,SPSR_SPIF))==0);
	Local_u8RecievedData=SPDR;
	return Local_u8RecievedData;
}

