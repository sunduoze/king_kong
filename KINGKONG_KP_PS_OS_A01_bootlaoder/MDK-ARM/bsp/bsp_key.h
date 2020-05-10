#ifndef _BSP_KEY_H_
#define _BSP_KEY_H_

#include "tim.h"
#include <stdbool.h>
#include "bsp_PinsReMap.h"

#define PWM_CYCLES 1440-1

/*LED指示灯  高电平亮*/
#define Led1Port   GPIO_Pin_7  		 //LED1控制引脚号
#define Led1Con    PA7						 //LED1控制

#define Led2Port   GPIO_Pin_13  		 //LED2控制引脚号
#define Led2Con    PC13						 //LED1控制

#define Led3Port   GPIO_Pin_14  		 //LED3控制引脚号
#define Led3Con    PC14						 //LED1控制

#define Led4Port   GPIO_Pin_15  		 //LED4控制引脚号
#define Led4Con    PC15						 //LED1控制

#define KEY_YES (0u)
#define KEY_NO  (1u) 

#define LED_ON  (1u)
#define LED_OFF (0u)

#define Volt_Adj_Mode (1u)   //半桥模式
#define Freq_Adj_Mode (2u)   //全桥模式

/*KEY输入  低电平有效*/
#define Key1Port      GPIO_Pin_0       //KEY1输入引脚号
#define Key1In        rPB0							 //KEY1输入

#define Key2Port      GPIO_Pin_1       //KEY1输入引脚号
#define Key2In        rPB1							 //KEY1输入

#define Key3Port      GPIO_Pin_2       //KEY1输入引脚号
#define Key3In        rPB2							 //KEY1输入

//#define Key4Port      GPIO_Pin_6       //KEY1输入引脚号
//#define Key4In        rPA6							 //KEY1输入

typedef struct
{
	bool Key_En;             //按键使能
	uint8_t Key_Mode;          //按键模式选择 
	void (*Key_Scan)( void );	 
}Key_ST;

extern Key_ST Key_st;
#endif//_BSP_KEY_H_
