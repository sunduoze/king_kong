/**
  ******************************************************************************
  * @file    IAP_Main/Src/menu.c 
  * @author  MCD Application Team
  * @version 1.0.0
  * @date    8-April-2015
  * @brief   This file provides the software which contains the main menu routine.
  *          The main menu gives the options of:
  *             - downloading a new binary file, 
  *             - uploading internal flash memory,
  *             - executing the binary file already loaded 
  *             - configuring the write protection of the Flash sectors where the 
  *               user loads his binary file.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2015 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */ 

/** @addtogroup STM32F1xx_IAP
  * @{
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "common.h"
#include "flash_if.h"
#include "menu.h"
#include "ymodem.h"

#include "usart.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
pFunction JumpToApplication;
uint32_t JumpAddress;
uint32_t FlashProtection = 0;
uint8_t aFileName[FILE_NAME_LENGTH];

/* Private function prototypes -----------------------------------------------*/
void SerialDownload(void);
void SerialUpload(void);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Download a file via serial port
  * @param  None
  * @retval None
  */
void SerialDownload(void)
{
  uint8_t number[11] = {0};
  uint32_t size = 0;
  COM_StatusTypeDef result;

  Serial_PutString("APP1升级中，请稍后(按下'a'终止)\n\r");
  result = Ymodem_Receive( &size );
  if (result == COM_OK)
  {
    Serial_PutString("\n\n\r编程完成!\n\r--\r\n 名称: ");
    Serial_PutString(aFileName);
    Int2Str(number, size);
    Serial_PutString("\n\r大小: ");
    Serial_PutString(number);
    Serial_PutString(" 字节\r\n");
//    Serial_PutString("-------------------\n");
  }
  else if (result == COM_LIMIT)
  {
    Serial_PutString("\n\n\r镜像文件超过存储空间!\n\r");
  }
  else if (result == COM_DATA)
  {
    Serial_PutString("\n\n\r验证失败!\n\r");
  }
  else if (result == COM_ABORT)
  {
    Serial_PutString("\r\n\n被用户终止.\n\r");
  }
  else
  {
    Serial_PutString("\n\r无法接受文件!\n\r");
  }
}

/**
  * @brief  Upload a file via serial port.
  * @param  None
  * @retval None
  */
void SerialUpload(void)
{
  uint8_t status = 0;

  Serial_PutString("\n\n\r选择接受文件\n\r");

  HAL_UART_Receive(&huart1, &status, 1, RX_TIMEOUT);
  if ( status == CRC16)
  {
    /* Transmit the flash image through ymodem protocol */
    status = Ymodem_Transmit((uint8_t*)APPLICATION_ADDRESS, (const uint8_t*)"UploadedFlashImage.bin", USER_FLASH_SIZE);

    if (status != 0)
    {
      Serial_PutString("\n\r传输文件时出错\n\r");
    }
    else
    {
      Serial_PutString("\n\r文件上传成功！\n\r");
    }
  }
}

/**
  * @brief  Display the Main Menu on HyperTerminal
  * @param  None
  * @retval None
  */
void Main_Menu(void)
{
  uint8_t key = 0;

//  Serial_PutString("\r\n======================================================================");
//  Serial_PutString("\r\n=              (C) COPYRIGHT 2015 STMicroelectronics                 =");
//  Serial_PutString("\r\n=                                                                    =");
//  Serial_PutString("\r\n=  STM32F1xx In-Application Programming Application  (Version 1.0.0) =");
//  Serial_PutString("\r\n=                                                                    =");
//  Serial_PutString("\r\n=                                   By MCD Application Team          =");
//	Serial_PutString("\r\n=                                   Porting By Enzo.sun              =");
//  Serial_PutString("\r\n======================================================================");
//  Serial_PutString("\r\n\r\n");
	
  Serial_PutString("\r\n= UART 在应用编程模式=");
	Serial_PutString("\r\n= Porting By Enzo.sun=");
//  Serial_PutString("\r\n\r\n");

  /* Test if any sector of Flash memory where user application will be loaded is write protected */
  FlashProtection = FLASH_If_GetWriteProtectionStatus();

  while (1)
  {

    Serial_PutString("\r\n======== 主菜单 ======= \r\n\n");
    Serial_PutString("  1 ->下载镜像到内部FLASH - 1\r\n");
    Serial_PutString("  2 ->从内部FLASH上传镜像 - 2\r\n");
    Serial_PutString("  3 ->执行加载的应用程序  - 3\r\n");


    if(FlashProtection != FLASHIF_PROTECTION_NONE)
    {
      Serial_PutString("  4 ->失能写保护         - 4\r\n");
    }
    else
    {
      Serial_PutString("  4 ->使能写保护          - 4\r\n");
    }
//    Serial_PutString("==========================\r\n");

    /* Clean the input path */
    __HAL_UART_FLUSH_DRREGISTER(&huart1);
	
    /* Receive key */
    HAL_UART_Receive(&huart1, &key, 1, RX_TIMEOUT);

    switch (key)
    {
    case '1' :
      /* Download user application in the Flash */
      SerialDownload();
      break;
    case '2' :
      /* Upload user application from the Flash */
			Serial_PutString("暂时不支持此功能...\r\n\n");
      //SerialUpload();
      break;
    case '3' :
      Serial_PutString("启动程序执行...\r\n\n");
      /* execute the new program */
      JumpAddress = *(__IO uint32_t*) (APPLICATION_ADDRESS + 4);
      /* Jump to user application */
      JumpToApplication = (pFunction) JumpAddress;
      /* Initialize user application's Stack Pointer */
      __set_MSP(*(__IO uint32_t*) APPLICATION_ADDRESS);
      JumpToApplication();
      break;
    case '4' :
      if (FlashProtection != FLASHIF_PROTECTION_NONE)
      {
        /* Disable the write protection */
        if (FLASH_If_WriteProtectionConfig(FLASHIF_WRP_DISABLE) == FLASHIF_OK)
        {
          Serial_PutString("写保护已移除\r\n");
          Serial_PutString("系统现在重启\r\n");
          /* Launch the option byte loading */
          HAL_FLASH_OB_Launch();
        }
        else
        {
          Serial_PutString("Error: Flash移除保护失败\r\n");
        }
      }
      else
      {
        if (FLASH_If_WriteProtectionConfig(FLASHIF_WRP_ENABLE) == FLASHIF_OK)
        {
					Serial_PutString("写保护生效\r\n");
          Serial_PutString("系统重启中\r\n");
          /* Launch the option byte loading */
          HAL_FLASH_OB_Launch();
        }
        else
        {
          Serial_PutString("Error: Flash写保护失败\r\n");
        }
      }
      break;
	default:
		Serial_PutString("序号错误 ! ==> 请输入 1, 2, 3 or 4\r");
	break;
    }
  }
}

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
