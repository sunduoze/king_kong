/*
 * bsp_iic2.c
 *
 * Created on: 2018年2月27日
 * Author: Enzo
 */

#include "bsp_iic2.h"


//void I2C_SCL(void)
//{
//	
//}

//void I2C_SDA(void)
//{
//	
//}

//void I2C_SCL_L(void)
//{
//	
//}

//void I2C2_SDA_IN(void)
//{
//	SDA_Port->CRL&=0X0FFFFFFF;	SDA_Port->CRL|=0X30000000;
//}

//void I2C2_SDA_OUT(void)
//{
//	SDA_Port->CRL&=0X0FFFFFFF;	SDA_Port->CRL|=0X80000000;
//}
//typedef struct
//{
////	(void*)IIC2_GPIO_Init;
//	GPIO_TypeDef* SDA_Port;
//	GPIO_TypeDef* SCL_Port;
//	__IO uint16_t SDA_Pin;
//	__IO uint16_t SCL_Pin;
//	void (*I2C_SCL)(void);
//	void (*I2C_SDA)(void);	  
//	void (*I2C2_SDA_IN)(void);	 
//	void (*I2C2_SDA_OUT)(void);	 	
////	__IO uint16_t I2C_SDA_L;

////		__IO uint16_t I2C_SDA_L;

//} GPIO_IIC2_TypeDef;





/**
  * @brief  IIC 专用Delay
  * @param  delayus
  * @retval None
  */
void Delayus_IIC2_1(uint16_t delayus)//实际1us
{
    uint16_t i;
    while(delayus--)
    {
        i = 2;
        while(i--);
    }
}

//产生IIC起始信号
void IIC2_Start(void)
{
    I2C2_SDA_OUT();     //sda线输出
    I2C2_SDA_H;
    I2C2_SCL_H;
    Delayus_IIC2_1(50);
    I2C2_SDA_L;//START:when CLK is high,DATA change form high to low
    Delayus_IIC2_1(60);
    I2C2_SCL_L;//钳住I2C总线，准备发送或接收数据
}
//产生IIC停止信号
void IIC2_Stop(void)
{
    I2C2_SDA_OUT();//sda线输出
    I2C2_SCL_L;
    I2C2_SDA_L;//STOP:when CLK is high DATA change form low to high
    Delayus_IIC2_1(60);
    I2C2_SCL_H;
    I2C2_SDA_H;//发送I2C总线结束信号
    Delayus_IIC2_1(60);
}
//等待应答信号到来
//返回值：1，接收应答失败
//        0，接收应答成功
uint8_t IIC2_Wait_Ack(void)
{
    uint8_t ucErrTime = 0;
    I2C2_SDA_IN();      //SDA设置为输入
    I2C2_SDA_H;
    Delayus_IIC2_1(10);//实际10us(1);
    I2C2_SCL_H;
    Delayus_IIC2_1(10);
    while(I2C2_READ_SDA)
    {
        ucErrTime++;
        if(ucErrTime > 250)
        {
            IIC2_Stop();
            return 1;
        }
    }
    I2C2_SCL_L;//时钟输出0
    return 0;
}
//产生ACK应答
void IIC2_Ack(void)
{
    I2C2_SCL_L;
    I2C2_SDA_OUT();
    I2C2_SDA_L;
    Delayus_IIC2_1(20);
    I2C2_SCL_H;
    Delayus_IIC2_1(50);
    I2C2_SCL_L;
}
//不产生ACK应答
void IIC2_NAck(void)
{
    I2C2_SCL_L;
    I2C2_SDA_OUT();
    I2C2_SDA_H;
    Delayus_IIC2_1(20);
    I2C2_SCL_H;
    Delayus_IIC2_1(50);
    I2C2_SCL_L;
}
//IIC发送一个字节
//返回从机有无应答
//1，有应答
//0，无应答
void IIC2_Send_Byte(uint8_t txd)
{
    uint8_t t;
    I2C2_SDA_OUT();
    I2C2_SCL_L;//拉低时钟开始数据传输
    for(t = 0; t < 8; t++)
    {
        if((txd & 0x80) >> 7)
        {
            I2C2_SDA_H;
        }
        else
        {
            I2C2_SDA_L;
        }
        txd <<= 1;
        Delayus_IIC2_1(20);   //对TEA5767这三个延时都是必须的
        I2C2_SCL_H;
        Delayus_IIC2_1(20);
        I2C2_SCL_L;
        Delayus_IIC2_1(20);
    }
}
//读1个字节，ack=1时，发送ACK，ack=0，发送nACK
uint8_t IIC2_Read_Byte(uint8_t ack)
{
    uint8_t i, receive = 0;
    I2C2_SDA_IN();//SDA设置为输入
    for(i = 0; i < 8; i++ )
    {
        I2C2_SCL_L;
        Delayus_IIC2_1(20);
        I2C2_SCL_H;
        receive <<= 1;
        if(I2C2_READ_SDA)receive++;
        Delayus_IIC2_1(10);
    }
    if (!ack)
        IIC2_NAck();//发送nACK
    else
        IIC2_Ack(); //发送ACK
    return receive;
}

uint8_t IIC2_Read_One_Byte(uint8_t Address, uint8_t ReadAddr)
{
    uint8_t  temp;

    IIC2_Start();
    IIC2_Send_Byte((Address << 1) & 0xfe);               //发送器件地址0XA0,写数据
    IIC2_Wait_Ack();

    IIC2_Send_Byte(ReadAddr);               //发送低地址
    IIC2_Wait_Ack();
    IIC2_Start();
    IIC2_Send_Byte((Address << 1) | 0x01);       //进入接收模式
    IIC2_Wait_Ack();
    temp = IIC2_Read_Byte(0);
    IIC2_Stop();
    Delayus_IIC2_1(100);	                         //延时一段时间不然数据写不成功
    return temp;
}

void IIC2_Write_One_Byte(uint8_t daddr, uint8_t COMM, uint8_t data)
{
    IIC2_Start();
    IIC2_Send_Byte((daddr << 1) & 0xfe);               //发送器件地址0XA0,写数据
    IIC2_Wait_Ack();

    IIC2_Send_Byte(COMM);               //发送低地址
    IIC2_Wait_Ack();

    IIC2_Send_Byte(data);
    IIC2_Wait_Ack();

    IIC2_Stop();
    Delayus_IIC2_1(100);	                         //延时一段时间不然数据写不成功
}

void IIC2_Write_Two_Byte(uint8_t daddr, uint8_t COMM, uint16_t data)
{
    IIC2_Start();
    IIC2_Send_Byte((daddr << 1) & 0xfe);               //发送器件地址0XA0,写数据
    IIC2_Wait_Ack();

    IIC2_Send_Byte(COMM);               //发送低地址
    IIC2_Wait_Ack();

    IIC2_Send_Byte((uint8_t)(data & 0x00ff));	    //Set Port0 IO
    IIC2_Wait_Ack();
    IIC2_Send_Byte((uint8_t)((data & 0xff00) >> 8));	//Set Port1 IO
    IIC2_Wait_Ack();

    IIC2_Stop();
    Delayus_IIC2_1(100);	                         //延时一段时间不然数据写不成功
}

uint16_t IIC2_Read_TWO_Byte(uint8_t Address, uint8_t ReadAddr)
{
    uint8_t  tempH, tempL;

    IIC2_Start();
    IIC2_Send_Byte((Address << 1) & 0xfe);               //发送器件地址0XA0,写数据
    IIC2_Wait_Ack();

    IIC2_Send_Byte(ReadAddr);               //发送低地址
    IIC2_Wait_Ack();
    IIC2_Start();
    IIC2_Send_Byte((Address << 1) | 0x01);       //进入接收模式
    IIC2_Wait_Ack();
    tempL = IIC2_Read_Byte(1);
    tempH = IIC2_Read_Byte(0);
    IIC2_Stop();
    Delayus_IIC2_1(100);	                         //延时一段时间不然数据写不成功
    return (tempH << 8) + tempL;
}
uint8_t IIC2_Dvice_find(uint8_t daddr)
{
    IIC2_Start();
    IIC2_Send_Byte((daddr << 1) & 0xfe);               //发送器件地址0XA0,写数据
    if(IIC2_Wait_Ack() == 0)return 1;
    else return 0;
}
void IIC2_ALS_intit(void)
{
    IIC2_Start();
    IIC2_Send_Byte(0x52);
    IIC2_Wait_Ack();
    IIC2_Send_Byte(0x8F); //0x8f
    IIC2_Wait_Ack();
    IIC2_Send_Byte(0x01);
    IIC2_Wait_Ack();

    IIC2_Start();
    IIC2_Send_Byte(0x52);
    IIC2_Wait_Ack();
    IIC2_Send_Byte(0x81);
    IIC2_Wait_Ack();
    IIC2_Send_Byte(0x02);
    IIC2_Wait_Ack();

    IIC2_Start();
    IIC2_Send_Byte(0x52);
    IIC2_Wait_Ack();
    IIC2_Send_Byte(0x80);
    IIC2_Wait_Ack();
    IIC2_Send_Byte(0x03);
    IIC2_Wait_Ack();
    IIC2_Stop();
}






