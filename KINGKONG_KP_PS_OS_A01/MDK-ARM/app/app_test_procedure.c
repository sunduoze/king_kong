/*
 * app_test_procedure.c
 *
 * Created on: 2018Äê2ÔÂ27ÈÕ
 * Author: Enzo
 */
 
#include "app_test_procedure.h"
#include "bsp_kingkong.h"
#include "app_debug.h"
#include "iwdg.h"

osThreadId initTaskHandle;

void InitTask(void const * argument)
{
  uartTaskThreadCreate(osPriorityNormal);//osPriorityBelowNormal
	iwdgTaskThreadCreate(osPriorityNormal);//);
	psTaskThreadCreate(osPriorityNormal);
  for(;;)
  {
    vTaskDelete(initTaskHandle); 
  }
}

/**
  * @brief  Create the UnderpanTask threads
  * @param  None
  * @retval None
  */
void initTaskThreadCreate(osPriority taskPriority)
{
	osThreadDef(initTask, InitTask, taskPriority, 0, 128);
  initTaskHandle = osThreadCreate(osThread(initTask), NULL);
}





