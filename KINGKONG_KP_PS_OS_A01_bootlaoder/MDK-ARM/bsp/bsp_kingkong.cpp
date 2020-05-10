/*
***
  * @file    : bsp_kingkong.h
  * @brief   : For hardware calibration
  * @version : 1.0
  * @date    : 2019.08.02
  * @author  : Enzo
  * @remarks :  
  ***
  */
  
#include "bsp_kingkong.h"

#include <string.h>
#include <stdlib.h>

#include "dac.h"


#include "stm_flash.h"
#include "bsp_io.h"
#include "lib_cali.h"
#include "bsp_ad5683r.h"

#include "bsp_bit_band.h"

#define BUG

extern calibration g_cali;
//force_val_t force_typ;

const char *Copyright[] = {
	"======================================================================",
	"=                   (C) COPYRIGHT 2019                               =",
	"======================================================================",
	"=       Wireless Charge Dummy Board Application (Version 5.0)        =",
	"=                                                 Date:2018/11/29    =",
	"=                                                Modified By Enzo.sun=",
	"======================================================================",
	"@End@"
};

const char *CmdList[] = {

	"*RST",         //CmdList[0]	"MCU Soft reset!"
	"*IDN?",        //CmdList[1]	"MCU Soft reset!"
	"Help",         //CmdList[2]	"Command Introduction!"
	"Version",      //CmdList[3]	"Show FW version!"
	"Copyright",    //CmdList[4]	"Show Copyright!"
	"OUTPUT 0", 
	"OUTPUT 1", 
	"VOL_READ", 
	"CUR_READ", 
	"CALI_READ", //Calibration data read
	"@End@"			//Sign of the end.

};

const char *VariableCmdList[] = {

	"FREQ_SET ",
	"VOL_SET ",
	"CALI_WRITE ",//Calibration data write
	"@End@"			//Sign of the end.

};

const char *CmdBrief[] = {
	"==========================================================================",
	"=                        Command Introduction                            =",
	"==========================================================================",
	" 1.Help       : Show this command introduction table.                     ",
	" 2.Version    : Show Firmware Version.                                    ",
	" 3.*RST       : MCU soft reset.                                           ",
	" 4.OUTPUT 0/1 : PS output enable or disable. Eg.'OUTPUT 1' Enable Output  ",
	" 5.VOL_SET    : Voltage output config. Eg.'VOL_SET 12.5' Set out as 12.5V ",
	" 7.VIN_READ   : DC/DC Voltage input value read back.                      ",
	" 8.VOUT_READ  : DC/DC Voltage output value read back.                     ",
	" 9.CUR_READ   : Output current read back.                                 ",
	" ?.FORCE_SET  : Set force . Eg.'VOL_SET 12.5' Set out as 12.5V ",
	
//	4种力设定
// 温度读取
// 初始化时，自动读取上次设定的默认值
	
//	"CALI_READ", //Calibration data read
//	"CALI_WRITE",//Calibration data write
	"==========================================================================",
	//"= Kindly Remind:All commands are case-insensitively!Have a good day! =",
	//"======================================================================",
	"@End@"							//Sign of the end.

};

/**
  * @brief  MCU soft reset
  * @param  None
  * @retval None
  */
void mcu_soft_start(void)
{
  HAL_NVIC_DisableIRQ(TIM2_IRQn);
	HAL_NVIC_DisableIRQ(USART1_IRQn);
	HAL_NVIC_SystemReset();
}

void vol_set(uint8_t *Value)
{
	uint8_t i=0;
	float cal = 0.0f;
	float dac_val = ANALOG_REFERENCE;//Modify by enzo
	uint8_t strTemp[6];
	float vol_temp;

	while(Value[i]!='\0')
	{
		strTemp[i] = Value[i];
		i++;
	}
//	printf("Value_Temp：%s \r\n",strTemp);	
	vol_temp = atof((const char *)strTemp);
	if(vol_temp > OUT_VOL_UP_LIMIT || vol_temp < OUT_VOL_DOWN_LIMIT)
	{
		vol_temp = OUT_VOL_DOWN_LIMIT;
		printf("Error:Invalid parameter!(Range:%.1f~%.1fV)\r\n", OUT_VOL_DOWN_LIMIT, OUT_VOL_UP_LIMIT);
		printf("Set Default %.1f V\r\n", OUT_VOL_DOWN_LIMIT);
	}
	printf("Voltage Set Para：%g[V]\r\n", vol_temp);


	//原始设定值和实际值进行校准
	//x=1.006137*y-0.582654
	vol_temp = vol_temp * g_cali.VoSet1[CALI_CH0].k  + g_cali.VoSet1[CALI_CH0].b;
	dac_val = -0.173913f * vol_temp + 3.0787f;
	AD5683R_Write_Voltage(dac_val);
	HAL_Delay(500);
	
#ifndef BUG
	CAL = JR_GET_ADC_AVERAGE(ADC_CHANNEL_8,20);
#endif

	cal = cal * ANALOG_REFERENCE * VOLT_ATTENUATION / 4096;
	cal = cal * g_cali.Volt_1[CALI_CH0].k  + g_cali.Volt_1[CALI_CH0].b;
	printf("Voltage read:%.2f\r\n", cal / 1000);
}

void vol_get(void)
{
	float vol;
#ifndef BUG
		vol = JR_GET_ADC_AVERAGE(ADC_CHANNEL_8,100);
#endif

	vol = vol * ANALOG_REFERENCE * VOLT_ATTENUATION / 4096;
//	printf("VOL_READ:%g V\r\n",VOLTAGE);
	vol = vol * g_cali.Volt_1[CALI_CH0].k  + g_cali.Volt_1[CALI_CH0].b;
	printf("VOL_READ:%.2f V\r\n", vol / 1000);
}

void cur_read(void)
{
	float cur;
#ifndef BUG
	cur = JR_GET_ADC_AVERAGE(ADC_CHANNEL_10,100);
#endif

//	cur -= Current_ZeroDrift;
	cur = cur * ANALOG_REFERENCE * CURR_ATTENUATION / 4096;
	cur = cur * g_cali.Curr_1[CALI_CH0].k  + g_cali.Curr_1[CALI_CH0].b;
	printf("Curr_READ:%.2f A\r\n", cur / 1000);
}

void output_config(uint8_t status)
{
	if(status)
	{
		HAL_Delay(10);
		PS_ENABLE;
		printf("Output enable!\r\n");
	}
	else
	{
		PS_DISABLE;
		HAL_Delay(10);
		printf("Output disable!\r\n");
	}
}




void force_set(float *f)
{
	
}

#define INT_DAC_REF 3.3107f

#define VOUT_VOLTAGE_MAX 30.5f
#define VOUT_VOLTAGE_MIN  8.5f

#define VOUT_fK (-46.74157303f)
#define VOUT_fB (44.88793258f)

//#define CALI_LIST_MAX 10
typedef float tfCalRat;
typedef struct _Cali_Ratio
{
	uint8_t  cali_list;
	tfCalRat tSlope;
	tfCalRat tOffset;
}Cali_Ratio;

uint16_t VoltGeneAlgorithm(float fK, float fB, float VoutVoltage)
{
	static float DacVolt;
//	static float fK, fB;
	/**Voltage Clamp**/
	if(VoutVoltage > VOUT_VOLTAGE_MAX)	VoutVoltage = VOUT_VOLTAGE_MAX;
	if(VoutVoltage < VOUT_VOLTAGE_MIN)	VoutVoltage = VOUT_VOLTAGE_MIN;
#ifdef INS_ADC
//		i+=50;
//	  if(i > 4095) i = 0;
//		HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, i);/*##-1- Set DAC channel1 DHR12RD register ################################################*/
//		HAL_Delay(500);
//		Toggle_Led_All();
#else //Ext ADC
	/*DAC Num Clamp*/
	DacVolt =  (VoutVoltage - fB) / fK;
	AD5683R_Write_Voltage(DacVolt);
//	UART_Printf(&UPPER_COM_HUART,"DacValt:%f!\r\n",DacVolt);
//	AD5683R_Write_Voltage(0.801f);	//0.514f //0.801f
#endif
	
	return HAL_OK;
}

void internal_dac_vol_set(float volt)
{
	uint16_t code = 0;
	code = volt * 4096.0f / INT_DAC_REF;
	HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, code);	//1.65V DAO=1.38V VOUT = 8V	/*##-1- Set DAC channel1 DHR12RD register ################################################*/
}

void external_dac_vol_set(float volt)
{
	uint16_t code = 0;
	code = volt * 4096.0f / INT_DAC_REF;
	HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, code);	//1.65V DAO=1.38V VOUT = 8V	/*##-1- Set DAC channel1 DHR12RD register ################################################*/
}




enum{
	FORCE1,
	FORCE2,
	FORCE3,
	FORCE4,
	FORCE_DEF//default
}ps_f_state;



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


//struct 
//{
//	float force_1;
//	float force_2;
//	float force_3;
//	float force_4;	
//}force_val_t;
	




//void ps_handle_fun(force_val_t f)
//{
//	static int8_t force_state = -1;
//	
//	ps_force_signal(&force_state);
//	HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_SET);
//	
//	switch (force_state)
//	{
//		case FORCE1:
//		{
//			force_set(f->f1);
//		}break;
//		case FORCE2:
//		{
//			force_set(f->f2);
//		}break;
//		case FORCE3:
//		{
//			force_set(f->f3);
//		}break;
//		case FORCE4:
//		{
//			force_set(f->f4);
//		}break;
//		default:
//		{
//			
//		}break;
//	}
//	
//}


