/*
***
  * @file    : lib_cali.h
  * @brief   : For hardware calibration
  * @version : 1.0
  * @date    : 2019.08.02
  * @author  : Enzo
  * @remarks :  
  ***
  */
  
#include "lib_cali.h"

#include <string.h>
#include <stdlib.h>

#include "stm_flash.h"
#include "bsp_io.h"

calibration g_cali;
const uint8_t flash_data_verify_str[] = "STORAGED";

void calibration_init(void)
{
	calibration cali_temp;
			/*��flash��ȡУ׼����*/
	uint8_t datatemp[sizeof(calibration)];		
	STMFLASH_Read(FLASH_calibration_SAVE_ADDR, (uint16_t*)datatemp, sizeof(calibration));
	memcpy(&cali_temp, datatemp, sizeof(calibration));
	//		�ж���Ʈֵ���ڱ�־ 
	if(!strncasecmp((const char *)flash_data_verify_str, (const char *)cali_temp.verify_flag, FLASH_DATA_VERIFY_STR_LEN))
	{
		/* ��ѯ���洢��־*/		
		printf("\r\n StorFlag = 1 \r\n");
			//ȡ��
		g_cali.Volt_1[CALI_CH0].k = cali_temp.Volt_1[CALI_CH0].k;
		g_cali.Volt_1[CALI_CH0].b = cali_temp.Volt_1[CALI_CH0].b;
		g_cali.Volt_2[CALI_CH0].k = cali_temp.Volt_2[CALI_CH0].k;
		g_cali.Volt_2[CALI_CH0].b = cali_temp.Volt_2[CALI_CH0].b;
		g_cali.Curr_1[CALI_CH0].k = cali_temp.Curr_1[CALI_CH0].k;
		g_cali.Curr_1[CALI_CH0].b = cali_temp.Curr_1[CALI_CH0].b;
		g_cali.VoSet1[CALI_CH0].k = cali_temp.VoSet1[CALI_CH0].k;
		g_cali.VoSet1[CALI_CH0].b = cali_temp.VoSet1[CALI_CH0].b;
	}
	else
	{
		printf("StorFlag = 0 ,Geting Default Value\r\n");
		/*д��Ĭ��ֵ*/
		memcpy(cali_temp.verify_flag, flash_data_verify_str, sizeof(cali_temp.verify_flag));
		cali_temp.Volt_1[CALI_CH0].k = 0.999597f;//0.9981f;
		cali_temp.Volt_1[CALI_CH0].b = 309.772645f;//228.43f;
		cali_temp.Volt_2[CALI_CH0].k = 1;
		cali_temp.Volt_2[CALI_CH0].b = 0;
		cali_temp.Curr_1[CALI_CH0].k = 1;
		cali_temp.Curr_1[CALI_CH0].b = 0;
		cali_temp.VoSet1[CALI_CH0].k = 1.0026f;//1.006137f;
		cali_temp.VoSet1[CALI_CH0].b = -0.0084f;//-0.582654f;
		memcpy(datatemp, &cali_temp, sizeof(cali_temp));
		STMFLASH_Write(FLASH_calibration_SAVE_ADDR, (uint16_t*)datatemp, sizeof(cali_temp));
		printf("StorFlag set to 1,Write Done! \r\n");
		/*����У׼��ʼֵ*/
		g_cali.Volt_1[CALI_CH0].k = 1.0f;//y = 0.9981x + 228.43
		g_cali.Volt_1[CALI_CH0].b = 0.0f;
		g_cali.Volt_2[CALI_CH0].k = 1;
		g_cali.Volt_2[CALI_CH0].b = 0;
		g_cali.Curr_1[CALI_CH0].k = 1;
		g_cali.Curr_1[CALI_CH0].b = 0;
		g_cali.VoSet1[CALI_CH0].k = 1;//1.006137f;
		g_cali.VoSet1[CALI_CH0].b = 0;//-0.582654f;
	}	
}
void cali_read(void)
{
	calibration cali_temp;
	/*��flash��ȡУ׼����*/
	uint8_t datatemp[sizeof(calibration)];		
	STMFLASH_Read(FLASH_calibration_SAVE_ADDR, (uint16_t*)datatemp, sizeof(calibration));
	memcpy(&cali_temp, datatemp, sizeof(calibration));
			//ȡ��
	printf("cali_temp.Volt_1[CALI_CH0].k %f\r\n", cali_temp.Volt_1[CALI_CH0].k);
	printf("cali_temp.Volt_1[CALI_CH0].b %f\r\n", cali_temp.Volt_1[CALI_CH0].b);
	
	printf("cali_temp.Volt_2[CALI_CH0].k %f\r\n", cali_temp.Volt_2[CALI_CH0].k);
	printf("cali_temp.Volt_2[CALI_CH0].b %f\r\n", cali_temp.Volt_2[CALI_CH0].b);
	
	printf("cali_temp.Curr_1[CALI_CH0].k %f\r\n", cali_temp.Curr_1[CALI_CH0].k);
	printf("cali_temp.Curr_1[CALI_CH0].b %f\r\n", cali_temp.Curr_1[CALI_CH0].b);	
	
	printf("cali_temp.VoSet1[CALI_CH0].k %f\r\n", cali_temp.VoSet1[CALI_CH0].k);
	printf("cali_temp.VoSet1[CALI_CH0].b %f\r\n", cali_temp.VoSet1[CALI_CH0].b);	
}

void cali_write(uint8_t *value)
{
	calibration cali_temp, cali_history;
	uint8_t datatemp[sizeof(calibration)];		

	printf("����ȱʡֵ���ο�<mV mA Ϊ��λ>��\r\n");
	cali_history.Volt_1[CALI_CH0].k = 0.999597f;//0.9981f;
	cali_history.Volt_1[CALI_CH0].b = 309.772645f;//228.43f;
	cali_history.Volt_2[CALI_CH0].k = 1;
	cali_history.Volt_2[CALI_CH0].b = 0;
	cali_history.Curr_1[CALI_CH0].k = 1;
	cali_history.Curr_1[CALI_CH0].b = 0;
	cali_history.VoSet1[CALI_CH0].k = 1.0026f;//1.006137f;
	cali_history.VoSet1[CALI_CH0].b = -0.0084f;//-0.582654f;0.999597
//309.772645,1,0,1,0,1.0026,-0.0084
	printf("DC/DC�����ѹ����\r\n");
	printf("cali_temp.Volt_1[CALI_CH0].k %f\r\n", cali_history.Volt_1[CALI_CH0].k);
	printf("cali_temp.Volt_1[CALI_CH0].b %f\r\n", cali_history.Volt_1[CALI_CH0].b);
	printf("O1 O2 ��������� �˴���Ч��\r\n");	
	printf("cali_temp.Volt_2[CALI_CH0].k %f\r\n", cali_history.Volt_2[CALI_CH0].k);
	printf("cali_temp.Volt_2[CALI_CH0].b %f\r\n", cali_history.Volt_2[CALI_CH0].b);
	printf("DC/DC�����������\r\n");	
	printf("cali_temp.Curr_1[CALI_CH0].k %f\r\n", cali_history.Curr_1[CALI_CH0].k);
	printf("cali_temp.Curr_1[CALI_CH0].b %f\r\n", cali_history.Curr_1[CALI_CH0].b);	
	printf("DC/DC��ѹ�趨����\r\n");	
	printf("cali_temp.VoSet1[CALI_CH0].k %f\r\n", cali_history.VoSet1[CALI_CH0].k);
	printf("cali_temp.VoSet1[CALI_CH0].b %f\r\n", cali_history.VoSet1[CALI_CH0].b);	
	
	uint8_t i = 0, j = 0, k = 0;
	uint8_t strTemp[15];
	float cali_data_temp[8];
	
	while(value[i]!='\0')
	{
		if(value[i] == ',')
		{
			cali_data_temp[k++] = atof((const char *)strTemp);
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
	cali_data_temp[k] = atof((const char *)strTemp);

	printf("\r\nlalalalalalallalallala \r\n");	
	
	for(i = 0; i < 8;)
	{
		if(cali_data_temp[i] <= 0.5f || cali_data_temp[i] >= 1.5f)
		{
			printf("\r\n У׼����Kֵ�쳣 Typ.<0.5f~1.5f>��������д�� \r\n");
			return ;
		}
		i+=2;
	}
	/*д����ֵ*/
	memcpy(cali_temp.verify_flag, flash_data_verify_str, sizeof(cali_temp.verify_flag));
	cali_temp.Volt_1[CALI_CH0].k = cali_data_temp[0];//0.9981f;
	cali_temp.Volt_1[CALI_CH0].b = cali_data_temp[1];//228.43f;
	cali_temp.Volt_2[CALI_CH0].k = cali_data_temp[2];
	cali_temp.Volt_2[CALI_CH0].b = cali_data_temp[3];
	cali_temp.Curr_1[CALI_CH0].k = cali_data_temp[4];
	cali_temp.Curr_1[CALI_CH0].b = cali_data_temp[5];
	cali_temp.VoSet1[CALI_CH0].k = cali_data_temp[6];//1.006137f;
	cali_temp.VoSet1[CALI_CH0].b = cali_data_temp[7];//-0.582654f;
	memcpy(datatemp, &cali_temp, sizeof(cali_temp));
	STMFLASH_Write(FLASH_calibration_SAVE_ADDR, (uint16_t*)datatemp, sizeof(cali_temp));
	printf("У׼ֵ��ȡ��ϲ�д��flash\r\n");
	printf("\r\n\r\n�ض�Flashֵ\r\n");
	cali_read();
	mcu_soft_start();
}


