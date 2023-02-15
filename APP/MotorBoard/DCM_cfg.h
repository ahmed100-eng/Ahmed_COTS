/**************************************************************/
/**************************************************************/
/*********		Author: Ahmed Abdelaziz			*******************/
/*********		File: DCM_cfg.h		*******************/
/*********		Version: 1.00				*******************/
/**************************************************************/
#ifndef DCM_CFG_H_
#define DCM_CFG_H_

/*Please choose which port to connect SWITCH Control PIN
	 * options:  1- DIO_u8PORTA
	 * 			 2- DIO_u8PORTB
	 * 			 3- DIO_u8PORTC
	 * 			 4- DIO_u8PORTD

*/


/*Please choose the SWITCH Control PIN
	 * options      1- DIO_u8PIN0
	 *              2- DIO_u8PIN1
	 *              3- DIO_u8PIN2
	 *              4- DIO_u8PIN3
	 *              5- DIO_u8PIN4
	 *              6- DIO_u8PIN5
	 *              7- DIO_u8PIN6
	 *              8- DIO_u8PIN7
	 *              */
/*Please choose if Have Braking Circuit or not options 1- ENABLE
 *                                                     2- DISABLE*/

#define SW_BRAKECIRCUIT    DISABLE


#endif
