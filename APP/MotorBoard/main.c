#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "defines.h"
#include <util/delay.h>

#include "DIO_interface.h"
#include "TIMERS_reg.h"
#include "PORT_interface.h"
#include "EXTI_interface.h"
#include "GIE_interface.h"
#include "TIMERS_interface.h"
#include "CLCD_interface.h"
#include "ADC_interface.h"
#include "DCM_interface.h"
#include "STM_interface.h"
#include "KPD_interface.h"

void APPlication(DCM_cfg * Copy_DCM_Data);
void EnterID(uint8 Copy_NumArr[],uint8 Copy_Size,uint8 Copy_counter);
void EnterPass(uint8 Copy_PassArr[],uint8 Copy_Size,uint8 Copy_counter);
sint32 MAP(sint32 InputRangeMin,sint32 InputRangeMax,sint32 OutputRangeMin,sint32 OutputRangeMax,sint32 InputValu);
void MotorSpeedControl(void);
void ResetSystem(void);

DCM_cfg *DCM_pType=NULL;
void main(void)
{
	PORT_voidInit();
	EXTI_voidInit();
	CLCD_voidInit();
	ADC_voidInit();
	//EXTI_u8SetCallBack(EXTI_u8INT2,&ResetSystem);
	//GIE_voidEnable();
	uint8 Local_u8HamokshaFace[8]={0b00001110,0b00011111,0b00010001,0b00011011,0b00010001,0b00011011,0b00001110,0};
	uint8 Local_u8HamokshaBody[8]={0b00000100,0b00000100,0b00011111,0b00000100,0b00000100,0b00000100,0b00011011,0};
	uint8 Local_LoopCounter1=0;
	uint8 Local_u8WrongPass=0,Local_u8Temprature=0,MappedLight=0;;
	uint8 Local_u8NumArr[4],Local_u8PassArr[4];
	uint16 Local_u16Temp=0,Local_u16ADCValue=0,Local_u16Light=0;
	DCM_cfg DCM_Type;
	DCM_Type.DCM_u8SwitchPort=DIO_u8PORTB;
	DCM_Type.DCM_u8Switch1Pin=DIO_u8PIN3;
	DCM_Type.DCM_u8Switch2Pin=DIO_u8PIN1;
	DCM_Type.DCM_u8Switch3Pin=DIO_u8PIN1;
	DCM_Type.DCM_u8Switch4Pin=DIO_u8PIN3;
	DCM_pType=&DCM_Type;
	CLCD_viodGoToXY(3,0);
	CLCD_u8SendString("WELECOME");
	_delay_ms(500);
	for(Local_LoopCounter1=0;Local_LoopCounter1<=15;Local_LoopCounter1++)
	{
		CLCD_voidSendCmd(1);
		CLCD_voidSendSpecialCharacter(Local_u8HamokshaFace,0,Local_LoopCounter1,0);
		CLCD_voidSendSpecialCharacter(Local_u8HamokshaBody,1,Local_LoopCounter1,1);
		_delay_ms(100);
	}

	CLCD_voidSendCmd(1);
	while(1)
	{
  	  CLCD_u8SendString("Enter ID");

      for(Local_LoopCounter1=0;Local_LoopCounter1<4;Local_LoopCounter1++)
      {

    	  CLCD_viodGoToXY(Local_LoopCounter1,1);

    	  switch(Local_LoopCounter1)
    	  {
    	  case 0 :
    	  {
           EnterID(Local_u8NumArr,4,Local_LoopCounter1);
    	  }break;
    	  case 1 :
    	  {
              EnterID(Local_u8NumArr,4,Local_LoopCounter1);
    	  }break;
    	  case 2 :
    	  {
              EnterID(Local_u8NumArr,4,Local_LoopCounter1);
    	  }break;
    	  case 3 :
    	  {
              EnterID(Local_u8NumArr,4,Local_LoopCounter1);
    	  }break;
    	  }
      }
      CLCD_voidSendCmd(1);
	  CLCD_u8SendString("Enter Password");

  	  for(Local_LoopCounter1=0;Local_LoopCounter1<4;Local_LoopCounter1++)
  	  {

  		  CLCD_viodGoToXY(Local_LoopCounter1,1);
    	  switch(Local_LoopCounter1)
    	  {
    	  case 0 :
    	  {
    		  EnterPass(Local_u8PassArr,4,Local_LoopCounter1);
    	  }break;
    	  case 1 :
    	  {
    		  EnterPass(Local_u8PassArr,4,Local_LoopCounter1);
          }break;
    	  case 2 :
    	  {
    		  EnterPass(Local_u8PassArr,4,Local_LoopCounter1);
          }break;
    	  case 3 :
    	  {
    		  EnterPass(Local_u8PassArr,4,Local_LoopCounter1);
          }break;
    	  }
  	  }
  	  if((Local_u8NumArr[0]==Local_u8PassArr[3])&&(Local_u8NumArr[1]==Local_u8PassArr[2])&&(Local_u8NumArr[2]==Local_u8PassArr[1])&&(Local_u8NumArr[3]==Local_u8PassArr[0]))
  	  {
	    CLCD_voidSendCmd(1);
		CLCD_u8SendString("DCM SW1-");
		CLCD_viodGoToXY(8,0);
		CLCD_u8SendString("STM SW2");
		CLCD_viodGoToXY(0,1);
		CLCD_u8SendString("SERVO M SW3");
  		  while(1)
  		  {
            APPlication(&DCM_Type);
	        ResetSystem();
  		  }
  	  }
  	  else
  	  {
  		  for(Local_u8WrongPass=0;Local_u8WrongPass<2;Local_u8WrongPass++)
  		  {
  			  if((Local_u8NumArr[0]==Local_u8PassArr[3])&&(Local_u8NumArr[1]==Local_u8PassArr[2])&&(Local_u8NumArr[2]==Local_u8PassArr[1])&&(Local_u8NumArr[3]==Local_u8PassArr[0]))
  			  {
  				  break;
  			  }
  			  else
  			  {
  				  Local_u16Temp=0;
	  		      CLCD_voidSendCmd(1);
	  		      CLCD_u8SendString("Enter Password");

  	  		  	  for(Local_LoopCounter1=0;Local_LoopCounter1<4;Local_LoopCounter1++)
  	  		  	  {
  	  		      	CLCD_viodGoToXY(Local_LoopCounter1,1);
  	  		    	  switch(Local_LoopCounter1)
  	  		    	  {
  	  		    	  case 0 :
  	  		    	  {
  	  		    		  EnterPass(Local_u8PassArr,4,Local_LoopCounter1);
                      }break;
  	  		    	  case 1 :
  	  		    	  {
  	  		    		  EnterPass(Local_u8PassArr,4,Local_LoopCounter1);
                      }break;
  	  		    	  case 2 :
  	  		    	  {
  	  		    		  EnterPass(Local_u8PassArr,4,Local_LoopCounter1);
                      }break;
  	  		    	  case 3 :
  	  		    	  {
  	  		    		  EnterPass(Local_u8PassArr,4,Local_LoopCounter1);
                      }break;
  	  		    	  }
  	  		  	  }
  			  }

  		  }
  		if(Local_u8WrongPass!=2)
  		{
	  		    CLCD_voidSendCmd(1);
	  			CLCD_u8SendString("DCM SW1-");
	  			CLCD_viodGoToXY(8,0);
	  			CLCD_u8SendString("STM SW2");
	  			CLCD_viodGoToXY(0,1);
	  			CLCD_u8SendString("SERVO M SW3");
  	  		  while(1)
  	  		  {
  	            APPlication(&DCM_Type);
  	            ResetSystem();
  	  		  }
  		}
  		else
  		{
  			CLCD_voidSendCmd(1);
  			CLCD_u8SendString("Fail Reset the system");
  			while(1)
  			{

  			}
  		}
  	  }

	}
}
void APPlication(DCM_cfg * Copy_DCM_Data)
{
    static uint8 Local_u8SWState=0,Local_u8RunFlag=0;
    uint16 Local_u16Angel=0,Local_u16ADCVal=0,Local_u16MappedVal=0,Local_u16Counter=0;
    Local_u8SWState=KPD_GetPressedKey();
    if(Local_u8SWState==1 && Local_u8RunFlag==0)
    {
    	Local_u8SWState=0xff;
    	CLCD_voidSendCmd(1);
    	CLCD_u8SendString("Conts Sp-SW1");
    	CLCD_viodGoToXY(0,1);
    	CLCD_u8SendString("Contr Sp-SW2");
        Local_u8RunFlag=1;
    	while(Local_u8SWState==0xff)
    	{
    		Local_u8SWState=KPD_GetPressedKey();
        	if(Local_u8SWState==1)
        	{
        		CLCD_voidSendCmd(1);
            	CLCD_u8SendString("Conts Sp-Run");
            	DCM_u8CW(Copy_DCM_Data);
                Local_u8SWState=0xff;
        	}
        	else if(Local_u8SWState==2)
        	{
        		Local_u8SWState=0xff;
        		CLCD_voidSendCmd(1);
        		TIMER0_voidInit();
            	CLCD_u8SendString("Contr Sp-Run");
            	while(Local_u8SWState==0xff)
            	{
                    MotorSpeedControl();
                    Local_u8SWState=KPD_GetPressedKey();
            	}
        	}
    	}
    }
     if(Local_u8SWState==2 && Local_u8RunFlag==0)
    {
    	CLCD_voidSendCmd(1);
    	CLCD_u8SendString("Enter Angel:");
    	Local_u8SWState=0xff;
    	Local_u8RunFlag=1;
    	while(Local_u8SWState!=11)
    	{
    		while(Local_u8SWState==0xff)
    		{
        		Local_u8SWState=KPD_GetPressedKey();

    		}
    		if(Local_u8SWState==10)
    		{
    			Local_u8SWState=0;
    		}
    		else if(Local_u8SWState==11)
    		{
    			break;
    		}
    		CLCD_voidSendNumber(Local_u8SWState);
    		Local_u16Angel=Local_u16Angel*10+Local_u8SWState;
        	Local_u8SWState=0xff;
    	}
    	Local_u8SWState=0xff;
    	CLCD_viodGoToXY(0,1);
    	CLCD_voidSendNumber(Local_u16Angel);
        STM_CW(&Stepper_One,Local_u16Angel);
        while(Local_u8SWState==0xff)
        {
        	Local_u8SWState=KPD_GetPressedKey();
        }
    }
     if(Local_u8SWState==3 && Local_u8RunFlag==0)
    {
    	Local_u8SWState=0xff;
    	CLCD_voidSendCmd(1);
    	CLCD_u8SendString("Angel:");
        TIMER1_voidInit();
        Local_u8RunFlag=1;
    	while(Local_u8SWState==0xff)
    	{
            ADC_u8StartConversionSynch(ADC_SINGLE_ENDED_CH0,&Local_u16ADCVal);
            Local_u16MappedVal=MAP(0,1023,1000,5000,Local_u16ADCVal);
            Local_u16Angel=(uint16)(((sint32)Local_u16MappedVal*45u/1000u)-45u);
            CLCD_viodGoToXY(7,0);
            CLCD_voidSendNumber(Local_u16Angel);
            for(Local_u16Counter=1000;Local_u16Counter<=Local_u16MappedVal;Local_u16Counter++)
            {
                TIMER1_void_Set_CompValue(40000,Local_u16Counter);
                _delay_ms(1);
                Local_u8SWState=KPD_GetPressedKey();
                if(Local_u8SWState==5)
                {
                    break;
                }
            }

    	}

    }
     if(Local_u8SWState==5 && Local_u8RunFlag==1)
    {
    	Local_u8RunFlag=0;
		CLCD_voidSendCmd(1);
	    CLCD_u8SendString("DCM SW1-");
		CLCD_viodGoToXY(8,0);
		CLCD_u8SendString("STM SW2");
		CLCD_viodGoToXY(0,1);
		CLCD_u8SendString("SERVO M SW3");
		PORT_voidInit();
		return;
    }
}
void EnterID(uint8 Copy_NumArr[],uint8 Copy_Size,uint8 Copy_counter)
{
	static uint8 Local_SWNum=0,Local_NotPressed=0;
	Local_NotPressed=0;
	  while(Local_NotPressed!=1)
	  {
          Local_SWNum=KPD_GetPressedKey();
		  if(Local_SWNum==1)
		  {
			  Copy_NumArr[Copy_counter]=1;
			  CLCD_voidSendNumber( Copy_NumArr[Copy_counter]);
			  Local_NotPressed=1;
		  }
		  if(Local_SWNum==2)
		  {
			  Copy_NumArr[Copy_counter]=2;
			  CLCD_voidSendNumber( Copy_NumArr[Copy_counter]);
			  Local_NotPressed=1;
		  }
		  if(Local_SWNum==3)
		  {
			  Copy_NumArr[Copy_counter]=3;
			  CLCD_voidSendNumber( Copy_NumArr[Copy_counter]);
			  Local_NotPressed=1;
		  }
		  if(Local_SWNum==4)
		  {
			  Copy_NumArr[Copy_counter]=4;
			  CLCD_voidSendNumber( Copy_NumArr[Copy_counter]);
			  Local_NotPressed=1;
		  }
	  }
}
void EnterPass(uint8 Copy_PassArr[],uint8 Copy_Size,uint8 Copy_counter)
{
	static uint8 Local_PassNum=0,Local_NotPressed=0;
	Local_NotPressed=0;
	  while(Local_NotPressed!=1)
	  {
          Local_PassNum=KPD_GetPressedKey();
		  if(Local_PassNum==1)
		  {
			  Copy_PassArr[Copy_counter]=1;
			  CLCD_viodGoToXY(Copy_counter,1);
			  CLCD_voidSendData('*');
			  Local_NotPressed=1;
		  }
		  if(Local_PassNum==2)
		  {
			  Copy_PassArr[Copy_counter]=2;
			  CLCD_viodGoToXY(Copy_counter,1);
			  CLCD_voidSendData('*');
			  Local_NotPressed=1;
		  }
		  if(Local_PassNum==3)
		  {
			  Copy_PassArr[Copy_counter]=3;
			  CLCD_viodGoToXY(Copy_counter,1);
			  CLCD_voidSendData('*');
			  Local_NotPressed=1;
		  }
		  if(Local_PassNum==4)
		  {
			  Copy_PassArr[Copy_counter]=4;
			  CLCD_viodGoToXY(Copy_counter,1);
			  CLCD_voidSendData('*');
			  Local_NotPressed=1;

		  }
	  }
}
sint32 MAP(sint32 InputRangeMin,sint32 InputRangeMax,sint32 OutputRangeMin,sint32 OutputRangeMax,sint32 InputValu)
{
	sint32 Local_Output=0;
	Local_Output=((OutputRangeMax-OutputRangeMin)*(InputValu-InputRangeMax))/(InputRangeMin-InputRangeMax);
	return Local_Output;
}
void MotorSpeedControl(void)
{
	static uint8 LOcal_u8MappedVal=0;
	static uint16 Local_u16ADCVal=0;
	ADC_u8StartConversionSynch(ADC_SINGLE_ENDED_CH0,&Local_u16ADCVal);
    LOcal_u8MappedVal=MAP(0,1023,0,255,Local_u16ADCVal);
    TIMER0_void_Set_CompValue(LOcal_u8MappedVal);
}
void ResetSystem(void)
{
    CLR_BIT(TCCR0,4);
    CLR_BIT(TCCR0,5);
	CLR_BIT(TCCR1A,TCCr1A_COM1A1);
	CLR_BIT(TCCR1A,TCCr1A_COM1A0);
    PORT_voidInit();
	APPlication(DCM_pType);

}
