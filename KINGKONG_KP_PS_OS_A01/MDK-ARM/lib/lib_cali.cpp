/*
***
  * @file    : lio_cali.h
  * @orief   : For hardware calibration
  * @version : 1.0
  * @date    : 2019.08.02
  * @author  : Enzo
  * @remargs :  
  ***
  */
  
#include "lib_cali.h"

#include <string.h>
#include <stdlib.h>

#include "stm_flash.h"
#include "bsp_io.h"
#include "bsp_uart.h"


const uint8_t flash_data_verify_str[] = "STORAGED";

uint8_t cali_init(calibration *cal)
{
	calibration cali_temp;
			/*从flash读取校准参数*/
	uint8_t datatemp[sizeof(calibration)];		
	STMFLASH_Read(FLASH_calibration_SAVE_ADDR, (uint16_t*)datatemp, sizeof(calibration));
	memcpy(&cali_temp, datatemp, sizeof(calibration));
	//		判断零飘值存在标志 
	if(!strncasecmp((const char *)flash_data_verify_str, (const char *)cali_temp.verify_flag, FLASH_DATA_VERIFY_STR_LEN))
	{
		/* 查询到存储标志*/		
		UART_Printf(&UPPER_COM_HUART, "\r\n StorFlag = 1 \r\n");
			//取出
		cal->volt_1[CALI_CH0].g = cali_temp.volt_1[CALI_CH0].g;
		cal->volt_1[CALI_CH0].o = cali_temp.volt_1[CALI_CH0].o;
		cal->volt_2[CALI_CH0].g = cali_temp.volt_2[CALI_CH0].g;
		cal->volt_2[CALI_CH0].o = cali_temp.volt_2[CALI_CH0].o;
		cal->curr_1[CALI_CH0].g = cali_temp.curr_1[CALI_CH0].g;
		cal->curr_1[CALI_CH0].o = cali_temp.curr_1[CALI_CH0].o;
		cal->vo_set[CALI_CH0].g = cali_temp.vo_set[CALI_CH0].g;
		cal->vo_set[CALI_CH0].o = cali_temp.vo_set[CALI_CH0].o;
		cal->force.f1 = cali_temp.force.f1;
		cal->force.f2 = cali_temp.force.f2;
		cal->force.f3 = cali_temp.force.f3;
		cal->force.f4 = cali_temp.force.f4;
	}
	else
	{
		UART_Printf(&UPPER_COM_HUART, "StorFlag = 0 ,Geting Default Value\r\n");
		/*写入默认值*/
		memcpy(cali_temp.verify_flag, flash_data_verify_str, sizeof(cali_temp.verify_flag));
		cali_temp.volt_1[CALI_CH0].g = 1.0f;
		cali_temp.volt_1[CALI_CH0].o = 0.0f;
		cali_temp.volt_2[CALI_CH0].g = 1;
		cali_temp.volt_2[CALI_CH0].o = 0;
		cali_temp.curr_1[CALI_CH0].g = 1;
		cali_temp.curr_1[CALI_CH0].o = 0;
		cali_temp.vo_set[CALI_CH0].g = 1.0f;
		cali_temp.vo_set[CALI_CH0].o = 0.0f;
		cali_temp.force.f1 = 80;
		cali_temp.force.f2 = 100;
		cali_temp.force.f3 = 40;
		cali_temp.force.f4 = 120;
		memcpy(datatemp, &cali_temp, sizeof(cali_temp));
		STMFLASH_Write(FLASH_calibration_SAVE_ADDR, (uint16_t*)datatemp, sizeof(cali_temp));
		UART_Printf(&UPPER_COM_HUART, "StorFlag set to 1,Write Done! \r\n");
		/*加载校准初始值*/
		cal->volt_1[CALI_CH0].g = 1.0f;//y = 0.9981x + 228.43
		cal->volt_1[CALI_CH0].o = 0.0f;
		cal->volt_2[CALI_CH0].g = 1;
		cal->volt_2[CALI_CH0].o = 0;
		cal->curr_1[CALI_CH0].g = 1;
		cal->curr_1[CALI_CH0].o = 0;
		cal->vo_set[CALI_CH0].g = 1;//1.006137f;
		cal->vo_set[CALI_CH0].o = 0;//-0.582654f;
		cal->force.f1 = cali_temp.force.f1;
		cal->force.f2 = cali_temp.force.f2;
		cal->force.f3 = cali_temp.force.f3;
		cal->force.f4 = cali_temp.force.f4;
//		memcpy(cal, &cali_temp, sizeof(cali_temp));
	}	
	return HAL_OK;
}


void cali_read(void)
{
	calibration cali_temp;
	/*从flash读取校准参数*/
	uint8_t datatemp[sizeof(calibration)];		
	STMFLASH_Read(FLASH_calibration_SAVE_ADDR, (uint16_t*)datatemp, sizeof(calibration));
	memcpy(&cali_temp, datatemp, sizeof(calibration));
	UART_Printf(&UPPER_COM_HUART, "\r\n\r\n回读Flash值\r\n");

			//取出
	UART_Printf(&UPPER_COM_HUART, "cali_temp.volt_1[CALI_CH0].g %g\r\n", cali_temp.volt_1[CALI_CH0].g);
	UART_Printf(&UPPER_COM_HUART, "cali_temp.volt_1[CALI_CH0].o %g\r\n", cali_temp.volt_1[CALI_CH0].o);
	
	UART_Printf(&UPPER_COM_HUART, "cali_temp.volt_2[CALI_CH0].g %g\r\n", cali_temp.volt_2[CALI_CH0].g);
	UART_Printf(&UPPER_COM_HUART, "cali_temp.volt_2[CALI_CH0].o %g\r\n", cali_temp.volt_2[CALI_CH0].o);
	
	UART_Printf(&UPPER_COM_HUART, "cali_temp.curr_1[CALI_CH0].g %g\r\n", cali_temp.curr_1[CALI_CH0].g);
	UART_Printf(&UPPER_COM_HUART, "cali_temp.curr_1[CALI_CH0].o %g\r\n", cali_temp.curr_1[CALI_CH0].o);	
	
	UART_Printf(&UPPER_COM_HUART, "cali_temp.vo_set[CALI_CH0].g %g\r\n", cali_temp.vo_set[CALI_CH0].g);
	UART_Printf(&UPPER_COM_HUART, "cali_temp.vo_set[CALI_CH0].o %g\r\n", cali_temp.vo_set[CALI_CH0].o);
	UART_Printf(&UPPER_COM_HUART, "cali_temp.force.f1:%g f2:%g f3:%g f4:%g\r\n",\
							cali_temp.force.f1, cali_temp.force.f2, cali_temp.force.f3, cali_temp.force.f4);		
}


uint8_t cali_write(const uint8_t *value)
{
	calibration cali_temp, cali_history;
	uint8_t datatemp[sizeof(calibration)];		

	UART_Printf(&UPPER_COM_HUART, "出厂缺省值供参考<V A 为单位>！\r\n");
	cali_history.volt_1[CALI_CH0].g = 0.999597f;//0.9981f;
	cali_history.volt_1[CALI_CH0].o = 309.772645f;//228.43f;
	cali_history.volt_2[CALI_CH0].g = 1;
	cali_history.volt_2[CALI_CH0].o = 0;
	cali_history.curr_1[CALI_CH0].g = 1;
	cali_history.curr_1[CALI_CH0].o = 0;
	cali_history.vo_set[CALI_CH0].g = 1.0026f;//1.006137f;
	cali_history.vo_set[CALI_CH0].o = -0.0084f;//-0.582654f;0.999597
	cali_history.force.f1 = 80;
	cali_history.force.f2 = 100;
	cali_history.force.f3 = 40;
	cali_history.force.f4 = 120;
//309.772645,1,0,1,0,1.0026,-0.0084
	UART_Printf(&UPPER_COM_HUART, "DC/DC输出电压档！\r\n");
	UART_Printf(&UPPER_COM_HUART, "cali_temp.volt_1[CALI_CH0].g %g\r\n", cali_history.volt_1[CALI_CH0].g);
	UART_Printf(&UPPER_COM_HUART, "cali_temp.volt_1[CALI_CH0].o %g\r\n", cali_history.volt_1[CALI_CH0].o);
	UART_Printf(&UPPER_COM_HUART, "DC/DC输入电压档！\r\n");	
	UART_Printf(&UPPER_COM_HUART, "cali_temp.volt_2[CALI_CH0].g %g\r\n", cali_history.volt_2[CALI_CH0].g);
	UART_Printf(&UPPER_COM_HUART, "cali_temp.volt_2[CALI_CH0].o %g\r\n", cali_history.volt_2[CALI_CH0].o);
	UART_Printf(&UPPER_COM_HUART, "DC/DC输出电流档！\r\n");	
	UART_Printf(&UPPER_COM_HUART, "cali_temp.curr_1[CALI_CH0].g %g\r\n", cali_history.curr_1[CALI_CH0].g);
	UART_Printf(&UPPER_COM_HUART, "cali_temp.curr_1[CALI_CH0].o %g\r\n", cali_history.curr_1[CALI_CH0].o);	
	UART_Printf(&UPPER_COM_HUART, "DC/DC电压设定档！\r\n");	
	UART_Printf(&UPPER_COM_HUART, "cali_temp.vo_set[CALI_CH0].g %g\r\n", cali_history.vo_set[CALI_CH0].g);
	UART_Printf(&UPPER_COM_HUART, "cali_temp.vo_set[CALI_CH0].o %g\r\n", cali_history.vo_set[CALI_CH0].o);	
	UART_Printf(&UPPER_COM_HUART, "4种压力设置档00 01 10 11！\r\n");	
	UART_Printf(&UPPER_COM_HUART, "cali_temp.force.f1:%g f2:%g f3:%g f4:%g\r\n", \
							cali_history.force.f1, cali_history.force.f2, cali_history.force.f3, cali_history.force.f4);		
	
	uint8_t i = 0, j = 0, g = 0;
	uint8_t strTemp[15];
	float cali_data_temp[12];
	
	while(value[i]!='\0')
	{
		if(value[i] == ',')
		{
			cali_data_temp[g++] = atof((const char *)strTemp);
			j = 0;
			memset(strTemp, 0, sizeof(strTemp));
		}
		else
		{
			strTemp[j] = value[i];
			j++;
		}
		i++;
	}
	cali_data_temp[g] = atof((const char *)strTemp);

	UART_Printf(&UPPER_COM_HUART, "\r\nlalalalalalallalallala \r\n");	
	
	for(i = 0; i < 8;)
	{
		if(cali_data_temp[i] <= 0.5f || cali_data_temp[i] >= 1.5f)
		{
			UART_Printf(&UPPER_COM_HUART, "\r\n 校准数据g值异常 Typ.<0.5f~1.5f>，请重新写入 \r\n");
			return HAL_ERROR;
		}
		i+=2;
	}
	/*写入新值*/
	memcpy(cali_temp.verify_flag, flash_data_verify_str, sizeof(cali_temp.verify_flag));
	cali_temp.volt_1[CALI_CH0].g = cali_data_temp[0];//0.9981f;
	cali_temp.volt_1[CALI_CH0].o = cali_data_temp[1];//228.43f;
	cali_temp.volt_2[CALI_CH0].g = cali_data_temp[2];
	cali_temp.volt_2[CALI_CH0].o = cali_data_temp[3];
	cali_temp.curr_1[CALI_CH0].g = cali_data_temp[4];
	cali_temp.curr_1[CALI_CH0].o = cali_data_temp[5];
	cali_temp.vo_set[CALI_CH0].g = cali_data_temp[6];//1.006137f;
	cali_temp.vo_set[CALI_CH0].o = cali_data_temp[7];//-0.582654f;
	cali_temp.force.f1 = cali_data_temp[8];
	cali_temp.force.f2 = cali_data_temp[9];
	cali_temp.force.f3 = cali_data_temp[10];
	cali_temp.force.f4 = cali_data_temp[11];
	memcpy(datatemp, &cali_temp, sizeof(cali_temp));
	STMFLASH_Write(FLASH_calibration_SAVE_ADDR, (uint16_t*)datatemp, sizeof(cali_temp));
	UART_Printf(&UPPER_COM_HUART, "校准值获取完毕并写入flash\r\n");
	return HAL_OK;
}


