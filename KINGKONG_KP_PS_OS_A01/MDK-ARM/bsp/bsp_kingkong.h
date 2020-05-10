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

#define HW_REVISION 	"V2.0"
#define FW_REVISION 	"V1.0.0"
	
	
#define EXT_ANALOG_REFERENCE 2500 //mV
#define INT_DAC_REF 3.3107f
//#define ADC_Vref 2500
#define VOLT_ATTENUATION 6.8f
#define CURR_ATTENUATION 1.0f // Samples res = 10 mOhm INA282 Gain = 50

/*
* 电路参数：Rfbt = 100k; Rfbb = 11k; Rfb_dac = 2.2k;
* Vdac = 0.9776 - 0.022 * Vo
*/
//dac_val = * vol_temp + 0.9776f;
#define VOUT_RATIO_GAIN   	-0.022f
#define VOUT_RATIO_OFFSET		0.9776f

/*
* 电磁铁参数：
//Voltage[V]	Force[g]
//14.88				80.21
//16.8				99.41
* V = 0.1f * F + 6.859f
*/
#define F_OUT_RATIO_GAIN   	0.1f
#define F_OUT_RATIO_OFFSET	6.859f

/*
* 输出电压测量：
//Rt = 30k + 4.99k； Rb = 2.49k
//Vadc = Vout * 0.066435f
*/
#define V_OUT_RATIO_GAIN   	15.052209f//0.066435f 避开除法

/*
* 输出电流测量：
//Rsample = 10mOhm Gain = 50 
//Vadc = Iout * 0.5f
*/
#define I_OUT_RATIO_GAIN   	4.0814f//0.5f//
#define I_OUT_RATIO_OFFSET	-0.002f
/*
* 输入电压测量：
//Rt = 30k + 4.99k； Rb = 2.49k
//Vadc = Vout * 0.066435f
*/
#define V_IN_RATIO_GAIN   	15.052209f//0.066435f 避开除法

	
#define OUT_VOL_UP_LIMIT 		22.0f
#define OUT_VOL_DOWN_LIMIT 	10.0f // 

#define ADC_CHANNEL_NUM 3
#define SAMPLE_NUM 10

#define DEFAULT_CHANNEL_DEBUG 0//ADC sample channel

enum{
	ADC_VOUT_CH = 0,
	ADC_IOUT_CH = 1,
	ADC_VIN_CH  = 2,
	ADC_TST_CH  = 3
};

typedef struct 
{
	float f1;
	float f2;
	float f3;
	float f4;	
}force_val_t;

enum{
	PS_EN,
	PS_DIS
};

extern void hardware_init(void);
extern void mcu_soft_start(void);

extern void output_config(uint8_t status, uint8_t lock);

extern uint8_t v_in_get(float *vol);
extern uint8_t v_out_get(float *vol);
extern uint8_t cur_out_get(float *cur, float zero_drift);
extern uint8_t temperature_get(float *temp);
extern void force_get(uint16_t *f);

extern void force_config_read(void);

extern uint8_t vol_set(const float *val);
extern uint8_t force_set(const float *f);

extern void ps_error_read(void);

extern void internal_dac_vol_set(float volt);
extern void external_dac_vol_set(float volt);

extern void ps_handle_fun(force_val_t *f);

extern void ExtADC_Monitor(void);

#ifdef __cplusplus
}
#endif


#endif /*BSP_KINGKONG_H_*/


