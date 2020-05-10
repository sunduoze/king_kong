/*
 * app_test_procedure.c
 *
 * Created on: 2018Äê2ÔÂ27ÈÕ
 * Author: Enzo
 */
 
#include "app_test_procedure.h"
#include "bsp_ad5683r.h"
#include "app_debug.h"
#include "iwdg.h"

osThreadId initTaskHandle;

void InitTask(void const * argument)
{
	HardWareInit();
//  debugTaskThreadCreate(osPriorityBelowNormal);
	iwdgTaskThreadCreate(osPriorityNormal);//osPriorityBelowNormal);
	psSetTaskThreadCreate(osPriorityHigh);
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
	osThreadDef(initTask, InitTask, taskPriority, 0, 256);
  initTaskHandle = osThreadCreate(osThread(initTask), NULL);
}





