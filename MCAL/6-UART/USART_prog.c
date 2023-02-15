

#include "STD_TYPES.h"
#include "defines.h"
#include "BIT_MATH.h"

#include "USART_interface.h"
#include "USART_reg.h"
#include "USART_private.h"
#include "USART_cfg.h"

static void (*UART_pvRecieveCallBackFunc)(void)=NULL;
static void (*UART_pvSendCallBackFunc)(void)=NULL;
static uint8 *UART_pu8SendArr=NULL;
static uint8 *UART_pu8RecieveArr=NULL;
static uint8 UART_u8SendSize=0;
static uint8 UART_u8RecieveSize=0;
static uint8 UART_u8SendCounter=0;
static uint8 UART_u8RecieveCounter=0;
static uint8 UART_TimeoutRecieveFlag=0;
void UART_voidInit(void)
{
	uint8 Local_u8UCSRC=0;
	uint16 Local_u16Speed=0;
#if UART_RX_ACTIVATION    ==    UART_RX_ENABLE
   SET_BIT(UCSRB,UCSRB_RXEN); 	/*Enable Receive Bit*/
#elif UART_RX_ACTIVATION    ==   UART_RX_DISABLE
   CLR_BIT(UCSRB,UCSRB_RXEN); 	/*DISABLE Receive Bit*/
#else #error wrong UART RX configuration
#endif
#if UART_TX_ACTIVATION    ==    UART_TX_ENABLE
   SET_BIT(UCSRB,UCSRB_TXEN); 	/*Enable Transmitting Bit*/
#elif UART_RX_ACTIVATION    ==   UART_TX_DISABLE
   CLR_BIT(UCSRB,UCSRB_TXEN);; 	/*Disable Transmitting Bit*/
#else #error wrong UART TX configuration
#endif
#if UART_DATABIT_MODE   ==    UART_8BITDATA
   /*8 Bit Data */
   CLR_BIT(UCSRB,UCSRB_UCSZ2);
   SET_BIT(Local_u8UCSRC,UCSRC_UCSZ0);
   SET_BIT(Local_u8UCSRC,UCSRC_UCSZ1);
#elif UART_DATABIT_MODE   ==    UART_6BITDATA
   /*6 Bit Data */
   CLR_BIT(UCSRB,UCSRB_UCSZ2);
   SET_BIT(Local_u8UCSRC,UCSRC_UCSZ0);
   CLR_BIT(Local_u8UCSRC,UCSRC_UCSZ1);
#elif UART_DATABIT_MODE   ==    UART_5BITDATA
   /*5 Bit Data */
   CLR_BIT(UCSRB,UCSRB_UCSZ2);
   CLR_BIT(Local_u8UCSRC,UCSRC_UCSZ0);
   CLR_BIT(Local_u8UCSRC,UCSRC_UCSZ1);
#elif UART_DATABIT_MODE   ==    UART_7BITDATA
   /*7 Bit Data */
   CLR_BIT(UCSRB,UCSRB_UCSZ2);
   CLR_BIT(Local_u8UCSRC,UCSRC_UCSZ0);
   SET_BIT(Local_u8UCSRC,UCSRC_UCSZ1);
#elif UART_DATABIT_MODE   ==    UART_9BITDATA
   /*9 Bit Data */
   SET_BIT(UCSRB,UCSRB_UCSZ2);
   SET_BIT(Local_u8UCSRC,UCSRC_UCSZ0);
   SET_BIT(Local_u8UCSRC,UCSRC_UCSZ1);
#else #error wrong Bit data configuration
#endif
#if UART_STOPBIT_MODE    ==    UART_STOPBIT1
   /*Stop bit 1 bit*/
   CLR_BIT(Local_u8UCSRC,UCSRC_USBS);
#elif UART_STOPBIT_MODE    ==    UART_STOPBIT2
   /*Stop bit 2 bits*/
   SET_BIT(Local_u8UCSRC,UCSRC_USBS);
#else #error Wrong stop bit configuration
#endif
#if UART_PARITY_MODE    ==    UART_NOPARITY
   /*No parity*/
   CLR_BIT(Local_u8UCSRC,UCSRC_UPM0);
   CLR_BIT(Local_u8UCSRC,UCSRC_UPM1);
#elif UART_PARITY_MODE    ==    UART_ODDPARITY
   /*Odd parity*/
   SET_BIT(Local_u8UCSRC,UCSRC_UPM0);
   SET_BIT(Local_u8UCSRC,UCSRC_UPM1);
#elif UART_PARITY_MODE    ==    UART_EVENPARITY
   /*Odd parity*/
   CLR_BIT(Local_u8UCSRC,UCSRC_UPM0);
   SET_BIT(Local_u8UCSRC,UCSRC_UPM1);
#else #error Wrong parity check mode configuration
#endif
   /*Baud rate calculation*/
   Local_u16Speed = (uint16)((16000000ul/(16*(uint32)UART_BAUDRATE))-1);
   if(Local_u16Speed <= 255u)
   {
	   UBRRL = (uint8)Local_u16Speed;
   }
   else
   {
	   UBRRL = (uint8)Local_u16Speed;
	   Local_u16Speed = Local_u16Speed >> 8;
	   UBRRH = 0x0f & (uint8)Local_u16Speed;
   }
   /*Writing to control register*/
   SET_BIT(Local_u8UCSRC,UCSRC_URSEL);
   UCSRC=Local_u8UCSRC;
}
void UART_voidTransData(uint8 Copy_u8Data)
{
	uint16 Local_u16TimeoutCounter=0;
	/*Checking the transmit buffer is empty*/
	while(GET_BIT(UCSRA,UCSRA_UDRE)==0);
    	UDR= Copy_u8Data;

}
uint8 UART_u8RecieveData(void)
{
	uint32 Local_u32TimeoutCounter=0u;
	UART_TimeoutRecieveFlag=0;
   while(GET_BIT(UCSRA,UCSRA_RXC)==0  && Local_u32TimeoutCounter <= 50000u)
   {
	   Local_u32TimeoutCounter++;
   }
   if(Local_u32TimeoutCounter > 50000u)
   {
	   UART_TimeoutRecieveFlag = 1u;
   }
   else
   {
	   Local_u32TimeoutCounter = 0u;
   }
   return UDR;
}
uint8 UART_u8SendString(const char *Copy_pString)
{
	uint8 Local_u8ErrorState=OK;
	uint8 Local_u8Counter=0;
	if(Copy_pString != NULL)
	{
		while(Copy_pString[Local_u8Counter] != '\0')
		{
			UART_voidTransData(Copy_pString[Local_u8Counter]);
			Local_u8Counter++;
		}
	}
	else
	{
		Local_u8ErrorState=NULL_PTR_ERR;
	}
	return Local_u8ErrorState;
}
uint8 UART_voidRecieveBufferSynch(uint8 Copy_u8DataArr[],uint8 Copy_u8Size)
{
   uint8 Local_u8Counter=0;

   while(Local_u8Counter < Copy_u8Size)
   {
	   Copy_u8DataArr[Local_u8Counter] = UART_u8RecieveData();
	   Local_u8Counter++;
       if(UART_TimeoutRecieveFlag == 1)
       {
    	   break;
       }
   }
   return 1;
}
uint8 UART_voidSendBufferAsynch(uint8 Copy_u8DataArr[],uint8 Copy_u8Size,void(*Copy_pvCallBackFunc)(void))
{
	uint8 Local_u8ErrorState=OK;
    if(Copy_pvCallBackFunc != NULL)
    {
    	/*Initialize the data globally*/
    	UART_pvSendCallBackFunc = Copy_pvCallBackFunc;
    	UART_pu8SendArr = Copy_u8DataArr;
    	UART_u8SendSize = Copy_u8Size;
    	UART_u8SendCounter=0;
        /*interrupt enable*/
        SET_BIT(UCSRB,UCSRB_TXCIE);
        UDR = UART_pu8SendArr[UART_u8SendCounter];
    }
	return Local_u8ErrorState;
}
uint8 UART_voidRecieveBufferAsynch(uint8 Copy_u8DataArr[],uint8 Copy_u8Size,void(*Copy_pvCallBackFunc)(void))
{
	uint8 Local_u8ErrorState=OK;
    if(Copy_pvCallBackFunc != NULL)
    {
    	/*Initialize the data globally*/
    	UART_pvRecieveCallBackFunc = Copy_pvCallBackFunc;
    	UART_pu8RecieveArr = Copy_u8DataArr;
    	UART_u8RecieveSize = Copy_u8Size;
    	UART_u8RecieveCounter=0;
        /*interrupt enable*/
        SET_BIT(UCSRB,UCSRB_RXCIE);
        UART_pu8RecieveArr[UART_u8RecieveCounter] = UDR;
    }
	return Local_u8ErrorState;
}
void __vector_15 (void) __attribute__((signal));
void __vector_15 (void)
{
	if(UART_pu8SendArr != NULL)
	{
		UART_u8SendCounter++;
		if(UART_u8SendCounter < UART_u8SendSize)
		{
			/*Send data doesn't complete send the next data*/
	        UDR = UART_pu8SendArr[UART_u8SendCounter];
		}
		else
		{
			/*Data sending finished*/
			UART_u8SendCounter=0;
			/*Disable interrupt*/
			CLR_BIT(UCSRB,UCSRB_TXCIE);
			/*Invoke the application notification  function*/
			if(UART_pvSendCallBackFunc != NULL)
			{
				UART_pvSendCallBackFunc();
			}
			else
			{
				/*Do no thing*/
			}
		}
	}
}
void __vector_13 (void) __attribute__((signal));
void __vector_13 (void)
{
	if(UART_pu8RecieveArr != NULL)
	{
		UART_u8RecieveCounter++;
		if(UART_u8RecieveCounter < UART_u8RecieveSize)
		{
			/*Receive data doesn't complete send the next data*/
			UART_pu8RecieveArr[UART_u8RecieveCounter] = UDR;
		}
		else
		{
			/*Data Receiving finished*/
			UART_u8RecieveCounter=0;
			/*Disable interrupt*/
			CLR_BIT(UCSRB,UCSRB_RXCIE);
			/*Invoke the application notification  function*/
			if(UART_pvRecieveCallBackFunc != NULL)
			{
				UART_pvRecieveCallBackFunc();
			}
			else
			{
				/*Do no thing*/
			}
		}
	}
}
void UART_ReceiveBufferFlush(void)
{
	   CLR_BIT(UCSRB,UCSRB_RXEN); 	/*D Receive Bit*/
	   SET_BIT(UCSRB,UCSRB_RXEN); 	/*Enable Receive Bit*/
}
