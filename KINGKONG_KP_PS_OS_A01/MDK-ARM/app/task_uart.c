/*
 * task_uart.c
 *
 * Created on: 2018年2月27日
 * Author: Enzo
 */
 
#include "task_uart.h"

#include <math.h>
#include <stdlib.h>
#include <string.h>


#include "bsp_io.h"
#include "bsp_kingkong.h"
#include "lib_cali.h"

__IO  uint8_t UART_RxCallback_Flag = Clear_Flag;
extern __IO uint8_t vout_debug_flag_g;

//#define	DBG_U2U


/**
  * @brief  Idle Call back
  * @param  UART_HandleTypeDef
  * @retval None
  */
void UART_IdleRxCallback(UART_HandleTypeDef *huart)
{
	if(huart == &UPPER_COM_HUART)
	{
		UART_RxCallback_Flag = UPPER_COM_Flag;
		#ifdef DBG_U2U
		UART_Printf(&UPPER_COM_HUART, "DBG1:arrUPPER_COM_Buf\r\n");
		UART_Printf(&UPPER_COM_HUART, (const char*)arrUPPER_COM_Buf);
		UART_Printf(&UPPER_COM_HUART, "\r\n");
		#endif
	}
  else if(huart == &PWR0204_1_HUART)
  {
		UART_RxCallback_Flag = PWR0204_1_Flag;
		#ifdef DBG_U2U
		UART_Printf(&UPPER_COM_HUART, "DBG2:arrPWR0204_1_Buf\r\n");
		UART_Printf(&UPPER_COM_HUART, (const char*)arrPWR0204_1_Buf);
		UART_Printf(&UPPER_COM_HUART, "\r\n");

		#endif
  }
	else if(huart == &PWR0204_2_HUART)
  {
		
		UART_RxCallback_Flag = PWR0204_2_Flag;
		#ifdef DBG_U2U
//				UART_Printf(&UPPER_COM_HUART, "___________________________________\r\n");
		UART_Printf(&UPPER_COM_HUART, "DBG3:arrPWR0204_2_Buf\r\n");
		UART_Printf(&UPPER_COM_HUART, (const char*)arrPWR0204_2_Buf);
		UART_Printf(&UPPER_COM_HUART, "\r\n");
		#endif
  }
	else if(huart == &DAQ0010_1_HUART)
  {		
		UART_RxCallback_Flag = DAQ0010_1_Flag;
		#ifdef DBG_U2U
		UART_Printf(&UPPER_COM_HUART, "DBG4:arrDAQ0010_1_Buf\r\n");
		UART_Printf(&UPPER_COM_HUART, (const char*)arrDAQ0010_1_Buf);
		UART_Printf(&UPPER_COM_HUART, "\r\n");
		#endif
//    judgementDataHandler();
  }
//	else if(huart == &DAQ3003_1_HUART)// UART5 鸡肋
//  {
//		UART_Printf(&UPPER_COM_HUART, "DBG5:arrDAQ3003_1_Buf\r\n");
//		UART_Printf(&UPPER_COM_HUART, (const char*)arrDAQ3003_1_Buf);
//		UART_Printf(&UPPER_COM_HUART, "\r\n");
//  }  
}


const char *Copyright[] = {
	"======================================================================",
	"=                   (C) COPYRIGHT 2019                               =",
	"======================================================================",
	"=       KINGKONG POWER SUPPLY MODULE Application (Version 1.0.0)     =",
	"=                                                 Date:2019/08/04    =",
	"=                                                 By Enzo.sun        =",
	"======================================================================",
	"@End@"
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

extern __IO float g_current_zero_drift;

void receive_data_handel(void)
{
	if(arrUPPER_COM_RX_STA & 0x8000)
	{
			/*CMD*/
			if (!strncasecmp("PS_EN", (const char *)arrUPPER_COM_Buf, 5))
			{
				arrUPPER_COM_RX_STA = 0;
				output_config(PS_EN, 1);
				UART_Printf(&UPPER_COM_HUART,"PS_EN OK\r\n");
			}		
			else if (!strncasecmp("PS_DI", (const char *)arrUPPER_COM_Buf, 5))
			{
				arrUPPER_COM_RX_STA = 0;
				output_config(PS_DIS, 1);
				UART_Printf(&UPPER_COM_HUART,"PS_DI OK\r\n");
			}
			else if (!strncasecmp("Vi_Rd", (const char *)arrUPPER_COM_Buf, 5))
			{
				arrUPPER_COM_RX_STA = 0;
				float vi_tmp = 0;
				if (v_in_get(&vi_tmp) == HAL_OK)
				{				
					vi_tmp *= 1000;
					UART_Printf(&UPPER_COM_HUART,"Vi_Rd:%.3f[V] OK\r\n", round(vi_tmp)/1000);
				}
				else
				{
					UART_Printf(&UPPER_COM_HUART,"Vi_Rd:%.3f[V] FAIL\r\n", vi_tmp);
				}
			}
			else if (!strncasecmp("Vo_Rd", (const char *)arrUPPER_COM_Buf, 5))
			{
				arrUPPER_COM_RX_STA = 0;
				float vo_tmp = 0;
				if (v_out_get(&vo_tmp) == HAL_OK)
				{
					vo_tmp *= 1000;
					UART_Printf(&UPPER_COM_HUART,"Vo_Rd:%.3f[V] OK\r\n", round(vo_tmp)/1000);
				}
				else
				{
					UART_Printf(&UPPER_COM_HUART,"Vo_Rd:%.3f[V] FAIL\r\n", vo_tmp);
				}
			}
			else if (!strncasecmp("Io_Rd", (const char *)arrUPPER_COM_Buf, 5))
			{
				arrUPPER_COM_RX_STA = 0;
				float io_tmp = 0;
				if (cur_out_get(&io_tmp, g_current_zero_drift) == HAL_OK)
				{
					UART_Printf(&UPPER_COM_HUART,"Io_Rd:%.3f[A]Zero:%.5f OK\r\n", io_tmp, g_current_zero_drift);
				}
				else
				{
					UART_Printf(&UPPER_COM_HUART,"Io_Rd:%.3f[A]Zero:%.5f FAIL\r\n", io_tmp, g_current_zero_drift);
				}
			}
			else if (!strncasecmp("Tm_Rd", (const char *)arrUPPER_COM_Buf, 5))
			{
				arrUPPER_COM_RX_STA = 0;
				float tm_tmp = 0;
				if (temperature_get(&tm_tmp) == HAL_OK)
				{
					UART_Printf(&UPPER_COM_HUART,"Tm_Rd:%.3f[Celsius] OK\r\n", tm_tmp);
				}
				else
				{
					UART_Printf(&UPPER_COM_HUART,"Tm_Rd:%.3f[Celsius] FAIL\r\n", tm_tmp);
				}
			}
			else if (!strncasecmp("Fo_Rd", (const char *)arrUPPER_COM_Buf, 5))
			{
				arrUPPER_COM_RX_STA = 0;
				uint16_t force_tmp = 0;
				force_config_read();
				force_get(&force_tmp);
				UART_Printf(&UPPER_COM_HUART,"Fo_Rd:%d[g] OK\r\n", force_tmp);
			}
			
			else if (!strncasecmp("Vo_St", (const char *)arrUPPER_COM_Buf, 5))
			{
				arrUPPER_COM_RX_STA = 0;
				vout_debug_flag_g = 1;
				uint8_t buf_tmp[8] = {0};
				float volt_tmp = 0;
				
				memcpy(&buf_tmp, (const char *)arrUPPER_COM_Buf + 6, 8);//15.1234
				volt_tmp = atof((const char*)buf_tmp);
				memset((void *)(arrUPPER_COM_Buf + 6), 0, 8);
				
				if (vol_set(&volt_tmp) == HAL_OK)//
				{
					UART_Printf(&UPPER_COM_HUART,"Vo_St:%g[V] OK\r\n", volt_tmp);
				}
				else
				{
					UART_Printf(&UPPER_COM_HUART,"Vo_St:%g[V] FAIL\r\n", volt_tmp);
				}
			}			
			else if (!strncasecmp("Fo_St", (const char *)arrUPPER_COM_Buf, 5))
			{
				arrUPPER_COM_RX_STA = 0;
				vout_debug_flag_g = 1;
				uint8_t buf_tmp[4] = {0};
				float force_tmp = 0;
				
				memcpy(&buf_tmp, (const char *)arrUPPER_COM_Buf + 6, 8);
				force_tmp = atof((const char*)buf_tmp);
				memset((void *)(arrUPPER_COM_Buf + 6), 0, 3);
				
				if (force_set(&force_tmp) == HAL_OK)//
				{
					UART_Printf(&UPPER_COM_HUART,"Fo_St:%g[g] OK\r\n", force_tmp);
				}
				else
				{
					UART_Printf(&UPPER_COM_HUART,"Fo_St:%g[g] FAIL\r\n", force_tmp);
				}
			}			
			else if (!strncasecmp("Err_Rd", (const char *)arrUPPER_COM_Buf, 5))
			{
				arrUPPER_COM_RX_STA = 0;
				ps_error_read();
			}
			else if (!strncasecmp("CalRd", (const char *)arrUPPER_COM_Buf, 5))
			{
				arrUPPER_COM_RX_STA = 0;
				cali_read();
				force_config_read();
				mcu_soft_start();
			}	
			else if (!strncasecmp("CalWt", (const char *)arrUPPER_COM_Buf, 5))
			{
				arrUPPER_COM_RX_STA = 0;		
				if(cali_write((const uint8_t *)arrUPPER_COM_Buf + 5) == HAL_OK)	
				{
					UART_Printf(&UPPER_COM_HUART,"CalWt OK\r\n");
					cali_read();
					UART_Printf(&UPPER_COM_HUART,"restart-ing\r\n");
					HAL_Delay(1000);
					mcu_soft_start();
				}
				else
				{
					UART_Printf(&UPPER_COM_HUART,"CalWt FAIL\r\n");
				}
			}	
			else if (!strncasecmp("*RST", (const char *)arrUPPER_COM_Buf, 4))
			{
				HAL_NVIC_DisableIRQ(TIM4_IRQn);
				HAL_NVIC_DisableIRQ(USART1_IRQn);
				HAL_NVIC_SystemReset();
				arrUPPER_COM_RX_STA = 0;
			}
			else if (!strncasecmp("*Help", (const char *)arrUPPER_COM_Buf, 5)) //注意 此操作需要手动重启
			{
				arrUPPER_COM_RX_STA = 0;
				UART_Printf(&UPPER_COM_HUART, (const char *)Copyright);
				UART_Printf(&UPPER_COM_HUART, (const char *)CmdBrief);
			}			
			else if (!strncasecmp("SlChk", (const char *)arrUPPER_COM_Buf, 5)) 
			{
				arrUPPER_COM_RX_STA = 0;
				ps_error_read();
			}			
			else if (!strncasecmp("Versi", (const char *)arrUPPER_COM_Buf, 5)) 
			{
				arrUPPER_COM_RX_STA = 0;
				UART_Printf(&UPPER_COM_HUART,"HW Version:%s\r\nFW Version:%s\r\nSW Version:TBD \r\n\r\n", HW_REVISION, FW_REVISION);
			}
			else if (!strncasecmp("*Boot", (const char *)arrUPPER_COM_Buf, 5)) 
			{
				arrUPPER_COM_RX_STA = 0;
				UART_Printf(&UPPER_COM_HUART, (const char *)"ERROR:TBD\r\n");
			}
			else
			{				
				arrUPPER_COM_RX_STA = 0;
				UART_Printf(&UPPER_COM_HUART,"\r\nCommand Error\r\n");
			}
	}
}
