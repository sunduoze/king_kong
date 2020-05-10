/*
 * bsp_stp16cp05.h
 *
 * Created on: 2018Äê2ÔÂ27ÈÕ
 * Author: Enzo
 */
#ifndef BSP_STP16CP05_H_
#define BSP_STP16CP05_H_

#include "stdint.h"
#include "stm32f1xx_hal.h"


//#include "spi.h"
//#define SPI3_TIME_OUT 0x0F

#define	STP16CP05_NUM	4
#define	STP16CP05_CH	4 * 16

#define     STP_MOSI_L                     HAL_GPIO_WritePin(SPI3_MOSI_GPIO_Port,SPI3_MOSI_Pin,GPIO_PIN_RESET);
#define     STP_MOSI_H                     HAL_GPIO_WritePin(SPI3_MOSI_GPIO_Port,SPI3_MOSI_Pin,GPIO_PIN_SET);

#define	    STP_SCK_L                      HAL_GPIO_WritePin(SPI3_SCK_GPIO_Port,SPI3_SCK_Pin,GPIO_PIN_RESET);
#define     STP_SCK_H                      HAL_GPIO_WritePin(SPI3_SCK_GPIO_Port,SPI3_SCK_Pin,GPIO_PIN_SET);

#define	    STP_LE_L                       HAL_GPIO_WritePin(IO_EXP_LE1_GPIO_Port, IO_EXP_LE1_Pin,GPIO_PIN_RESET);
#define     STP_LE_H                       HAL_GPIO_WritePin(IO_EXP_LE1_GPIO_Port, IO_EXP_LE1_Pin,GPIO_PIN_SET);

#define	    STP_CS_L                       HAL_GPIO_WritePin(IO_EXP_CS1_GPIO_Port, IO_EXP_CS1_Pin,GPIO_PIN_RESET);
#define     STP_CS_H                       HAL_GPIO_WritePin(IO_EXP_CS1_GPIO_Port, IO_EXP_CS1_Pin,GPIO_PIN_SET);

extern void STP16CP05_Single_IO_OUTPUT(uint8_t Channel);
extern void STP16CP05_Multi_IO_OUTPUT(uint32_t MultiChannel_H, uint32_t MultiChannel_L);
extern void STP16CP05_WrDat(uint16_t dat);

#define	EXIO_L_1	(uint32_t)0x00000001	/*	Pin	1	selected	*/
#define	EXIO_L_2	(uint32_t)0x00000002	/*	Pin	2	selected	*/
#define	EXIO_L_3	(uint32_t)0x00000004	/*	Pin	3	selected	*/
#define	EXIO_L_4	(uint32_t)0x00000008	/*	Pin	4	selected	*/
#define	EXIO_L_5	(uint32_t)0x00000010	/*	Pin	5	selected	*/
#define	EXIO_L_6	(uint32_t)0x00000020	/*	Pin	6	selected	*/
#define	EXIO_L_7	(uint32_t)0x00000040	/*	Pin	7	selected	*/
#define	EXIO_L_8	(uint32_t)0x00000080	/*	Pin	8	selected	*/
#define	EXIO_L_9	(uint32_t)0x00000100	/*	Pin	9	selected	*/
#define	EXIO_L_10	(uint32_t)0x00000200	/*	Pin	10	selected	*/
#define	EXIO_L_11	(uint32_t)0x00000400	/*	Pin	11	selected	*/
#define	EXIO_L_12	(uint32_t)0x00000800	/*	Pin	12	selected	*/
#define	EXIO_L_13	(uint32_t)0x00001000	/*	Pin	13	selected	*/
#define	EXIO_L_14	(uint32_t)0x00002000	/*	Pin	14	selected	*/
#define	EXIO_L_15	(uint32_t)0x00004000	/*	Pin	15	selected	*/
#define	EXIO_L_16	(uint32_t)0x00008000	/*	Pin	16	selected	*/
							
#define	EXIO_L_17	(uint32_t)0x00010000	/*	Pin	17	selected	*/
#define	EXIO_L_18	(uint32_t)0x00020000	/*	Pin	18	selected	*/
#define	EXIO_L_19	(uint32_t)0x00040000	/*	Pin	19	selected	*/
#define	EXIO_L_20	(uint32_t)0x00080000	/*	Pin	20	selected	*/
#define	EXIO_L_21	(uint32_t)0x00100000	/*	Pin	21	selected	*/
#define	EXIO_L_22	(uint32_t)0x00200000	/*	Pin	22	selected	*/
#define	EXIO_L_23	(uint32_t)0x00400000	/*	Pin	23	selected	*/
#define	EXIO_L_24	(uint32_t)0x00800000	/*	Pin	24	selected	*/
#define	EXIO_L_25	(uint32_t)0x01000000	/*	Pin	25	selected	*/
#define	EXIO_L_26	(uint32_t)0x02000000	/*	Pin	26	selected	*/
#define	EXIO_L_27	(uint32_t)0x04000000	/*	Pin	27	selected	*/
#define	EXIO_L_28	(uint32_t)0x08000000	/*	Pin	28	selected	*/
#define	EXIO_L_29	(uint32_t)0x10000000	/*	Pin	29	selected	*/
#define	EXIO_L_30	(uint32_t)0x20000000	/*	Pin	30	selected	*/
#define	EXIO_L_31	(uint32_t)0x40000000	/*	Pin	31	selected	*/
#define	EXIO_L_32	(uint32_t)0x80000000	/*	Pin	32	selected	*/
							
#define	EXIO_L_All	(uint32_t)0xFFFFFFFF	/*	All	pins	selected	*/
							
#define	EXIO_H_33	(uint32_t)0x00000001	/*	Pin	33	selected	*/
#define	EXIO_H_34	(uint32_t)0x00000002	/*	Pin	34	selected	*/
#define	EXIO_H_35	(uint32_t)0x00000004	/*	Pin	35	selected	*/
#define	EXIO_H_36	(uint32_t)0x00000008	/*	Pin	36	selected	*/
#define	EXIO_H_37	(uint32_t)0x00000010	/*	Pin	37	selected	*/
#define	EXIO_H_38	(uint32_t)0x00000020	/*	Pin	38	selected	*/
#define	EXIO_H_39	(uint32_t)0x00000040	/*	Pin	39	selected	*/
#define	EXIO_H_40	(uint32_t)0x00000080	/*	Pin	40	selected	*/
#define	EXIO_H_41	(uint32_t)0x00000100	/*	Pin	41	selected	*/
#define	EXIO_H_42	(uint32_t)0x00000200	/*	Pin	42	selected	*/
#define	EXIO_H_43	(uint32_t)0x00000400	/*	Pin	43	selected	*/
#define	EXIO_H_44	(uint32_t)0x00000800	/*	Pin	44	selected	*/
#define	EXIO_H_45	(uint32_t)0x00001000	/*	Pin	45	selected	*/
#define	EXIO_H_46	(uint32_t)0x00002000	/*	Pin	46	selected	*/
#define	EXIO_H_47	(uint32_t)0x00004000	/*	Pin	47	selected	*/
#define	EXIO_H_48	(uint32_t)0x00008000	/*	Pin	48	selected	*/
							
#define	EXIO_H_49	(uint32_t)0x00010000	/*	Pin	49	selected	*/
#define	EXIO_H_50	(uint32_t)0x00020000	/*	Pin	50	selected	*/
#define	EXIO_H_51	(uint32_t)0x00040000	/*	Pin	51	selected	*/
#define	EXIO_H_52	(uint32_t)0x00080000	/*	Pin	52	selected	*/
#define	EXIO_H_53	(uint32_t)0x00100000	/*	Pin	53	selected	*/
#define	EXIO_H_54	(uint32_t)0x00200000	/*	Pin	54	selected	*/
#define	EXIO_H_55	(uint32_t)0x00400000	/*	Pin	55	selected	*/
#define	EXIO_H_56	(uint32_t)0x00800000	/*	Pin	56	selected	*/
#define	EXIO_H_57	(uint32_t)0x01000000	/*	Pin	57	selected	*/
#define	EXIO_H_58	(uint32_t)0x02000000	/*	Pin	58	selected	*/
#define	EXIO_H_59	(uint32_t)0x04000000	/*	Pin	59	selected	*/
#define	EXIO_H_60	(uint32_t)0x08000000	/*	Pin	60	selected	*/
#define	EXIO_H_61	(uint32_t)0x10000000	/*	Pin	61	selected	*/
#define	EXIO_H_62	(uint32_t)0x20000000	/*	Pin	62	selected	*/
#define	EXIO_H_63	(uint32_t)0x40000000	/*	Pin	63	selected	*/
#define	EXIO_H_64	(uint32_t)0x80000000	/*	Pin	64	selected	*/
							
#define	EXIO_H_All	(uint32_t)0xFFFFFFFF	/*	All	pins	selected	*/
#define EXIO_MASK             0xFFFFFFFFU /* PIN mask for assert test */


#define IS_EXIO(CH)           ((((CH) & EXIO_MASK ) != 0x00U) && (((CH) & ~EXIO_MASK) == 0x00U))

#endif /*BSP_STP16CP05_H_*/


