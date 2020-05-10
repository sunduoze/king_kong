/*
 * app_Main.h
 *
 * Created on: 2017年11月14日
 * Author: Enzo
 */
#ifndef APP_MAIN_H_
#define APP_MAIN_H_

#include "stdint.h"

//#define ALIGN 

#define BUTTON_NUM 		84
#define PROJ_NAME_LEN 10//Please Don't Change

#define FLASH_SAVE_ADDR  0X08020000//0X08020000 //起始地址从128kB/(sum=256k)	//设置FLASH 保存地址(必须为偶数，且其值要大于本代码所占用FLASH的大小+0X08000000)
/*Flash = Code + Ro-data = 11336 +500 约 11.5kB*/


#define FLOAT_FOMAT
typedef float TypeButtonPoint;//the type of ButtonPoint

typedef struct{/*ButtonPoint*/
	TypeButtonPoint AxisX;
	TypeButtonPoint AxisY;
}ButtonPoint;//2* int = 8 Byte

typedef struct{/*DrvSinglePoint*/
	uint8_t MCP23S17Cs;     //IO Expand Chip CS Pin
	uint8_t MCP23S17Io;     //IO Expand Chip Io     [0:7]
	uint8_t MCP23S17Port;   //IO Expand Chip Port   0:A 1:B
	uint8_t AlignByteNC;		//Only for Data Storge Align
}DrvSinglePoint;//1*3 + 1 = 8 Byte

typedef struct{/*Button*/
	DrvSinglePoint  Drv[2];  //Point Driver   Include 2 Single Point Info
                           // MP   0:X-Axis    1:Y-Axis
	ButtonPoint     BtnC;	   //KeyBoard Button Coordinate
}Button;//4*2 + 8 = 16 Byte

#ifdef ALIGN 
#pragma pack(1)
#endif
typedef struct{/*KeyBoard*/
/*10*/uint8_t          ProN[PROJ_NAME_LEN];  	//Project Name
/*1 */uint8_t					 BtnTyp;								//Button Type 				'M':Matrix 'S':Single
/*1 */uint8_t 			 	 Stdx;	    						//KeyBoard Standard 	ANSI:'A' ISO:'I' JIS:'J'
/*8 */ButtonPoint	     OrgP;	   							//Original Point Coordinate
/*16*/Button     			 Btn[BUTTON_NUM];   		//ButtonInfo  Include Button name & DrvPoint & Coordinate
}KeyBoard;/*36 Byte*/
#ifdef ALIGN 
#pragma pack()
#endif

extern void MCP23S17Init(void);
extern void MachineAging(void);
extern KeyBoard kb_X13_ANSI;

extern void MCP23S17_Test(void);
extern void KeyBoardParameterPrint(const KeyBoard *kb);

extern void Write2Flash(KeyBoard *kbTemp);
extern void ParaStor(uint8_t Sta);
extern uint8_t Extract_Parameter(uint8_t *inputStr,void *tarNum, uint8_t ParaType,uint8_t ParaNum,uint8_t Separator);
#endif /*APP_MAIN_H_*/



