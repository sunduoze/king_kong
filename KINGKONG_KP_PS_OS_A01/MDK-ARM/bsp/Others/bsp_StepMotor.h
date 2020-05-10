#ifndef __BSP_STEPMOTOR_H__
#define __BSP_STEPMOTOR_H__



#include "stm32f1xx_hal.h"
#include "tim.h"
#include "bsp_delay.h"


#define htimStepMotor htim1
#define STEPMOTOR_TIMx							TIM1
#define STEPMOTOR_TIM_CHANNELn    	TIM_CHANNEL_1
#define STEPMOTOR_TIM_IT_CCx 				TIM_IT_CC1
#define STEPMOTOR_TIM_FLAG_CCx     	TIM_FLAG_CC1
#define STEPMOTOR_TIMx_IRQHandler  	TIM1_CC_IRQHandler

#define STEPMOTOR_TIM_PRESCALER    (36-1)//35  144->250kHz  72->500kHz 36->500kHz 16->604kHz

#define LIM_POS_LEVEL						    1	 // 正极限引脚有效电平
#define LIM_NEG_LEVEL						    1	 // 负极限引脚有效电平
#define ORI_DOWNLEVEL               0  // 原点脉冲信号

#define HOME_POSITION	              0  // 原点坐标
//P:丝杆导程 SPR：每圈的脉冲数（整步） F:脉冲频率 Plus：脉冲数量 
//#define SPEED  = F    * (P / (SPR * MICRO_STEP))
//#define LENGTH = PLUS * (P / (SPR * MICRO_STEP))

#define F_SPR                       200 //整步 步距角:1.8° 360/1.8 = 200
#define MICRO_STEP                  32 
#define SPR                         (F_SPR * MICRO_STEP)   // 旋转一圈需要的脉冲数
#define P														5 //[mm]
#define SPEED  = F    * (P / SPR)
#define LENGTH = PLUS * (P / SPR)

#define X_StepMotorDirN() 	  HAL_GPIO_WritePin(X_AXIS_DIR_GPIO_Port, X_AXIS_DIR_Pin, GPIO_PIN_RESET);
#define X_StepMotorDirP() 	  HAL_GPIO_WritePin(X_AXIS_DIR_GPIO_Port, X_AXIS_DIR_Pin, GPIO_PIN_SET);

#define Y_StepMotorDirN() 	  HAL_GPIO_WritePin(Y_AXIS_DIR_GPIO_Port, Y_AXIS_DIR_Pin, GPIO_PIN_SET);
#define Y_StepMotorDirP() 	  HAL_GPIO_WritePin(Y_AXIS_DIR_GPIO_Port, Y_AXIS_DIR_Pin, GPIO_PIN_RESET);

#define DELAY_RATIO 7
#define Tog_X_Axis(D1,D2) {HAL_GPIO_WritePin(X_AXIS_STEP_GPIO_Port, X_AXIS_STEP_Pin, GPIO_PIN_SET);delay_us(D1/DELAY_RATIO);	HAL_GPIO_WritePin(X_AXIS_STEP_GPIO_Port, X_AXIS_STEP_Pin, GPIO_PIN_RESET);delay_us(D2/DELAY_RATIO);}
#define Stop_X_Axis() {HAL_GPIO_WritePin(X_AXIS_STEP_GPIO_Port, X_AXIS_STEP_Pin, GPIO_PIN_RESET);}
#define Tog_Y_Axis(D1,D2) {HAL_GPIO_WritePin(Y_AXIS_STEP_GPIO_Port, Y_AXIS_STEP_Pin, GPIO_PIN_SET);delay_us(D1/DELAY_RATIO);	HAL_GPIO_WritePin(Y_AXIS_STEP_GPIO_Port, Y_AXIS_STEP_Pin, GPIO_PIN_RESET);delay_us(D2/DELAY_RATIO);}
#define Stop_Y_Axis() {HAL_GPIO_WritePin(Y_AXIS_STEP_GPIO_Port, Y_AXIS_STEP_Pin, GPIO_PIN_RESET);}

//#define StepMotorDirN() 	  HAL_GPIO_WritePin(Z_AXIS_DIR_GPIO_Port, Z_AXIS_DIR_Pin, GPIO_PIN_RESET);
//#define StepMotorDirP() 	  HAL_GPIO_WritePin(Z_AXIS_DIR_GPIO_Port, Z_AXIS_DIR_Pin, GPIO_PIN_SET);
#define StepMotorENABLE() 	//HAL_GPIO_WritePin(Z_AXIS_DIR_GPIO_Port, Z_AXIS_DIR_Pin, GPIO_PIN_SET);
#define StepMotorDISABLE() 	//HAL_GPIO_WritePin(Z_AXIS_DIR_GPIO_Port, Z_AXIS_DIR_Pin, GPIO_PIN_RESET);

enum
{
	STOP,
	ACCELERATE,
	DECELERATE,
	UNIFORM
};
#define Normal	0
#define LimPos	1
#define LimNeg	2
#define OrginP	3
//enum{
//	Normal = 0,
//	LimPos = 1,
//	LimNeg = 2,
//	OrginP = 3
//};

extern __IO uint8_t X_AxisSensorFlag;
extern __IO uint8_t Y_AxisSensorFlag;

extern __IO uint8_t X_AxisStatus;
extern __IO uint8_t Y_AxisStatus;


extern __IO int32_t  X_Axis_StepPosition;//Step Motor Real Location
extern __IO int32_t  Y_Axis_StepPosition;

extern __IO uint8_t TimerFlag;
extern __IO uint8_t EXT_X_STOP_FLAG;
extern __IO uint8_t EXT_Y_STOP_FLAG;

void StepMotor_X_INTTask(void);
void StepMotor_Y_INTTask(void);

extern void X_AxisSensorDetect(void);
extern void Y_AxisSensorDetect(void);
extern void X_AxisMoveRelative(__IO int32_t Steps, __IO uint32_t Alpha1, __IO uint32_t Alpha2, __IO uint32_t Omega);
extern void Y_AxisMoveRelative(__IO int32_t Steps, __IO uint32_t Alpha1, __IO uint32_t Alpha2, __IO uint32_t Omega);

#endif	/* __BSP_STEPMOTOR_H__ */
