/*
 * app_Storage.h
 *
 * Created on: 2017��11��14��
 * Author: Enzo
 */
#ifndef APP_STORAGE_H_
#define APP_STORAGE_H_

#include "stm32f1xx_hal.h"
#include "stdint.h"
#include "app_main.h"

#define MAX_MODULE_NUM 			66 //How many module you can storage ��
#define FLASH_DEFAULE_FILL	0xFF

#define FLASH_MODULE_START_INFO_SAVE_ADDR  	0X08020000//0X08020000 //��ʼ��ַ��128kB/(sum=256k)	//����FLASH �����ַ(����Ϊż��������ֵҪ���ڱ�������ռ��FLASH�Ĵ�С+0X08000000)
/*Flash = Code + Ro-data = 11336 +500 Լ 11.5kB*/
#define FLASH_MODULE_START_INDEX_TABLE			FLASH_MODULE_START_INFO_SAVE_ADDR + 4
// 0x08020434
#define FLASH_MODULE_BUTTON_INFO_SAVE_ADDR  (FLASH_MODULE_START_INDEX_TABLE + (MAX_MODULE_NUM + 1) * 16 )//Offset -> header of users flash & Index Table * (MAX_MODULE_NUM + 1) !!  sizeof(IndexTable) = 16
//extern KeyBoard kbTemp;//��Ȼ���������Ż� =+++++=

extern void ReadLastStorageMod(void);
extern void PrintProjStorgeIndexTable2PC(void);/*Print project num & name & address  ..storage information*/
extern void StorgeNewMod(KeyBoard *kb);
extern void SelectProjInIndexTableFromPC(uint8_t num);
#endif /*APP_STORAGE_H_*/



