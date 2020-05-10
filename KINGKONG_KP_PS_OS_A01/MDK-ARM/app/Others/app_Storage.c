/*
 * app_storage.c
 *
 * Created on: 2017年11月14日
 * Author: Enzo
 */
 
#include "app_storage.h"
#include "stm_flash.h"
#include "lib_malloc.h"

//#define DEBUG_TEST

//仅通过ModuleNum 来进行排序，进行标识
/*The header of users flash storage*/
typedef struct
{
	uint8_t 						ModuleNum;			/*the count of modules*/
	uint8_t 						ResidualNum;		/*How many count of modules we can storage ? */
	uint8_t 						CurrentModule;	/*Current module Sign we used*/
	uint8_t 						AlignByteNC;		//Only for Data Storge Align
}StorageHead;/*4 Byte*/

/*The Index Table of module flash storage*/
typedef struct
{
/*10*/uint8_t         ProN[PROJ_NAME_LEN];//Project Name
/*4 */uint32_t 				MStA;								/*the flash storge address of modules */
/*1 */uint8_t 				CurM;								/*Storage module location 没tm什么卵用，与头中的CM保持一致把??????bug ？？？？潜在BUG？？？？？？*/
								/*1: Valid  0:Invalid*/
/*1 */uint8_t 				State;							/*This Module data is Valid or Invalid [For del some keyboard module info]*/  
}IndexTable;/*16 Byte*/

volatile IndexTable ModIndexTab[MAX_MODULE_NUM];


extern volatile KeyBoard kbTemp;//竟然被编译器优化 =+++++=


/*Read last storage module info to kbTemp*/
void ReadLastStorageMod(void)
{
	StorageHead sfh;
	uint8_t datatemp[sizeof(StorageHead)];		
	STMFLASH_Read(FLASH_MODULE_START_INFO_SAVE_ADDR,(uint16_t*)datatemp,sizeof(StorageHead));
	mymemcpy(&sfh, datatemp, sizeof(StorageHead));
	if(sfh.ModuleNum == FLASH_DEFAULE_FILL)//First write test module info to flash
	{
		/* Write  header of users flash to flash */
		sfh.ModuleNum = 0;
		sfh.ResidualNum = MAX_MODULE_NUM;
		sfh.CurrentModule = 0;
		sfh.AlignByteNC = 0;
		mymemcpy(datatemp, &sfh, sizeof(StorageHead));
		STMFLASH_Write(FLASH_MODULE_START_INFO_SAVE_ADDR, (uint16_t*)datatemp, sizeof(StorageHead));
		
		#ifdef DEBUG_TEST/* Test storage is OK ? */
			STMFLASH_Read(FLASH_MODULE_START_INFO_SAVE_ADDR, (uint16_t*)datatemp, sizeof(StorageHead));
			mymemcpy(&sfh, datatemp, sizeof(StorageHead));
			printf("ModuleNum %d ResidualNum %d CurrentModule %d\r\n", sfh.ModuleNum, sfh.ResidualNum, sfh.CurrentModule);
		#endif

		/* test module */
		uint8_t str[PROJ_NAME_LEN] = "X13ansiTe ";
		mymemcpy((void *)ModIndexTab[0].ProN, (void *)str, PROJ_NAME_LEN);
		ModIndexTab[0].MStA								 = FLASH_MODULE_BUTTON_INFO_SAVE_ADDR;
		ModIndexTab[0].CurM								 = sfh.CurrentModule;
		ModIndexTab[0].State							 = 0;/*1: Valid  0:Invalid*/
		
		uint8_t datatemp1[sizeof(IndexTable)];
		mymemcpy(datatemp1, (void *)ModIndexTab, sizeof(IndexTable));
		STMFLASH_Write(FLASH_MODULE_START_INDEX_TABLE + sfh.ModuleNum * sizeof(IndexTable), (uint16_t*)datatemp1, sizeof(IndexTable));
		#ifdef DEBUG_TEST
			/* Test storage is OK ? */
			STMFLASH_Read(FLASH_MODULE_START_INFO_SAVE_ADDR,(uint16_t*)datatemp,sizeof(StorageHead));
			mymemcpy(&sfh, datatemp, sizeof(StorageHead));
			printf("sfh.ModuleNum %d sfh.ResidualNum %d sfh.CurrentModule %d \r\n",sfh.ModuleNum,sfh.ResidualNum,sfh.CurrentModule);
			/* Test storage is OK ? */	
			STMFLASH_Read(FLASH_MODULE_START_INDEX_TABLE,(uint16_t*)datatemp1,sizeof(IndexTable));
			mymemcpy((void *)ModIndexTab, datatemp1, sizeof(IndexTable));
			printf("ModIndexTab ProN %s MStA %d CurM %d State %d\r\n",ModIndexTab[0].ProN, ModIndexTab[0].MStA, ModIndexTab[0].CurM, ModIndexTab[0].State);
		#endif
		uint16_t *mem = (uint16_t *)mymalloc(sizeof(KeyBoard));	
		mymemcpy(mem, &kb_X13_ANSI, sizeof(KeyBoard));					//Storage X13 info for the part of Test module
		STMFLASH_Write(FLASH_MODULE_BUTTON_INFO_SAVE_ADDR,(uint16_t*)mem,sizeof(KeyBoard));
		mymemcpy((void *)&kbTemp, mem, sizeof(KeyBoard));
		printf("\r\n\r\nFirst use the Key Board Test Platform\r\n\r\n");
	}
	else	//Extract storage Keyboard info to kbTemp /* Non-first write*/
	{	
		/*First:Extract -> Header*/
		STMFLASH_Read(FLASH_MODULE_START_INFO_SAVE_ADDR,(uint16_t*)datatemp,sizeof(StorageHead));
		mymemcpy(&sfh, datatemp, sizeof(StorageHead));
		#ifdef DEBUG_TEST
			printf("sfh.ModuleNum %d sfh.ResidualNum %d sfh.CurrentModule %d \r\n",sfh.ModuleNum,sfh.ResidualNum,sfh.CurrentModule);
		#endif	
		/*Second:Extract -> IndexTable */
		uint8_t datatemp1[sizeof(IndexTable)];
		STMFLASH_Read(FLASH_MODULE_START_INDEX_TABLE,(uint16_t*)datatemp1,sizeof(IndexTable));
		mymemcpy((void *)ModIndexTab, datatemp1, sizeof(IndexTable));
		#ifdef DEBUG_TEST
			printf("ModIndexTab ProN %s MStA %d CurM %d \r\n",ModIndexTab[0].ProN, ModIndexTab[0].MStA, ModIndexTab[0].CurM);
		#endif	
		uint16_t *mem = (uint16_t *)mymalloc(sizeof(KeyBoard));
		STMFLASH_Read(ModIndexTab[sfh.CurrentModule].MStA, mem, sizeof(KeyBoard));
		mymemcpy((void *)&kbTemp, mem, sizeof(KeyBoard));
//		myfree(mem);//屏蔽此句解除不能新malloc的限制 Printf module info 时出现问题
		printf("Read Out CurrentModule Data from flash !!!\r\n");
		
		#ifdef DEBUG_TEST//___ERROR
//			__NOP();		
		KeyBoardParameterPrint((const KeyBoard *)&kbTemp);
		printf("\r\n KeyBoard SIZE:::%d \r\n",sizeof(KeyBoard));	//ModIndexTab[MAX_MODULE_NUM]
		printf("\r\n 66 * IndexTable::::%d \r\n",MAX_MODULE_NUM * sizeof(IndexTable));	//ModIndexTab[MAX_MODULE_NUM]
		#endif

	}
}

/*Print project num & name & address  ..storage information*/
void PrintProjStorgeIndexTable2PC(void)
{
	static uint8_t i = 0,j;
	StorageHead sfh;
	uint8_t datatemp[sizeof(StorageHead)];		
	STMFLASH_Read(FLASH_MODULE_START_INFO_SAVE_ADDR, (uint16_t*)datatemp, sizeof(StorageHead));
	mymemcpy(&sfh, datatemp, sizeof(StorageHead));
	j = sfh.ModuleNum;
	printf("ModuleNum:%d ResidualNum:%d CurrentModule:%d \r\n",sfh.ModuleNum, sfh.ResidualNum, sfh.CurrentModule);
	
	
	uint8_t datatemp1[MAX_MODULE_NUM * sizeof(IndexTable)];
	STMFLASH_Read(FLASH_MODULE_START_INDEX_TABLE,(uint16_t*)datatemp1,MAX_MODULE_NUM * sizeof(IndexTable));
	mymemcpy((void *)ModIndexTab, datatemp1, MAX_MODULE_NUM * sizeof(IndexTable));
//	printf("ModIndexTab ProN %s MStA %d CurM %d State %d\r\n",ModIndexTab[0].ProN, ModIndexTab[0].MStA, ModIndexTab[0].CurM, ModIndexTab[0].State);
//	printf("ModIndexTab ProN %s MStA %d CurM %d State %d\r\n",ModIndexTab[1].ProN, ModIndexTab[1].MStA, ModIndexTab[1].CurM, ModIndexTab[1].State);
	for(i = 0; i <= j; i++)//从第二个开始打印输出
	{
		printf("ModIndexTab ProN %s MStA %d CurM %d State %d\r\n",ModIndexTab[i].ProN, ModIndexTab[i].MStA, ModIndexTab[i].CurM, ModIndexTab[i].State);
//		printf("ProjectName %s ModuleStorgeAddress %d CurrentModule %d State %d\r\n",ModIndexTab[i].ProN, ModIndexTab[i].MStA, ModIndexTab[i].CurM, ModIndexTab[i].State);
		/*与软件协商 中间添加什么符号或者类型的标志来进行整个字符串中信息提取*/
	}
	__nop();
}

void SelectProjInIndexTableFromPC(uint8_t num)
{
	static uint8_t i = 0,j;
	StorageHead sfh;
	uint8_t datatemp[sizeof(StorageHead)];		
	STMFLASH_Read(FLASH_MODULE_START_INFO_SAVE_ADDR, (uint16_t*)datatemp, sizeof(StorageHead));
	mymemcpy(&sfh, datatemp, sizeof(StorageHead));
	j = sfh.ModuleNum;
	printf("ModuleNum:%d ResidualNum:%d CurrentModule:%d \r\n",sfh.ModuleNum, sfh.ResidualNum, sfh.CurrentModule);
	
	
	uint8_t datatemp1[MAX_MODULE_NUM * sizeof(IndexTable)];
	STMFLASH_Read(FLASH_MODULE_START_INDEX_TABLE,(uint16_t*)datatemp1,MAX_MODULE_NUM * sizeof(IndexTable));
	mymemcpy((void *)ModIndexTab, datatemp1, MAX_MODULE_NUM * sizeof(IndexTable));
	for(i = 0; i <= j; i++)//从第二个开始打印输出
	{
		printf("ProjectName %s ModuleStorgeAddress %d CurrentModule %d State %d\r\n",ModIndexTab[i].ProN, ModIndexTab[i].MStA, ModIndexTab[i].CurM, ModIndexTab[i].State);
		/*与软件协商 中间添加什么符号或者类型的标志来进行整个字符串中信息提取*/
	}
//	STMFLASH_Read(FLASH_MODULE_START_INFO_SAVE_ADDR,(uint16_t*)datatemp,sizeof(StorageHead));
//	mymemcpy(&sfh, datatemp, sizeof(StorageHead));

		/* Write  header of users flash to flash */
//		sfh.ModuleNum = sfh.ModuleNum;
//		sfh.ResidualNum = sfh.ResidualNum;
		sfh.CurrentModule = num;
//		sfh.AlignByteNC = sfh.AlignByteNC;
		mymemcpy(datatemp, &sfh, sizeof(StorageHead));
		STMFLASH_Write(FLASH_MODULE_START_INFO_SAVE_ADDR, (uint16_t*)datatemp, sizeof(StorageHead));
		
		#ifdef DEBUG_TEST/* Test storage is OK ? */
			STMFLASH_Read(FLASH_MODULE_START_INFO_SAVE_ADDR, (uint16_t*)datatemp, sizeof(StorageHead));
			mymemcpy(&sfh, datatemp, sizeof(StorageHead));
			printf("ModuleNum %d ResidualNum %d CurrentModule %d\r\n", sfh.ModuleNum, sfh.ResidualNum, sfh.CurrentModule);
		#endif
	
//	HAL_NVIC_DisableIRQ(TIM4_IRQn);
//	HAL_NVIC_DisableIRQ(USART1_IRQn);
//	HAL_NVIC_SystemReset();
}
/*Storge a keyboard module info to flash from PC*/
void StorgeNewMod(KeyBoard *kb)
{
	StorageHead sfh;
	uint8_t datatemp[sizeof(StorageHead)];	
	/*First:Extract -> Header*/
	STMFLASH_Read(FLASH_MODULE_START_INFO_SAVE_ADDR, (uint16_t*)datatemp, sizeof(StorageHead));
	mymemcpy(&sfh, datatemp, sizeof(StorageHead));
	#ifdef DEBUG_TEST
	printf("ModuleNum: %d ResidualNum: %d CurrentModule: %d \r\n", sfh.ModuleNum, sfh.ResidualNum, sfh.CurrentModule);
	#endif	
//	/*Second:Extract -> IndexTable */
//	uint8_t datatemp1[sizeof(IndexTable)];//Single Member of IntexTable
//	STMFLASH_Read(FLASH_MODULE_START_INDEX_TABLE + sfh.ModuleNum * sizeof(IndexTable), (uint16_t*)datatemp1,sizeof(IndexTable));
//	mymemcpy((void *)ModIndexTab, datatemp1, sizeof(IndexTable));	

//	#ifdef DEBUG_TEST
//		printf("\r\n StorgeNewMod:CurrentModule:%d ModuleStorgeAddress:%d ProjectName:%s \r\n",ModIndexTab[sfh.CurrentModule].CurM, ModIndexTab[sfh.CurrentModule].MStA, ModIndexTab[sfh.CurrentModule].ProN);
//	#endif	
	/*Update Header Info & Write  header of users flash to flash*/
	sfh.ModuleNum ++;
	sfh.ResidualNum --;
//		sfh.CurrentModule = sfh.CurrentModule;
	mymemcpy(datatemp, &sfh, sizeof(StorageHead));
	STMFLASH_Write(FLASH_MODULE_START_INFO_SAVE_ADDR, (uint16_t*)datatemp,sizeof(StorageHead));
	/*Update IndexTable & Index Table to flash*/
	mymemcpy((void *)ModIndexTab[sfh.ModuleNum].ProN, kb->ProN, PROJ_NAME_LEN);
	ModIndexTab[sfh.ModuleNum].MStA								 = FLASH_MODULE_BUTTON_INFO_SAVE_ADDR + sfh.ModuleNum * sizeof(KeyBoard);
	ModIndexTab[sfh.ModuleNum].CurM								 = sfh.CurrentModule;
	ModIndexTab[sfh.ModuleNum].State							 = 1;/*1: Valid  0:Invalid*/

	uint8_t datatemp1[sizeof(IndexTable)];
	mymemcpy(datatemp1, (void *)(ModIndexTab + sfh.ModuleNum), sizeof(IndexTable));
	STMFLASH_Write(FLASH_MODULE_START_INDEX_TABLE + sfh.ModuleNum * sizeof(IndexTable), (uint16_t*)datatemp1, sizeof(IndexTable));
	#ifdef DEBUG_TEST
		printf("\r\n\r\n Name:%s \r\n", ModIndexTab[sfh.ModuleNum].ProN);
		/* Test storage is OK ? */
		STMFLASH_Read(FLASH_MODULE_START_INFO_SAVE_ADDR,(uint16_t*)datatemp,sizeof(StorageHead));
		mymemcpy(&sfh, datatemp, sizeof(StorageHead));
		printf("ModuleNum %d ResidualNum %d CurrentModule %d\r\n",sfh.ModuleNum,sfh.ResidualNum,sfh.CurrentModule);
		/* Test storage is OK ? */	
		STMFLASH_Read(FLASH_MODULE_START_INDEX_TABLE + sfh.ModuleNum * sizeof(IndexTable) ,(uint16_t*)datatemp1,sizeof(IndexTable));
		mymemcpy((void *)ModIndexTab, datatemp1, sizeof(IndexTable));
		printf("ModIndexTab ProN %s MStA %d CurM %d State %d\r\n",ModIndexTab[sfh.CurrentModule].ProN, ModIndexTab[sfh.CurrentModule].MStA, ModIndexTab[sfh.CurrentModule].CurM, ModIndexTab[0].State);
	#endif
	uint16_t *mem = (uint16_t *)mymalloc(sizeof(KeyBoard));
	mymemcpy(mem, kb, sizeof(KeyBoard));// Type Convert
	STMFLASH_Write(ModIndexTab[sfh.ModuleNum].MStA,(uint16_t*)mem,sizeof(KeyBoard));
//	myfree(mem);
	printf("\r\n free ok !\r\n");
	
	#ifdef DEBUG_TEST
		uint8_t datatempKB[sizeof(KeyBoard)];		
		STMFLASH_Read(ModIndexTab[sfh.ModuleNum].MStA,(uint16_t*)datatempKB,sizeof(KeyBoard));
		mymemcpy(kb, datatempKB, sizeof(KeyBoard));
		KeyBoardParameterPrint(kb);
		printf("\r\n Printf KeyBoard INfo ok !\r\n");
	#endif

	
}




	


