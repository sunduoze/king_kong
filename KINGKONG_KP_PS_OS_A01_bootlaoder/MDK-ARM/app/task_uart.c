/*
 * task_uart.c
 *
 * Created on: 2018年2月27日
 * Author: Enzo
 */
 
#include "task_uart.h"

__IO  uint8_t UART_RxCallback_Flag = Clear_Flag;

//#define	DBG_U2U


/**
  * @brief  Idle Call back
  * @param  UART_HandleTypeDef
  * @retval None
  */
void UART_IdleRxCallback(UART_HandleTypeDef *huart)
{
	if(huart == &UPPER_COM_HUART)
	{
		UART_RxCallback_Flag = UPPER_COM_Flag;
		#ifdef DBG_U2U
		UART_Printf(&UPPER_COM_HUART, "DBG1:arrUPPER_COM_Buf\r\n");
		UART_Printf(&UPPER_COM_HUART, (const char*)arrUPPER_COM_Buf);
		UART_Printf(&UPPER_COM_HUART, "\r\n");
		#endif
	}
  else if(huart == &PWR0204_1_HUART)
  {
		UART_RxCallback_Flag = PWR0204_1_Flag;
		#ifdef DBG_U2U
		UART_Printf(&UPPER_COM_HUART, "DBG2:arrPWR0204_1_Buf\r\n");
		UART_Printf(&UPPER_COM_HUART, (const char*)arrPWR0204_1_Buf);
		UART_Printf(&UPPER_COM_HUART, "\r\n");

		#endif
  }
	else if(huart == &PWR0204_2_HUART)
  {
		
		UART_RxCallback_Flag = PWR0204_2_Flag;
		#ifdef DBG_U2U
//				UART_Printf(&UPPER_COM_HUART, "___________________________________\r\n");
		UART_Printf(&UPPER_COM_HUART, "DBG3:arrPWR0204_2_Buf\r\n");
		UART_Printf(&UPPER_COM_HUART, (const char*)arrPWR0204_2_Buf);
		UART_Printf(&UPPER_COM_HUART, "\r\n");
		#endif
  }
	else if(huart == &DAQ0010_1_HUART)
  {		
		UART_RxCallback_Flag = DAQ0010_1_Flag;
		#ifdef DBG_U2U
		UART_Printf(&UPPER_COM_HUART, "DBG4:arrDAQ0010_1_Buf\r\n");
		UART_Printf(&UPPER_COM_HUART, (const char*)arrDAQ0010_1_Buf);
		UART_Printf(&UPPER_COM_HUART, "\r\n");
		#endif
//    judgementDataHandler();
  }
//	else if(huart == &DAQ3003_1_HUART)// UART5 鸡肋
//  {
//		UART_Printf(&UPPER_COM_HUART, "DBG5:arrDAQ3003_1_Buf\r\n");
//		UART_Printf(&UPPER_COM_HUART, (const char*)arrDAQ3003_1_Buf);
//		UART_Printf(&UPPER_COM_HUART, "\r\n");
//  }  
}

void ReceiveDataHandel(void)
{
	
	if(arrUPPER_COM_RX_STA & 0x8000)
	{
			/*CMD*/
			if(!strncasecmp("Reset", (const char *)arrUPPER_COM_Buf, 5))
			{
				HAL_NVIC_DisableIRQ(TIM4_IRQn);
				HAL_NVIC_DisableIRQ(USART1_IRQn);
				HAL_NVIC_SystemReset();
				arrUPPER_COM_RX_STA = 0;
			}
			else if(!strncasecmp("Help", (const char *)arrUPPER_COM_Buf, 4)) //注意 此操作需要手动重启
			{
				arrUPPER_COM_RX_STA = 0;
				UART_Printf(&UPPER_COM_HUART, "Help me");
			}
			else
			{				
				UART_Printf(&UPPER_COM_HUART,"\r\nCommand Error\r\n");
				arrUPPER_COM_RX_STA = 0;
			}
	}
}
