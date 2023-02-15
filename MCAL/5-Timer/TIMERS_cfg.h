/*
 * TIMERS_cfg.h
 *
 *  Created on: Jan 15, 2023
 *      Author: Pc
 */

#ifndef TIMERS_CFG_H_
#define TIMERS_CFG_H_

/*Choose the Prescaler configuration options : 1-NO_CLOCK_SOURCE
 *                                             2-DIVISION_BY_1
 *                                             3-DIVISION_BY_8
 *                                             4-DIVISION_BY_64
 *                                             5-DIVISION_BY_256
 *                                             6-DIVISION_BY_1024
 *                                             7-EXTERNAL_CLOCK_FEDG
 *                                             8-EXTERNAL_CLOCK_REDG*/


#define TIMER0_u8PRESCALER       DIVISION_BY_8
#define TIMER1_u8PRESCALER       DIVISION_BY_8
#define TIMER2_u8PRESCALER       DIVISION_BY_8

#endif /* TIMERS_CFG_H_ */
