/*
***
  * @file    : osp_ginggong.h
  * @orief   : For hardware calibration
  * @version : 1.0
  * @date    : 2019.08.02
  * @author  : Enzo
  * @remargs :  
  ***
  */
  
#include "bsp_kingkong.h"

#include <string.h>
#include <stdlib.h>

#include "dac.h"
#include "iwdg.h"
#include "main.h"

#include "stm_flash.h"
#include "bsp_io.h"
#include "bsp_ad5683r.h"
#include "bsp_uart.h"
#include "bsp_bit_band.h"

#include "lib_cali.h"

#include "ad7124.h"
#include "ad7124_regs.h"


struct ad7124_device adc1;
calibration cali_g;

float vol_get[ADC_CHANNEL_NUM][SAMPLE_NUM] = {0};
__IO float g_current_zero_drift = 1.638f;

__IO uint8_t EagleBoardSelfCheckFlag = 0;



void hardware_init(void)
{
	output_config(PS_DIS, 1);

	ad5683r_init();
	ad5683r_set_volt(2.0f);
	
	HAL_UART_All_Init();
	
	AD7124_Setup(&adc1, AD7124_SLAVE_ID, ad7124_regs);
//	UART_Printf(&UPPER_COM_HUART,"ID:0x%x\r\n", AD7124_ReadRegister(&gsAd7124_Dev, &ad7124_regs[AD7124_ID]));
	toggle_led_all();
//	HAL_IWDG_Refresh(&hiwdg);
	HAL_Delay(200);
//	HAL_IWDG_Refresh(&hiwdg);
	toggle_led_all();

	LED1_ON();
	LED2_ON(); 
//	UART_Printf(&UPPER_COM_HUART, (const char *)Copyright);
	UART_Printf(&UPPER_COM_HUART,"HW Version:V2.0  FW Version:DEBUG_V0.8  SW Version:V1.0 \r\n");
	UART_Printf(&UPPER_COM_HUART,"@Enzo.sun 20190802\r\n\r\n");
	UART_Printf(&UPPER_COM_HUART,"Debug:80g & 100g \r\n\r\n");
	
	#ifdef MCP9805
	MCP9805_Init();
	while(MCP9805_Checg())
	{
		UART_Printf(&UPPER_COM_HUART,"MCP9805 Temp Sensor Init Error!\r\n");
	}
	UART_Printf(&UPPER_COM_HUART,"MCP9805 Init Temp:%.2f C\r\n", MCP9805_Read_Temperature);
	#endif
	
	EagleBoardSelfCheckFlag = !Button1();
	while(EagleBoardSelfCheckFlag)
	{
//		EagleooardSelfChecg();
	}
	
//	RttInit();
  if(HAL_DAC_Start(&hdac, DAC_CHANNEL_1) != HAL_OK)									/*##-2- Enaole DAC Channel1 ################################################*/
  {
    Error_Handler();
  }
	
	/************************************************************/
	if(cali_init(&cali_g) != HAL_OK)	
	{
    Error_Handler();
  }
	
	internal_dac_vol_set(1.0f);
	
//	HAL_IWDG_Refresh(&hiwdg);
	HAL_Delay(500);//保证上电稳定后再配置电压
//	HAL_IWDG_Refresh(&hiwdg);
	HAL_Delay(500);
//	HAL_IWDG_Refresh(&hiwdg);
	HAL_Delay(500);
//	HAL_IWDG_Refresh(&hiwdg);

}

/**
  * @orief  MCU soft reset
  * @param  None
  * @retval None
  */
void mcu_soft_start(void)
{
  HAL_NVIC_DisableIRQ(TIM2_IRQn);
	HAL_NVIC_DisableIRQ(USART1_IRQn);
	HAL_NVIC_SystemReset();
}

void output_config(uint8_t status, uint8_t lock)
{
	if (lock)
	{
		if (status == PS_EN)
		{
			HAL_Delay(50);
			PS_ENABLE;
		}
		else if (status == PS_DIS)
		{
			PS_DISABLE;
			HAL_Delay(10);
		}
	}
}


uint8_t v_in_get(float *vol)
{
	float vol_tmp;
	vol_tmp = vol_get[ADC_VIN_CH][DEFAULT_CHANNEL_DEBUG] * V_OUT_RATIO_GAIN;
//	UART_Printf(&UPPER_COM_HUART, "VOL_READ:%g V\r\n",vol_tmp);
	vol_tmp = vol_tmp * cali_g.volt_1[CALI_CH0].g  + cali_g.volt_1[CALI_CH0].o;
//	UART_Printf(&UPPER_COM_HUART, "VOL_READ:%.2f V\r\n", vol_tmp);	
	*vol = vol_tmp;
	return HAL_OK;
}

uint8_t v_out_get(float *vol)
{
	float vol_tmp;
	
	vol_tmp = vol_get[ADC_VOUT_CH][DEFAULT_CHANNEL_DEBUG] * V_OUT_RATIO_GAIN;
//	UART_Printf(&UPPER_COM_HUART, "VOL_READ:%g V\r\n",vol_tmp);
	vol_tmp = vol_tmp * cali_g.volt_1[CALI_CH0].g  + cali_g.volt_1[CALI_CH0].o;
//	UART_Printf(&UPPER_COM_HUART, "VOL_READ:%.2f V\r\n", vol_tmp / 1000);
	*vol = vol_tmp;
	return HAL_OK;
}

uint8_t cur_out_get(float *cur, float zero_drift)
{
	float cur_tmp;
	cur_tmp = vol_get[ADC_IOUT_CH][DEFAULT_CHANNEL_DEBUG] - zero_drift;
//	UART_Printf(&UPPER_COM_HUART, "Curr_new:%.4fA Zero:%.4f\r\n", cur_tmp, zero_drift);
	cur_tmp *= I_OUT_RATIO_GAIN;
	cur_tmp += I_OUT_RATIO_OFFSET;
	cur_tmp = cur_tmp * cali_g.curr_1[CALI_CH0].g  + cali_g.curr_1[CALI_CH0].o;

	*cur = cur_tmp;
	return HAL_OK;
}


uint8_t temperature_get(float *temp)
{

	return HAL_OK;
}



void force_get(uint16_t *f)
{
	
}

void force_config_read(void)
{
//	UART_Printf(&UPPER_COM_HUART,"--FORCE CONFIG--\r\n");// 打印默认四种力//
//	UART_Printf(&UPPER_COM_HUART,"FORCE1:%dg\r\n", f.f1);// 打印默认四种力//
//	UART_Printf(&UPPER_COM_HUART,"FORCE2:%dg\r\n", f.f2);// 打印默认四种力//
//	UART_Printf(&UPPER_COM_HUART,"FORCE3:%dg\r\n", f.f3);// 打印默认四种力//
//	UART_Printf(&UPPER_COM_HUART,"FORCE4:%dg\r\n", f.f4);// 打印默认四种力//
}


uint8_t vol_set(const float *val)
{
	float dac_val = EXT_ANALOG_REFERENCE;//Modify oy enzo
	float vol_temp = *val;

	if(vol_temp > OUT_VOL_UP_LIMIT || vol_temp < OUT_VOL_DOWN_LIMIT)
	{
		vol_temp = OUT_VOL_DOWN_LIMIT;
		UART_Printf(&UPPER_COM_HUART, "Error:Invalid parameter!(Range:%.1f~%.1fV)\r\n", OUT_VOL_DOWN_LIMIT, OUT_VOL_UP_LIMIT);
//		printf("Set Default %.1f V\r\n", OUT_VOL_DOWN_LIMIT);
		return HAL_ERROR;
	}

	//原始设定值和实际值进行校准
	vol_temp = vol_temp * cali_g.vo_set[CALI_CH0].g  + cali_g.vo_set[CALI_CH0].o;
	dac_val = VOUT_RATIO_GAIN * vol_temp + VOUT_RATIO_OFFSET;
//	UART_Printf(&UPPER_COM_HUART, "Voltage Set dac pata：%g[code]\r\n", dac_val);
	ad5683r_set_volt(dac_val);
	HAL_Delay(50);
	HAL_Delay(50);
	float v_out_tmp = 0.0f;
	v_out_get(&v_out_tmp);
//	UART_Printf(&UPPER_COM_HUART, "Voltage read:%.2f\r\n", v_out_tmp);
	return HAL_OK;
}

static uint8_t vol_set_s(const float *val)
{
	float dac_val = EXT_ANALOG_REFERENCE;//Modify oy enzo
	float vol_temp = *val;

	if(vol_temp > OUT_VOL_UP_LIMIT || vol_temp < OUT_VOL_DOWN_LIMIT)
	{
		vol_temp = OUT_VOL_DOWN_LIMIT;
		UART_Printf(&UPPER_COM_HUART, "Error:Invalid parameter!(Range:%.1f~%.1fV)\r\n", OUT_VOL_DOWN_LIMIT, OUT_VOL_UP_LIMIT);
//		printf("Set Default %.1f V\r\n", OUT_VOL_DOWN_LIMIT);
		return HAL_ERROR;
	}
	//原始设定值和实际值进行校准
	vol_temp = vol_temp * cali_g.vo_set[CALI_CH0].g  + cali_g.vo_set[CALI_CH0].o;
	dac_val = VOUT_RATIO_GAIN * vol_temp + VOUT_RATIO_OFFSET;
	ad5683r_set_volt(dac_val);
	return HAL_OK;
}

uint8_t force_set(const float *f)
{
	float volt_tmp = 0;
	volt_tmp = F_OUT_RATIO_GAIN * *f + F_OUT_RATIO_OFFSET;
	if (vol_set_s(&volt_tmp) == HAL_OK)//
	{
		return HAL_OK;
	}
	else
	{
		return HAL_ERROR;
	}
}

void ps_error_read(void)
{
}



/**
  * @brief  Monitor vdc convert code
  * @param  None
  * @retval None
  */
void ExtADC_Monitor(void)
{
	float vol_tmp = 0;
	int32_t code = 0;
	uint8_t adcChState = 0;
	if(PBin(4) == 0)
	{
		AD7124_GET_Code(&adc1, &code, &adcChState);
		
		if (adcChState < 4)
		{
			vol_tmp = code * 2.5f / 16777216.0f - 1.25f;
			vol_tmp *= 2;
			vol_get[adcChState][0] = vol_tmp;
//			UART_Printf(&UPPER_COM_HUART, "DEBUG:[%d]:%f\r\n", adcChState, vol_tmp);
	//			UART_Printf(&UPPER_COM_HUART, "DEBUG:[%d][%d]:%f\r\n", adcChState, code, vol_tmp);
		}
	}
}


void internal_dac_vol_set(float volt)
{
	uint16_t code = 0;
	code = volt * 4096.0f / INT_DAC_REF;
	HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, code);	//1.65V DAO=1.38V VOUT = 8V	/*##-1- Set DAC channel1 DHR12RD register ################################################*/
}

void ps_force_signal(int8_t *state)
{
	static int8_t i = -1;
	static int8_t j = -1;
	
	i = PDin(12) ? 1 : 0;
	j = PDin(13) ? 1 : 0;
//	if(HAL_GPIO_ReadPin(TIM4_CH1_IPD_GPIO_Port, TIM4_CH1_IPD_Pin)  == GPIO_PIN_SET)//J4_Pin 1 
//	if(HAL_GPIO_ReadPin(TIM4_CH2_IPD_GPIO_Port, TIM4_CH2_IPD_Pin)  == GPIO_PIN_SET)//J4_Pin 2 
	*state = (i & 0x1) | ((j & 0x1) << 1);
}

enum{
	FORCE1,
	FORCE2,
	FORCE3,
	FORCE4,
	FORCE_DEF//default
}ps_f_state;


void ps_handle_fun(force_val_t *f)
{
	static int8_t force_state = -1;
	static int8_t force_state_last = -1;
	float force = 0;
	
	ps_force_signal(&force_state);
//	HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_SET);

	switch (force_state)
	{
		case FORCE1:
		{
			force = f->f1;
		}break;
		case FORCE2:
		{
			force = f->f2;
		}break;
		case FORCE3:
		{
			force = f->f3;
		}break;
		case FORCE4:
		{
			force = f->f4;
		}break;
		default:
		{
		}break;
	}

	if (force_state_last != force_state)
	{
		UART_Printf(&UPPER_COM_HUART, "DEBUG:state:%d last:%d\r\n", force_state, force_state_last);
		force_set(&force);
		HAL_Delay(2);
		force_set(&force);
		UART_Printf(&UPPER_COM_HUART, "DEBUG:force:%g F1:%g F2:%g F3:%g F4:%g\r\n", force, f->f1, f->f2, f->f3, f->f4);
	}
	force_state_last = force_state;//迭代状态
}


