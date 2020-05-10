/*
 * task_uart.h
 *
 * Created on: 2018Äê2ÔÂ27ÈÕ
 * Author: Enzo
 */
#ifndef TASK_UART_H_
#define TASK_UART_H_

#include "stdint.h"
#include "stm32f1xx_hal.h"
#include "bsp_uart.h"

#include "string.h"
extern __IO  uint8_t UART_RxCallback_Flag;

extern void UART_IdleRxCallback(UART_HandleTypeDef *huart);
extern void receive_data_handel(void);
#endif /*TASK_UART_H_*/


