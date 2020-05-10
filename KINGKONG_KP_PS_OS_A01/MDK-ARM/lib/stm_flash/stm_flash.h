#ifndef __STM_FLASH_H__
#define __STM_FLASH_H__
#include "stdint.h"  

#define DELAY_FLASH		HAL_Delay(1);


#define STM32_FLASH_SIZE 	256 	 			//��ѡSTM32��FLASH������С(��λΪK)
#define STM32_FLASH_WREN 	1              		//ʹ��FLASHд��(0��������;1��ʹ��)
//////////////////////////////////////////////////////////////////////////////////////////////////////

//FLASH��ʼ��ַ
#define STM32_FLASH_BASE 0x08000000 			//STM32 FLASH����ʼ��ַ

void STMFLASH_Unlock(void);					  	//FLASH����
void STMFLASH_Lock(void);					  	//FLASH����
uint8_t STMFLASH_GetStatus(void);				  	//���״̬
uint8_t STMFLASH_WaitDone(uint16_t time);				  	//�ȴ���������
uint8_t STMFLASH_ErasePage(uint32_t paddr);			  	//����ҳ
uint8_t STMFLASH_WriteHalfWord(uint32_t faddr, uint16_t dat);	//д�����
uint16_t STMFLASH_ReadHalfWord(uint32_t faddr);		  	//��������  
void STMFLASH_WriteLenByte(uint32_t WriteAddr,uint32_t DataToWrite,uint16_t Len);	//ָ����ַ��ʼд��ָ�����ȵ�����
uint32_t STMFLASH_ReadLenByte(uint32_t ReadAddr,uint16_t Len);						//ָ����ַ��ʼ��ȡָ����������
void STMFLASH_Write(uint32_t WriteAddr,uint16_t *pBuffer,uint16_t NumToWrite);		//��ָ����ַ��ʼд��ָ�����ȵ�����
void STMFLASH_Read(uint32_t ReadAddr,uint16_t *pBuffer,uint16_t NumToRead);   		//��ָ����ַ��ʼ����ָ�����ȵ�����

//����д��
void Test_Write(uint32_t WriteAddr,uint16_t WriteData);								   
#endif

















