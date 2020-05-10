/*
 * bsp_ad5683r.h
 *
 * Created on: 2018年6月3日
 * Author: Enzo
 */ 
 
#ifndef AD5683R_H
#define AD5683R_H

#include "stdint.h"
#include "stm32f1xx_hal.h"

#include "main.h"

#define		SPI_S1_MOSI_L		HAL_GPIO_WritePin(SPI_S1_MOSI_GPIO_Port, SPI_S1_MOSI_Pin, GPIO_PIN_RESET);
#define		SPI_S1_MOSI_H		HAL_GPIO_WritePin(SPI_S1_MOSI_GPIO_Port, SPI_S1_MOSI_Pin, GPIO_PIN_SET);

#define		SPI_S1_CLK_L		HAL_GPIO_WritePin(SPI_S1_CLK_GPIO_Port, SPI_S1_CLK_Pin, GPIO_PIN_RESET);
#define		SPI_S1_CLK_H		HAL_GPIO_WritePin(SPI_S1_CLK_GPIO_Port, SPI_S1_CLK_Pin, GPIO_PIN_SET);

#define		SPI_S1_CS_L			HAL_GPIO_WritePin(SPI_S1_CS_GPIO_Port, SPI_S1_CS_Pin, GPIO_PIN_RESET);
#define		SPI_S1_CS_H			HAL_GPIO_WritePin(SPI_S1_CS_GPIO_Port, SPI_S1_CS_Pin, GPIO_PIN_SET);


#define WRITE_CTRL_REG 						  0x4  //写入控制寄存器
#define WRITE_DAC_AND_INPUT_REG               0x3  // 写入DAC和输入寄存器
#define WRITE_INPUT_REG 					  0x1  // 写入输入寄存器
#define WRITE_UPDATE_DAC_REG				  0x2  // 更新DAC

extern void ad5683r_init(void);
extern void AD5683R_Write_Command(uint8_t ConValue);
extern void AD5683R_Write_Value(uint16_t DacValue);
extern void ad5683r_set_volt(float volt_val);


//Sample : AD5683_WriteToCtrl(DCEN_MODE|GAIN_OF_TWO|REF_DIS|PD_100KOHM|RESET)
#define	DCDIS_MODE	0					//Disable Daisy Chain
#define DCEN_MODE 	1					//Enable Daisy Chain

#define GAIN_OF_ONE	0					//Configure Gain = 1
#define GAIN_OF_TWO	2					//Configure Gain = 2

#define REF_EN			0					//AD5683R have an Internal Reference = 2v5. It can be enabled or disabled for AD5683R.
#define REF_DIS			4					//AD5683 needs external reference. This is always disable for AD5683.
				
#define PD_NORMAL		0					
#define PD_1KOHM		8					//Only use this in AD5683R. This function is not available for AD5683.
#define PD_100KOHM	16				//Only use this in AD5683R. This function is not available for AD5683.
#define	PD_THREE_STATE	24		//Only use this in AD5683R. This function is not available for AD5683.

#define	DRESET				32				//Only use this in AD5683R. This function is not available for AD5683.
#endif
