
#ifndef USART_INTERFACE_H_
#define USART_INTERFACE_H_

void UART_voidInit(void);
void UART_voidTransData(uint8 Copy_u8Data);
uint8 UART_u8RecieveData(void);
uint8 UART_u8SendString(const char *Copy_pString);
uint8 UART_voidRecieveBufferSynch(uint8 Copy_u8DataArr[],uint8 Copy_u8Size);
uint8 UART_voidSendBufferAsynch(uint8 Copy_u8DataArr[],uint8 Copy_u8Size,void(*Copy_pvCallBackFunc)(void));
uint8 UART_voidRecieveBufferAsynch(uint8 Copy_u8DataArr[],uint8 Copy_u8Size,void(*Copy_pvCallBackFunc)(void));
void UART_ReceiveBufferFlush(void);

#endif
