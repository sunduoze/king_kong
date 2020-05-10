/*
 * bsp_iic1.c
 *
 * Created on: 2018��2��27��
 * Author: Enzo
 */

#include "bsp_iic1.h"


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

//void I2C1_SDA_IN(void)
//{
//	SDA_Port->CRL&=0X0FFFFFFF;	SDA_Port->CRL|=0X30000000;
//}

//void I2C1_SDA_OUT(void)
//{
//	SDA_Port->CRL&=0X0FFFFFFF;	SDA_Port->CRL|=0X80000000;
//}
//typedef struct
//{
////	(void*)IIC1_GPIO_Init;
//	GPIO_TypeDef* SDA_Port;
//	GPIO_TypeDef* SCL_Port;
//	__IO uint16_t SDA_Pin;
//	__IO uint16_t SCL_Pin;
//	void (*I2C_SCL)(void);
//	void (*I2C_SDA)(void);	  
//	void (*I2C1_SDA_IN)(void);	 
//	void (*I2C1_SDA_OUT)(void);	 	
////	__IO uint16_t I2C_SDA_L;

////		__IO uint16_t I2C_SDA_L;

//} GPIO_IIC1_TypeDef;





/**
  * @brief  IIC ר��Delay
  * @param  delayus
  * @retval None
  */
void Delayus_IIC1_1(uint16_t delayus)//ʵ��1us
{
    uint16_t i;
    while(delayus--)
    {
        i = 2;
        while(i--);
    }
}

//����IIC��ʼ�ź�
void IIC1_Start(void)
{
    I2C1_SDA_OUT();     //sda�����
    I2C1_SDA_H;
    I2C1_SCL_H;
    Delayus_IIC1_1(50);
    I2C1_SDA_L;//START:when CLK is high,DATA change form high to low
    Delayus_IIC1_1(60);
    I2C1_SCL_L;//ǯסI2C���ߣ�׼�����ͻ��������
}
//����IICֹͣ�ź�
void IIC1_Stop(void)
{
    I2C1_SDA_OUT();//sda�����
    I2C1_SCL_L;
    I2C1_SDA_L;//STOP:when CLK is high DATA change form low to high
    Delayus_IIC1_1(60);
    I2C1_SCL_H;
    I2C1_SDA_H;//����I2C���߽����ź�
    Delayus_IIC1_1(60);
}
//�ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ��
//        0������Ӧ��ɹ�
uint8_t IIC1_Wait_Ack(void)
{
    uint8_t ucErrTime = 0;
    I2C1_SDA_IN();      //SDA����Ϊ����
    I2C1_SDA_H;
    Delayus_IIC1_1(10);//ʵ��10us(1);
    I2C1_SCL_H;
    Delayus_IIC1_1(10);
    while(I2C1_READ_SDA)
    {
        ucErrTime++;
        if(ucErrTime > 250)
        {
            IIC1_Stop();
            return 1;
        }
    }
    I2C1_SCL_L;//ʱ�����0
    return 0;
}
//����ACKӦ��
void IIC1_Ack(void)
{
    I2C1_SCL_L;
    I2C1_SDA_OUT();
    I2C1_SDA_L;
    Delayus_IIC1_1(20);
    I2C1_SCL_H;
    Delayus_IIC1_1(50);
    I2C1_SCL_L;
}
//������ACKӦ��
void IIC1_NAck(void)
{
    I2C1_SCL_L;
    I2C1_SDA_OUT();
    I2C1_SDA_H;
    Delayus_IIC1_1(20);
    I2C1_SCL_H;
    Delayus_IIC1_1(50);
    I2C1_SCL_L;
}
//IIC����һ���ֽ�
//���شӻ�����Ӧ��
//1����Ӧ��
//0����Ӧ��
void IIC1_Send_Byte(uint8_t txd)
{
    uint8_t t;
    I2C1_SDA_OUT();
    I2C1_SCL_L;//����ʱ�ӿ�ʼ���ݴ���
    for(t = 0; t < 8; t++)
    {
        if((txd & 0x80) >> 7)
        {
            I2C1_SDA_H;
        }
        else
        {
            I2C1_SDA_L;
        }
        txd <<= 1;
        Delayus_IIC1_1(20);   //��TEA5767��������ʱ���Ǳ����
        I2C1_SCL_H;
        Delayus_IIC1_1(20);
        I2C1_SCL_L;
        Delayus_IIC1_1(20);
    }
}
//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK
uint8_t IIC1_Read_Byte(uint8_t ack)
{
    uint8_t i, receive = 0;
    I2C1_SDA_IN();//SDA����Ϊ����
    for(i = 0; i < 8; i++ )
    {
        I2C1_SCL_L;
        Delayus_IIC1_1(20);
        I2C1_SCL_H;
        receive <<= 1;
        if(I2C1_READ_SDA)receive++;
        Delayus_IIC1_1(10);
    }
    if (!ack)
        IIC1_NAck();//����nACK
    else
        IIC1_Ack(); //����ACK
    return receive;
}

uint8_t IIC1_Read_One_Byte(uint8_t Address, uint8_t ReadAddr)
{
    uint8_t  temp;

    IIC1_Start();
    IIC1_Send_Byte((Address << 1) & 0xfe);               //����������ַ0XA0,д����
    IIC1_Wait_Ack();

    IIC1_Send_Byte(ReadAddr);               //���͵͵�ַ
    IIC1_Wait_Ack();
    IIC1_Start();
    IIC1_Send_Byte((Address << 1) | 0x01);       //�������ģʽ
    IIC1_Wait_Ack();
    temp = IIC1_Read_Byte(0);
    IIC1_Stop();
    Delayus_IIC1_1(100);	                         //��ʱһ��ʱ�䲻Ȼ����д���ɹ�
    return temp;
}

void IIC1_Write_One_Byte(uint8_t daddr, uint8_t COMM, uint8_t data)
{
    IIC1_Start();
    IIC1_Send_Byte((daddr << 1) & 0xfe);               //����������ַ0XA0,д����
    IIC1_Wait_Ack();

    IIC1_Send_Byte(COMM);               //���͵͵�ַ
    IIC1_Wait_Ack();

    IIC1_Send_Byte(data);
    IIC1_Wait_Ack();

    IIC1_Stop();
    Delayus_IIC1_1(100);	                         //��ʱһ��ʱ�䲻Ȼ����д���ɹ�
}

void IIC1_Write_Two_Byte(uint8_t daddr, uint8_t COMM, uint16_t data)
{
    IIC1_Start();
    IIC1_Send_Byte((daddr << 1) & 0xfe);               //����������ַ0XA0,д����
    IIC1_Wait_Ack();

    IIC1_Send_Byte(COMM);               //���͵͵�ַ
    IIC1_Wait_Ack();

    IIC1_Send_Byte((uint8_t)(data & 0x00ff));	    //Set Port0 IO
    IIC1_Wait_Ack();
    IIC1_Send_Byte((uint8_t)((data & 0xff00) >> 8));	//Set Port1 IO
    IIC1_Wait_Ack();

    IIC1_Stop();
    Delayus_IIC1_1(100);	                         //��ʱһ��ʱ�䲻Ȼ����д���ɹ�
}

uint16_t IIC1_Read_TWO_Byte(uint8_t Address, uint8_t ReadAddr)
{
    uint8_t  tempH, tempL;

    IIC1_Start();
    IIC1_Send_Byte((Address << 1) & 0xfe);               //����������ַ0XA0,д����
    IIC1_Wait_Ack();

    IIC1_Send_Byte(ReadAddr);               //���͵͵�ַ
    IIC1_Wait_Ack();
    IIC1_Start();
    IIC1_Send_Byte((Address << 1) | 0x01);       //�������ģʽ
    IIC1_Wait_Ack();
    tempL = IIC1_Read_Byte(1);
    tempH = IIC1_Read_Byte(0);
    IIC1_Stop();
    Delayus_IIC1_1(100);	                         //��ʱһ��ʱ�䲻Ȼ����д���ɹ�
    return (tempH << 8) + tempL;
}
uint8_t IIC1_Dvice_find(uint8_t daddr)
{
    IIC1_Start();
    IIC1_Send_Byte((daddr << 1) & 0xfe);               //����������ַ0XA0,д����
    if(IIC1_Wait_Ack() == 0)return 1;
    else return 0;
}
void IIC1_ALS_intit(void)
{
    IIC1_Start();
    IIC1_Send_Byte(0x52);
    IIC1_Wait_Ack();
    IIC1_Send_Byte(0x8F); //0x8f
    IIC1_Wait_Ack();
    IIC1_Send_Byte(0x01);
    IIC1_Wait_Ack();

    IIC1_Start();
    IIC1_Send_Byte(0x52);
    IIC1_Wait_Ack();
    IIC1_Send_Byte(0x81);
    IIC1_Wait_Ack();
    IIC1_Send_Byte(0x02);
    IIC1_Wait_Ack();

    IIC1_Start();
    IIC1_Send_Byte(0x52);
    IIC1_Wait_Ack();
    IIC1_Send_Byte(0x80);
    IIC1_Wait_Ack();
    IIC1_Send_Byte(0x03);
    IIC1_Wait_Ack();
    IIC1_Stop();
}






