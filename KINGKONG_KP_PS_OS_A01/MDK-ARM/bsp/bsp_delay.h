/*
 * bsp_delay.h
 *
 * Created on: 2017Äê11ÔÂ14ÈÕ
 * Author: Enzo
 */
#ifndef BSP_DELAY_H_
#define BSP_DELAY_H_

#include "stdint.h"

//#define Tog_LED() {HAL_GPIO_WritePin(LED0_GPIO_Port, LED0_Pin, GPIO_PIN_SET);HAL_Delay(200);	HAL_GPIO_WritePin(LED0_GPIO_Port, LED0_Pin, GPIO_PIN_RESET);HAL_Delay(200);}
void delay_us(uint32_t nUs) ;
void delay_ms(uint32_t nUs) ;
#endif



