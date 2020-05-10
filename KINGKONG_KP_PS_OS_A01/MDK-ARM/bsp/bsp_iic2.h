/*
 * bsp_iic1.h
 *
 * Created on: 2018年2月27日
 * Author: Enzo
 */
#ifndef BSP_IIC2_H_
#define BSP_IIC2_H_

#include "stdint.h"
#include "stm32f1xx_hal.h"



//typedef struct
//{
////	(void*)IIC_GPIO_Init;
//	GPIO_TypeDef* SDA_Port;
//	GPIO_TypeDef* SCL_Port;
//	__IO uint16_t SDA_Pin;
//	__IO uint16_t SCL_Pin;
//	
//	__IO uint16_t I2C_SCL;
//	__IO uint16_t I2C_SCL_L;
//	__IO uint16_t I2C_SDA_H;
//	__IO uint16_t I2C_SDA_L;

//		__IO uint16_t I2C_SDA_L;
//	
//	SDA_IN,
//	I2C2_SDA_IN,
//	
//} GPIO_IIC_TypeDef;

//typedef struct
//{
////	`GPIO_IIC_TypeDef IIC,
//	
//	(void*)Init,
//	(void*)Start,
//	(void*)Stop,
//	(void*)Wait_Ack,
//	(void*)Ack,
//	(void*)NAck,

//	(void*)WriteByte,
//	(void*)WriteOneByte,
//	(void*)WriteTwoByte,
//	(void*)ReadByte,
//	(void*)ReadOneByte,			
//	(void*)ReadTwoByte,			

//	(void*)DviceFind,
//} IIC_TypeDef;

//void	IIC2_SDA_IN(){GPIOB->CRL&=0X0FFFFFFF;	GPIOB->CRL|=0X80000000;}

#define I2C2_SDA_IN()  {IIC2_S_SDA_GPIO_Port->CRH&=0XFFFFFFF0;	IIC2_S_SDA_GPIO_Port->CRH|=0X00000008;}
#define I2C2_SDA_OUT() {IIC2_S_SDA_GPIO_Port->CRH&=0XFFFFFFF0;	IIC2_S_SDA_GPIO_Port->CRH|=0X00000003;}

//IO操作函数	 
//#define IIC_SCL    PEout(7) //SCL
//#define IIC_SDA    PEout(8) //SDA	 


#define 	I2C2_READ_SDA  				HAL_GPIO_ReadPin(IIC2_S_SDA_GPIO_Port, IIC2_S_SDA_Pin)


#define		I2C2_SCL_L				HAL_GPIO_WritePin(IIC2_S_SCL_GPIO_Port, IIC2_S_SCL_Pin, GPIO_PIN_RESET);
#define		I2C2_SCL_H				HAL_GPIO_WritePin(IIC2_S_SCL_GPIO_Port, IIC2_S_SCL_Pin, GPIO_PIN_SET);

#define		I2C2_SDA_L				HAL_GPIO_WritePin(IIC2_S_SDA_GPIO_Port, IIC2_S_SDA_Pin, GPIO_PIN_RESET);
#define		I2C2_SDA_H				HAL_GPIO_WritePin(IIC2_S_SDA_GPIO_Port, IIC2_S_SDA_Pin, GPIO_PIN_SET);

#define		RELAY_STATE_EN		HAL_GPIO_WritePin(RELAY_STATE_EN_GPIO_Port, RELAY_STATE_EN_Pin, GPIO_PIN_RESET);
#define		RELAY_STATE_DIS		HAL_GPIO_WritePin(RELAY_STATE_EN_GPIO_Port, RELAY_STATE_EN_Pin, GPIO_PIN_SET);

//IIC所有操作函数
extern void IIC2_Init(void);                //初始化IIC的IO口				 
extern void IIC2_Start(void);				//发送IIC开始信号
extern void IIC2_Stop(void);	  			//发送IIC停止信号
extern void IIC2_Send_Byte(uint8_t txd);			//IIC发送一个字节
extern uint8_t IIC2_Read_Byte(unsigned char ack);//IIC读取一个字节
extern uint8_t IIC2_Wait_Ack(void); 				//IIC等待ACK信号
extern void IIC2_Ack(void);					//IIC发送ACK信号
extern void IIC2_NAck(void);				//IIC不发送ACK信号

extern void IIC2_Write_One_Byte(uint8_t daddr,uint8_t COMM,uint8_t data);
extern uint8_t IIC2_Read_One_Byte(uint8_t daddr,uint8_t addr);	
extern uint16_t IIC2_Read_TWO_Byte(uint8_t Address,uint8_t ReadAddr);
extern void IIC2_Write_Two_Byte(uint8_t daddr,uint8_t COMM,uint16_t data);
extern void IIC2_ALS_intit(void);
extern uint8_t IIC2_Dvice_find(uint8_t daddr);

#endif /*BSP_IIC2_H_*/


