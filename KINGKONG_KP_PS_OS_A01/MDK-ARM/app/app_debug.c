/*
 * app_debug.c
 *
 * Created on: 2018Äê2ÔÂ27ÈÕ
 * Author: Enzo
 */
 
#include "app_debug.h"

#include <stdint.h>

#include "iwdg.h"
#include "dac.h"

#include "SEGGER_RTT.h"

#include "bsp_delay.h"
#include "bsp_io.h"
#include "bsp_uart.h"
#include "bsp_mcp9805.h"
#include "bsp_ad5683r.h"
#include "bsp_kingkong.h"
#include "bsp_bit_band.h"

#include "app_test_procedure.h"

#include "lib_cali.h"

#include "task_uart.h"


extern calibration cali_g;
__IO uint8_t vout_debug_flag_g;


osThreadId iwdgTaskHandle;
osThreadId uartTaskHandle;
osThreadId psSetTaskHandle;

void uart_task(void const * argument)
{
	portTickType xLastWakeTime;
  xLastWakeTime = xTaskGetTickCount();//	xLastWakeTime = osKernelSysTick();
//	float f = 40.0f;
  for (;;)
  {
//		if (PDin(13))
//		{
//			force_set(&f);
//		}
		receive_data_handel();
		ExtADC_Monitor();
		osDelayUntil(&xLastWakeTime, 1);  //		osDelay(1000);  
  }
}

extern __IO float g_current_zero_drift;
extern float vol_get[ADC_CHANNEL_NUM][SAMPLE_NUM];


void iwdg_task(void const * argument)
{	
	HAL_GPIO_TogglePin(LED2_GPIO_Port, LED2_Pin);
	portTickType xLastWakeTime;
  xLastWakeTime = xTaskGetTickCount();//xLastWakeTime = osKernelSysTick();
	
  for (;;)
  {
		if (!Button1())
		{
			g_current_zero_drift = vol_get[ADC_IOUT_CH][DEFAULT_CHANNEL_DEBUG];
		}
		else
		{
			output_config(PS_EN, 1);
		}
		
		HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
    osDelayUntil(&xLastWakeTime, 500);  //osDelay(1000);  
//		HAL_IWDG_Refresh(&hiwdg);// 40Khz / 16 / 2500 -> 2s
  }
}



void ps_task(void const * argument)
{
	portTickType xLastWakeTime;
  xLastWakeTime = xTaskGetTickCount();
	
  for(;;)
  {
		if (!vout_debug_flag_g)
		{
			ps_handle_fun(&cali_g.force);
		}
		osDelayUntil(&xLastWakeTime, 10);  
  }
}
/**
  * @brief  Create the DebugTask threads
  * @param  None
  * @retval None
  */
void uartTaskThreadCreate(osPriority taskPriority)
{
	osThreadDef(uartTask, uart_task, taskPriority, 0, 256);
  uartTaskHandle = osThreadCreate(osThread(uartTask), NULL);
}

/**
  * @brief  Create the DebugTask threads
  * @param  None
  * @retval None
  */
void iwdgTaskThreadCreate(osPriority taskPriority)
{
	osThreadDef(iwdgTask, iwdg_task, taskPriority, 0, 32);
  iwdgTaskHandle = osThreadCreate(osThread(iwdgTask), NULL);
}

/**
  * @brief  Create the DebugTask threads
  * @param  None
  * @retval None
  */	
void psTaskThreadCreate(osPriority taskPriority)
{
	osThreadDef(psSetTask, ps_task, taskPriority, 0, 256);
  psSetTaskHandle = osThreadCreate(osThread(psSetTask), NULL);
}


