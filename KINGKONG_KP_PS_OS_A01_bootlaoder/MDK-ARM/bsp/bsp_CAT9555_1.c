/*
 * bsp_CAT9555_1.c
 *
 * Created on: 2018年2月27日
 * Author: Enzo
 */

#include "bsp_CAT9555_1.h"

/**
  * @brief  CAT9555_1_Config 
  * @param  Address:  PortData:
  * @retval None
  */
void CAT9555_1_Config(uint8_t Address, uint16_t PortData)
{
    //配置CAT9555 portx端口模式
    IIC1_Start();
    IIC1_Send_Byte(0x40 | (Address << 1)); //write slave address
    IIC1_Wait_Ack();
    IIC1_Send_Byte(0x06);           //write reg comm
    IIC1_Wait_Ack();
    IIC1_Send_Byte((uint8_t)(PortData & 0x00ff));	    //Set Port0 IO
    IIC1_Wait_Ack();
    IIC1_Send_Byte((uint8_t)((PortData & 0xff00) >> 8));	//Set Port1 IO
    IIC1_Wait_Ack();
    IIC1_Stop();
    //  IIC1_Start();
    //  HAL_Delay(5);
}

uint8_t CAT9555_1_ReadOneBit(uint8_t Address, uint8_t BitNum16)
{
    uint16_t temp0, temp1;
    uint8_t temp;
    //读取CAT9555 portx数据
    IIC1_Start();
    IIC1_Send_Byte(0x40 | Address << 1);
    IIC1_Wait_Ack();
    IIC1_Send_Byte(0x00);      //need read Portx reg
    IIC1_Wait_Ack();
    IIC1_Start();
    IIC1_Send_Byte(0x41 | Address << 1); //read from address
    IIC1_Wait_Ack();
    temp0 = IIC1_Read_Byte(1);
    // I2C_Ack();
    temp1 = IIC1_Read_Byte(0);
    // I2C_NAck();
    IIC1_Stop();
    // IIC1_Start();
    temp = (uint8_t)((temp1 << 8 | temp0) >> BitNum16) & 0x0001;
    return temp;
}

uint16_t CAT9555_1_ReadTwoByte(uint8_t Address)
{
    uint16_t temp0 = 0;
    uint16_t temp1 = 0;
    uint16_t temp2 = 0;

    //读取CAT9555 portx数据
    IIC1_Start();
    IIC1_Send_Byte(0x40 | Address << 1);
    IIC1_Wait_Ack();
    IIC1_Send_Byte(0x00);      //need read Portx reg
    IIC1_Wait_Ack();
    IIC1_Start();
    IIC1_Send_Byte(0x41 | Address << 1); //read from address
    IIC1_Wait_Ack();
    temp0 = IIC1_Read_Byte(1);
    // I2C_Ack();
    temp1 = IIC1_Read_Byte(0);
    // I2C_NAck();
    // IIC1_Start();
    IIC1_Stop();
    temp2 = (temp1 << 8) | temp0;
    return temp2;
}

void CAT9555_1_WriteOneBit(uint8_t Address, uint8_t BitNum16, uint8_t WriteDate)
{
    uint16_t temp;
    temp = CAT9555_1_ReadTwoByte(Address);
    if(WriteDate == 1)
        temp |= 1 << BitNum16;
    else if(WriteDate == 0)
        temp &= ~(1 << BitNum16);
    else
        //	printf("ERROR\r");
        //写数据到CAT9555 Portx端口
        IIC1_Start();
    IIC1_Send_Byte(0x40 | (Address << 1)); //write slave address|write command
    IIC1_Wait_Ack();
    IIC1_Send_Byte(0x02);	//Write reg comm
    IIC1_Wait_Ack();

    IIC1_Send_Byte((uint8_t)(temp & 0x00ff));	  //Write port0
    IIC1_Wait_Ack();
    IIC1_Send_Byte((uint8_t)((temp & 0xff00) >> 8)); //Write port1
    IIC1_Wait_Ack();
    //  IIC1_Start();
    IIC1_Stop();
    HAL_Delay(1);//Delayus(10);
}

void CAT9555_1_WriteTwoByte(uint8_t Address, uint16_t WriteDate)
{
    //写数据到CAT9555 Portx端口
    IIC1_Start();
    IIC1_Send_Byte(0x40 | (Address << 1)); //write slave address|write command
    IIC1_Wait_Ack();
    IIC1_Send_Byte(0x02);	//Write reg comm
    IIC1_Wait_Ack();

    IIC1_Send_Byte((uint8_t)(WriteDate & 0x00ff));	  //Write port0
    IIC1_Wait_Ack();
    IIC1_Send_Byte((uint8_t)((WriteDate & 0xff00) >> 8)); //Write port1
    IIC1_Wait_Ack();
    //	IIC1_Start();
    IIC1_Stop();
    HAL_Delay(1);

}

void CAT9555_1_INIT(void)
{
    //将Bit1~Bit128位配置为输出 8*16
    CAT9555_1_Config(0, 0);
    CAT9555_1_Config(1, 0);
    CAT9555_1_Config(2, 0);
    CAT9555_1_Config(3, 0);
    CAT9555_1_Config(4, 0);
    CAT9555_1_Config(5, 0);
    CAT9555_1_Config(6, 0);
    CAT9555_1_Config(7, 0);

    // RelayBoard_AllRelay_EN();
    CAT9555_1_RelayBoard_AllRelay_DIS();
    HAL_Delay(10);
    // RelayBoard_AllRelay_EN();
    CAT9555_1_RelayBoard_AllRelay_DIS();
    // RelayBoard_AllRelay_DIS();
    // RelayBoard_AllRelay_EN();
}





/**********继电器控制**********
功能:2 line 继电器板控制(测试点导通)
版本:V1.00   日期:13.07.01
修改:xiaodong.liu
作者:value
输入参数：A B D,E 4点
 ************************/


void CAT9555_1_ReadTestPoint(uint16_t ReadData, uint8_t ControlBit)  //0XA001
{
    uint8_t BUS, Point;
    BUS = ReadData >> 12;
    Point = ((ReadData & 0XF00) >> 8) * 100 + ((ReadData & 0X0F0) >> 4) * 10 + (ReadData & 0X00F);
    switch(BUS)
    {
    case 0x0A:
        if((1 <= Point) && (Point <= 16))
        {
            CAT9555_1_WriteOneBit(0x00, Point - 1, ControlBit);
        }
        else if((17 <= Point) && (Point <= 32))
            CAT9555_1_WriteOneBit(0x01, Point - 17, ControlBit);
        break;

    case 0x0B:
        if((1 <= Point) && (Point <= 16))
            CAT9555_1_WriteOneBit(0x02, Point - 1, ControlBit);
        else if((17 <= Point) && (Point <= 32))
            CAT9555_1_WriteOneBit(0x03, Point - 17, ControlBit);
        break;

    case 0x0D:
        if((1 <= Point) && (Point <= 16))
            CAT9555_1_WriteOneBit(0x04, Point - 1, ControlBit);
        else if((17 <= Point) && (Point <= 32))
            CAT9555_1_WriteOneBit(0x05, Point - 17, ControlBit);
        break;

    case 0x0E:
        if((1 <= Point) && (Point <= 16))
            CAT9555_1_WriteOneBit(0x06, Point - 1, ControlBit);
        else if((17 <= Point) && (Point <= 32))
            CAT9555_1_WriteOneBit(0x07, Point - 17, ControlBit);
        break;
    }
}



void CAT9555_1_RelayBoard_AllRelay_DIS(void)
{
    CAT9555_1_WriteTwoByte(0x00, 0x0000); //cat9555 chip 1
    CAT9555_1_WriteTwoByte(0x01, 0x0000); //cat9555 chip 2
    CAT9555_1_WriteTwoByte(0x02, 0x0000); //cat9555 chip 3
    CAT9555_1_WriteTwoByte(0x03, 0x0000); //cat9555 chip 4
    CAT9555_1_WriteTwoByte(0x04, 0x0000); //cat9555 chip 5
    CAT9555_1_WriteTwoByte(0x05, 0x0000); //cat9555 chip 6
    CAT9555_1_WriteTwoByte(0x06, 0x0000); //cat9555 chip 7
    CAT9555_1_WriteTwoByte(0x07, 0x0000); //cat9555 chip 8
}

void CAT9555_1_RelayBoard_AllRelay_EN(void)
{
    CAT9555_1_WriteTwoByte(0x00, 0xFFFF); //cat9555 chip 1
    CAT9555_1_WriteTwoByte(0x01, 0xFFFF); //cat9555 chip 2
    CAT9555_1_WriteTwoByte(0x02, 0xFFFF); //cat9555 chip 3
    CAT9555_1_WriteTwoByte(0x03, 0xFFFF); //cat9555 chip 4
    CAT9555_1_WriteTwoByte(0x04, 0xFFFF); //cat9555 chip 5
    CAT9555_1_WriteTwoByte(0x05, 0xFFFF); //cat9555 chip 6
    CAT9555_1_WriteTwoByte(0x06, 0xFFFF); //cat9555 chip 7
    CAT9555_1_WriteTwoByte(0x07, 0xFFFF); //cat9555 chip 8
}





