/*
 * bsp_uart.h
 *
 * Created on: 2018Äê2ÔÂ27ÈÕ
 * Author: Enzo
 */
#ifndef BSP_UART_H_
#define BSP_UART_H_

#include "stdint.h"
#include "stdarg.h"
#include "stm32f1xx_hal.h"
#include "usart.h"


#ifdef RTT_MASTER
	#include "SEGGER_RTT.h"
#endif
	

enum
{
	UPPER_COM_Flag,
	PWR0204_1_Flag,
	PWR0204_2_Flag,
	DAQ0010_1_Flag,//DMM
	DAQ3003_1_Flag,//LCR
	Clear_Flag
};
#define UPPER_COM_HUART huart1
#define PWR0204_1_HUART huart2
#define PWR0204_2_HUART huart3 
#define DAQ0010_1_HUART huart4
#define DAQ3003_1_HUART huart5//¼¦Àß MD


#define UPPER_COM_BUF_LEN	36
#define PWR0204_1_BUF_LEN 36
#define PWR0204_2_BUF_LEN 36 
#define DAQ0010_1_BUF_LEN 36
#define DAQ3003_1_BUF_LEN 36

#define UPPER_COM_BUF_CLR	memset(&arrUPPER_COM_Buf,0,UPPER_COM_BUF_LEN);
#define PWR0204_1_BUF_CLR	memset(&arrPWR0204_1_Buf,0,PWR0204_1_BUF_LEN);
#define PWR0204_2_BUF_CLR	memset(&arrPWR0204_2_Buf,0,PWR0204_2_BUF_LEN);
#define DAQ0010_1_BUF_CLR	memset(&arrDAQ0010_1_Buf,0,DAQ0010_1_BUF_LEN);
#define DAQ3003_1_BUF_CLR	memset(&arrDAQ3003_1_Buf,0,DAQ3003_1_BUF_LEN);


extern __IO uint8_t arrUPPER_COM_Buf[UPPER_COM_BUF_LEN];
extern __IO uint8_t arrPWR0204_1_Buf[PWR0204_1_BUF_LEN];
extern __IO uint8_t arrPWR0204_2_Buf[PWR0204_2_BUF_LEN];
extern __IO uint8_t arrDAQ0010_1_Buf[DAQ0010_1_BUF_LEN];
extern __IO uint8_t arrDAQ3003_1_Buf[DAQ3003_1_BUF_LEN];

extern uint16_t arrUPPER_COM_RX_STA;      
extern uint16_t arrPWR0204_1_RX_STA;    
extern uint16_t arrPWR0204_2_RX_STA;     
extern uint16_t arrDAQ0010_1_RX_STA;    
extern uint16_t arrDAQ3003_1_RX_STA;    


extern void REG_UART1_Init(uint32_t band);
extern void REG_UART2_Init(uint32_t band);	
extern void REG_UART3_Init(uint32_t band);
extern void REG_UART4_Init(uint32_t band);
extern void REG_UART5_Init(uint32_t band);

extern void HAL_UART_All_Init(void);
extern void UART_Printf(UART_HandleTypeDef *huart, const char* fmt, ...);
extern HAL_StatusTypeDef LL_UART_Receive_IT(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size);
extern void LL_UsartIdleHanlder(UART_HandleTypeDef *huart,uint16_t Size);
extern uint8_t Extract_Parameter(uint8_t *inputStr,void *tarNum, uint8_t ParaType,uint8_t ParaNum,uint8_t Separator);

#endif /*BSP_UART_H_*/


