/*
 * app_debug.c
 *
 * Created on: 2018年2月27日
 * Author: Enzo
 */
 
#include "app_debug.h"

#include "iwdg.h"


#include "SEGGER_RTT.h"
#include "dac.h"
#include "stdint.h"
#include "bsp_delay.h"
#include "bsp_io.h"
#include "bsp_stp16cp05.h"
#include "bsp_uart.h"
#include "bsp_mcp9805.h"
#include "bsp_cat9555_1.h"
#include "bsp_cat9555_2.h"
#include "bsp_ad5683r.h"
#include "app_test_procedure.h"

#include "bsp_kingkong.h"
#include "lib_cali.h"

//osThreadId iwdgTaskHandle;
//osThreadId debugTaskHandle;
//osThreadId psSetTaskHandle;

__IO uint8_t EagleBoardSelfCheckFlag = 0;


void HardWareInit(void)
{
	HAL_UART_All_Init();
	Toggle_Led_All();
//	HAL_IWDG_Refresh(&hiwdg);
	HAL_Delay(200);
//	HAL_IWDG_Refresh(&hiwdg);
//	calibration_init();
//	vol_set((uint8_t *)"12");
	Toggle_Led_All();
	LED1_ON();
	LED2_ON(); 
	UART_Printf(&UPPER_COM_HUART,"\r\nWelcome to use KingKong KP Platform OK !\r\n");
	UART_Printf(&UPPER_COM_HUART,"HW Version:V2.0  FW Version:DEBUG_V0.8  SW Version:V1.0 \r\n");
	UART_Printf(&UPPER_COM_HUART,"@Enzo.sun 20190802\r\n\r\n");
	UART_Printf(&UPPER_COM_HUART,"Debug:80g & 100g \r\n\r\n");
	#ifdef MCP9805
	MCP9805_Init();
	while(MCP9805_Check())
	{
		UART_Printf(&UPPER_COM_HUART,"MCP9805 Temp Sensor Init Error!\r\n");
	}
	UART_Printf(&UPPER_COM_HUART,"MCP9805 Init Temp:%.2f C\r\n", MCP9805_Read_Temperature);
	#endif
	EagleBoardSelfCheckFlag = !Button1();
	if(EagleBoardSelfCheckFlag)
	{
		AD5683R_Write_Voltage(0.6064f);	//OPTO 先修的板子 16.80V	~99.9g
		HAL_Delay(1);
		AD5683R_Write_Voltage(0.6064f);	//OPTO 先修的板子 16.80V	~99.9g
	}
	else
	{
		AD5683R_Write_Voltage(0.661f);	//OPTO 先修的板子 14.33V	~80.5g
		HAL_Delay(1);
		AD5683R_Write_Voltage(0.661f);	//OPTO 先修的板子 14.33V	~80.5g
	}
//	RttInit();
	HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, 2048);	//1.65V DAO=1.38V VOUT = 8V	/*##-1- Set DAC channel1 DHR12RD register ################################################*/
  if(HAL_DAC_Start(&hdac, DAC_CHANNEL_1) != HAL_OK)									/*##-2- Enable DAC Channel1 ################################################*/
  {
    Error_Handler();
  }
	/************************************************************/
	
	internal_dac_vol_set(1.0f);
	PS_ENABLE;
//		HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, 2048);		/*##-1- Set DAC channel1 DHR12RD register ################################################*/

//	AD5683R_Write_Voltage(0.801f);	//8.02V			0.514f //0.801f
//	AD5683R_Write_Voltage(0.65f);	//8.02V		14.88V 	0.514f //0.801f
	
//	AD5683R_Write_Voltage(0.572f);	//O18.36V   退回的电磁铁
	//IA板子	ad5683r_set_volt(0.5364f);	//20.00V		~138g ~136g ~139g


//	ad5683r_set_volt(0.6064f);	//OPTO 先修的板子 16.80V	~99.9g
//Voltage[V]	Force[g]
//14.88	80.21
//16.8	99.41

	
	while (1)
	{
		HAL_GPIO_WritePin(PWR0204_1_EN_GPIO_Port, PWR0204_1_EN_Pin, 1);
		HAL_Delay(100);
		HAL_GPIO_WritePin(PWR0204_1_EN_GPIO_Port, PWR0204_1_EN_Pin, 0);
		HAL_Delay(100);
//		HAL_Delay(800);
//		HAL_IWDG_Refresh(&hiwdg);
		HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
		
	}
	
//	AD5683R_Write_Voltage(0.65f);	//8.02V		14.88V 	0.514f //0.801f
}

 

//#include "task_uart.h"
//void DebugTask(void const * argument)
//{
//  for(;;)
//  {
//		ReceiveDataHandel();
////    vTaskDelete(initTaskHandle);
//  }
//}


//void IwdgTask(void const * argument)
//{
//	HAL_GPIO_TogglePin(LED2_GPIO_Port, LED2_Pin);
//	portTickType xLastWakeTime;
////	xLastWakeTime = osKernelSysTick();
//  xLastWakeTime = xTaskGetTickCount();
//  for(;;)
//  {
//    osDelayUntil(&xLastWakeTime,800);  //		osDelay(1000);  
//		HAL_IWDG_Refresh(&hiwdg);// 40Khz / 16 / 2500 -> 2s
//		HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
////    vTaskDelete(iwdgTaskHandle);
//  }
//}

//void PsSetTask(void const * argument)
//{
//	portTickType xLastWakeTime;
//  xLastWakeTime = xTaskGetTickCount();
//  for(;;)
//  {
//		ReceiveDataHandel();
//		
//		
//  }
//}
///**
//  * @brief  Create the DebugTask threads
//  * @param  None
//  * @retval None
//  */
//void debugTaskThreadCreate(osPriority taskPriority)
//{
//	osThreadDef(debugTask, DebugTask, taskPriority, 0, 64);
//  debugTaskHandle = osThreadCreate(osThread(debugTask), NULL);
//}

///**
//  * @brief  Create the DebugTask threads
//  * @param  None
//  * @retval None
//  */
//void iwdgTaskThreadCreate(osPriority taskPriority)
//{
//	osThreadDef(iwdgTask, IwdgTask, taskPriority, 0, 64);
//  iwdgTaskHandle = osThreadCreate(osThread(iwdgTask), NULL);
//}

///**
//  * @brief  Create the DebugTask threads
//  * @param  None
//  * @retval None
//  */	
//void psSetTaskThreadCreate(osPriority taskPriority)
//{
//	osThreadDef(psSetTask, PsSetTask, taskPriority, 0, 64);
//  psSetTaskHandle = osThreadCreate(osThread(psSetTask), NULL);
//}

















