/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * Copyright (c) 2019 STMicroelectronics International N.V. 
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without 
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice, 
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other 
  *    contributors to this software may be used to endorse or promote products 
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this 
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under 
  *    this license is void and will automatically terminate your rights under 
  *    this license. 
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS" 
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT 
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT 
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define KEY3_Pin GPIO_PIN_2
#define KEY3_GPIO_Port GPIOE
#define KEY4_Pin GPIO_PIN_3
#define KEY4_GPIO_Port GPIOE
#define KEY5_Pin GPIO_PIN_4
#define KEY5_GPIO_Port GPIOE
#define KEY6_Pin GPIO_PIN_5
#define KEY6_GPIO_Port GPIOE
#define KEY7_Pin GPIO_PIN_6
#define KEY7_GPIO_Port GPIOE
#define KEY8_Pin GPIO_PIN_13
#define KEY8_GPIO_Port GPIOC
#define LED1_Pin GPIO_PIN_0
#define LED1_GPIO_Port GPIOC
#define ETH_MDC_Pin GPIO_PIN_1
#define ETH_MDC_GPIO_Port GPIOC
#define LED2_Pin GPIO_PIN_2
#define LED2_GPIO_Port GPIOC
#define LED3_Pin GPIO_PIN_3
#define LED3_GPIO_Port GPIOC
#define ETH_REF_CLK_Pin GPIO_PIN_1
#define ETH_REF_CLK_GPIO_Port GPIOA
#define ETH_MDIO_Pin GPIO_PIN_2
#define ETH_MDIO_GPIO_Port GPIOA
#define BUCK_PS_EN_Pin GPIO_PIN_3
#define BUCK_PS_EN_GPIO_Port GPIOA
#define TEST_OUT_Pin GPIO_PIN_5
#define TEST_OUT_GPIO_Port GPIOA
#define DMM_PS_EN_Pin GPIO_PIN_6
#define DMM_PS_EN_GPIO_Port GPIOA
#define ETH_CRS_DV_Pin GPIO_PIN_7
#define ETH_CRS_DV_GPIO_Port GPIOA
#define ETH_RXD0_Pin GPIO_PIN_4
#define ETH_RXD0_GPIO_Port GPIOC
#define ETH_RXD1_Pin GPIO_PIN_5
#define ETH_RXD1_GPIO_Port GPIOC
#define ETH_TX_EN_Pin GPIO_PIN_0
#define ETH_TX_EN_GPIO_Port GPIOB
#define ETH_RST_N_Pin GPIO_PIN_1
#define ETH_RST_N_GPIO_Port GPIOB
#define AD7124_CS_Pin GPIO_PIN_2
#define AD7124_CS_GPIO_Port GPIOB
#define IIC2_S_SCL_Pin GPIO_PIN_7
#define IIC2_S_SCL_GPIO_Port GPIOE
#define IIC2_S_SDA_Pin GPIO_PIN_8
#define IIC2_S_SDA_GPIO_Port GPIOE
#define OUT_CH8_Pin GPIO_PIN_9
#define OUT_CH8_GPIO_Port GPIOE
#define OUT_CH7_Pin GPIO_PIN_11
#define OUT_CH7_GPIO_Port GPIOE
#define OUT_CH6_Pin GPIO_PIN_13
#define OUT_CH6_GPIO_Port GPIOE
#define OUT_CH5_Pin GPIO_PIN_14
#define OUT_CH5_GPIO_Port GPIOE
#define PWR0204_2_EN_Pin GPIO_PIN_15
#define PWR0204_2_EN_GPIO_Port GPIOE
#define ETH_TXD0_Pin GPIO_PIN_12
#define ETH_TXD0_GPIO_Port GPIOB
#define ETH_TXD1_Pin GPIO_PIN_13
#define ETH_TXD1_GPIO_Port GPIOB
#define Button1_Pin GPIO_PIN_14
#define Button1_GPIO_Port GPIOB
#define Button2_Pin GPIO_PIN_15
#define Button2_GPIO_Port GPIOB
#define SPI_S1_MISO_Pin GPIO_PIN_8
#define SPI_S1_MISO_GPIO_Port GPIOD
#define SPI_S1_CS_Pin GPIO_PIN_9
#define SPI_S1_CS_GPIO_Port GPIOD
#define SPI_S1_CLK_Pin GPIO_PIN_10
#define SPI_S1_CLK_GPIO_Port GPIOD
#define SPI_S1_MOSI_Pin GPIO_PIN_11
#define SPI_S1_MOSI_GPIO_Port GPIOD
#define TIM4_CH1_IPD_Pin GPIO_PIN_12
#define TIM4_CH1_IPD_GPIO_Port GPIOD
#define TIM4_CH2_IPD_Pin GPIO_PIN_13
#define TIM4_CH2_IPD_GPIO_Port GPIOD
#define TIM4_CH3_IPD_Pin GPIO_PIN_14
#define TIM4_CH3_IPD_GPIO_Port GPIOD
#define TIM4_CH4_OPP_Pin GPIO_PIN_15
#define TIM4_CH4_OPP_GPIO_Port GPIOD
#define IO_EXP_CS1_Pin GPIO_PIN_3
#define IO_EXP_CS1_GPIO_Port GPIOD
#define IO_EXP_LE1_Pin GPIO_PIN_4
#define IO_EXP_LE1_GPIO_Port GPIOD
#define PWR0204_1_EN_Pin GPIO_PIN_7
#define PWR0204_1_EN_GPIO_Port GPIOD
#define I2C1_SCL_Pin GPIO_PIN_6
#define I2C1_SCL_GPIO_Port GPIOB
#define I2C1_SDA_Pin GPIO_PIN_7
#define I2C1_SDA_GPIO_Port GPIOB
#define RELAY_STATE_EN_Pin GPIO_PIN_8
#define RELAY_STATE_EN_GPIO_Port GPIOB
#define KEY1_Pin GPIO_PIN_0
#define KEY1_GPIO_Port GPIOE
#define KEY2_Pin GPIO_PIN_1
#define KEY2_GPIO_Port GPIOE
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
