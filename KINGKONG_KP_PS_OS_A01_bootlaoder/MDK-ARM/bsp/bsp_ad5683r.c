/*
 * bsp_ad5683r.c
 *
 * Created on: 2018年6月3日
 * Author: Enzo
 */ 

 /* Includes ------------------------------------------------------------------*/
#include "bsp_ad5683r.h"



/*********************SPI 写数据************************************/
void SPI_S1_WrDat(uint8_t dat)
{
	uint8_t i=8, temp=0;
	for(i=0;i<8;i++) //发送一个八位数据
	{
		SPI_S1_CLK_L;
//		HAL_Delay(1);
		temp = dat&0x80;
		if (temp == 0)
		{
			SPI_S1_MOSI_L;
		}
		else
		{
			SPI_S1_MOSI_H;
		}
//		HAL_Delay(1);
		SPI_S1_CLK_H;
//		HAL_Delay(1);
		dat<<=1;
	}
}

void AD5683R_Wr24BitDat(uint32_t dat)
{
	uint8_t i=0;
	uint32_t temp=0;
	dat &= 0x00FFFFFF;
	for(i=0;i<24;i++) //发送一个八位数据
	{
		SPI_S1_CLK_L;
//		HAL_Delay(1);
		temp = dat&0x800000;
		if (temp == 0)
		{
			SPI_S1_MOSI_L;
		}
		else
		{
			SPI_S1_MOSI_H;
		}
//		HAL_Delay(1);
		SPI_S1_CLK_H;
//		HAL_Delay(1);
		dat<<=1;
	}
}

/**
  * @brief  The function of this function is to write instructions AD5683 internal register.
* @param ulConValue : Command Value   Only [19:14]6Bits Data Eg:0x02 000000b 000010b
  * @arg None
  * @retval None
  */ 
		
void AD5683R_Write_Command(uint8_t ConValue){
		static uint32_t value;
		__IO uint8_t Tx_CMD[3]={0,0,0};
		value = (ConValue & 0x0000003F);//取六位
		value <<= 14;
		value |= (WRITE_CTRL_REG)<<20;					 				 // Append Command to bits 23-20.
//		value &= 0xFFC000;
    Tx_CMD[0] = (uint8_t)(value>>16);
    Tx_CMD[1] = (uint8_t)(value>>8);
    Tx_CMD[2] = (uint8_t)value;

		#ifdef HW_SPI
			uint8_t Rx_Value = 0;
			SPI_DAC_SS_LOW(SPI1);
			Spi_TransmitReceive(SPI1,Tx_CMD,&Rx_Value,3);
			SPI_DAC_SS_HIGH(SPI1);
		#else
			SPI_S1_CS_L;
			AD5683R_Wr24BitDat(value);
			SPI_S1_CS_H;
		#endif
}
/**
  * @brief  The function of this function is to write dac value AD5683 internal register.
  * @param ulDacValue : voltage Value
  * @arg [23:20]:Command [19:4]:Dac Data [3:0]: Default
  * @retval None
  */ 
void AD5683R_Write_Value_H(uint16_t DacValue){
	static uint32_t value;
	value = DacValue;
	value <<= 4;//
	value |= (WRITE_DAC_AND_INPUT_REG)<<20;
	SPI_S1_CS_L;
	AD5683R_Wr24BitDat(value);
	SPI_S1_CS_H;
}
void AD5683R_Write_Value_L(uint16_t DacValue){
	static uint32_t value;
//	uint8_t Tx_Data[3]={0,0,0};
	value = DacValue;
	value <<= 4;//
	value |= (WRITE_UPDATE_DAC_REG)<<20;
	SPI_S1_CS_L;
	AD5683R_Wr24BitDat(value);
	SPI_S1_CS_H;
}
/**
  * @brief  The function of this function is to write voltage value AD5683 internal register.
  * @param VoltValue : 0-Vref
  * @arg 
  * @retval None
  */ 
void AD5683R_Write_Voltage(float VoltValue){
	#define AD5683_VREF 1.25f// MD 不知为何 凸(艹皿艹 )
	static float Volt_Temp;
	if(VoltValue > 0.0f)
	{
		Volt_Temp = VoltValue / AD5683_VREF;
		if(VoltValue < 1.25f)
		{
			AD5683R_Write_Value_L(Volt_Temp * 65536);
		}
		else if(VoltValue < 2.5f)
		{
			AD5683R_Write_Value_H((uint32_t)((Volt_Temp - 1) * 65536));
		}
		else
		{
			AD5683R_Write_Value_H(65535);
		}
	}
}
	

void AD5683R_Init()
{
	AD5683R_Write_Command(0x0000|(uint8_t)0x00);
//		AD5683R_Write_Command(0x0000|(uint8_t)0x20);

}








/**
  * @brief  The function of this function is to write dac value AD5683 internal register.
  * @param ulDacValue : voltage Value
  * @arg [23:20]:Command [19:4]:Dac Data [3:0]: Default
  * @retval None
  */ 
void AD5683R_Write_Value(uint16_t DacValue){
	static uint32_t value;
//	uint8_t Tx_Data[3]={0,0,0};
	value = DacValue;
	value <<= 4;//
	value |= (WRITE_DAC_AND_INPUT_REG)<<20;
//	Tx_Data[0] = (uint8_t)(value>>16);
//	Tx_Data[1] = (uint8_t)(value>>8);
//	Tx_Data[2] = (uint8_t)value;

	#ifdef HW_SPI
		uint8_t Rx_Value = 0;
		SPI_DAC_SS_LOW(SPI1);
		Spi_TransmitReceive(SPI1,Tx_Data,&Rx_Value,3);
		SPI_DAC_SS_HIGH(SPI1);
	#else
		SPI_S1_CS_L;
		AD5683R_Wr24BitDat(value);
		SPI_S1_CS_H;
	#endif
}


