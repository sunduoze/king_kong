/*
 * app_test_procedure.c
 *
 * Created on: 2018年2月27日
 * Author: Enzo
 */
 
#include "app_test_procedure.h"

//#define DEBUG_MODE
unsigned char CurrentTestBus=0;
unsigned char CurrentTestNum=0;
unsigned char CurrentTestPin=0;

__IO uint32_t EXT_Relay_Last_State = 0;

unsigned char strcompare(char *S1,char *S2,unsigned short n)
{
	unsigned short i;
	for(i=0;i<n;i++)
	{
		if(S1[i]!=S2[i])
			return 0;
	}
	return 1;
}


/**
  * @brief  LAT Station
  * @param  
  * @retval None
  */

#define TASK_LIST_LEN 5 //<255
void EagleBoardSelfCheckTask(uint8_t TaskListNum);
void EagleBoardSelfCheck(void)
{
	static uint16_t TimeBase;
	static uint8_t ButFlag1 = 1, ButFlag2 = 1;
	static uint8_t TaskList;
	while(1)
	{
		if(TimeBase++ > 65530)	TimeBase = 0;
		if(TimeBase % 10 == 0)
		{
				EagleBoardSelfCheckTask(1);
		}
		if(TimeBase % 20 == 0)
		{
			if(!ButFlag1)
			{
				if(TaskList++ > TASK_LIST_LEN)	TaskList = 0;

			}
			if(!ButFlag2)
			{
				if(TaskList-- < 1)	TaskList = TASK_LIST_LEN;
				
			}
		}
		if(TimeBase % 80 == 0)
		{
			Toggle_OUT_CH_All();
			Toggle_Led_All();
		}
		ButFlag1 = Button1();
		ButFlag2 = Button1();
		HAL_Delay(1);	
	}
}

/**
  * @brief  EagleBoardSelfCheckTask 
  * @param  
  * @retval None
  */
void EagleBoardSelfCheckTask(uint8_t TaskListNum)
{
  switch(TaskListNum)
  {
    case 1://PWR0204
    {
				if(UART_RxCallback_Flag == PWR0204_1_Flag)
				{	
						UART_RxCallback_Flag = Clear_Flag;
						UART_Printf(&UPPER_COM_HUART, "PS1:");
						UART_Printf(&UPPER_COM_HUART, (const char *)arrPWR0204_1_Buf);	//Quiescent Current
						UART_Printf(&UPPER_COM_HUART, "\r\n");
						arrPWR0204_1_RX_STA = 0;
				}
				else if(UART_RxCallback_Flag == PWR0204_2_Flag)
				{
						UART_RxCallback_Flag = Clear_Flag;
						UART_Printf(&UPPER_COM_HUART, "PS2:");
						UART_Printf(&UPPER_COM_HUART, (const char *)arrPWR0204_2_Buf);	//Quiescent Current
						UART_Printf(&UPPER_COM_HUART, "\r\n");
						arrPWR0204_2_RX_STA = 0;
				}
				else
				{
						static uint8_t InitFlag;
						if(InitFlag)
						{
							UART_Printf(&PWR0204_1_HUART, "MEAS:CURR:LOW?\r\n");
							UART_Printf(&PWR0204_2_HUART, "MEAS:CURR:LOW?\r\n");
//							HAL_GPIO_TogglePin(LED2_GPIO_Port, LED2_Pin);
						}
						else
						{
							arrUPPER_COM_RX_STA = 0;
//							uint16_t Temp[4];
//							const uint8_t buf[]="01700800009045000004489AB5";//ABDE
//							*Temp =     (*((uint8_t *)buf +  3)<<8)|*((uint8_t *)buf +  4);
//							*(Temp+1) = (*((uint8_t *)buf +  5)<<8)|*((uint8_t *)buf +  6);
//							*(Temp+2) = (*((uint8_t *)buf +  7)<<8)|*((uint8_t *)buf +  8);
//							*(Temp+3) = (*((uint8_t *)buf +  9)<<8)|*((uint8_t *)buf +  10);
////							for(int i = 0; i < 4;i++)//每16位数据相互颠倒
////							{
////								UART_Printf(&UPPER_COM_HUART, "0x%x\r\n", *(Temp + i));
////							}				
//							Temp_32_L = (uint32_t) (*Temp)    <<16 | (*(Temp+1));
//							Temp_32_H = (uint32_t) (*(Temp+2))<<16 | (*(Temp+3));
////							UART_Printf(&UPPER_COM_HUART, "0x%x\r\n", Temp_32_L);
////							UART_Printf(&UPPER_COM_HUART, "0x%x\r\n", Temp_32_H);
//							STP16CP05_Multi_IO_OUTPUT(Temp_32_H, Temp_32_L);
//							STP16CP05_Multi_IO_OUTPUT(EXIO_H_36 | EXIO_H_39 | EXIO_H_43, EXIO_L_1 | EXIO_L_13 | EXIO_L_3 | EXIO_L_16 |EXIO_L_7 );//ABDE
							UART_Printf(&PWR0204_1_HUART, "OUTP 1\r\n");
							HAL_Delay(50);
							UART_Printf(&PWR0204_1_HUART, "SOUR:VOLT 3.0\r\n"); //设置输出电压值命令
							HAL_Delay(50);
							UART_Printf(&PWR0204_1_HUART, "SOUR:CURR 0.001\r\n"); //设置保护电流值命令
							
							UART_Printf(&PWR0204_2_HUART, "OUTP 1\r\n");
							HAL_Delay(50);
							UART_Printf(&PWR0204_2_HUART, "SOUR:VOLT 1.8\r\n"); //设置输出电压值命令
							HAL_Delay(50);
							UART_Printf(&PWR0204_2_HUART, "SOUR:CURR 0.001\r\n"); //设置保护电流值命令

							UART_Printf(&UPPER_COM_HUART, "PWR0204 1 & 2 INIT OK\n");
							InitFlag = 1;
							
						}
				}
		}
		default:
		{

		} break;
	}
}



