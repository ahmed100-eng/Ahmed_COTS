


#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_

#define ADC_SINGLE_ENDED_CH0   0u
#define ADC_SINGLE_ENDED_CH1   1u
#define ADC_SINGLE_ENDED_CH2   2u
#define ADC_SINGLE_ENDED_CH3   3u
#define ADC_SINGLE_ENDED_CH4   4u
#define ADC_SINGLE_ENDED_CH5   5u
#define ADC_SINGLE_ENDED_CH6   6u
#define ADC_SINGLE_ENDED_CH7   7u

typedef struct ADC_Chain
{
	uint8 ADC_u8ChainSize;
	uint8 *ADC_pu8ChannelArr;
	uint16 *ADC_pu8ResultArr;
	void (*ADC_pvNotificationFunc)(void);
	struct ADC_chain* pADC_chain;
}ADC_Chain_t;


void ADC_voidInit(void);
uint8 ADC_u8StartConversionSynch(uint8 Copy_u8Channel,uint16* Copy_pu16Result);
uint8 ADC_u8StartConversionAsynch(uint8 Copy_u8Channel,uint16* Copypu16Result,void (*Copy_pvNotficationFunc)(void));
uint8 ADC_u8StartChainingConvAsynch(ADC_Chain_t*Copy_Data);

#endif
