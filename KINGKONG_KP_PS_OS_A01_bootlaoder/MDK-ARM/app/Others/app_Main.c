/*
 * app_main.c
 *
 * Created on: 2017年11月14日
 * Author: Enzo
 */

#include "app_main.h"
#include "stm32f1xx_hal.h"
#include "spi.h"
#include "MCP23S17.h"
#include "bsp_delay.h"
#include "stm_flash.h"
#include "lib_malloc.h"

#include "usart.h"
const uint8_t TEXT_Buffer[]={"STM32 FLASH TEST"};
#define SIZE sizeof(TEXT_Buffer)	 	//数组长度
uint8_t datatemp[SIZE];		


//void Write2Flash(KeyBoard *kbTemp)
//{
//		uint16_t *mem = (uint16_t *)mymalloc(sizeof(KeyBoard));
//		printf("\r\n malloc ok !\r\n");
//		mymemcpy(mem, kbTemp, sizeof(KeyBoard));// Type Convert
//	printf("\r\n cpy ok !\r\n");
//		STMFLASH_Write(FLASH_SAVE_ADDR,(uint16_t*)mem,sizeof(KeyBoard));
//	printf("\r\n flash w ok !\r\n");
//		myfree(mem);
//	printf("\r\n free ok !\r\n");
//}

//void ParaStor(uint8_t Sta)
//{
//	if(Sta)
//	{
//		uint16_t *mem = (uint16_t *)mymalloc(sizeof(KeyBoard));
//		mymemcpy(mem, &kb_X13_ANSI, sizeof(KeyBoard));
//		STMFLASH_Write(FLASH_SAVE_ADDR,(uint16_t*)mem,sizeof(KeyBoard));
//		myfree(mem);
//	}
//	else
//	{
//		KeyBoard kb_X1;
//		STMFLASH_Read(FLASH_SAVE_ADDR,(uint16_t*)datatemp,sizeof(KeyBoard));
//		mymemcpy(&kb_X1, datatemp, sizeof(KeyBoard));
//		KeyBoardParameterPrint(&kb_X1);
//	}
//}

#define IS_09(c)  ((c >= '0') && (c <= '9'))
/**
  * @brief  Extract parameters from a string
  * @param  inputStr : The input string
  * @param  tarNum   : The pointer of parameter
  * @param  ParaType : Type of parameter
  *   @arg  'i'  : int32_t
  *   @arg  'f'  : float
  * @param  ParaNum  : amount of parameter
  *   @arg  0    : not specify parameter number,end with '\0'
  *   @arg  1~255: amount of parameter
  * @param  Separator: Separator of parameter
  * @retval 1: Correct
  *         0: Error
  *         by Junior Yip
  */
uint8_t Extract_Parameter(uint8_t *inputStr,void *tarNum, uint8_t ParaType,uint8_t ParaNum,uint8_t Separator){
	
	uint16_t i=0;
	uint8_t j=0,Len=0;
	int32_t NumSign=0;
	uint8_t NumFlag=0,DotFlag=0;
	
	//convert to int32_t
	if(ParaType=='i'){
		
		int32_t *intNum;
		int32_t NumBuf=0;
		intNum=tarNum;
		
		while(ParaNum==0?inputStr[i]!='\0':j<ParaNum){
			
			//Symbol check
			if(NumSign==0){
				if(inputStr[i]=='-'){
					NumSign = -1;
					i++;
				}
				else
					NumSign = 1;
			}
			
			if(IS_09(inputStr[i])){
				if(Len>10){
					return 0;
				}
				NumBuf=NumBuf*10 + inputStr[i]-'0';
				Len++;
			}
			else if(inputStr[i]==Separator){
				
				intNum[j]=NumBuf*NumSign;
				NumBuf=0;
				j++;
				Len=0;
				NumSign=0;
			}
			else{
		//String format error
				return 0;
			}
			if(inputStr[++i]=='\0'){
				intNum[j]=NumBuf*NumSign;
				j++;
				NumSign=0;
				NumBuf=0;
				Len=0;
			}
		}
		
	}
	//convert to float
	else if(ParaType=='f'){
		
		float *floatNum;
		floatNum=tarNum;
		float NumBuf=0;
		float temp=10;
		
		while(ParaNum==0?inputStr[i]!='\0':j<ParaNum){
			
			//Symbol check
			if(NumSign==0){
				if(inputStr[i]=='-'){
					NumSign = -1;
					i++;
				}
				else
					NumSign = 1;
			}
			
			if(IS_09(inputStr[i])){
				if(Len>10){
					return 0;
				}
				if(DotFlag==0){
					NumBuf=NumBuf*10 + inputStr[i]-'0';
				}
				else{
					NumBuf = NumBuf + ((float)((int32_t)inputStr[i]-'0'))/temp;
					temp=temp*10;
				}
				Len++;
				NumFlag=1;
			}
			else if(inputStr[i]=='.' && DotFlag==0 && NumFlag==1){
				Len=0;
				NumFlag=0;
				DotFlag=1;
			}
			else if(inputStr[i]==Separator&&NumFlag==1){
				Len=0;
				floatNum[j]=NumBuf*NumSign;
				j++;
				temp=10;
				NumBuf=0;
				NumSign=0;
				NumFlag=0;
				DotFlag=0;
			}
			else{
		//String format error
				return 0;
			}
			
			if(inputStr[++i]=='\0'){
				Len=0;
				floatNum[j]=NumBuf*NumSign;
				j++;
				temp=10;
				NumBuf=0;
				NumSign=0;
				NumFlag=0;
				DotFlag=0;
			}
		}
	}
	else{
		//Error Type
		return 0;
	}
		
	if(ParaNum==0 || j==ParaNum)
		return 1;
	else 
		//ParaNum error
		return 0;
	
}

KeyBoard kb_X13_ANSI = {// MAX 211 60
/*ProN*/"IA641 ANSI",
/*BtnTyp*/1,	//1:single 0:matrix
/*Stdx*/	0,	//ANSI:0 ISO:1 JIS:2
/*OrgP*/{46.836,33.32},
/*Btn */{
/*
IO Expand Chip CS Pin [1:8]
IO Expand Chip Io     [0:7]
IO Expand Chip Part   0:A 1:B
____________________________________________
	MP_x:	Matrix Point Driver x-Axis 
				or Single Point Driver
	MP_y:	Matrix Point Driver y-Axis
	BP_X:	the X Axis Coordinate of ButtonPoint
	BP_Y:	the Y Axis Coordinate of ButtonPoint
____________________________________________
  MP_x          MP_y         BP_X    BP_Y				
  |               |            |      |
----------- --------------- ------- ------		*/
0,0x01,0x12,0,0,0x01,0x12,0,-46.836,-33.32, 
0,0x02,0x12,0,0,0x02,0x12,0,-26.505,-33.32, 
0,0x04,0x12,0,0,0x04,0x12,0,-6.174,-33.32, 
0,0x08,0x12,0,0,0x08,0x12,0,14.156,-33.32, 
0,0x10,0x12,0,0,0x10,0x12,0,34.487,-33.32, 
0,0x20,0x12,0,0,0x20,0x12,0,54.817,-33.32, 
0,0x40,0x12,0,0,0x40,0x12,0,75.147,-33.32, 
0,0x80,0x12,0,0,0x80,0x12,0,95.478,-33.32, 
0,0x01,0x13,0,0,0x01,0x13,0,115.808,-33.32, 
0,0x02,0x13,0,0,0x02,0x13,0,136.139,-33.32, 
0,0x04,0x13,0,0,0x04,0x13,0,156.47,-33.32, 
0,0x08,0x13,0,0,0x08,0x13,0,176.8,-33.32, 
0,0x10,0x13,0,0,0x10,0x13,0,197.131,-33.32, 
0,0x20,0x13,0,0,0x20,0x13,0,217.461,-33.32, 
0,0x40,0x13,0,0,0x40,0x13,0,-47.501,-18.5, 
0,0x80,0x13,0,0,0x80,0x13,0,-28.501,-18.5, 
1,0x01,0x12,0,1,0x01,0x12,0,-9.501,-18.5, 
1,0x02,0x12,0,1,0x02,0x12,0,9.499,-18.5, 
1,0x04,0x12,0,1,0x04,0x12,0,28.499,-18.5, 
1,0x08,0x12,0,1,0x08,0x12,0,47.499,-18.5, 
1,0x10,0x12,0,1,0x10,0x12,0,66.499,-18.5, 
1,0x20,0x12,0,1,0x20,0x12,0,85.499,-18.5, 
1,0x40,0x12,0,1,0x40,0x12,0,104.499,-18.5, 
1,0x80,0x12,0,1,0x80,0x12,0,123.499,-18.5, 
1,0x01,0x13,0,1,0x01,0x13,0,142.499,-18.5, 
1,0x02,0x13,0,1,0x02,0x13,0,161.499,-18.5, 
1,0x04,0x13,0,1,0x04,0x13,0,180.499,-18.5, 
1,0x08,0x13,0,1,0x08,0x13,0,204.249,-18.5, 
1,0x10,0x13,0,1,0x10,0x13,0,-42.751,0, 
1,0x20,0x13,0,1,0x20,0x13,0,-19,0, 
1,0x40,0x13,0,1,0x40,0x13,0,0,0, 
1,0x80,0x13,0,1,0x80,0x13,0,19,0, 
2,0x01,0x12,0,2,0x01,0x12,0,38,0, 
2,0x02,0x12,0,2,0x02,0x12,0,57,0, 
2,0x04,0x12,0,2,0x04,0x12,0,76,0, 
2,0x08,0x12,0,2,0x08,0x12,0,95,0, 
2,0x10,0x12,0,2,0x10,0x12,0,114,0, 
2,0x20,0x12,0,2,0x20,0x12,0,133,0, 
2,0x40,0x12,0,2,0x40,0x12,0,152,0, 
2,0x80,0x12,0,2,0x80,0x12,0,171,0, 
2,0x01,0x13,0,2,0x01,0x13,0,190,0, 
2,0x02,0x13,0,2,0x02,0x13,0,209,0, 
2,0x04,0x13,0,2,0x04,0x13,0,-48.876,18.5, 
2,0x08,0x13,0,2,0x08,0x13,0,-31.876,18.5, 
2,0x10,0x13,0,2,0x10,0x13,0,-14.25,18.5, 
2,0x20,0x13,0,2,0x20,0x13,0,4.75,18.5, 
2,0x40,0x13,0,2,0x40,0x13,0,23.75,18.5, 
2,0x80,0x13,0,2,0x80,0x13,0,42.75,18.5, 
3,0x01,0x12,0,3,0x01,0x12,0,61.75,18.5, 
3,0x02,0x12,0,3,0x02,0x12,0,80.75,18.5, 
3,0x04,0x12,0,3,0x04,0x12,0,99.75,18.5, 
3,0x08,0x12,0,3,0x08,0x12,0,118.75,18.5, 
3,0x10,0x12,0,3,0x10,0x12,0,137.75,18.5, 
3,0x20,0x12,0,3,0x20,0x12,0,156.75,18.5, 
3,0x40,0x12,0,3,0x40,0x12,0,175.75,18.5, 
3,0x80,0x12,0,3,0x80,0x12,0,193.374,18.5, 
3,0x01,0x13,0,3,0x01,0x13,0,-47.501,37, 
3,0x02,0x13,0,3,0x02,0x13,0,-23.751,37, 
3,0x04,0x13,0,3,0x04,0x13,0,-4.75,37, 
3,0x08,0x13,0,3,0x08,0x13,0,14.25,37, 
3,0x10,0x13,0,3,0x10,0x13,0,33.25,37, 
3,0x20,0x13,0,3,0x20,0x13,0,52.25,37, 
3,0x40,0x13,0,3,0x40,0x13,0,71.25,37, 
3,0x80,0x13,0,3,0x80,0x13,0,90.249,37, 
4,0x01,0x12,0,4,0x01,0x12,0,109.249,37, 
4,0x02,0x12,0,4,0x02,0x12,0,128.249,37, 
4,0x04,0x12,0,4,0x04,0x12,0,147.249,37, 
4,0x08,0x12,0,4,0x08,0x12,0,166.249,37, 
4,0x10,0x12,0,4,0x10,0x12,0,185.249,37, 
4,0x20,0x12,0,4,0x20,0x12,0,208.999,37, 
4,0x40,0x12,0,4,0x40,0x12,0,-47.501,55.5, 
4,0x80,0x12,0,4,0x80,0x12,0,-28.501,55.5, 
4,0x01,0x13,0,4,0x01,0x13,0,-9.501,55.5, 
4,0x02,0x13,0,4,0x02,0x13,0,11.874,55.5, 
4,0x04,0x13,0,4,0x04,0x13,0,33.249,55.5, 
4,0x08,0x13,0,4,0x08,0x13,0,71.249,55.5, 
4,0x10,0x13,0,4,0x10,0x13,0,109.249,55.5, 
4,0x20,0x13,0,4,0x20,0x13,0,130.624,55.5, 
4,0x40,0x13,0,4,0x40,0x13,0,151.999,55.5, 
4,0x80,0x13,0,4,0x80,0x13,0,210.374,18.5, 
5,0x01,0x12,0,5,0x01,0x12,0,170.999,55.5, 
5,0x02,0x12,0,5,0x02,0x12,0,210.374,18.5, 
5,0x04,0x12,0,5,0x04,0x12,0,189.999,59.741, 
5,0x08,0x12,0,5,0x08,0x12,0,208.999,55.5 
}};



/* KeyStorke Parameter Initlization */
void KeyBoardParameterInit(KeyBoard *kb, uint8_t ProjName[PROJ_NAME_LEN], uint8_t ButtonType, uint8_t Standard, ButtonPoint OriginalPoint, const Button *pBtn)
{
	//kb->ProN = ProjName;
	mymemcpy(kb->ProN,ProjName,sizeof(ProjName[PROJ_NAME_LEN]));
	kb->BtnTyp = ButtonType;
	kb->Stdx = Standard;
	kb->OrgP = OriginalPoint;
	//memcpy((kb->OrgP), pBtn, sizeof(Button));
	for(int i = BUTTON_NUM; i > 0; i--)
	{
				kb->Btn[i] 	= *pBtn++;
	}
}

void KeyBoardParameterPrint(const KeyBoard *kb)
{
//					printf("\r\nPrjI :%s", kbTemp.ProN);
	#ifdef FLOAT_FOMAT
	static uint8_t i;
	if(kb->BtnTyp == 1)//1:single 0:matrix
	{
		printf("Single Point \r\n");
    printf("Name:%s Standard:%d  ORG_X:%f ORG_Y:%f \r\n", kb->ProN, kb->Stdx, kb->OrgP.AxisX, kb->OrgP.AxisY);
    printf("DrvP_Single_Cs: %d DrvP_Single_Io: %d MCP23S17Port: %d \r\n",kb->Btn[0].Drv[0].MCP23S17Cs, kb->Btn[0].Drv[0].MCP23S17Io, kb->Btn[0].Drv[0].MCP23S17Port);   printf("\r\n");
		for(i = 0; i < BUTTON_NUM; i++)
    {
			printf("DrvP_M0_Cs: %d DrvP_M0_Io: %d MCP23S17_M0: %d \r\n", kb->Btn[i].Drv[0].MCP23S17Cs, kb->Btn[i].Drv[0].MCP23S17Io, kb->Btn[i].Drv[0].MCP23S17Port);
			printf("DrvP_M0_Cs: %d DrvP_M0_Io: %d MCP23S17_M0: %d \r\n", kb->Btn[i].Drv[1].MCP23S17Cs, kb->Btn[i].Drv[1].MCP23S17Io, kb->Btn[i].Drv[1].MCP23S17Port);
			printf("[%d]   ", i);       printf("DrvPx: %f  DrvPy: %f \r\n", kb->Btn[i].BtnC.AxisX, kb->Btn[i].BtnC.AxisY);
		}
	}
	else if(kb->BtnTyp == 0)
	{
		printf("Matrix Point \r\n");
		printf("Name:%s Standard:%d  ORG_X:%f ORG_Y:%f \r\n", kb->ProN, kb->Stdx, kb->OrgP.AxisX,kb->OrgP.AxisY);
    printf("\r\n");
    for(i = 0; i < BUTTON_NUM; i++)
    {
			printf("DrvP_M0_Cs: %d DrvP_M0_Io: %d MCP23S17_M0: %d \r\n", kb->Btn[i].Drv[0].MCP23S17Cs, kb->Btn[i].Drv[0].MCP23S17Io, kb->Btn[i].Drv[0].MCP23S17Port);
			printf("DrvP_M0_Cs: %d DrvP_M0_Io: %d MCP23S17_M0: %d \r\n", kb->Btn[i].Drv[1].MCP23S17Cs, kb->Btn[i].Drv[1].MCP23S17Io, kb->Btn[i].Drv[1].MCP23S17Port);
			printf("[%d]    ", i);       printf("DrvPx: %f  DrvPy: %f \r\n", kb->Btn[i].BtnC.AxisX, kb->Btn[i].BtnC.AxisY);
    }
	}	
	#else
	static uint8_t i;
	if(kb->BtnTyp)//1:single 0:matrix
	{
		printf("Single Point \r\n");
    printf("Name:%s Standard:%d  ORG_X:%d ORG_Y:%d \r\n", kb->ProN, kb->Stdx, kb->OrgP.AxisX,kb->OrgP.AxisY);
    printf("DrvP_Single_Cs: %d DrvP_Single_Io: %d MCP23S17Port: %d \r\n",kb->Btn[0].Drv[0].MCP23S17Cs, kb->Btn[0].Drv[0].MCP23S17Io, kb->Btn[0].Drv[0].MCP23S17Port);   printf("\r\n");
		for(i = 0; i < BUTTON_NUM; i++)
    {
			printf("DrvP_M0_Cs: %d DrvP_M0_Io: %d MCP23S17_M0: %d \r\n", kb->Btn[i].Drv[0].MCP23S17Cs, kb->Btn[i].Drv[0].MCP23S17Io, kb->Btn[i].Drv[0].MCP23S17Port);
			printf("DrvP_M0_Cs: %d DrvP_M0_Io: %d MCP23S17_M0: %d \r\n", kb->Btn[i].Drv[1].MCP23S17Cs, kb->Btn[i].Drv[1].MCP23S17Io, kb->Btn[i].Drv[1].MCP23S17Port);
			printf("[%d]   ", i);       printf("DrvPx: %d  DrvPy: %d \r\n", kb->Btn[i].BtnC.AxisX, kb->Btn[i].BtnC.AxisY);
		}
	}
	else
	{
		printf("Matrix Point \r\n");
		printf("Name:%s Standard:%d  ORG_X:%d ORG_Y:%d \r\n", kb->ProN, kb->Stdx, kb->OrgP.AxisX,kb->OrgP.AxisY);
    printf("\r\n");
    for(i = 0; i < BUTTON_NUM; i++)
    {
			printf("DrvP_M0_Cs: %d DrvP_M0_Io: %d MCP23S17_M0: %d \r\n", kb->Btn[i].Drv[0].MCP23S17Cs, kb->Btn[i].Drv[0].MCP23S17Io, kb->Btn[i].Drv[0].MCP23S17Port);
			printf("DrvP_M0_Cs: %d DrvP_M0_Io: %d MCP23S17_M0: %d \r\n", kb->Btn[i].Drv[1].MCP23S17Cs, kb->Btn[i].Drv[1].MCP23S17Io, kb->Btn[i].Drv[1].MCP23S17Port);
			printf("[%d]    ", i);       printf("DrvPx: %d  DrvPy: %d \r\n", kb->Btn[i].BtnC.AxisX, kb->Btn[i].BtnC.AxisY);
    }
	}
	#endif
	
//	printf("\r\n\r\nKbStandard:%d TypeButtonPoint:%d\r\n",sizeof(uint8_t),sizeof(TypeButtonPoint));
//	printf("ButtonPoint:%d DrvSinglePoint:%d\r\n",sizeof(ButtonPoint),sizeof(DrvSinglePoint));	
//	printf("Button:%d KeyBoard:%d\r\n",sizeof(Button),sizeof(KeyBoard));
//	printf("uint8_t:%d uint16_t:%d\r\n",sizeof(uint8_t),sizeof(uint16_t));
//	printf("uint32_t:%d float:%d\r\n\r\n",sizeof(uint32_t),sizeof(float));
}






void MCP23S17_Test(void)
{
	static uint16_t i;
	
	for(i = 0; i < BUTTON_NUM; i++)
	{

//			EXIO_WriteBits(MCP1,EXIOA,EXIO_Pin_All,0);
//			HAL_Delay(200);
//			EXIO_WriteBits(MCP1,EXIOA,EXIO_Pin_All,1);
//			HAL_Delay(200);
			if(kb_X13_ANSI.BtnTyp)//1:single 0:matrix
			{
				EXIO_WriteBits(
								kb_X13_ANSI.Btn[i].Drv[0].MCP23S17Cs, 
								kb_X13_ANSI.Btn[i].Drv[0].MCP23S17Port,//EXIO_Pin_All,1);
								kb_X13_ANSI.Btn[i].Drv[0].MCP23S17Io, 1);
	//			HAL_Delay(100);
				delay_us(100000);
				
							EXIO_WriteBits(
								kb_X13_ANSI.Btn[i].Drv[0].MCP23S17Cs, 
								kb_X13_ANSI.Btn[i].Drv[0].MCP23S17Port,//EXIO_Pin_All,0);
								kb_X13_ANSI.Btn[i].Drv[0].MCP23S17Io, 0);
	//			HAL_Delay(100);
				delay_us(100000);
				if((i + 8) % 8 == 7 && i!=BUTTON_NUM)	
				{
						EXIO_WriteBits(
						kb_X13_ANSI.Btn[i].Drv[0].MCP23S17Cs, 
						kb_X13_ANSI.Btn[i].Drv[0].MCP23S17Port,//EXIO_Pin_All,0);
						kb_X13_ANSI.Btn[i].Drv[0].MCP23S17Io, 0);	
				}
			}
			else/* Matrix */
			{
					EXIO_WriteBits(/*X-Axis*/
												kb_X13_ANSI.Btn[i].Drv[0].MCP23S17Cs, 
												kb_X13_ANSI.Btn[i].Drv[0].MCP23S17Port,
												kb_X13_ANSI.Btn[i].Drv[0].MCP23S17Io, 0);
					EXIO_WriteBits(/*Y-Axis*/
										kb_X13_ANSI.Btn[i].Drv[1].MCP23S17Cs, 
										kb_X13_ANSI.Btn[i].Drv[1].MCP23S17Port,
										kb_X13_ANSI.Btn[i].Drv[1].MCP23S17Io, 0);
				Tog_LED();
				
				EXIO_WriteBits(MCP1,EXIOA,EXIO_Pin_All,0);
				Tog_LED();
				EXIO_WriteBits(MCP1,EXIOA,EXIO_Pin_All,1);
				Tog_LED();
			}		
	}
}

#include "app_Communication.h"
#include "app_main.h"
#include "app_MotionControl.h"
void MachineAging(void)
{
	static uint16_t i;
	ButtonPoint Temp;
	while(1)
	{
		for(i = 0; i < BUTTON_NUM; i++)
		{
				Temp.AxisX = CurrentBoard.Btn[i].BtnC.AxisX / 4.0f;
				Temp.AxisY = CurrentBoard.Btn[i].BtnC.AxisY / 4.0f;//实际配置为 8 MicroStep
				CoordinateMoveAbsolute(Temp.AxisX, tAlpha1, tAlpha2,(uint32_t)(tSetOmega*2*3.14*5.0), Temp.AxisY,tAlpha1, tAlpha2,(uint32_t)(tSetOmega*2*3.14*5.0));
				if(kb_X13_ANSI.BtnTyp)//1:single 0:matrix
				{

					EXIO_WriteBits(
									kb_X13_ANSI.Btn[i].Drv[0].MCP23S17Cs, 
									kb_X13_ANSI.Btn[i].Drv[0].MCP23S17Port,//EXIO_Pin_All,1);
									kb_X13_ANSI.Btn[i].Drv[0].MCP23S17Io, 1);
		//			HAL_Delay(100);
					delay_ms(100);
					
								EXIO_WriteBits(
									kb_X13_ANSI.Btn[i].Drv[0].MCP23S17Cs, 
									kb_X13_ANSI.Btn[i].Drv[0].MCP23S17Port,//EXIO_Pin_All,0);
									kb_X13_ANSI.Btn[i].Drv[0].MCP23S17Io, 0);
		//			HAL_Delay(100);
					delay_ms(100);
					if((i + 8) % 8 == 7 && i!=BUTTON_NUM)	
					{
							EXIO_WriteBits(
							kb_X13_ANSI.Btn[i].Drv[0].MCP23S17Cs, 
							kb_X13_ANSI.Btn[i].Drv[0].MCP23S17Port,//EXIO_Pin_All,0);
							kb_X13_ANSI.Btn[i].Drv[0].MCP23S17Io, 0);	
					}
				}
				else/* Matrix */
				{
						EXIO_WriteBits(/*X-Axis*/
													kb_X13_ANSI.Btn[i].Drv[0].MCP23S17Cs, 
													kb_X13_ANSI.Btn[i].Drv[0].MCP23S17Port,
													kb_X13_ANSI.Btn[i].Drv[0].MCP23S17Io, 0);
						EXIO_WriteBits(/*Y-Axis*/
											kb_X13_ANSI.Btn[i].Drv[1].MCP23S17Cs, 
											kb_X13_ANSI.Btn[i].Drv[1].MCP23S17Port,
											kb_X13_ANSI.Btn[i].Drv[1].MCP23S17Io, 0);
		/************************此处可能存在BUG*********************************/
	//				Tog_LED();
	//				
	//				EXIO_WriteBits(MCP1,EXIOA,EXIO_Pin_All,0);
	//				Tog_LED();
	//				EXIO_WriteBits(MCP1,EXIOA,EXIO_Pin_All,1);
	//				Tog_LED();
				}		
		}
	}
}

void MCP23S17Init(void)
{
	/*       MCP23S17     */
	MCP23S17_Init(MCP1,&hspi2,MCP23S17_CS0_GPIO_Port,MCP23S17_CS0_Pin);
	MCP23S17_Init(MCP2,&hspi2,MCP23S17_CS1_GPIO_Port,MCP23S17_CS1_Pin);
	MCP23S17_Init(MCP3,&hspi2,MCP23S17_CS2_GPIO_Port,MCP23S17_CS2_Pin);
	MCP23S17_Init(MCP4,&hspi2,MCP23S17_CS3_GPIO_Port,MCP23S17_CS3_Pin);
	MCP23S17_Init(MCP5,&hspi2,MCP23S17_CS4_GPIO_Port,MCP23S17_CS4_Pin);
	MCP23S17_Init(MCP6,&hspi2,MCP23S17_CS5_GPIO_Port,MCP23S17_CS5_Pin);

	EXIO_OutputConfig(MCP1,EXIOA,EXIO_Pin_All);
	EXIO_OutputConfig(MCP1,EXIOB,EXIO_Pin_All);
	EXIO_OutputConfig(MCP2,EXIOA,EXIO_Pin_All);
	EXIO_OutputConfig(MCP2,EXIOB,EXIO_Pin_All);
	EXIO_OutputConfig(MCP3,EXIOA,EXIO_Pin_All);
	EXIO_OutputConfig(MCP3,EXIOB,EXIO_Pin_All);
	EXIO_OutputConfig(MCP4,EXIOA,EXIO_Pin_All);
	EXIO_OutputConfig(MCP4,EXIOB,EXIO_Pin_All);
	EXIO_OutputConfig(MCP5,EXIOA,EXIO_Pin_All);
	EXIO_OutputConfig(MCP5,EXIOB,EXIO_Pin_All);
	EXIO_OutputConfig(MCP6,EXIOA,EXIO_Pin_All);
	EXIO_OutputConfig(MCP6,EXIOB,EXIO_Pin_All);


	EXIO_WriteBits(MCP1,EXIOA,EXIO_Pin_All,0);
	EXIO_WriteBits(MCP1,EXIOB,EXIO_Pin_All,0);
	EXIO_WriteBits(MCP2,EXIOA,EXIO_Pin_All,0);
	EXIO_WriteBits(MCP2,EXIOB,EXIO_Pin_All,0);
	EXIO_WriteBits(MCP3,EXIOA,EXIO_Pin_All,0);
	EXIO_WriteBits(MCP3,EXIOB,EXIO_Pin_All,0);
	EXIO_WriteBits(MCP4,EXIOA,EXIO_Pin_All,0);
	EXIO_WriteBits(MCP4,EXIOB,EXIO_Pin_All,0);
	EXIO_WriteBits(MCP5,EXIOA,EXIO_Pin_All,0);
	EXIO_WriteBits(MCP5,EXIOB,EXIO_Pin_All,0);
	EXIO_WriteBits(MCP6,EXIOA,EXIO_Pin_All,0);
	EXIO_WriteBits(MCP6,EXIOB,EXIO_Pin_All,0);
}


