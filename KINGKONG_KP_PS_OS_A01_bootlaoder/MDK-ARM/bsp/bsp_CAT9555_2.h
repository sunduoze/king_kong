/*
 * bsp_CAT9555_1.h
 *
 * Created on: 2018年2月27日
 * Author: Enzo
 */
#ifndef BSP_CAT9555_2_H_
#define BSP_CAT9555_2_H_

#include "stdint.h"
#include "stm32f1xx_hal.h"
#include "bsp_iic2.h"


#define A 'A'
#define B 'B'
#define D 'D'
#define E 'E'

#define EN  '1'
#define DIS '0'

/*变量定义*/
//uint8_t RelayControl[]={"RS*****\r"}; //set on or off
//uint8_t RelayAllON[]={"RO\r"};   //ALL on
//uint8_t RelayAllOFF[]={"RF\r"};	//all off
//uint8_t OK[]={"OK*_*\r"};
//uint8_t AllRelayOff_EX_A2_B2[]={"RE\r"}; //all relay off BUT A2 B2
//uint8_t AllRelayOn_BUS_X[]={"RB_**\r\0"}; //all ON BUS X     ON/OFF

/*函数*/
extern void CAT9555_2_INIT(void);
//void ReadTestPoint(uint16_t ReadData,uint8_t ControlBit);
//void TestBoard_AllRelay_DIS(void);
//void TestPointON2line(uint HPoint, uint LPoint);//两线法测试
//void TestPointON4line(uint HPoint, uint LPoint,uint SensorH,uint SensorL); //四线法测试
//void TestPointON2line2(uint HPoint, uint LPoint);
//void TestPointON2line3(uint HPoint, uint LPoint);
//void TestPointON2lineOffLPoint(uint HPoint, uint LPoint);
//void TestPointON2lineOpposite(uint HPoint, uint LPoint);..
//void AllRelayOn_BUS_X_FUNC(char BUS_Name,char BITData);
extern void CAT9555_2_RelayBoard_AllRelay_DIS(void);
extern void CAT9555_2_RelayBoard_AllRelay_EN(void);
extern void CAT9555_2_ReadTestPoint(uint16_t ReadData,uint8_t ControlBit);
extern void CAT9555_2_WriteOneBit(uint8_t Address, uint8_t BitNum16, uint8_t WriteDate);
//extern void ReadTestPoint(uint16_t ReadData,uint8_t ControlBit);   //0XA001
//extern void RelayBoard_AllRelay_DIS(void);
//extern void RelayBoard_AllRelay_EN(void);



#endif /*BSP_CAT9555_2_H_*/


