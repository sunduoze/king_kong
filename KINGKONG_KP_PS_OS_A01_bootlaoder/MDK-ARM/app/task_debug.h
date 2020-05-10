/*
 * task_debug.h
 *
 * Created on: 2018��2��27��
 * Author: Enzo
 */
#ifndef TASK_DEBUG_H_
#define TASK_DEBUG_H_

#include "stdint.h"
#include "stm32f1xx_hal.h"

#include "usart.h"

typedef enum{

	RolKp = 0,
	RolKi,
	RolKd,

	PitKp,
	PitKi,
	PitKd,

	YawKp,
	YawKi,
	YawKd,

	RolOmgKp,
	RolOmgKi,
	RolOmgKd,

	PitOmgKp,
	PitOmgKi,
	PitOmgKd,

	YawOmgKp,
	YawOmgKi,
	YawOmgKd,

	ExpRol,
	ExpPit,
	ExpYaw,

	Throttle,
	WatchDog,
	DogBattary,

	RealRol,
	RealPit,
	RealYaw,

  ChassisCurrent1,
  ChassisCurrent2,
  ChassisCurrent3,
  ChassisCurrent4,

  ChassisVoltage,	//total
  ChassisCurrent,	//total

  LandingStatus,
  BinarySensor,	// can express many 0/1 sensors 
  StateMachine1,

  RemainLifeValue,
  ChassisOmega,		//landing the island
  ChassisAngle,

	GyroKp,
	GyroKi,
	GyroKd,

	Monitor1,
	Monitor2,
	Monitor3,
	Monitor4,
	Monitor5,
	Monitor6,
	Monitor7,
	Monitor8,

	SetupA,
	SetupB,
	SetupC,
	CmdJump2IAP,
	//for cmds
	CmdGyroNeedCalibrate,
	CmdReadAllFromMcu,  //PC���ͳ��ĸ���ֵ��0����MCU�������ʹ MCU���ص�ǰ�������в�����
	CmdSaveAllToFlash,  //PC���ͳ��ĸ���ֵ��0����MCU�������ʹ MCU���浱ǰ�������в�����Flash
	CmdResetMCU, 				//�������
	CmdMcuGotParamOK,   //PC�������0����˵��MCU�ɹ��յ���ִ�����
	//���ĸ�����������ʾPC��MCU���������Ӧ��
  
  //��
  MixAngle,
  MixX,
  MixY,

  RcTableLength,
}RcTableType;

enum{
    Head1 = 0,
    Head2,
    DataID,
    Byte0,
    Byte1,
    Byte2,
    Byte3,
    SumCheck,
    Tail,
    FrameLength,    //length = 9
};  //����֡���ֽ�˳����data��head1�� = 0x55 

uint8_t debugFrame[FrameLength];

typedef union{
	uint8_t   u8Type[4];
	int8_t    s8Type[4];
	uint16_t  u16Type[2];
	int16_t   s16Type[2];
  int32_t   s32Type;
  uint32_t  u32Type;
	float     fType;
}FloatConvertType; 
//������Ҫע��ע���С�ˣ�

extern void debugSendFrame(UART_HandleTypeDef *huart, RcTableType id, float data);

#endif /*TASK_DEBUG_H_*/


