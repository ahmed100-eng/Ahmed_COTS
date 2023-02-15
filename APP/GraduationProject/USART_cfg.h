#ifndef USART_CFG_H_
#define USART_CFG_H_

/*Configuration of UART Receiver options : 1- UART_RX_ENABLE
 *                                         2- UART_RX_DISABLE */
#define UART_RX_ACTIVATION        UART_RX_ENABLE

/*Configuration of UART Receiver options : 1- UART_TX_ENABLE
 *                                         2- UART_TX_DISABLE */
#define UART_TX_ACTIVATION        UART_TX_ENABLE

/*Configuration of UART Data bits mode options : 1-UART_5BITDATA
 *                                               2-UART_6BITDATA
 *                                               3-UART_7BITDATA
 *                                               4-UART_8BITDATA
 *                                               5-UART_9BITDATA*/
#define UART_DATABIT_MODE         UART_8BITDATA

/*Configuration of Number of stop bit options : 1- UART_STOPBIT1
 *                                            2- UART_STOPBIT2*/
#define UART_STOPBIT_MODE         UART_STOPBIT1


/*Configuration of parity mode options : 1- UART_NOPARITY
 *                                       2- UART_ODDPARITY
 *                                       3- UART_EVENPARITY*/

#define UART_PARITY_MODE          UART_NOPARITY

/*Configuration of Baud rate please write the speed*/

#define UART_BAUDRATE             9600ul

#endif
