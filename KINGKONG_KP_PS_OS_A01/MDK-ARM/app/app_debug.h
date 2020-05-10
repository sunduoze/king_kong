/*
 * app_debug.h
 *
 * Created on: 2018Äê2ÔÂ27ÈÕ
 * Author: Enzo
 */
#ifndef APP_DEBUG_H_
#define APP_DEBUG_H_

#include "stm32f1xx_hal.h"

#include "cmsis_os.h"


//#define CALI_LIST_MAX 10
extern void iwdgTaskThreadCreate(osPriority taskPriority);
extern void psTaskThreadCreate(osPriority taskPriority);
extern void uartTaskThreadCreate(osPriority taskPriority);

#endif /*APP_DEBUG_H_*/


