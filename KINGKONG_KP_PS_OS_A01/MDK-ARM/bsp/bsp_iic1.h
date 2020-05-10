/*
 * bsp_iic1.h
 *
 * Created on: 2018年2月27日
 * Author: Enzo
 */
#ifndef BSP_IIC1_H_
#define BSP_IIC1_H_

#include "stdint.h"
#include "stm32f1xx_hal.h"
#include "main.h"


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
//	I2C1_SDA_IN,
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

//void	IIC1_SDA_IN(){GPIOB->CRL&=0X0FFFFFFF;	GPIOB->CRL|=0X80000000;}

#define I2C1_SDA_IN()  {I2C1_SDA_GPIO_Port->CRL&=0X0FFFFFFF;	I2C1_SDA_GPIO_Port->CRL|=0X80000000;}
#define I2C1_SDA_OUT() {I2C1_SDA_GPIO_Port->CRL&=0X0FFFFFFF;	I2C1_SDA_GPIO_Port->CRL|=0X30000000;}

//IO操作函数	 
//#define IIC_SCL    PBout(6) //SCL
//#define IIC_SDA    PBout(7) //SDA	 
#define 	I2C1_READ_SDA  		HAL_GPIO_ReadPin(I2C1_SDA_GPIO_Port, I2C1_SDA_Pin)


#define		I2C1_SCL_L				HAL_GPIO_WritePin(I2C1_SCL_GPIO_Port, I2C1_SCL_Pin, GPIO_PIN_RESET);
#define		I2C1_SCL_H				HAL_GPIO_WritePin(I2C1_SCL_GPIO_Port, I2C1_SCL_Pin, GPIO_PIN_SET);

#define		I2C1_SDA_L				HAL_GPIO_WritePin(I2C1_SDA_GPIO_Port, I2C1_SDA_Pin, GPIO_PIN_RESET);
#define		I2C1_SDA_H				HAL_GPIO_WritePin(I2C1_SDA_GPIO_Port, I2C1_SDA_Pin, GPIO_PIN_SET);

#define		RELAY_STATE_EN		HAL_GPIO_WritePin(RELAY_STATE_EN_GPIO_Port, RELAY_STATE_EN_Pin, GPIO_PIN_RESET);
#define		RELAY_STATE_DIS		HAL_GPIO_WritePin(RELAY_STATE_EN_GPIO_Port, RELAY_STATE_EN_Pin, GPIO_PIN_SET);

//IIC所有操作函数
extern void IIC1_Init(void);                //初始化IIC的IO口				 
extern void IIC1_Start(void);				//发送IIC开始信号
extern void IIC1_Stop(void);	  			//发送IIC停止信号
extern void IIC1_Send_Byte(uint8_t txd);			//IIC发送一个字节
extern uint8_t IIC1_Read_Byte(unsigned char ack);//IIC读取一个字节
extern uint8_t IIC1_Wait_Ack(void); 				//IIC等待ACK信号
extern void IIC1_Ack(void);					//IIC发送ACK信号
extern void IIC1_NAck(void);				//IIC不发送ACK信号

extern void IIC1_Write_One_Byte(uint8_t daddr,uint8_t COMM,uint8_t data);
extern uint8_t IIC1_Read_One_Byte(uint8_t daddr,uint8_t addr);	
extern uint16_t IIC1_Read_TWO_Byte(uint8_t Address,uint8_t ReadAddr);
extern void IIC1_Write_Two_Byte(uint8_t daddr,uint8_t COMM,uint16_t data);
extern void IIC1_ALS_intit(void);
extern uint8_t IIC1_Dvice_find(uint8_t daddr);

#endif /*BSP_IIC1_H_*/


