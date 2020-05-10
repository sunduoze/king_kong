/*
 * bootloader.c
 *
 * Created on: 2018年7月4日
 * Author: Enzo
 */
 
#include "bootloader.h"
#include "usart.h"
#include "gpio.h"
#include "menu.h"
#include "common.h"

/**
  * @brief  Sets the vector table location and Offset.
  * @param  NVIC_VectTab: specifies if the vector table is in RAM or FLASH memory.
  *   This parameter can be one of the following values:
  *     @arg NVIC_VectTab_RAM
  *     @arg NVIC_VectTab_FLASH
  * @param  Offset: Vector Table base offset field. This value must be a multiple 
  *         of 0x200.
  * @retval None
  */
void NVIC_SetVectorTable(uint32_t NVIC_VectTab, uint32_t Offset)
{ 
  /* Check the parameters */
  assert_param(IS_NVIC_VECTTAB(NVIC_VectTab));
  assert_param(IS_NVIC_OFFSET(Offset));  
   
  SCB->VTOR = NVIC_VectTab | (Offset & (uint32_t)0x1FFFFF80);
}

/**
  * @brief  EagleBoardSelfCheckTask 
  * @param  
  * @retval None
  */

void HAL_BOOT_LOADER(void)
{
#ifndef DEBUG_MODE 
	#ifndef BOOTLOADER
		NVIC_SetVectorTable(NVIC_VectTab_FLASH, APP1_PRE_OFFSET);
	#endif
		
	#ifdef BOOTLOADER
		MX_GPIO_Init();
		MX_USART1_UART_Init();

		if(HAL_GPIO_ReadPin(Button1_GPIO_Port, Button1_Pin) == 0)//IAP Update
		{
			/* Initialise Flash */
			FLASH_If_Init();
			/* Execute the IAP driver in order to reprogram the Flash */
			/* Display main menu */
			Main_Menu();
		}
		else																										//Normal Execute Prog
		{
		 /* Test if user code is programmed starting from address "APPLICATION_ADDRESS" */
			if (((*(__IO uint32_t*)APPLICATION_ADDRESS) & 0x2FFE0000 ) == 0x20000000)
			{
	//			Serial_PutString("\n\r执行用户程序-ing\n\r");
				/* 跳转到用户程序 */
				JumpAddress = *(__IO uint32_t*) (APPLICATION_ADDRESS + 4);
				JumpToApplication = (pFunction) JumpAddress;
				/* 初始化用户堆栈指针 */
				__set_MSP(*(__IO uint32_t*) APPLICATION_ADDRESS);
				JumpToApplication();
			}
			else
			{
				Serial_PutString("\n\rno user app\n\r");
			}
		}
		while(1)
		{
			HAL_GPIO_TogglePin(LED2_GPIO_Port, LED2_Pin);
			HAL_Delay(100);
			HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
			HAL_Delay(100);

		}
		
	#endif
#endif
}

  
  



