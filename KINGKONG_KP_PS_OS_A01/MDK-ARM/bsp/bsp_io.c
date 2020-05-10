/*
 * bsp_io.c
 *
 * Created on: 2018Äê2ÔÂ27ÈÕ
 * Author: Enzo
 */
#include "bsp_io.h"

/**
  * @brief  Toggle_IO_CH_All_Pin
  * @param  Test
  * @retval None
  */
void Toggle_OUT_CH_All(void)
{
//	HAL_GPIO_TogglePin(OUT_CH1_GPIO_Port, OUT_CH1_Pin);
//	HAL_GPIO_TogglePin(OUT_CH2_GPIO_Port, OUT_CH2_Pin);
//	HAL_GPIO_TogglePin(OUT_CH3_GPIO_Port, OUT_CH3_Pin);
//	HAL_GPIO_TogglePin(OUT_CH4_GPIO_Port, OUT_CH4_Pin);
//	HAL_GPIO_TogglePin(OUT_CH5_GPIO_Port, OUT_CH5_Pin);
//	HAL_GPIO_TogglePin(OUT_CH6_GPIO_Port, OUT_CH6_Pin);
//	HAL_GPIO_TogglePin(OUT_CH7_GPIO_Port, OUT_CH7_Pin);
//	HAL_GPIO_TogglePin(OUT_CH8_GPIO_Port, OUT_CH8_Pin);
}


void toggle_led_all(void)
{
	HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
	HAL_GPIO_TogglePin(LED2_GPIO_Port, LED2_Pin);
	HAL_GPIO_TogglePin(LED3_GPIO_Port, LED3_Pin);
	HAL_Delay(100);
	HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
	HAL_GPIO_TogglePin(LED2_GPIO_Port, LED2_Pin);
	HAL_GPIO_TogglePin(LED3_GPIO_Port, LED3_Pin);
	HAL_Delay(100);
	HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
	HAL_GPIO_TogglePin(LED2_GPIO_Port, LED2_Pin);
	HAL_GPIO_TogglePin(LED3_GPIO_Port, LED3_Pin);
	HAL_Delay(100);
	HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
	HAL_GPIO_TogglePin(LED2_GPIO_Port, LED2_Pin);
	HAL_GPIO_TogglePin(LED3_GPIO_Port, LED3_Pin);
	
}

