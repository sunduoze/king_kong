/*
 * app_Communication.h
 *
 * Created on: 2017Äê11ÔÂ14ÈÕ
 * Author: Enzo
 */
#ifndef APP_COMMUNICATION_H_
#define APP_COMMUNICATION_H_

#include "stdint.h"
#include "app_main.h"

extern  int32_t tSteps;
extern  int32_t tAlpha1;//40;
extern  int32_t tAlpha2;//40;
extern  float tSetOmega;//1.65;//1->
extern  KeyBoard CurrentBoard;

extern void ReceiveDataHandel(void);
extern void ReceiveAndSaveData(KeyBoard *kbTemp);
extern KeyBoard CurrentBoard;
#endif /*APP_COMMUNICATION_H_*/


