/*
 * app_Main.h
 *
 *  Created on: 2017Äê11ÔÂ14ÈÕ
 *      Author: Enzo
 */
#ifndef APP_MAIN_H_
#define APP_MAIN_H_

#include "stdint.h"



#define BUTTON_NUM 84
typedef int TypeButtonPoint;//the type of ButtonPoint

typedef enum{/*Standard*/
	ANSI,
	ISO,
	JIS
}KbStandard;
/*
typedef enum{/*Project*//*
	X13,
	X10,
	X8,W
	X5,
	X1,
	X_1,
	X_2,
	X_3,
	X_4
}KbProject;
*/

typedef struct{/*ButtonPoint*/
	TypeButtonPoint AxisX;
	TypeButtonPoint AxisY;
}ButtonPoint;

typedef struct{/*DrvSinglePoint*/
	uint8_t MCP23S17Cs;     //IO Expand Chip CS Pin
	uint8_t MCP23S17Io;     //IO Expand Chip Io     [0:7]
	uint8_t MCP23S17Port;   //IO Expand Chip Port   0:A 1:B
}DrvSinglePoint;

typedef struct{/*Button*/
	DrvSinglePoint  Drv[2];  //Point Driver   Include 2 Single Point Info
                           // MP   0:X-Axis    1:Y-Axis
	ButtonPoint     BtnC;	   //KeyBoard Button Coordinate
}Button;

#ifdef ALIGN
#pragma pack(1)
#endif
typedef struct{/*KeyBoard*/
	uint8_t          *ProN;  //Project Name
	uint8_t					 BtnTyp;		//Button Type 				1:single 0:matrix
	KbStandard 			 Stdx;	//KeyBoard Standard 	    Eg. AINSI ISO JIS
	ButtonPoint	     OrgP;	//Original Point Coordinate
	Button     			 Btn[BUTTON_NUM];   //ButtonInfo  Include Button name & DrvPoint & Coodinate
}KeyBoard;
#ifdef ALIGN
#pragma pack()
#endif


extern KeyBoard kb_X13_ANSI;



#endif /*APP_MAIN_H_*/



