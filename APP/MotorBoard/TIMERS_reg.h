/*
 * TIMERS_reg.h
 *
 *  Created on: Dec 24, 2022
 *      Author: Pc
 */

#ifndef TIMERS_REG_H_
#define TIMERS_REG_H_

#define TCCR0             *((volatile uint8*)0x53)
#define TCNT0             *((volatile uint8*)0x52)
#define TIMSK             *((volatile uint8*)0x59)
#define OCR0              *((volatile uint8*)0x5c)


#define TCCR1A            *((volatile uint8*)0x4f)
#define TCCR1A_WGM10       0u
#define TCCR1A_WGM11       1u
#define TCCR1A_FOC1B       2u
#define TCCR1A_FOC1A       3u
#define TCCr1A_COM1B0      4u
#define TCCr1A_COM1B1      5u
#define TCCr1A_COM1A0      6u
#define TCCr1A_COM1A1      7u

#define TCCR1B             *((volatile uint8*)0x4e)
#define TCCR1B_CS10        0u
#define TCCR1B_CS11        1u
#define TCCR1B_CS12        2u
#define TCCR1B_WGM12       3u
#define TCCR1B_WGM13       4u
#define TCCR1B_ICES1       6u
#define TCCR1B_ICNC1       7u

#define TCNT1             *((volatile uint16*)0x4c)


#define OCR1A              *((volatile uint16*)0x4a)


#define OCR1B              *((volatile uint16*)0x48)


#define ICR1              *((volatile uint16*)0x46)


#define TIMSK              *((volatile uint8*)0x59)
#define TIMSK_TOIE1        2u
#define TIMSK_OCIE1B       3u
#define TIMSK_OCIE1A       4u
#define TIMSK_TICIE1       5u

#endif /* TIMERS_REG_H_ */
