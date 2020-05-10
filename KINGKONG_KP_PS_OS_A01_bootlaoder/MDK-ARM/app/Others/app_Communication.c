/*
 * app_Communication.c
 *
 * Created on: 2017年11月14日
 * Author: Enzo
 */
 
#include "app_Communication.h"
#include "app_KeyStroke.h"
#include "app_MotionControl.h"
#include "app_storage.h"
#include "stm32f1xx_hal.h"
#include "app_main.h"
#include "usart.h"
#include "string.h"
#include "lib_malloc.h"
#include "stm_flash.h"
#include "bsp_delay.h"
#include "bsp_StepMotor.h"




KeyBoard CurrentBoard;
__IO uint16_t TimeRise = 88, TimeFall = 88;
__IO uint16_t KeyStrokeNum = 20;

/*
Command List:Header

Cmd1： Project Information:（包含有项目名称10B、打键方式1B、键盘标准1B） 12 Byte
PrjI`
Cmd2： Original Point Coordinate Information:Original Point Coordinate(8 Byte)
OrgP`
Cmd3： Button Coordinate Information:The Member[ButtonPoint] of ButtonInfo (8 * BUTTON_NUM ByteByte)
BtnC`
Cmd4： Driver I/O Information: (8 * BUTTON_NUM ByteByte)
DrvI`
*/
void ReceiveDataHandel(void)
{
	
	if(USART_RX_STA & 0x8000)
	{
			/*Project Information 10  Byte*/
			if(!strncasecmp("PrjI`", (const char *)USART_RX_BUF, 5))
			{
				uint8_t RcvBuf[10];
				strncpy((char *)RcvBuf, (const char *)USART_RX_BUF + 5, 10);//Offset 5 buf address to save Header
				printf("\r\nPrjI :%s", RcvBuf);
				strncpy((char *)RcvBuf, (const char *)USART_RX_BUF + 5 + 10, 2);
				printf("\r\nBtnTyp:%d Stdx:%d\r\n", (uint8_t)RcvBuf[0] - 48, (uint8_t)RcvBuf[1] - 48);
				USART_RX_STA = 0;
			}
			/*Original Point Coordinate Information:Original Point Coordinate(8 Byte)*/
			else if(!strncasecmp("OrgP`", (const char *)USART_RX_BUF, 5))
			{
				float RcvBuf[2];
				Extract_Parameter(&USART_RX_BUF[5], RcvBuf, 'f', 2 * 2, ',');//Offset 5 buf address to save Header
				printf("X-Axis:%.3f \r\n",RcvBuf[0]);
				printf("Y-Axis:%.3f \r\n",RcvBuf[1]);
				USART_RX_STA = 0;
			}
			/*Button Point Coordinate Information:the Member[ButtonPoint] of ButtonInfo (8 * BUTTON_NUM ByteByte)*/
			else if(!strncasecmp("BtnC`", (const char *)USART_RX_BUF, 5))
			{
				float RcvBuf[USART_REC_LEN];
				Extract_Parameter(&USART_RX_BUF[5], RcvBuf, 'f', BUTTON_NUM * 2, ',');
				for(int i = 0;i < BUTTON_NUM * 2;i++)
				{
					if(i < 84)	//0-83   X-Axis
					{
						printf("[%d] X-Axis:%.3f \r\n",i,RcvBuf[i]);
					}
					else				//84-167 Y-Axis
					{
						printf("[%d] Y-Axis:%.3f \r\n",i - 84,RcvBuf[i]);
					}
					if(i == 83)		printf("\r\n\r\n");
				}
				USART_RX_STA = 0;
			}
			/* Driver I/O Information*/ //This part is agreed
//			else if(!strncasecmp("DrvI`", (const char *)USART_RX_BUF, 5))
//			{
//				uint8_t RcvBuf[USART_REC_LEN];
//				Extract_Parameter(&USART_RX_BUF[5], RcvBuf, 'i', BUTTON_NUM * 2, ',');
//				for(int i = 0;i < BUTTON_NUM * 2;i++)
//				{
//					if(i < 84)	//0-83   X-Axis
//					{
//						printf("[%d] X-Axis:%d \r\n",i,RcvBuf[i]);
//					}
//					else				//84-167 Y-Axis
//					{
//						printf("[%d] Y-Axis:%d \r\n",i - 84,RcvBuf[i]);
//					}
//					if(i == 83)		printf("\r\n\r\n");
//				}
//				USART_RX_STA = 0;
//			}
			
			else if(!strncasecmp("Aging", (const char *)USART_RX_BUF, 5))
			{
				USART_RX_STA = 0;
			}
			else if(!strncasecmp("Reset", (const char *)USART_RX_BUF, 5))
			{
				HAL_NVIC_DisableIRQ(TIM4_IRQn);
				HAL_NVIC_DisableIRQ(USART1_IRQn);
				HAL_NVIC_SystemReset();
				USART_RX_STA = 0;
			}
			else	printf("\r\nCommand Error\r\n");
	}
}

#include "MCP23S17.h"
int32_t tSteps = 32000;
int32_t tAlpha1 = 40;//40;
int32_t tAlpha2 = 40;//40;
float tSetOmega = 1.4;//1.65;//1-> 32 2-> 64   Max 19634  此参数为乘以31.4以后的效果

void ReceiveAndSaveData(KeyBoard *kbTemp)
{
	static uint8_t RcvCompleteFlag, RcvF1,RcvF2,RcvF3;
	
	if(USART_RX_STA & 0x8000)
	{
			/**Storge********************************************************/
			/*Project Information 10  Byte*/
			if(!strncasecmp("PrjI`", (const char *)USART_RX_BUF, 5))
			{
				static uint8_t RcvBuf[12 + 1];
//				strncpy((char *)kbTemp->ProN, (const char *)USART_RX_BUF + 5, 12);//Offset 5 buf address to save Header
				strncpy((char *)RcvBuf, (const char *)USART_RX_BUF + 5, 12);
				strncpy((char *)kbTemp->ProN, (const char *)RcvBuf, 10);
				printf("\r\nBtnTyp:%c Stdx:%c\r\n", (uint8_t)RcvBuf[10], (uint8_t)RcvBuf[11]);
				RcvF1 = 1;
				printf("PrjI OK\r\n");
				USART_RX_STA = 0;
			}
			/*Original Point Coordinate Information:Original Point Coordinate(8 Byte)*/
			else if(!strncasecmp("OrgP`", (const char *)USART_RX_BUF, 5))
			{
				float RcvBuf[2];
				Extract_Parameter(&USART_RX_BUF[5], RcvBuf, 'f', 2 * 2, ',');//Offset 5 buf address to save Header
				kbTemp->OrgP.AxisX = RcvBuf[0];
				kbTemp->OrgP.AxisY = RcvBuf[1];
				if(kbTemp->OrgP.AxisX >= -1000.0 && kbTemp->OrgP.AxisX <= 1000.0 &&
					 kbTemp->OrgP.AxisY >= -1000.0 && kbTemp->OrgP.AxisY <= 1000.0)//RcvBuf >= 0[类型决定] && RcvBuf <= BUTTON_NUM
				{
//				printf("X-Axis:%.3f \r\n",RcvBuf[0]);
//				printf("Y-Axis:%.3f \r\n",RcvBuf[1]);
					printf("OrgP OK\r\n");
					RcvF2 = 1;
				}
				else
				{
					printf("Parameter Err!\r\n");
				}
				USART_RX_STA = 0;
			}
			/*Button Point Coordinate Information:the Member[ButtonPoint] of ButtonInfo (8 * BUTTON_NUM ByteByte)*/
			else if(!strncasecmp("BtnC`", (const char *)USART_RX_BUF, 5))
			{
				float RcvBuf[USART_REC_LEN];
				Extract_Parameter(&USART_RX_BUF[5], RcvBuf, 'f', BUTTON_NUM * 2, ',');
				for(int i = 0;i < BUTTON_NUM * 2;i++)
				{
					if(i < 84)	//0-83   X-Axis
					{
						kbTemp->Btn[i].BtnC.AxisX = RcvBuf[i];
//						printf("[%d] X-Axis:%.3f \r\n",i,RcvBuf[i]);
					}
					else				//84-167 Y-Axis
					{
						kbTemp->Btn[i].BtnC.AxisY = RcvBuf[i];
//						printf("[%d] Y-Axis:%.3f \r\n",i - 84,RcvBuf[i]);
					}
				}
				RcvF3 = 1;
				printf("BtnC OK\r\n");
				USART_RX_STA = 0;
			}

			/*Machine Aging */
			else if(!strncasecmp("Aging", (const char *)USART_RX_BUF, 5))
			{
				MachineAging();
				printf("Aging OK\r\n");
				USART_RX_STA = 0;
			}
			/**END OF Storge*************************************************/
			
			/*Key Stroke Counts*/
			else if(!strncasecmp("KySN`", (const char *)USART_RX_BUF, 5))  
			{
				static uint16_t RcvBuf;
				Extract_Parameter(&USART_RX_BUF[5], &RcvBuf, 'i', 1, ',');
				printf("KySN %d\r\n",RcvBuf);
				if(RcvBuf <= UINT16_MAX )//Maxim is 65535 
				{
					KeyStrokeNum = RcvBuf;
					printf("KySN OK\r\n");
				}
				else
				{
					printf("Parameter Err!\r\n");
				}
				USART_RX_STA = 0;
			}
			/*Raise & fall Time [ms] */
			else if(!strncasecmp("Time`", (const char *)USART_RX_BUF, 5))  
			{
				uint32_t RcvBuf[2];
				Extract_Parameter(&USART_RX_BUF[5], RcvBuf, 'i', 2, ',');
				printf("TimeRise %d TimeFall %d \r\n", RcvBuf[0], RcvBuf[1]);		
				TimeFall = RcvBuf[0];	
				TimeRise = RcvBuf[1];
				printf("Time OK\r\n");
				USART_RX_STA = 0;
			}
			/*Button Num */
			else if(!strncasecmp("Junc`", (const char *)USART_RX_BUF, 5))
			{
				uint16_t RcvBuf = 0;//Non Static
				ButtonPoint Temp;
				Extract_Parameter(&USART_RX_BUF[5], &RcvBuf, 'i', 1, ',');
				printf("J%d\r\n",RcvBuf);
				if(RcvBuf <= BUTTON_NUM )//RcvBuf >= 0[类型决定] && RcvBuf <= BUTTON_NUM
				{
					RcvBuf =RcvBuf - 1;//In Real Machine,J1 is J0 in the code 
					
//					Move to someware
					printf("Real GoTo X_Axis:%f Y_Axis:%f \r\n",CurrentBoard.Btn[RcvBuf].BtnC.AxisX, CurrentBoard.Btn[RcvBuf].BtnC.AxisY);
					printf("GoTo X_Axis:%f Y_Axis:%f \r\n",CurrentBoard.Btn[RcvBuf].BtnC.AxisX + CurrentBoard.OrgP.AxisX, CurrentBoard.Btn[RcvBuf].BtnC.AxisY + CurrentBoard.OrgP.AxisY);
					Temp.AxisX = CurrentBoard.Btn[RcvBuf].BtnC.AxisX / 4.0f;
					Temp.AxisY = CurrentBoard.Btn[RcvBuf].BtnC.AxisY / 4.0f;//实际配置为 8 MicroStep
					CoordinateMoveAbsolute(Temp.AxisX, tAlpha1, tAlpha2,(uint32_t)(tSetOmega*2*3.14*5.0), Temp.AxisY,tAlpha1, tAlpha2,(uint32_t)(tSetOmega*2*3.14*5.0));
					KeyStroke(RcvBuf, TimeRise, TimeFall, KeyStrokeNum);
					printf("OK\r\n");
				}
				else
				{
					printf("Parameter Err!\r\n");
				}
				USART_RX_STA = 0;
			}
			/*Go to Point*/
			else if(!strncasecmp("GoTo`", (const char *)USART_RX_BUF, 5))
			{
				float fRcvBuf[4];
				Extract_Parameter(&USART_RX_BUF[5], &fRcvBuf, 'f',2, ',');//Offset 5 buf address to save Header
				if(EXT_X_STOP_FLAG && EXT_Y_STOP_FLAG)
				{
					CoordinateMoveAbsolute(fRcvBuf[0],tAlpha1, tAlpha2,(uint32_t)(tSetOmega*2*3.14*5.0),fRcvBuf[1],tAlpha1, tAlpha2,(uint32_t)(tSetOmega*2*3.14*5.0));
					printf("GoTo %.2f,%.2f OK\r\n", fRcvBuf[0], fRcvBuf[1]);
				}
				USART_RX_STA = 0;
			}
			/*Go to Original Point*/
			else if(!strncasecmp("Orgin", (const char *)USART_RX_BUF, 5))
			{
				SearchOrg_X_Axis(0,0,0);
				SearchOrg_Y_Axis(0,0,0);
				X_Axis_StepPosition = 0;//保险起见，还是加上 防止BUG
				Y_Axis_StepPosition = 0;
				printf("\r\nGo to orginal point OK\r\n");
				USART_RX_STA = 0;
			}		
			/*Select Project Module & Write to flash*/
			else if(!strncasecmp("SelM`", (const char *)USART_RX_BUF, 5))
			{
				uint16_t RcvBuf = 0;//Non Static
				Extract_Parameter(&USART_RX_BUF[5], &RcvBuf, 'i', 1, ',');
				SelectProjInIndexTableFromPC(RcvBuf);
				printf("\r\n Project Select OK\r\n");
				USART_RX_STA = 0;
			}		
			/*Reset*/
			else if(!strncasecmp("Reset", (const char *)USART_RX_BUF, 5))
			{
				HAL_NVIC_DisableIRQ(TIM4_IRQn);
				HAL_NVIC_DisableIRQ(USART1_IRQn);
				HAL_NVIC_SystemReset();
				USART_RX_STA = 0;
			}
			else
			{
				printf("\r\nCommand Error\r\n");
				USART_RX_STA = 0;	
			}
			
			RcvCompleteFlag = RcvF1 + RcvF2 + RcvF3;
			if(RcvCompleteFlag == 3)
			{	
				RcvF1 = 0;
				RcvF2 = 0;
				RcvF3 = 0;
				RcvCompleteFlag = 0;
				printf("\r\nKeyBoard Info ->->-> Writing !\r\n");
				StorgeNewMod(kbTemp);

				HAL_GPIO_WritePin(LED0_GPIO_Port, LED0_Pin, GPIO_PIN_SET);
				delay_us(200000);	
				HAL_GPIO_WritePin(LED0_GPIO_Port, LED0_Pin, GPIO_PIN_RESET);
				delay_us(50000);
				HAL_GPIO_WritePin(LED0_GPIO_Port, LED0_Pin, GPIO_PIN_SET);
				delay_us(100000);	
				HAL_GPIO_WritePin(LED0_GPIO_Port, LED0_Pin, GPIO_PIN_RESET);
				delay_us(50000);
				HAL_GPIO_WritePin(LED0_GPIO_Port, LED0_Pin, GPIO_PIN_SET);
				delay_us(50000);	
				HAL_GPIO_WritePin(LED0_GPIO_Port, LED0_Pin, GPIO_PIN_RESET);
				delay_us(50000);
				HAL_GPIO_WritePin(LED0_GPIO_Port, LED0_Pin, GPIO_PIN_SET);
				delay_us(200000);	
				HAL_GPIO_WritePin(LED0_GPIO_Port, LED0_Pin, GPIO_PIN_RESET);
				delay_us(50000);
				printf("\r\nKeyBoard Info ->->-> Save Completed !\r\n");
				KeyBoardParameterPrint(kbTemp);
				delay_us(50000);
				
			}
	}
}

