/*
 * bootloader.h
 *
 * Created on: 2018Äê7ÔÂ4ÈÕ
 * Author: Enzo
 */
#ifndef BOOTLOADER_H_
#define BOOTLOADER_H_

#include "stdint.h"
#include "stm32f1xx_hal.h"

#define NVIC_VectTab_RAM              ((uint32_t)0x20000000)
#define NVIC_VectTab_FLASH            ((uint32_t)0x08000000)
#define IS_NVIC_VECTTAB(VECTTAB) 			(((VECTTAB) == NVIC_VectTab_RAM) || \
																			((VECTTAB) == NVIC_VectTab_FLASH))
#define IS_NVIC_OFFSET(OFFSET)  			((OFFSET) < 0x000FFFFF)

#define SYS_BASE_ADDR			0x08000000
#define SYS_BOOT_SIZE			0x00002700
#define SYS_PARA_SIZE			0x00001300
#define APP1_START_ADDR		0x08005000  /*SYS_BASE_ADDR+SYS_BOOT_SIZE+SYS_PARA_SIZE*/
#define APP1_PRE_OFFSET		0x00005000 	/*SYS_BOOT_SIZE + SYS_PARA_SIZE*/

extern void HAL_BOOT_LOADER(void);

#endif /*BOOTLOADER_H_*/


