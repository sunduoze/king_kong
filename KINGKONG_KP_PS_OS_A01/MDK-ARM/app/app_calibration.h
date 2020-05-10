/*
 * app_test_procedure.h
 *
 * Created on: 2018年2月27日
 * Author: Enzo
 */
#ifndef APP_TEST_PROCEDURE_H_
#define APP_TEST_PROCEDURE_H_

#include "stdint.h"
#include "string.h"
#include "stm32f1xx_hal.h"

#include "bsp_uart.h"
#include "bsp_stp16cp05.h"
#include "bsp_CAT9555_1.h"
#include "bsp_CAT9555_2.h"
#include "task_uart.h"
#include "lib_crc16.h"
#include "bsp_io.h"

#define PROTOCOL_HEAD_LEN		(uint8_t)0x03
//Slaver Address[0-255]
#define EAGLE_BOARD_ADDR		(uint8_t)0x01
#define ADDR_MASK						(uint8_t)0xFF
//Function Code[0-127]
/****************************************/
#define MCU_RESET						(uint8_t)0x01
//#define EAGLE_BRD_SELF_CHK	(uint8_t)0x00
#define PrivateAllInit			(uint8_t)0x02 /*New Added*/
#define RelayAllOFF					(uint8_t)0x7F
#define RelayAllON					(uint8_t)0x7E
#define RelayAllInit				(uint8_t)0x7D

#define BRD_RELAY_IO				(uint8_t)0x70


#define EXT_RELAY_ADDR			(uint8_t)0x20//[20-2F] 16个设备 /******************/
#define EXT_RELAY_State			(uint8_t)0x71//回读外部继电器状态



/****************************************/
#define DAQ0010_MEAS_RES		(uint8_t)0x6F
#define DAQ0010_PWR_ON			(uint8_t)0x6E
#define DAQ0010_PWR_OFF			(uint8_t)0x6D

#define DAQ0010_VOLT				(uint8_t)0x66

#define DAQ0010_RANG				(uint8_t)0x65
#define DAQ0010_RANG_MASK		(uint8_t)0x0F

#define DAQ0010_CLAMP_VOLT	(uint8_t)0x64
#define DAQ0010_CLAMP_MASK	(uint8_t)0xFF

#define DAQ0010_OUT0				(uint8_t)0x63
#define DAQ0010_OUT1				(uint8_t)0x62
#define DAQ0010_IDN					(uint8_t)0x61
#define DAQ0010_INIT				(uint8_t)0x60
/****************************************/
#define PWR0204_1_MEAS_CUR	(uint8_t)0x5F
#define PWR0204_1_VOLT			(uint8_t)0x5E
#define PWR0204_1_CURR			(uint8_t)0x5D
#define PWR0204_1_MEAS_VOL	(uint8_t)0x5C

#define PWR0204_1_OUT0			(uint8_t)0x53
#define PWR0204_1_OUT1			(uint8_t)0x52
#define PWR0204_1_IDN				(uint8_t)0x51
#define PWR0204_1_INIT			(uint8_t)0x50
/****************************************/
#define PWR0204_2_MEAS_CUR	(uint8_t)0x4F
#define PWR0204_2_VOLT			(uint8_t)0x4E
#define PWR0204_2_CURR			(uint8_t)0x4D
#define PWR0204_2_MEAS_VOL	(uint8_t)0x4C

#define PWR0204_2_OUT0			(uint8_t)0x43
#define PWR0204_2_OUT1			(uint8_t)0x42
#define PWR0204_2_IDN				(uint8_t)0x41
#define PWR0204_2_INIT			(uint8_t)0x40
/****************************************/
#define CYLINDER_1_ON				(uint8_t)0x3F
#define CYLINDER_1_OFF			(uint8_t)0x3E
#define CYLINDER_2_ON				(uint8_t)0x3D
#define CYLINDER_2_OFF			(uint8_t)0x3C

/****************************************/
#define ERR_INITFAILED      (uint8_t)0x81
#define ERR_CRC_ERROR       (uint8_t)0x82
#define ERR_WRONG_COMMAND   (uint8_t)0x83
#define ERR_ADDROUTOFRANGE  (uint8_t)0x84
#define ERR_WRONG_PARAM     (uint8_t)0x85
#define ERR_LENOUTOFRANGE   (uint8_t)0x86
#define ERR_TIMEOUT         (uint8_t)0xFF



extern void AllHardwareInit_CMD(void);
extern void UART_IdleRxCallback(UART_HandleTypeDef *huart);
extern uint8_t LAT_Station(void);
extern void EagleBoardSelfCheck(void);
#endif /*APP_TEST_PROCEDURE_H_*/


