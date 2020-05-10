/*
 * app_MotionControl.h
 *
 * Created on: 2017年11月14日
 * Author: Enzo
 */
#ifndef APP_MOTIONCONTROL_H_
#define APP_MOTIONCONTROL_H_

#include "stm32f1xx_hal.h"
#include "stdint.h"

#define X_AXIS_SENSOR_LIM_N() 		HAL_GPIO_ReadPin(X_AXIS_SENSOR_LIM_N_GPIO_Port, X_AXIS_SENSOR_LIM_N_Pin)
#define X_AXIS_SENSOR_LIM_P() 		HAL_GPIO_ReadPin(X_AXIS_SENSOR_LIM_P_GPIO_Port, X_AXIS_SENSOR_LIM_P_Pin)
#define X_AXIS_SENSOR_ORIGINAL() 	HAL_GPIO_ReadPin(X_AXIS_SENSOR_ORIGINAL_GPIO_Port, X_AXIS_SENSOR_ORIGINAL_Pin)

#define DIR_DELAY()								delay_us(1000)
#define SEEKFAST_DELAY_TIME				760//delay   <300us 震动 现在500也震动
#define SEEKSLOW_DELAY_TIME				900//

extern void X_AxixMove(__IO float Length, __IO uint32_t Alpha1, __IO uint32_t Alpha2, __IO uint32_t Speed);
extern void Y_AxixMove(__IO float Length, __IO uint32_t Alpha1, __IO uint32_t Alpha2, __IO uint32_t Speed);
extern void X_AxisMoveAbsolute(__IO int32_t PositionDesire,__IO uint32_t Alpha1, __IO uint32_t Alpha2,__IO uint32_t Omega);
extern void Y_AxisMoveAbsolute(__IO int32_t PositionDesire,__IO uint32_t Alpha1, __IO uint32_t Alpha2,__IO uint32_t Omega);
extern uint8_t SearchOrg_X_Axis(__IO int32_t Omega,__IO uint32_t Alpha1, __IO uint32_t Alpha2);
extern uint8_t SearchOrg_Y_Axis(__IO int32_t Omega,__IO uint32_t Alpha1, __IO uint32_t Alpha2);

extern void CoordinateMoveAbsolute(__IO int32_t X_Position,__IO uint32_t X_Alpha1, __IO uint32_t X_Alpha2,__IO uint32_t X_Omega,
																	 __IO int32_t Y_Position,__IO uint32_t Y_Alpha1, __IO uint32_t Y_Alpha2,__IO uint32_t Y_Omega);
#endif /*APP_MOTIONCONTROL_H_*/



