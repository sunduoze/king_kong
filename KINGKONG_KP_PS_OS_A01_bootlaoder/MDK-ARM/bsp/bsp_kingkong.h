/*
***
  * @file    : bsp_kingkong.cpp
  * @brief   : For hardware calibration
  * @version : 1.0
  * @date    : 2019.08.02
  * @author  : Enzo
  * @remarks :  
  ***
  */
  
#ifndef BSP_KINGKONG_H_
#define BSP_KINGKONG_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdarg.h>
#include "stm32f1xx_hal.h"

#define ANALOG_REFERENCE 2500 //mV
//#define ADC_Vref 2500
#define VOLT_ATTENUATION 6.8f
#define CURR_ATTENUATION 1.0f // Samples res = 10 mOhm INA282 Gain = 50

	
	
#define OUT_VOL_UP_LIMIT 		22.0f
#define OUT_VOL_DOWN_LIMIT 	10.0f // 

//typedef struct 
//{
//	float f1;
//	float f2;
//	float f3;
//	float f4;	
//}force_val_t;
//	
extern void vol_set(uint8_t *Value);
extern void vol_get(void);
extern void cur_read(void);
extern void output_config(uint8_t status);
extern void internal_dac_vol_set(float volt);
extern void external_dac_vol_set(float volt);
	
	
	
#ifdef __cplusplus
}
#endif


#endif /*BSP_KINGKONG_H_*/


