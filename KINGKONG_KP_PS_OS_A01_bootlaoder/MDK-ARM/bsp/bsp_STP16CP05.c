/*
 * bsp_stp16cp05.c
 *
 * Created on: 2018年2月27日
 * Author: Enzo
 */
 
#include "bsp_stp16cp05.h"

/**
  * @brief  STP16CP05 SPI 写数据 
  * @param  dat: 数据 16位
  * @retval None
  */
void STP16CP05_WrDat(uint16_t dat)
{
	#ifdef SWUST_FREESCALE_LIB_Enzo
	uint16_t i = 0, temp = 0;
	for(i = 0; i < 16; i++) //Send a Bit
	{
			STP_SCK_L;
			temp = dat & 0x8000;
			if (temp == 0)
			{
					STP_MOSI_L;  //0
			}
			else
			{
					STP_MOSI_H;  //1
			}
			STP_SCK_H;
			dat<<=1;
	}
	#endif
}


/**
  * @brief  STP16CP05 单通道输出
  * @param  Channel: 通道编号
  * @retval None
  */
void STP16CP05_Single_IO_OUTPUT(uint8_t Channel)
{
	#ifdef SWUST_FREESCALE_LIB_Enzo
		STP_CS_L;
	static uint32_t temp_bit;
	if(Channel > 0 && Channel <= STP16CP05_CH)
	{
		Channel -= 1;
		if(Channel > 32)
		{
			temp_bit = 1<<(Channel - 32);
			STP16CP05_WrDat((temp_bit & 0xFFFF0000)>>16);
			STP16CP05_WrDat((temp_bit & 0xFFFF));
			STP16CP05_WrDat(0);
			STP16CP05_WrDat(0);
		}
		else
		{
			temp_bit = 1<<(Channel);
			STP16CP05_WrDat(0);
			STP16CP05_WrDat(0);
			STP16CP05_WrDat((temp_bit & 0xFFFF0000)>>16);
			STP16CP05_WrDat((temp_bit & 0xFFFF));
		}
		STP_LE_H;
		STP_LE_L;
	}
	#endif
		STP_CS_H;
}




/**
  * @brief  STP16CP05 单通道输出
  * @param  Channel: 通道编号
  * @retval None
  * @remark 
	* 	STP16CP05_Multi_IO_OUTPUT(0, EXIO_L_1 | EXIO_L_2);
	*		HAL_Delay(1000);
	*		STP16CP05_Multi_IO_OUTPUT(EXIO_H_33 | EXIO_H_34, 0);
	*		HAL_Delay(1000);
	*		STP16CP05_Single_IO_OUTPUT(64);
  */
void STP16CP05_Multi_IO_OUTPUT(uint32_t MultiChannel_H, uint32_t MultiChannel_L)
{

	#ifdef SWUST_FREESCALE_LIB_Enzo
	  assert_param(IS_EXIO(MultiChannel_H));
		assert_param(IS_EXIO(MultiChannel_L));

//	static uint32_t temp_bit;
//	
//	if(Channel > 0 && Channel <= STP16CP05_CH)
//	{
//		Channel -= 1;
//		if(Channel > 32)
//		{
////			temp_H = Channel - 32;
//			temp_bit = 1<<(Channel - 32);
//			STP16CP05_WrDat((temp_bit & 0xFFFF0000)>>16);
//			STP16CP05_WrDat((temp_bit & 0xFFFF));
//			STP16CP05_WrDat(0);
//			STP16CP05_WrDat(0);
//		}
//		else
//		{
////			temp_L = Channel;
//			temp_bit = 1<<(Channel);
//			STP16CP05_WrDat(0);
//			STP16CP05_WrDat(0);
//			STP16CP05_WrDat((temp_bit & 0xFFFF0000)>>16);
//			STP16CP05_WrDat((temp_bit & 0xFFFF));
//		}
		
		
		STP16CP05_WrDat((MultiChannel_H & 0xFFFF0000)>>16);
		STP16CP05_WrDat((MultiChannel_H & 0xFFFF));
		STP16CP05_WrDat((MultiChannel_L & 0xFFFF0000)>>16);
		STP16CP05_WrDat((MultiChannel_L & 0xFFFF));

		
		
	//			HAL_SPI_Transmit(&hspi3, (uint8_t *)"ABCDE", 2, SPI3_TIME_OUT);//0xffff);
	//		HAL_GPIO_WritePin(IO_EXP_CS1_GPIO_Port, IO_EXP_CS1_Pin, GPIO_PIN_SET);
		STP_LE_H;
		STP_LE_L;
//	__NOP();
#endif

}


void STP16CP05_Multi_IO_OUTPUT2(uint32_t MultiChannel_H, uint32_t MultiChannel_L)
{
//	  assert_param(IS_EXIO(MultiChannel_H));
//		assert_param(IS_EXIO(MultiChannel_L));
////	uint32_t temp_H, temp_L;
//	static uint32_t temp_bit;
//	
//	if(Channel > 0 && Channel <= STP16CP05_CH)
//	{
//		Channel -= 1;
//		if(Channel > 32)
//		{
////			temp_H = Channel - 32;
//			temp_bit = 1<<(Channel - 32);
//			STP16CP05_WrDat((temp_bit & 0xFFFF0000)>>16);
//			STP16CP05_WrDat((temp_bit & 0xFFFF));
//			STP16CP05_WrDat(0);
//			STP16CP05_WrDat(0);
//		}
//		else
//		{
////			temp_L = Channel;
//			temp_bit = 1<<(Channel);
//			STP16CP05_WrDat(0);
//			STP16CP05_WrDat(0);
//			STP16CP05_WrDat((temp_bit & 0xFFFF0000)>>16);
//			STP16CP05_WrDat((temp_bit & 0xFFFF));
//		}
//	//			HAL_SPI_Transmit(&hspi3, (uint8_t *)"ABCDE", 2, SPI3_TIME_OUT);//0xffff);
//	//		HAL_GPIO_WritePin(IO_EXP_CS1_GPIO_Port, IO_EXP_CS1_Pin, GPIO_PIN_SET);
//		STP_LE_H;
//		STP_LE_L;
////	__NOP();
//		
//	}
}




