/*
 * bsp_io.h
 *
 * Created on: 2018Äê2ÔÂ27ÈÕ
 * Author: Enzo
 */
#ifndef BSP_IO_H_
#define BSP_IO_H_

#include "stdint.h"
#include "stm32f1xx_hal.h"

#define		PS_ENABLE		HAL_GPIO_WritePin(BUCK_PS_EN_GPIO_Port, BUCK_PS_EN_Pin, GPIO_PIN_SET);
#define		PS_DISABLE	HAL_GPIO_WritePin(BUCK_PS_EN_GPIO_Port, BUCK_PS_EN_Pin, GPIO_PIN_RESET);

//#define KEY3_Pin GPIO_PIN_2
//#define KEY3_GPIO_Port GPIOE
//#define KEY4_Pin GPIO_PIN_3
//#define KEY4_GPIO_Port GPIOE
//#define KEY5_Pin GPIO_PIN_4
//#define KEY5_GPIO_Port GPIOE
//#define KEY6_Pin GPIO_PIN_5
//#define KEY6_GPIO_Port GPIOE
//#define KEY7_Pin GPIO_PIN_6
//#define KEY7_GPIO_Port GPIOE
//#define KEY8_Pin GPIO_PIN_13
//#define KEY8_GPIO_Port GPIOC

#define Button1()						HAL_GPIO_ReadPin(Button1_GPIO_Port, Button1_Pin);
#define Button2()						HAL_GPIO_ReadPin(Button2_GPIO_Port, Button2_Pin);

#define OUT_CH1_ON()		{ HAL_GPIO_WritePin(OUT_CH1_GPIO_Port,OUT_CH1_Pin,GPIO_PIN_RESET);}
#define OUT_CH1_OFF()		{ HAL_GPIO_WritePin(OUT_CH1_GPIO_Port,OUT_CH1_Pin,GPIO_PIN_SET);	}
#define OUT_CH2_ON()		{ HAL_GPIO_WritePin(OUT_CH2_GPIO_Port,OUT_CH2_Pin,GPIO_PIN_RESET);}
#define OUT_CH2_OFF()		{ HAL_GPIO_WritePin(OUT_CH2_GPIO_Port,OUT_CH2_Pin,GPIO_PIN_SET);	}
#define OUT_CH3_ON()		{ HAL_GPIO_WritePin(OUT_CH3_GPIO_Port,OUT_CH3_Pin,GPIO_PIN_RESET);}
#define OUT_CH3_OFF()		{ HAL_GPIO_WritePin(OUT_CH3_GPIO_Port,OUT_CH3_Pin,GPIO_PIN_SET);	}
#define OUT_CH4_ON()		{ HAL_GPIO_WritePin(OUT_CH4_GPIO_Port,OUT_CH4_Pin,GPIO_PIN_RESET);}
#define OUT_CH4_OFF()		{ HAL_GPIO_WritePin(OUT_CH4_GPIO_Port,OUT_CH4_Pin,GPIO_PIN_SET);	}
#define OUT_CH5_ON()		{ HAL_GPIO_WritePin(OUT_CH5_GPIO_Port,OUT_CH5_Pin,GPIO_PIN_RESET);}
#define OUT_CH5_OFF()		{ HAL_GPIO_WritePin(OUT_CH5_GPIO_Port,OUT_CH5_Pin,GPIO_PIN_SET);	}
#define OUT_CH6_ON()		{ HAL_GPIO_WritePin(OUT_CH6_GPIO_Port,OUT_CH6_Pin,GPIO_PIN_RESET);}
#define OUT_CH6_OFF()		{ HAL_GPIO_WritePin(OUT_CH6_GPIO_Port,OUT_CH6_Pin,GPIO_PIN_SET);	}


#define LED1_ON()			{ HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,GPIO_PIN_SET);	}
#define LED1_OFF()		{ HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,GPIO_PIN_RESET);}
#define LED2_ON()			{ HAL_GPIO_WritePin(LED2_GPIO_Port,LED2_Pin,GPIO_PIN_SET);	}
#define LED2_OFF()		{ HAL_GPIO_WritePin(LED2_GPIO_Port,LED2_Pin,GPIO_PIN_RESET);}
#define LED3_ON()			{ HAL_GPIO_WritePin(LED3_GPIO_Port,LED3_Pin,GPIO_PIN_SET);	}
#define LED3_OFF()		{ HAL_GPIO_WritePin(LED3_GPIO_Port,LED3_Pin,GPIO_PIN_RESET);}

extern void Toggle_OUT_CH_All(void);
extern void Toggle_Led_All(void);

#define I2C2_SDA_IN()  {IIC2_S_SDA_GPIO_Port->CRH&=0XFFFFFFF0;	IIC2_S_SDA_GPIO_Port->CRH|=0X00000008;}
#define I2C2_SDA_OUT() {IIC2_S_SDA_GPIO_Port->CRH&=0XFFFFFFF0;	IIC2_S_SDA_GPIO_Port->CRH|=0X00000003;}

#endif /*BSP_IO_H_*/


