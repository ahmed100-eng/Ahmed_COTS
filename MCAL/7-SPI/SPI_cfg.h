/*
 * SPI_cfg.h
 *
 *  Created on: Jan 17, 2023
 *      Author: Pc
 */

#ifndef SPI_CFG_H_
#define SPI_CFG_H_

/*Select the Mode of SPI peripheral options : 1-SPI_MASTER
 *                                            2-SPI_SLAVE*/

#define SPI_MODE            SPI_MASTER

/*Select the idle state options : 1-SPI_IDLE_HIGH
 *                                2-SPI_IDLE_LOW*/

#define SPI_IDLE_STATE       SPI_IDLE_LOW


/*Select the clock Phase settings options : 1-SAMPLE_FIRST
 *                                          2-SETUP_FIRST*/
#define SPI_CLOCK_PHASE         SAMPLE_FIRST


/*Select the prescaler of clock options : 1-DIVISION_BY_2
 *                                        2-DIVISION_BY_4
 *                                        3-DIVISION_BY_8
 *                                        4-DIVISION_BY_16
 *                                        5-DIVISION_BY_32
 *                                        6-DIVISION_BY_64
 *                                        7-DIVISION_BY_128*/

#define SPI_PRESCALER             DIVISION_BY_128

/*Enable the SPI peripheral options 1-ENABLED
 *                                  2-DISABLED*/

#define SPI_ENABLE               ENABLED

/*Enable the SPI peripheral interrupt options 1-ENABLED
 *                                            2-DISABLED*/

#define SPI_INT_ENABLE               DISABLED

/*Select the Data order Direction 1-SPI_DATA_LSB
 *                                2-SPI_DATA_MSB*/

#define SPI_DATA_DIRECTION       SPI_DATA_LSB



#endif /* SPI_CFG_H_ */
