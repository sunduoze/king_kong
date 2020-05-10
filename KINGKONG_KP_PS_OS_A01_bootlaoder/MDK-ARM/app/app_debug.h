/*
 * app_debug.h
 *
 * Created on: 2018Äê2ÔÂ27ÈÕ
 * Author: Enzo
 */
#ifndef APP_DEBUG_H_
#define APP_DEBUG_H_

#include "stm32f1xx_hal.h"

//#include "cmsis_os.h"


//#define CALI_LIST_MAX 10
//extern void iwdgTaskThreadCreate(osPriority taskPriority);
//extern void psSetTaskThreadCreate(osPriority taskPriority);
//extern void debugTaskThreadCreate(osPriority taskPriority);

extern uint16_t VoltGeneAlgorithm(float fK, float fB, float VoutVoltage);
extern void HardWareInit(void);
#endif /*APP_DEBUG_H_*/


