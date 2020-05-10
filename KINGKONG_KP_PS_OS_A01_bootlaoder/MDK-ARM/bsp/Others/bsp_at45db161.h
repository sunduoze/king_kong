
/*
 * bsp_at45db161.h
 *
 * Created on: 2017年11月14日
 * Author: Enzo
 */
#ifndef BSP_AT45DB161_H_
#define BSP_AT45DB161_H_

#include "stm32f1xx_hal.h"
#include "stdint.h"

#define EEPROM_SCK_H 		HAL_GPIO_WritePin(EEPROM_SCK_GPIO_Port, EEPROM_SCK_Pin, GPIO_PIN_SET)
#define EEPROM_SCK_L 		HAL_GPIO_WritePin(EEPROM_SCK_GPIO_Port, EEPROM_SCK_Pin, GPIO_PIN_RESET)
#define EEPROM_MOSI_H 	HAL_GPIO_WritePin(EEPROM_MOSI_GPIO_Port, EEPROM_MOSI_Pin, GPIO_PIN_SET)
#define EEPROM_MOSI_L 	HAL_GPIO_WritePin(EEPROM_MOSI_GPIO_Port, EEPROM_MOSI_Pin, GPIO_PIN_RESET)
#define EEPROM_CS_H			HAL_GPIO_WritePin(EEPROM_CS_GPIO_Port, EEPROM_CS_Pin, GPIO_PIN_SET)
#define EEPROM_CS_L			HAL_GPIO_WritePin(EEPROM_CS_GPIO_Port, EEPROM_CS_Pin, GPIO_PIN_RESET)
#define EEPROM_MISO			HAL_GPIO_ReadPin(EEPROM_MISO_GPIO_Port, EEPROM_MISO_Pin)


/* Exported macro ------------------------------------------------------------*/
///* Select SPI FLASH: Chip Select pin low  */
//#define SPI_FLASH_CS_LOW()       GPIO_ResetBits(GPIO_CS, GPIO_Pin_CS)
///* Deselect SPI FLASH: Chip Select pin high */
//#define SPI_FLASH_CS_HIGH()      GPIO_SetBits(GPIO_CS, GPIO_Pin_CS)

/* Exported functions ------------------------------------------------------- */
/*----- High layer function -----*/
void SPI_FLASH_Init(void);
void SPI_FLASH_PageErase(uint32_t SectorAddr);
void SPI_FLASH_BulkErase(void);
uint32_t SPI_FLASH_ReadID(void);

void SPI_FLASH_ReadSector(uint8_t* pBuffer, uint32_t SectorAddr, uint16_t NumByteToRead);
void SPI_FLASH_WriteSector(uint8_t* pBuffer, uint32_t SectorAddr, uint16_t NumByteToRead);



/*----- Low layer function -----*/
uint8_t SPI_FLASH_ReadByte(void);
uint8_t SPI_FLASH_SendByte(uint8_t byte);
void SPI_FLASH_WaitForWriteEnd(void);
#endif /*BSP_AT45DB161_H_*/

