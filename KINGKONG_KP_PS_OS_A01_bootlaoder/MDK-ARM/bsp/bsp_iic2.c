/*
 * bsp_iic2.c
 *
 * Created on: 2018��2��27��
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
  * @brief  IIC ר��Delay
  * @param  delayus
  * @retval None
  */
void Delayus_IIC2_1(uint16_t delayus)//ʵ��1us
{
    uint16_t i;
    while(delayus--)
    {
        i = 2;
        while(i--);
    }
}

//����IIC��ʼ�ź�
void IIC2_Start(void)
{
    I2C2_SDA_OUT();     //sda�����
    I2C2_SDA_H;
    I2C2_SCL_H;
    Delayus_IIC2_1(50);
    I2C2_SDA_L;//START:when CLK is high,DATA change form high to low
    Delayus_IIC2_1(60);
    I2C2_SCL_L;//ǯסI2C���ߣ�׼�����ͻ��������
}
//����IICֹͣ�ź�
void IIC2_Stop(void)
{
    I2C2_SDA_OUT();//sda�����
    I2C2_SCL_L;
    I2C2_SDA_L;//STOP:when CLK is high DATA change form low to high
    Delayus_IIC2_1(60);
    I2C2_SCL_H;
    I2C2_SDA_H;//����I2C���߽����ź�
    Delayus_IIC2_1(60);
}
//�ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ��
//        0������Ӧ��ɹ�
uint8_t IIC2_Wait_Ack(void)
{
    uint8_t ucErrTime = 0;
    I2C2_SDA_IN();      //SDA����Ϊ����
    I2C2_SDA_H;
    Delayus_IIC2_1(10);//ʵ��10us(1);
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
    I2C2_SCL_L;//ʱ�����0
    return 0;
}
//����ACKӦ��
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
//������ACKӦ��
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
//IIC����һ���ֽ�
//���شӻ�����Ӧ��
//1����Ӧ��
//0����Ӧ��
void IIC2_Send_Byte(uint8_t txd)
{
    uint8_t t;
    I2C2_SDA_OUT();
    I2C2_SCL_L;//����ʱ�ӿ�ʼ���ݴ���
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
        Delayus_IIC2_1(20);   //��TEA5767��������ʱ���Ǳ����
        I2C2_SCL_H;
        Delayus_IIC2_1(20);
        I2C2_SCL_L;
        Delayus_IIC2_1(20);
    }
}
//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK
uint8_t IIC2_Read_Byte(uint8_t ack)
{
    uint8_t i, receive = 0;
    I2C2_SDA_IN();//SDA����Ϊ����
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
        IIC2_NAck();//����nACK
    else
        IIC2_Ack(); //����ACK
    return receive;
}

uint8_t IIC2_Read_One_Byte(uint8_t Address, uint8_t ReadAddr)
{
    uint8_t  temp;

    IIC2_Start();
    IIC2_Send_Byte((Address << 1) & 0xfe);               //����������ַ0XA0,д����
    IIC2_Wait_Ack();

    IIC2_Send_Byte(ReadAddr);               //���͵͵�ַ
    IIC2_Wait_Ack();
    IIC2_Start();
    IIC2_Send_Byte((Address << 1) | 0x01);       //�������ģʽ
    IIC2_Wait_Ack();
    temp = IIC2_Read_Byte(0);
    IIC2_Stop();
    Delayus_IIC2_1(100);	                         //��ʱһ��ʱ�䲻Ȼ����д���ɹ�
    return temp;
}

void IIC2_Write_One_Byte(uint8_t daddr, uint8_t COMM, uint8_t data)
{
    IIC2_Start();
    IIC2_Send_Byte((daddr << 1) & 0xfe);               //����������ַ0XA0,д����
    IIC2_Wait_Ack();

    IIC2_Send_Byte(COMM);               //���͵͵�ַ
    IIC2_Wait_Ack();

    IIC2_Send_Byte(data);
    IIC2_Wait_Ack();

    IIC2_Stop();
    Delayus_IIC2_1(100);	                         //��ʱһ��ʱ�䲻Ȼ����д���ɹ�
}

void IIC2_Write_Two_Byte(uint8_t daddr, uint8_t COMM, uint16_t data)
{
    IIC2_Start();
    IIC2_Send_Byte((daddr << 1) & 0xfe);               //����������ַ0XA0,д����
    IIC2_Wait_Ack();

    IIC2_Send_Byte(COMM);               //���͵͵�ַ
    IIC2_Wait_Ack();

    IIC2_Send_Byte((uint8_t)(data & 0x00ff));	    //Set Port0 IO
    IIC2_Wait_Ack();
    IIC2_Send_Byte((uint8_t)((data & 0xff00) >> 8));	//Set Port1 IO
    IIC2_Wait_Ack();

    IIC2_Stop();
    Delayus_IIC2_1(100);	                         //��ʱһ��ʱ�䲻Ȼ����д���ɹ�
}

uint16_t IIC2_Read_TWO_Byte(uint8_t Address, uint8_t ReadAddr)
{
    uint8_t  tempH, tempL;

    IIC2_Start();
    IIC2_Send_Byte((Address << 1) & 0xfe);               //����������ַ0XA0,д����
    IIC2_Wait_Ack();

    IIC2_Send_Byte(ReadAddr);               //���͵͵�ַ
    IIC2_Wait_Ack();
    IIC2_Start();
    IIC2_Send_Byte((Address << 1) | 0x01);       //�������ģʽ
    IIC2_Wait_Ack();
    tempL = IIC2_Read_Byte(1);
    tempH = IIC2_Read_Byte(0);
    IIC2_Stop();
    Delayus_IIC2_1(100);	                         //��ʱһ��ʱ�䲻Ȼ����д���ɹ�
    return (tempH << 8) + tempL;
}
uint8_t IIC2_Dvice_find(uint8_t daddr)
{
    IIC2_Start();
    IIC2_Send_Byte((daddr << 1) & 0xfe);               //����������ַ0XA0,д����
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






