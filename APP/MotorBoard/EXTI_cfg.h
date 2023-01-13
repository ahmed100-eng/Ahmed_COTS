

#ifndef EXTI_CFG_H_
#define EXTI_CFG_H_

/*detail configure the INT0 sense control options are 1-EXTI_u8LOW_LEVEL
 *                                                    2-EXTI_u8ON_CHANGE
 *                                                    3-EXTI_u8FALLINGEDGE
 *                                                    4-EXTI_u8RISINGEDGE*/

#define INT0_SENSE_CTRL      EXTI_u8FALLINGEDGE

/*detail configure the INT0 intial state options are   1-ENABLED
 *                                                    2-DISABLED
 *                                                    */

#define INT0_INTIAL_STATE     ENABLED

/*detail configure the INT1 sense control options are 1-EXTI_u8LOW_LEVEL
 *                                                    2-EXTI_u8ON_CHANGE
 *                                                    3-EXTI_u8FALLINGEDGE
 *                                                    4-EXTI_u8RISINGEDGE*/

#define INT1_SENSE_CTRL      EXTI_u8FALLINGEDGE

/*detail configure the INT1 intial state options are   1-ENABLED
 *                                                    2-DISABLED
 *                                                    */

#define INT1_INTIAL_STATE     ENABLED


/*detail configure the INT2 sense control options are
 *                                                    1-EXTI_u8FALLINGEDGE
 *                                                    2-EXTI_u8RISINGEDGE*/

#define INT2_SENSE_CTRL      EXTI_u8FALLINGEDGE

/*detail configure the INT2 intial state options are   1-ENABLED
 *                                                    2-DISABLED
 *                                                    */

#define INT2_INTIAL_STATE     ENABLED



#endif
