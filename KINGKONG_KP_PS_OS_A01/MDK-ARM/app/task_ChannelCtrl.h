/*
 * task_ChannelCtrl.h
 *
 * Created on: 2018Äê2ÔÂ27ÈÕ
 * Author: Enzo
 */
#ifndef TASK_CHANNELCTRL_H_
#define TASK_CHANNELCTRL_H_

#include "stdint.h"
#include "stm32f1xx_hal.h"

#include "bsp_stp16cp05.h"
#include "bsp_CAT9555_1.h"


extern void ReadTestPoint(uint16_t ReadData,uint8_t ControlBit);   //0XA001

#endif /*TASK_CHANNELCTRL_H_*/


