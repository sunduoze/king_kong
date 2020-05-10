/*
 * lib_crc16.h
 *
 * Created on: 2018年2月27日
 * Author: Enzo
 */
#ifndef LIB_CRC_H_
#define LIB_CRC_H_

#include "stdint.h"

uint16_t Get_Crc16(uint8_t *puchMsg,uint16_t usDataLen);
uint8_t Get_Crc8(uint8_t *ptr,uint16_t len);

#endif/*LIB_CRC_H_*/




























