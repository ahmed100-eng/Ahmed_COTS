

#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "defines.h"

#include "ADC_private.h"
#include "ADC_cfg.h"
#include "ADC_reg.h"
#include "ADC_interface.h"
#include "GIE_interface.h"

static uint16 *ADC_pu16ConversionResult = NULL ;
static void (*ADC_pvNotificationFunc)(void)= NULL;
static uint8 ADC_u8BusyFlag = IDLE;
static ADC_ChainConv_t *ADC_pstChainData= NULL;
static uint8 ADC_u8ChainCounter;
static uint8 ADC_u8Chose=0u;

void ADC_voidInit(void)
{
	/*Reference selection*/
#if ADC_u8REF_VOLT  == AREF_REF
	   CLR_BIT(ADMUX,ADMUX_REFS0);
	   CLR_BIT(ADMUX,ADMUX_REFS1);
#elif ADC_u8REF_VOLT ==  AVCC_REF
   SET_BIT(ADMUX,ADMUX_REFS0);
   CLR_BIT(ADMUX,ADMUX_REFS1);
#elif ADC_u8REF_VOLT  == INTERNAL_2560mV_REF
   SET_BIT(ADMUX,ADMUX_REFS0);
   SET_BIT(ADMUX,ADMUX_REFS1);
#else #error ADC_u8REF_VOLT wrong configuration
#endif
   /*Enable left adjusting*/
#if ADC_RESOLUTION  == EIGHT_BITS
   /*Enable left adjusting*/
   SET_BIT(ADMUX,ADMUX_ADLAR);
#elif ADC_RESOLUTION  == TEN_BITS
   CLR_BIT(ADMUX,ADMUX_ADLAR);
#else #error wrong ADC_RESOLUTION configuration
#endif
#if ADC_u8INT_ENABLE  ==  DISABLED
   CLR_BIT(ADCSRA,ADCSRA_ADIE);
#elif ADC_u8INT_ENABLE  ==  ENABLED
   SET_BIT(ADCSRA,ADCSRA_ADIE);
#else #error wrong ADC_u8INT_ENABLE configuration
#endif
   /*configure Prescaler setting*/
   ADCSRA &= PRESCALER_MASK;
   ADCSRA |= ADC_u8PRESCALER_VAL;

   /*Enable ADC*/
   SET_BIT(ADCSRA,ADCSRA_ADEN);

}
uint8 ADC_u8StartConversionSynch(uint8 Copy_u8Channel,uint16* Copy_pu16Result)

{
   uint8 Local_u8ErrorState=OK;

   if(Copy_pu16Result!= NULL)
   {
	   /*Check if ADC is not busy*/
	   if(ADC_u8BusyFlag == IDLE)
	   {
		   uint32 Local_u32TimeoutCounter= 0u;
		   /*ADC is now busy*/
		   ADC_u8BusyFlag = BUSY;



	   /*configure the analog Channel */
		ADMUX &= CHANNEL_MASK;
		ADMUX|=Copy_u8Channel;

		/*Start conversion*/
		SET_BIT(ADCSRA,ADCSRA_ADSC);
		/*Enable interrupt flag*/
		//GIE_voidEnable();
		//SET_BIT(ADCSRA,ADCSRA_ADIE);

		/*Wait until ADC conversion complete*/
		while(((GET_BIT(ADCSRA,ADCSRA_ADIF))==0) && Local_u32TimeoutCounter < ADC_u32TIMEOUT)
			{
			  Local_u32TimeoutCounter++;
			}
		if(Local_u32TimeoutCounter>=ADC_u32TIMEOUT)
		{
			/*Loop is broken because flag isn't raised until timeout is passed*/
			Local_u8ErrorState=TIMEOUT_ERR;
		}
		else
		{
			/*Loop is broken because flag is raised befor timeout is passed*/

		/*Clear The conversion complete flag*/
		SET_BIT(ADCSRA,ADCSRA_ADIF);
		/*Read the data*/
	#if ADC_RESOLUTION == EIGHT_BITS
		*Copy_pu16Result= ADCH;
	#elif ADC_RESOLUTION == TEN_BITS
		*Copy_pu16Result= ADC;
	#endif
		/*ADC is now IDLE*/
		ADC_u8BusyFlag = IDLE;
		}
     }
	   else
	   {
		   /*ADC was busy, assign the error state*/
		   Local_u8ErrorState = BUSY_STATE_ERR;
	   }
   }
   else
   {
	   Local_u8ErrorState=NULL_PTR_ERR;
   }


	return Local_u8ErrorState;

}
uint8 ADC_u8StartSingleConversionAsynch(uint8 Copy_u8Channel,uint16* Copypu16Result,void (*Copy_pvNotficationFunc)(void))
{
	uint8 Local_u8ErrorState = OK;
	if((Copypu16Result != NULL) && (Copy_pvNotficationFunc != NULL))
	{
		/*Check if ADC is not busy*/
	   if(ADC_u8BusyFlag == IDLE)
	   {
		   /*ADC is now busy*/
		   ADC_u8BusyFlag = BUSY;
		   /*Start conversion Asynch is the choose*/
		   ADC_u8Chose=SINGLE_CONV_ASYNCH;

		/*initialize the result pointer globally*/
		ADC_pu16ConversionResult = Copypu16Result;
		/*initialize the notification function pointer globally*/
		ADC_pvNotificationFunc = Copy_pvNotficationFunc;
		/*configure the analoge Channel */
		ADMUX &= CHANNEL_MASK;
		ADMUX|=Copy_u8Channel;

		/*Start conversion*/
		SET_BIT(ADCSRA,ADCSRA_ADSC);

		/*Enable interrupt flag*/
		SET_BIT(ADCSRA,ADCSRA_ADIE);

		}
	   else
	   {
		   /*ADC was busy, assign the error state*/
		   Local_u8ErrorState = BUSY_STATE_ERR;
	   }
	}
	else
	{
		Local_u8ErrorState = NULL_PTR_ERR;
	}
	return Local_u8ErrorState;
}
uint8 ADC_u8StartChainingConvAsynch(ADC_ChainConv_t*Copy_pstData)
{
	uint8 Local_u8ErrorState=OK;
	if((Copy_pstData!=NULL) && (Copy_pstData->ADC_pu8ChannelArr != NULL)&& (Copy_pstData->ADC_pvNotificationFunc != NULL)&& (Copy_pstData->ADC_pu8ResultArr != NULL) )
	{
		/*Check if ADC is not busy*/
	   if(ADC_u8BusyFlag == IDLE)
	   {
		   /*ADC is now busy*/
		   ADC_u8BusyFlag = BUSY;
		   /*Start Chain conversion Asynch is the choose*/
		   ADC_u8Chose=CHAIN_CONV_ASYNCH;
           ADC_pstChainData= Copy_pstData;
	       ADC_u8ChainCounter=0;
			/*configure the analog Channel */
			ADMUX &= CHANNEL_MASK;
			ADMUX|=ADC_pstChainData->ADC_pu8ChannelArr[ADC_u8ChainCounter];
		    /*Start first conversion*/
			SET_BIT(ADCSRA,ADCSRA_ADSC);

			/*Enable interrupt flag*/
			SET_BIT(ADCSRA,ADCSRA_ADIE);
	   }
	   else
	   {
		   /*ADC was busy, assign the error state*/
		   Local_u8ErrorState = BUSY_STATE_ERR;
	   }
	}
	else
	{
		Local_u8ErrorState=NULL_PTR_ERR;
	}
    return Local_u8ErrorState;
}
/**
 * @brief ADC conversion complete ISR
 *
 */
void __vector_16 (void)    __attribute__((signal));
void __vector_16 (void)
{
	if(ADC_pu16ConversionResult != NULL)
	{
		if(ADC_u8Chose==SINGLE_CONV_ASYNCH)
		{
#if ADC_RESOLUTION == EIGHT_BITS
	*ADC_pu16ConversionResult= ADCH;
#elif ADC_RESOLUTION == TEN_BITS
	*ADC_pu16ConversionResult= ADC;
#endif
	/*Disable the ADC conversion complete interrupt*/
	CLR_BIT(ADCSRA,ADCSRA_ADIE);
	/*ADC is now IDLE*/
	ADC_u8BusyFlag = IDLE;
	/*Invoke the application notification function */
	if(ADC_pvNotificationFunc !=NULL)
	{
		ADC_pvNotificationFunc();
	}
	else
	{
		/*Notification function pointer is NULL*/
	}
		}
		else if(ADC_u8Chose==CHAIN_CONV_ASYNCH)
		{
#if ADC_RESOLUTION == EIGHT_BITS
	ADC_pstChainData->ADC_pu8ResultArr[ADC_u8ChainCounter]= ADCH;
#elif ADC_RESOLUTION == TEN_BITS
	ADC_pstChainData->ADC_pu8ResultArr[ADC_u8ChainCounter]= ADC;
#endif
	/*Increase counter*/
	ADC_u8ChainCounter++;

	if(ADC_u8ChainCounter<ADC_pstChainData->ADC_u8ChainSize)
	{
		/*Chain is not finished yet*/

		/*configure the analog Channel */
		ADMUX &= CHANNEL_MASK;
		ADMUX|=ADC_pstChainData->ADC_pu8ChannelArr[ADC_u8ChainCounter];
	    /*Start next conversion*/
		SET_BIT(ADCSRA,ADCSRA_ADSC);
	}
	else
	{
		/*Chain is finished*/
		/*Disable the ADC conversion complete interrupt*/
		CLR_BIT(ADCSRA,ADCSRA_ADIE);
		/*ADC is now IDLE*/
		ADC_u8BusyFlag = IDLE;
		/*Invoke the application notification function */
		if(ADC_pvNotificationFunc !=NULL)
		{

			ADC_pstChainData->ADC_pvNotificationFunc();
		}
		else
		{
			/*Notification function pointer is NULL*/
		}
	}

		}

	}
	else
	{
		/*Conversion result pointer is NULL*/
	}
}
