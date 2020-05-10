/*
***
  * @file    : lib_cali.cpp
  * @brief   : For hardware calibration
  * @version : 1.0
  * @date    : 2019.08.02
  * @author  : Enzo
  * @remarks :  
  ***
  */
  
#ifndef LIB_CALI_H_
#define LIB_CALI_H_

#ifdef __cplusplus
extern "C" {
#endif


#include "stm32f1xx_hal.h"
	
#include <stdint.h>
#include <stdarg.h>
	
//#include "usart.h"
#define CALI_CH0 0
#define CALIB_SUM_SINGLE_CHANNEL 10
#define FLASH_calibration_SAVE_ADDR 	0X08030000//0X08020000 //起始地址从384kB/(sum=512k)	//设置FLASH 保存地址(必须为偶数，且其值要大于本代码所占用FLASH的大小+0X08000000)

#define FLASH_DATA_VERIFY_STR_LEN 10
	
typedef struct 
{
	float k;
	float b;
}calib_ratio;//Linear calibration

/*The header of users flash storage*/
typedef struct 
{
	uint8_t 		verify_flag[FLASH_DATA_VERIFY_STR_LEN];			 	/*storage verify flag*/
	calib_ratio Volt_1[CALIB_SUM_SINGLE_CHANNEL];
	calib_ratio Volt_2[CALIB_SUM_SINGLE_CHANNEL];
	calib_ratio Curr_1[CALIB_SUM_SINGLE_CHANNEL];
	calib_ratio VoSet1[CALIB_SUM_SINGLE_CHANNEL];
}calibration;


extern void calibration_init(void);
extern void cali_write(uint8_t *value);
extern void cali_read(void);
extern void mcu_soft_start(void);

#ifdef __cplusplus
}
#endif


#endif /*LIB_CALI_H_*/


