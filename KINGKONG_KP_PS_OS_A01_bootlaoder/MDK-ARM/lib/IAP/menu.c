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

  Serial_PutString("APP1 updating(press'a'stop)\n\r");
  result = Ymodem_Receive( &size );
  if (result == COM_OK)
  {
    Serial_PutString("\n\n\rDFU ok!\n\r--\r\n name:");
    Serial_PutString(aFileName);
    Int2Str(number, size);
    Serial_PutString("\n\rsize:");
    Serial_PutString(number);
    Serial_PutString(" byte\r\n");
//    Serial_PutString("-------------------\n");
  }
  else if (result == COM_LIMIT)
  {
    Serial_PutString("\n\n\rfile over flash size!\n\r");
  }
  else if (result == COM_DATA)
  {
    Serial_PutString("\n\n\rverify fail!\n\r");
  }
  else if (result == COM_ABORT)
  {
    Serial_PutString("\r\n\nstop by user.\n\r");
  }
  else
  {
    Serial_PutString("\n\runsupport!\n\r");
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

  Serial_PutString("\n\n\rSelect file\n\r");

  HAL_UART_Receive(&huart1, &status, 1, RX_TIMEOUT);
  if ( status == CRC16)
  {
    /* Transmit the flash image through ymodem protocol */
    status = Ymodem_Transmit((uint8_t*)APPLICATION_ADDRESS, (const uint8_t*)"UploadedFlashImage.bin", USER_FLASH_SIZE);

    if (status != 0)
    {
      Serial_PutString("\n\rtransmit fail\n\r");
    }
    else
    {
      Serial_PutString("\n\rupdate sucess\n\r");
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
	
  Serial_PutString("\r\n= UART DFU =");
	Serial_PutString("\r\n= Porting By Enzo.sun=");
//  Serial_PutString("\r\n\r\n");

  /* Test if any sector of Flash memory where user application will be loaded is write protected */
  FlashProtection = FLASH_If_GetWriteProtectionStatus();

  while (1)
  {

    Serial_PutString("\r\nMENU >>>\r\n\n");
    Serial_PutString("  1 ->DOWNLOAD\r\n");
    Serial_PutString("  2 ->UPLOAD\r\n");
    Serial_PutString("  3 ->RUN\r\n");


    if(FlashProtection != FLASHIF_PROTECTION_NONE)
    {
      Serial_PutString("  4 ->EN PROTEC\r\n");
    }
    else
    {
      Serial_PutString("  4 ->DIS PROTEC\r\n");
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
			Serial_PutString("NOT PERMIT...\r\n\n");
      //SerialUpload();
      break;
    case '3' :
      Serial_PutString("APP RUNING...\r\n\n");
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
          Serial_PutString("REMOVE PROTECT\r\n");
          Serial_PutString("SYSTEM RESTART\r\n");
          /* Launch the option byte loading */
          HAL_FLASH_OB_Launch();
        }
        else
        {
          Serial_PutString("Error: Flash remove protect fail\r\n");
        }
      }
      else
      {
        if (FLASH_If_WriteProtectionConfig(FLASHIF_WRP_ENABLE) == FLASHIF_OK)
        {
					Serial_PutString("protect ok\r\n");
          Serial_PutString("system restart\r\n");
          /* Launch the option byte loading */
          HAL_FLASH_OB_Launch();
        }
        else
        {
          Serial_PutString("Error: Flash write protect fail\r\n");
        }
      }
      break;
	default:
		Serial_PutString("Num fail->1, 2, 3 or 4\r");
	break;
    }
  }
}

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
