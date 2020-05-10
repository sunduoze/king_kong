/*
 * app_main.c
 *
 * Created on: 2017年11月14日
 * Author: Enzo
 */

#include "app_main.h"
//#include "stm32f1xx_hal.h"
//#include "spi.h"
//#include "MCP23S17.h"
//#include "bsp_delay.h"
//#include "stm_flash.h"

const uint8_t TEXT_Buffer[]={"STM32 FLASH TEST"};
#define SIZE sizeof(TEXT_Buffer)	 	//数组长度
uint8_t datatemp[SIZE];

#define FLASH_SAVE_ADDR  0X08020000 //起始地址从128kB/256K	//设置FLASH 保存地址(必须为偶数，且其值要大于本代码所占用FLASH的大小+0X08000000)
/*Flash = Code + Ro-data = 11336 +500 约 11.5kB*/


/*
void Stm_flashW(void)
{
	STMFLASH_Write(FLASH_SAVE_ADDR,(uint16_t*)TEXT_Buffer,SIZE);
}


void Stm_flashR(void)
{
	STMFLASH_Read(FLASH_SAVE_ADDR,(uint16_t*)datatemp,SIZE);
	printf("StorgeInfo:%s",datatemp);
}


void Test1(void)
{

	KeyBoardParameterPrint(&kb_X13_ANSI);
}*/


KeyBoard kb_X13_ANSI = {
/*ProN*/(uint8_t *)"X13 ANSI Single KeyStroke",
/*BtnTyp*/1,
/*Stdx*/ANSI,
/*OrgP*/{123,321},
/*Btn */{
/*
IO Expand Chip CS Pin [1:8]
IO Expand Chip Io     [0:7]
IO Expand Chip Part   0:A 1:B
____________________________________________
	MP_x:	Matrix Point Driver x-Axis
				or Single Point Deiver
	MP_y:	Matrix Point Driver y-Axis
	BP_X:	the X Axis Coordinate of ButtonPoint
	BP_Y:	the Y Axis Coordinate of ButtonPoint
____________________________________________
  MP_x          MP_y    BP_X BP_Y
  |               |      |    |
----------- ----------- --- ----					*/
0,0x01,0x12,0,0x01,0x12,824,987,
0,0x02,0x12,0,0x02,0x12,678,80,
0,0x04,0x12,0,0x04,0x12,329,573,
0,0x08,0x12,0,0x08,0x12,260,659,
0,0x10,0x12,0,0x10,0x12,659,317,
0,0x20,0x12,0,0x20,0x12,150,900,
0,0x40,0x12,0,0x40,0x12,49,393,
0,0x80,0x12,0,0x80,0x12,752,67, //7
0,0x01,0x13,0,0x01,0x13,707,620,
0,0x02,0x13,0,0x02,0x13,126,418,
0,0x04,0x13,0,0x04,0x13,447,18,
0,0x08,0x13,0,0x08,0x13,565,429,
0,0x10,0x13,0,0x10,0x13,477,33,
0,0x20,0x13,0,0x20,0x13,756,173,
0,0x40,0x13,0,0x40,0x13,338,289,
0,0x80,0x13,0,0x80,0x13,986,448,
1,0x01,0x12,1,0x01,0x12,584,415,
1,0x02,0x12,1,0x02,0x12,283,699,
1,0x04,0x12,1,0x04,0x12,829,777,
1,0x08,0x12,1,0x08,0x12,25,269,
1,0x10,0x12,1,0x10,0x12,166,92,
1,0x20,0x12,1,0x20,0x12,586,187,
1,0x40,0x12,1,0x40,0x12,917,445,
1,0x80,0x12,1,0x80,0x12,20,769,
1,0x01,0x13,1,0x01,0x13,510,505,
1,0x02,0x13,1,0x02,0x13,517,721,
1,0x04,0x13,1,0x04,0x13,206,18,
1,0x08,0x13,1,0x08,0x13,678,631,
1,0x10,0x13,1,0x10,0x13,272,863,
1,0x20,0x13,1,0x20,0x13,250,65,
1,0x40,0x13,1,0x40,0x13,603,682,
1,0x80,0x13,1,0x80,0x13,658,156,
2,0x01,0x12,2,0x01,0x12,413,240,
2,0x02,0x12,2,0x02,0x12,885,672,
2,0x04,0x12,2,0x04,0x12,564,807,
2,0x08,0x12,2,0x08,0x12,512,490,
2,0x10,0x12,2,0x10,0x12,403,21,
2,0x20,0x12,2,0x20,0x12,998,627,
2,0x40,0x12,2,0x40,0x12,635,932,
2,0x80,0x12,2,0x80,0x12,998,465,
2,0x01,0x13,2,0x01,0x13,695,351,
2,0x02,0x13,2,0x02,0x13,760,805,
2,0x04,0x13,2,0x04,0x13,715,617,
2,0x08,0x13,2,0x08,0x13,351,380,
2,0x10,0x13,2,0x10,0x13,251,27,
2,0x20,0x13,2,0x20,0x13,567,831,
2,0x40,0x13,2,0x40,0x13,313,382,
2,0x80,0x13,2,0x80,0x13,994,354,
3,0x01,0x12,3,0x01,0x12,402,505,
3,0x02,0x12,3,0x02,0x12,667,819,
3,0x04,0x12,3,0x04,0x12,151,897,
3,0x08,0x12,3,0x08,0x12,77,924,
3,0x10,0x12,3,0x10,0x12,693,219,
3,0x20,0x12,3,0x20,0x12,237,788,
3,0x40,0x12,3,0x40,0x12,285,10,
3,0x80,0x12,3,0x80,0x12,505,157,
3,0x01,0x13,3,0x01,0x13,338,91,
3,0x02,0x13,3,0x02,0x13,633,356,
3,0x04,0x13,3,0x04,0x13,732,84,
3,0x08,0x13,3,0x08,0x13,714,732,
3,0x10,0x13,3,0x10,0x13,746,815,
3,0x20,0x13,3,0x20,0x13,487,913,
3,0x40,0x13,3,0x40,0x13,191,228,
3,0x80,0x13,3,0x80,0x13,715,838,
4,0x01,0x12,4,0x01,0x12,628,685,
4,0x02,0x12,4,0x02,0x12,261,419,
4,0x04,0x12,4,0x04,0x12,887,589,
4,0x08,0x12,4,0x08,0x12,371,367,
4,0x10,0x12,4,0x10,0x12,572,710,
4,0x20,0x12,4,0x20,0x12,482,490,
4,0x40,0x12,4,0x40,0x12,924,704,
4,0x80,0x12,4,0x80,0x12,851,749,
4,0x01,0x13,4,0x01,0x13,76,843,
4,0x02,0x13,4,0x02,0x13,889,662,
4,0x04,0x13,4,0x04,0x13,551,287,
4,0x08,0x13,4,0x08,0x13,756,820,
4,0x10,0x13,4,0x10,0x13,455,351,
4,0x20,0x13,4,0x20,0x13,544,910,
4,0x40,0x13,4,0x40,0x13,593,43,
4,0x80,0x13,4,0x80,0x13,361,923,
5,0x01,0x12,5,0x01,0x12,131,335,
5,0x02,0x12,5,0x02,0x12,952,533,
5,0x04,0x12,5,0x04,0x12,412,454,
5,0x08,0x12,5,0x08,0x12,984,914

}};


//typedef struct{/*KeyBoard*/
//	uint8_t          ProN[20];  //Project Name
//	uint8_t					 BtnTyp;		//Button Type 				1:single 0:matrix
//	KbProject				 Proj;	//KeyBoard Project		    Eg. X13 ...
//	KbStandard 			 Stdx;	//KeyBoard Standard 	    Eg. AINSI ISO JIS
//	ButtonPoint	     OrgP;	//Original Point Coordinate
//	Button     			 Btn[BUTTON_NUM];   //ButtonInfo  Include Button name & DrvPoint & Coodinate
//}KeyBoard;

/* KeyStorke Parameter Initlization */
void KeyBoardParameterInit(KeyBoard *kb, uint8_t *ProjName, uint8_t ButtonType, KbStandard Standard, ButtonPoint OriginalPoint, const Button *pBtn)
{
    static uint8_t i;
	kb->ProN = ProjName;
	kb->BtnTyp = ButtonType;
	kb->Stdx = Standard;
	kb->OrgP = OriginalPoint;
	//memcpy((kb->OrgP), pBtn, sizeof(Button));
	for( i = BUTTON_NUM; i > 0; i--)
	{
				kb->Btn[i] 	= *pBtn++;
	}
}

void KeyBoardParameterPrint(KeyBoard *kb)
{
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
			printf("%d     ", i);       printf("DrvPx: %d  DrvPy: %d \r\n", kb->Btn[i].BtnC.AxisX, kb->Btn[i].BtnC.AxisY);
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
			printf("%d     ", i);       printf("DrvPx: %d  DrvPy: %d \r\n", kb->Btn[i].BtnC.AxisX, kb->Btn[i].BtnC.AxisY);
    }
	}
}



