#include "STD_TYPES.h"
#include "defines.h"
#include "BIT_MATH.h"
#include <util/delay.h>

#include "DIO_interface.h"
#include "PORT_interface.h"
#include "ADC_interface.h"
#include "TIMERS_interface.h"
#include "PWM_interface.h"
#include "USART_interface.h"
#include "TWI_interface.h"


#include "EEPROM_interface.h"

uint8 APP_u8EnteryChoice(uint8 Copy_u8Arr[],uint8 Copy_u8Size);
uint8 APP_u8ID_Password_Entering(void);
uint8 APP_u8ID_Password_Check(void);
void APP_voidDisplayChoices(void);
uint8 APP_u8ChoiceChecking(uint8 Copy_u8DataArr[],uint8 Copy_u8Size);
void APP_voidHomeControl(uint8 Copy_u8Choose);
sint32 MAP(sint32 InputRangeMin,sint32 InputRangeMax,sint32 OutputRangeMin,sint32 OutputRangeMax,sint32 InputValu);

void APP_voidTurn_OnLed(void);
void APP_voidTurnOffLed(void);
void APP_voidOpenDoor(void);
void APP_voidCloseDoor(void);
void APP_OpenFan(void);
void APP_CloseFan(void);
void APP_ControlLight(void);
void APP_ControlMotorSpeed(void);

uint8 APP_RecievedDataArr[27]={0};
void main(void)
{
	_delay_ms(100);

	uint8 Local_u8EntryChooseFlag = 0;
    uint8 Local_u8Reciving_Finish=0;

	PORT_voidInit();
	TWI_voidMasterInit(10);
	UART_voidInit();

	UART_u8SendString("Welcome to semi smart home");
    UART_u8SendString("1-Log in");
    UART_u8SendString("2-Register");

	while(1)
	{
		while(Local_u8Reciving_Finish == 0)
		{
			   UART_ReceiveBufferFlush();
			   Local_u8Reciving_Finish = UART_voidRecieveBufferSynch(APP_RecievedDataArr,27);
		       if(APP_RecievedDataArr[0] == 0)
		       {
		    	   Local_u8Reciving_Finish = 0;
		       }
		}
	   Local_u8Reciving_Finish = 0;
       Local_u8EntryChooseFlag = APP_u8EnteryChoice(APP_RecievedDataArr,27);
		switch (Local_u8EntryChooseFlag)
		{
		case 0:
		{
			UART_u8SendString("Wrong choice");
		}break;
		case 1:
		{
			uint8 Local_u8LoginFlag = 0;
			while (Local_u8LoginFlag == 0)
			{
				Local_u8LoginFlag = APP_u8ID_Password_Check();
			}
			if (Local_u8LoginFlag == 1)
			{
				UART_u8SendString("Successful log in");
				APP_voidDisplayChoices();
				while(1)
				{
					UART_ReceiveBufferFlush();
					while (Local_u8Reciving_Finish == 0)
					{
						Local_u8Reciving_Finish = UART_voidRecieveBufferSynch(APP_RecievedDataArr, 27);
						if (APP_RecievedDataArr[0] == 0)
						{
							Local_u8Reciving_Finish = 0;
						}
					}
					if (Local_u8Reciving_Finish == 1)
					{
						uint8 Local_u8Choose = 0;
						Local_u8Choose = APP_u8ChoiceChecking(APP_RecievedDataArr,27);
						APP_voidHomeControl(Local_u8Choose);
						Local_u8Reciving_Finish = 0;
						if(Local_u8Choose == 10)
						{
							break;
						}
						if(Local_u8Choose == 0)
						{
							UART_u8SendString("Wrong choice");
						}
					}
				}
			}
			else
			{
				UART_u8SendString("Wrong password");
			}
		}break;
		case 2:
		{
			uint8 Local_u8RegisterFlag = 0;
			while (Local_u8RegisterFlag == 0)
			{
				Local_u8RegisterFlag = APP_u8ID_Password_Entering();
			}
			if (Local_u8RegisterFlag == 1) {
				UART_u8SendString("Successful Register");
			}
		}break;
		}
	}
}
uint8 APP_u8EnteryChoice(uint8 Copy_u8Arr[],uint8 Copy_u8Size)
{
	uint8 Local_u8Flag=0,Local_u8Counter=0;
	char *Login="log in";
	char *Register="register";
    while(Login[Local_u8Counter] != '\0')
    {
    	if(Copy_u8Arr[Local_u8Counter] == Login[Local_u8Counter])
    	{
    		Local_u8Flag = 1;
    	}
    	else
    	{
    		Local_u8Flag = 0;
    		break;
    	}
    	Local_u8Counter++;
    }
    if(Local_u8Flag == 0)
    {
    	Local_u8Counter = 0;
        while(Register[Local_u8Counter] != '\0')
        {
        	if(Copy_u8Arr[Local_u8Counter] == Register[Local_u8Counter])
        	{
        		Local_u8Flag = 2;
        	}
        	else
        	{
        		Local_u8Flag = 0;
        		break;
        	}
        	Local_u8Counter++;
        }
    }
    for(Local_u8Counter=0;Local_u8Counter<Copy_u8Size;Local_u8Counter++)
    {
    	Copy_u8Arr[Local_u8Counter] = 0;
    }
    return Local_u8Flag;
}
uint8 APP_u8ID_Password_Entering(void)
{

	uint8 Local_u8Riciving_finish=0;
	uint8 Local_u8Counter=0;
	uint8 Local_u8Pass=0;
	uint16 Local_u8ID=0;
	uint8 Local_u8ID_Arr[4] = {0};
	uint8 Local_u8Pass_Arr[4] = {0};
	UART_u8SendString("Please enter new ID :");
	UART_ReceiveBufferFlush();
	while(Local_u8Riciving_finish == 0)
	{
		Local_u8Riciving_finish = UART_voidRecieveBufferSynch(Local_u8ID_Arr,3);
        if(Local_u8ID_Arr[0] == 0)
        {

        	Local_u8Riciving_finish = 0;
        }
	}
	Local_u8Riciving_finish = 0;
	UART_u8SendString("Please enter new Password :");
	UART_ReceiveBufferFlush();
	while(Local_u8Riciving_finish == 0)
	{
		Local_u8Riciving_finish = UART_voidRecieveBufferSynch(Local_u8Pass_Arr,3);
        if(Local_u8Pass_Arr[0] == 0)
        {
        	Local_u8Riciving_finish = 0;
        }
	}
	for(Local_u8Counter = 0;Local_u8Counter < 3;Local_u8Counter++)
	{
		Local_u8ID_Arr[Local_u8Counter] = Local_u8ID_Arr[Local_u8Counter] - '0';
		Local_u8Pass_Arr[Local_u8Counter] = Local_u8Pass_Arr[Local_u8Counter] - '0';
		Local_u8ID = Local_u8ID*10 + (uint16)Local_u8ID_Arr[Local_u8Counter];
		Local_u8Pass = Local_u8Pass*10 + Local_u8Pass_Arr[Local_u8Counter];
	}
	EEPROM_voidWriteDataByte(Local_u8ID,Local_u8Pass);
	return 1u;
}
uint8 APP_u8ID_Password_Check(void)
{
	uint8 Local_u8Riciving_finish=0;
	uint8 Local_u8Check=0;
	uint8 Local_u8Counter=0;
	uint8 Local_u8Pass=0;
	uint16 Local_u8ID=0;
	uint8 Local_u8SavedPass=0;
	uint8 Local_u8ID_Arr[4] = {0};
	uint8 Local_u8Pass_Arr[4] = {0};
	UART_u8SendString("Please enter your ID :");
	UART_ReceiveBufferFlush();
	while(Local_u8Riciving_finish == 0)
	{
		Local_u8Riciving_finish = UART_voidRecieveBufferSynch(Local_u8ID_Arr,3);
        if(Local_u8ID_Arr[0] == 0)
        {
        	Local_u8Riciving_finish = 0;
        }
	}
	Local_u8Riciving_finish = 0;
	UART_u8SendString("Please enter your Password :");
	UART_ReceiveBufferFlush();
	while(Local_u8Riciving_finish == 0)
	{
		Local_u8Riciving_finish = UART_voidRecieveBufferSynch(Local_u8Pass_Arr,3);
        if(Local_u8Pass_Arr[0] == 0)
        {
        	Local_u8Riciving_finish = 0;
        }
	}
	for(Local_u8Counter = 0;Local_u8Counter < 3;Local_u8Counter++)
	{
		Local_u8ID_Arr[Local_u8Counter] = Local_u8ID_Arr[Local_u8Counter] - '0';
		Local_u8Pass_Arr[Local_u8Counter] = Local_u8Pass_Arr[Local_u8Counter] - '0';
		Local_u8ID = Local_u8ID*10 + (uint16)Local_u8ID_Arr[Local_u8Counter];
		Local_u8Pass = Local_u8Pass*10 + Local_u8Pass_Arr[Local_u8Counter];
	}
	EEPROM_voidReadDataByte(Local_u8ID,&Local_u8SavedPass);
	if(Local_u8Pass == Local_u8SavedPass)
	{
		Local_u8Check = 1;
	}
	else
	{
		Local_u8Check = 2;
	}

	return Local_u8Check;
}
void APP_voidDisplayChoices(void)
{
	UART_u8SendString("1");
	UART_u8SendString("2");
	UART_u8SendString("3");
	UART_u8SendString("4");
	UART_u8SendString("5");
	UART_u8SendString("6");
	UART_u8SendString("7");
	UART_u8SendString("8");
	UART_u8SendString("9");
	UART_u8SendString("10");
}
uint8 APP_u8ChoiceChecking(uint8 Copy_u8DataArr[],uint8 Copy_u8Size)
{
	uint8 Local_ChooseFlag = 0,Local_u8Counter=0;
	static uint8 Choose_1[] = {"turn on light"};
	static uint8 Choose_2[] = {"turn off light"};
	static uint8 Choose_3[] = {"control light"};
	static uint8 Choose_4[] = {"open the door"};
	static uint8 Choose_5[] = {"close the door"};
	static uint8 Choose_6[] = {"open the motor"};
	static uint8 Choose_7[] = {"close the motor"};
	static uint8 Choose_8[] = {"control motor speed with hand"};
	static uint8 Choose_9[] = {"finish"};
	static uint8 Choose_10[] = {"back to main menu"};
	while(Choose_1[Local_u8Counter] != '\0')
	{
        if(Copy_u8DataArr[Local_u8Counter] == Choose_1[Local_u8Counter])
        {
        	Local_ChooseFlag = 1;
        }
        else
        {
        	Local_ChooseFlag = 0;
        	break;
        }
        Local_u8Counter++;
	}
	if(Local_ChooseFlag == 0)
	{
		Local_u8Counter = 0;
		while(Choose_2[Local_u8Counter] != '\0')
		{
	        if(Copy_u8DataArr[Local_u8Counter] == Choose_2[Local_u8Counter])
	        {
	        	Local_ChooseFlag = 2;
	        }
	        else
	        {
	        	Local_ChooseFlag = 0;
	        	break;
	        }
	        Local_u8Counter++;
		}
	}
	if(Local_ChooseFlag == 0)
	{
		Local_u8Counter = 0;
		while(Choose_3[Local_u8Counter] != '\0')
		{
	        if(Copy_u8DataArr[Local_u8Counter] == Choose_3[Local_u8Counter])
	        {
	        	Local_ChooseFlag = 3;
	        }
	        else
	        {
	        	Local_ChooseFlag = 0;
	        	break;
	        }
	        Local_u8Counter++;
		}
	}
	if(Local_ChooseFlag == 0)
	{
		Local_u8Counter = 0;
		while(Choose_4[Local_u8Counter] != '\0')
		{
	        if(Copy_u8DataArr[Local_u8Counter] == Choose_4[Local_u8Counter])
	        {
	        	Local_ChooseFlag = 4;
	        }
	        else
	        {
	        	Local_ChooseFlag = 0;
	        	break;
	        }
	        Local_u8Counter++;
		}
	}
	if(Local_ChooseFlag == 0)
	{
		Local_u8Counter = 0;
		while(Choose_5[Local_u8Counter] != '\0')
		{
	        if(Copy_u8DataArr[Local_u8Counter] == Choose_5[Local_u8Counter])
	        {
	        	Local_ChooseFlag = 5;
	        }
	        else
	        {
	        	Local_ChooseFlag = 0;
	        	break;
	        }
	        Local_u8Counter++;
		}
	}
	if(Local_ChooseFlag == 0)
	{
		Local_u8Counter = 0;
		while(Choose_6[Local_u8Counter] != '\0')
		{
	        if(Copy_u8DataArr[Local_u8Counter] == Choose_6[Local_u8Counter])
	        {
	        	Local_ChooseFlag = 6;
	        }
	        else
	        {
	        	Local_ChooseFlag = 0;
	        	break;
	        }
	        Local_u8Counter++;
		}
	}
	if(Local_ChooseFlag == 0)
	{
		Local_u8Counter = 0;
		while(Choose_7[Local_u8Counter] != '\0')
		{
	        if(Copy_u8DataArr[Local_u8Counter] == Choose_7[Local_u8Counter])
	        {
	        	Local_ChooseFlag = 7;
	        }
	        else
	        {
	        	Local_ChooseFlag = 0;
	        	break;
	        }
	        Local_u8Counter++;
		}
	}
	if(Local_ChooseFlag == 0)
	{
		Local_u8Counter = 0;
		while(Choose_8[Local_u8Counter] != '\0')
		{
	        if(Copy_u8DataArr[Local_u8Counter] == Choose_8[Local_u8Counter])
	        {
	        	Local_ChooseFlag = 8;
	        }
	        else
	        {
	        	Local_ChooseFlag = 0;
	        	break;
	        }
	        Local_u8Counter++;
		}
	}
	if(Local_ChooseFlag == 0)
	{
		Local_u8Counter = 0;
		while(Choose_9[Local_u8Counter] != '\0')
		{
	        if(Copy_u8DataArr[Local_u8Counter] == Choose_9[Local_u8Counter])
	        {
	        	Local_ChooseFlag = 9;
	        }
	        else
	        {
	        	Local_ChooseFlag = 0;
	        	break;
	        }
	        Local_u8Counter++;
		}
	}
	if(Local_ChooseFlag == 0)
	{
		Local_u8Counter = 0;
		while(Choose_10[Local_u8Counter] != '\0')
		{
	        if(Copy_u8DataArr[Local_u8Counter] == Choose_10[Local_u8Counter])
	        {
	        	Local_ChooseFlag = 10;
	        }
	        else
	        {
	        	Local_ChooseFlag = 0;
	        	break;
	        }
	        Local_u8Counter++;
		}
	}
	for(Local_u8Counter = 0;Local_u8Counter <Copy_u8Size;Local_u8Counter++)
	{
		Copy_u8DataArr[Local_u8Counter] = 0;
	}
	return Local_ChooseFlag;
}
void APP_voidHomeControl(uint8 Copy_u8Choose)
{
	switch(Copy_u8Choose)
	{
	case 1 : APP_voidTurn_OnLed();break;
	case 2 : APP_voidTurnOffLed();break;
	case 3 : APP_ControlLight();break;
	case 4 : APP_voidOpenDoor();break;
	case 5 : APP_voidCloseDoor();break;
	case 6 : APP_OpenFan();break;
	case 7 : APP_CloseFan();break;
	case 8 :APP_ControlMotorSpeed();break;
	}
}
void APP_voidTurn_OnLed(void)
{
	DIO_u8SetPinValue(DIO_u8PORTA,DIO_u8PIN1,DIO_u8PIN_HIGH);
	DIO_u8SetPinValue(DIO_u8PORTA,DIO_u8PIN2,DIO_u8PIN_HIGH);
	DIO_u8SetPinValue(DIO_u8PORTA,DIO_u8PIN3,DIO_u8PIN_HIGH);
	DIO_u8SetPinValue(DIO_u8PORTA,DIO_u8PIN4,DIO_u8PIN_HIGH);
	DIO_u8SetPinValue(DIO_u8PORTA,DIO_u8PIN5,DIO_u8PIN_HIGH);
	DIO_u8SetPinValue(DIO_u8PORTA,DIO_u8PIN6,DIO_u8PIN_HIGH);
}
void APP_voidTurnOffLed(void)
{
	DIO_u8SetPinValue(DIO_u8PORTA,DIO_u8PIN1,DIO_u8PIN_LOW);
	DIO_u8SetPinValue(DIO_u8PORTA,DIO_u8PIN2,DIO_u8PIN_LOW);
	DIO_u8SetPinValue(DIO_u8PORTA,DIO_u8PIN3,DIO_u8PIN_LOW);
	DIO_u8SetPinValue(DIO_u8PORTA,DIO_u8PIN4,DIO_u8PIN_LOW);
	DIO_u8SetPinValue(DIO_u8PORTA,DIO_u8PIN5,DIO_u8PIN_LOW);
	DIO_u8SetPinValue(DIO_u8PORTA,DIO_u8PIN6,DIO_u8PIN_LOW);
}
void APP_voidOpenDoor(void)
{
	uint8 Local_u8Counter = 0;
	for(Local_u8Counter = 2;Local_u8Counter<13;Local_u8Counter++)
	{
	    PWM_voidSetFrequency_SetDutyCycle(50,Local_u8Counter);
	}
}
void APP_voidCloseDoor(void)
{
	uint8 Local_u8Counter = 0;
	for(Local_u8Counter = 12;Local_u8Counter>1;Local_u8Counter--)
	{
	    PWM_voidSetFrequency_SetDutyCycle(50,Local_u8Counter);
	}
}
void APP_OpenFan(void)
{
	DIO_u8SetPinValue(DIO_u8PORTD,DIO_u8PIN7,DIO_u8PIN_HIGH);
}
void APP_CloseFan(void)
{
	DIO_u8SetPinValue(DIO_u8PORTD,DIO_u8PIN7,DIO_u8PIN_LOW);
	TIMER2_voidSet_FastPwmMode(NORMAL_PWM);
}
void APP_ControlLight(void)
{
    uint16 Local_u16ADCResult = 0;
    uint8  Local_u8Choose=0,Local_u8Reciving_Finish = 0;

    ADC_voidInit();
    while(Local_u8Choose != 9)
    {
		Local_u8Reciving_Finish = UART_voidRecieveBufferSynch(APP_RecievedDataArr,27);
		Local_u8Choose = APP_u8ChoiceChecking(APP_RecievedDataArr,27);
        ADC_u8StartConversionSynch(ADC_SINGLE_ENDED_CH0,&Local_u16ADCResult);
        if(Local_u16ADCResult <= 110)
        {
        	DIO_u8SetPinValue(DIO_u8PORTA,DIO_u8PIN1,DIO_u8PIN_HIGH);
        	DIO_u8SetPinValue(DIO_u8PORTA,DIO_u8PIN2,DIO_u8PIN_HIGH);
        	DIO_u8SetPinValue(DIO_u8PORTA,DIO_u8PIN3,DIO_u8PIN_HIGH);
        	DIO_u8SetPinValue(DIO_u8PORTA,DIO_u8PIN4,DIO_u8PIN_HIGH);
        	DIO_u8SetPinValue(DIO_u8PORTA,DIO_u8PIN5,DIO_u8PIN_HIGH);
        	DIO_u8SetPinValue(DIO_u8PORTA,DIO_u8PIN6,DIO_u8PIN_HIGH);
        }
        else if (Local_u16ADCResult > 110 && Local_u16ADCResult <= 115)
        {
        	DIO_u8SetPinValue(DIO_u8PORTA,DIO_u8PIN1,DIO_u8PIN_HIGH);
        	DIO_u8SetPinValue(DIO_u8PORTA,DIO_u8PIN2,DIO_u8PIN_HIGH);
        	DIO_u8SetPinValue(DIO_u8PORTA,DIO_u8PIN3,DIO_u8PIN_HIGH);
        	DIO_u8SetPinValue(DIO_u8PORTA,DIO_u8PIN4,DIO_u8PIN_HIGH);
        	DIO_u8SetPinValue(DIO_u8PORTA,DIO_u8PIN5,DIO_u8PIN_LOW);
        	DIO_u8SetPinValue(DIO_u8PORTA,DIO_u8PIN6,DIO_u8PIN_LOW);
        }
        else if (Local_u16ADCResult >115 && Local_u16ADCResult <= 125)
        {
        	DIO_u8SetPinValue(DIO_u8PORTA,DIO_u8PIN1,DIO_u8PIN_HIGH);
        	DIO_u8SetPinValue(DIO_u8PORTA,DIO_u8PIN2,DIO_u8PIN_HIGH);
        	DIO_u8SetPinValue(DIO_u8PORTA,DIO_u8PIN3,DIO_u8PIN_LOW);
        	DIO_u8SetPinValue(DIO_u8PORTA,DIO_u8PIN4,DIO_u8PIN_LOW);
        	DIO_u8SetPinValue(DIO_u8PORTA,DIO_u8PIN5,DIO_u8PIN_LOW);
        	DIO_u8SetPinValue(DIO_u8PORTA,DIO_u8PIN6,DIO_u8PIN_LOW);
        }
        else
        {
        	DIO_u8SetPinValue(DIO_u8PORTA,DIO_u8PIN1,DIO_u8PIN_LOW);
        	DIO_u8SetPinValue(DIO_u8PORTA,DIO_u8PIN2,DIO_u8PIN_LOW);
        	DIO_u8SetPinValue(DIO_u8PORTA,DIO_u8PIN3,DIO_u8PIN_LOW);
        	DIO_u8SetPinValue(DIO_u8PORTA,DIO_u8PIN4,DIO_u8PIN_LOW);
        	DIO_u8SetPinValue(DIO_u8PORTA,DIO_u8PIN5,DIO_u8PIN_LOW);
        	DIO_u8SetPinValue(DIO_u8PORTA,DIO_u8PIN6,DIO_u8PIN_LOW);
        }
    }

}
void APP_ControlMotorSpeed(void)
{
	static uint16 Local_u16Diastance=0;
    static uint32 Local_u32OnTime=0;
    static uint32 Local_u32PeriodTime=0;
    uint8 Local_u8Choose=0,Local_u8Reciving_Finish = 0;
	TIMER0_2_Cfg_t Timer2;
	TIMER0_2_Cfg_t Timer0;
	Timer2.WFG_MODE = FAST_PWM;
	Timer2.FASTPWM_MODE = SET_TOP_CLR_COMP;
	Timer0.WFG_MODE = FAST_PWM;
	Timer0.FASTPWM_MODE = SET_TOP_CLR_COMP;
	TIMER2_u8Init(&Timer2);
	TIMER0_u8Init(&Timer0);
	TIMER0_void_Set_CompValue(63);
    while(Local_u8Choose != 9)
    {
	    Local_u8Reciving_Finish = UART_voidRecieveBufferSynch(APP_RecievedDataArr,27);
		Local_u8Choose = APP_u8ChoiceChecking(APP_RecievedDataArr,27);
    	PWM_u8Measure_Frequency_DutyCycle(&Local_u32OnTime,&Local_u32PeriodTime);
        Local_u16Diastance = (uint16)(340u * Local_u32OnTime / 200u);
        if( Local_u16Diastance >= 1000 && Local_u16Diastance <2000)
        {
        	TIMER2_void_Set_CompValue(63);
        }
        else if (Local_u16Diastance < 1000 && Local_u16Diastance >= 500)
        {
        	TIMER2_void_Set_CompValue(125);
        }
        else if (Local_u16Diastance <500 )
        {
        	TIMER2_void_Set_CompValue(200);
        }
    }
}
sint32 MAP(sint32 InputRangeMin,sint32 InputRangeMax,sint32 OutputRangeMin,sint32 OutputRangeMax,sint32 InputValu)
{
	sint32 Local_Output=0;
	Local_Output=((OutputRangeMax-OutputRangeMin)*(InputValu-InputRangeMax))/(InputRangeMin-InputRangeMax);
	return Local_Output;
}
