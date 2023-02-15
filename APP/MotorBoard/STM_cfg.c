#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "DIO_interface.h"

#include "STM_interface.h"



Stepper_t  Stepper_One={
		.STM_u8Port=DIO_u8PORTC,
		.STM_u8Blue=DIO_u8PIN0,
		.STM_u8Pink=DIO_u8PIN1,
		.STM_u8Yellow=DIO_u8PIN2,
		.STM_u8Orange=DIO_u8PIN3,
};





	/*Please select the Port to connect the motor options 1-DIO_u8PORTA
	 *                                                    2-DIO_u8PORTB
	 *                                                    3-DIO_u8PORTC
	 *                                                    4-DIO_u8PORTD*/


	/*Please select the pins to connect the motor wire options 1-DIO_u8PIN0
	 *                                                         2-DIO_u8PIN1
	 *                                                         3-DIO_u8PIN2
	 *                                                         4-DIO_u8PIN3
	 *                                                         5-DIO_u8PIN4
	 *                                                         6-DIO_u8PIN5
	 *                                                         7-DIO_u8PIN6
	 *                                                         8-DIO_u8PIN7*/







