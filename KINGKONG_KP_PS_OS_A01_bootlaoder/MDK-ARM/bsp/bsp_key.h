#ifndef _BSP_KEY_H_
#define _BSP_KEY_H_

#include "tim.h"
#include <stdbool.h>
#include "bsp_PinsReMap.h"

#define PWM_CYCLES 1440-1

/*LEDָʾ��  �ߵ�ƽ��*/
#define Led1Port   GPIO_Pin_7  		 //LED1�������ź�
#define Led1Con    PA7						 //LED1����

#define Led2Port   GPIO_Pin_13  		 //LED2�������ź�
#define Led2Con    PC13						 //LED1����

#define Led3Port   GPIO_Pin_14  		 //LED3�������ź�
#define Led3Con    PC14						 //LED1����

#define Led4Port   GPIO_Pin_15  		 //LED4�������ź�
#define Led4Con    PC15						 //LED1����

#define KEY_YES (0u)
#define KEY_NO  (1u) 

#define LED_ON  (1u)
#define LED_OFF (0u)

#define Volt_Adj_Mode (1u)   //����ģʽ
#define Freq_Adj_Mode (2u)   //ȫ��ģʽ

/*KEY����  �͵�ƽ��Ч*/
#define Key1Port      GPIO_Pin_0       //KEY1�������ź�
#define Key1In        rPB0							 //KEY1����

#define Key2Port      GPIO_Pin_1       //KEY1�������ź�
#define Key2In        rPB1							 //KEY1����

#define Key3Port      GPIO_Pin_2       //KEY1�������ź�
#define Key3In        rPB2							 //KEY1����

//#define Key4Port      GPIO_Pin_6       //KEY1�������ź�
//#define Key4In        rPA6							 //KEY1����

typedef struct
{
	bool Key_En;             //����ʹ��
	uint8_t Key_Mode;          //����ģʽѡ�� 
	void (*Key_Scan)( void );	 
}Key_ST;

extern Key_ST Key_st;
#endif//_BSP_KEY_H_
