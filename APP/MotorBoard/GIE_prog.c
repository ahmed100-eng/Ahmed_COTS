#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "GIE_reg.h"
#include "GIE_interface.h"


void GIE_voidEnable(void)
{
	//SET_BIT(SREG,SREG_I);
	 __asm __volatile("SEI"); /*Inline assemble to set I bit*/
}
void GIE_voidDisable(void)
{
	//CLR_BIT(SREG,SREG_I);
	__asm __volatile("CLI"); /*Inline assemble to clear I bit*/
}
