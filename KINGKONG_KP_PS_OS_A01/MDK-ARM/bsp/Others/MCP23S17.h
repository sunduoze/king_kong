/**
  ******************************************************************************
  * @file    MCP23S17.h 
  * @author  Junior Yip
  * @version 2.0.0
  * @date    20-July-2016
  * @modify  2017-08-06
  * @brief   MCP23S17 Driver Header
  ******************************************************************************
  * @History
  * ST Library version 3.5.0
  * SPI INTERFACE MAX SPEED :10 MHz
  * I/O PIN DEFAULT TO INPUT
  * WORK MODE : SEQUENTIAL MODE
  * <h2><center>&copy; COPYRIGHT 2016 Junior Yip</center></h2>
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef JUNIOR_MCP23S17_H
#define JUNIOR_MCP23S17_H



/* Includes ------------------------------------------------------------------*/
#ifdef USE_HAL_DRIVER
#if defined (STM32F030x6) || defined (STM32F030x8) ||                          \
    defined (STM32F031x6) || defined (STM32F038xx) ||                          \
    defined (STM32F042x6) || defined (STM32F048xx) || defined (STM32F070x6) || \
    defined (STM32F051x8) || defined (STM32F058xx) ||                          \
    defined (STM32F071xB) || defined (STM32F072xB) || defined (STM32F078xx) || defined (STM32F070xB) || \
    defined (STM32F091xC) || defined (STM32F098xx) || defined (STM32F030xC)
#include "stm32f0xx.h"
#include "stm32f0xx_hal.h"
#include "stm32f0xx_hal_spi.h"
#endif /* STM32F0xx */

#if defined (STM32F100xB) || defined (STM32F100xE) || defined (STM32F101x6) || \
    defined (STM32F101xB) || defined (STM32F101xE) || defined (STM32F101xG) || \
		defined (STM32F102x6) || defined (STM32F102xB) || defined (STM32F103x6) || \
    defined (STM32F103xB) || defined (STM32F103xE) || defined (STM32F103xG) || \
		defined (STM32F105xC) || defined (STM32F107xC)
#include "stm32f1xx.h"
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_spi.h"
#endif /* STM32F10x */

#if defined(STM32F2)
//Reserve for STM32F2
#endif /* STM32F2 */

#if defined(STM32F3)
//Reserve for STM32F3
#endif /* STM32F3 */

#if defined (STM32F405xx) || defined (STM32F415xx) || defined (STM32F407xx) || defined (STM32F417xx) || \
    defined (STM32F427xx) || defined (STM32F437xx) || defined (STM32F429xx) || defined (STM32F439xx) || \
    defined (STM32F401xC) || defined (STM32F401xE) || defined (STM32F410Tx) || defined (STM32F410Cx) || \
    defined (STM32F410Rx) || defined (STM32F411xE) || defined (STM32F446xx) || defined (STM32F469xx) || \
    defined (STM32F479xx) || defined (STM32F412Cx) || defined (STM32F412Rx) || defined (STM32F412Vx) || \
    defined (STM32F412Zx) || defined (STM32F413xx) || defined (STM32F423xx)
#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_spi.h"
#endif /* STM32F4 */

#if defined(STM32F7)
//Reserve for STM32F7
#endif /* STM32F7 */

#if defined(STM32L0)
//Reserve for STM32L0
#endif /* STM32L0 */

#if defined(STM32L1) 
//Reserve for STM32L1
#endif /* STM32L1 */

#if defined(STM32L4)
//Reserve for STM32L4
#endif

#endif /* USE_HAL_DRIVER */


#ifdef USE_STDPERIPH_DRIVER

#if defined (STM32F030) || defined (STM32F031) || defined (STM32F030X6)  || defined (STM32F030X8) || \
		defined (STM32F051) || defined (STM32F0XX) || defined (STM32F0XX_MD) ||    \
    defined (STM32F072) || defined (STM32F042) || defined (STM32F091)    ||    \
    defined (STM32F070xB) || defined (STM32F070x6) || defined (STM32F030xC) || \
		defined (STM32F0XX_LD) || defined (STM32F0XX_HD)
#include "stm32f0xx.h"
#include "stm32f0xx_spi.h"
#endif /* STM32F1 */

#if defined (STM32F10X_LD) || defined (STM32F10X_MD) || defined (STM32F10X_LD_VL) || \
		defined (STM32F10X_XL) || defined (STM32F10X_CL) || defined (STM32F10X_MD_VL) || \
		defined (STM32F10X_HD) || defined (STM32F10X_HD_VL)
#include "stm32f10x.h"
#include "stm32f10x_spi.h"
#endif /* STM32F1 */

#if defined(STM32F2)
//Reserve for STM32F2
#endif /* STM32F2 */

#if defined(STM32F3)
//Reserve for STM32F3
#endif /* STM32F3 */

#if defined (STM32F4XX)
#include "stm32f4xx.h"
#include "stm32f4xx_spi.h"
#endif /* STM32F4 */

#if defined(STM32F7)
//Reserve for STM32F7
#endif /* STM32F7 */

#if defined(STM32L0)
//Reserve for STM32L0
#endif /* STM32L0 */

#if defined(STM32L1) 
//Reserve for STM32L1
#endif /* STM32L1 */

#if defined(STM32L4)
//Reserve for STM32L4
#endif

#endif /* USE_STDPERIPH_DRIVER */

/* Exported constants --------------------------------------------------------*/
#define MCP_DEBUGOUT 0
#define USE_SIM_SPI  0
#define MAX_MCP23S17 6
#define MCP_TIME_OUT 0x000000FF //#define MCP_TIME_OUT 0x000FFFFF

#define MCP1  0x00
#define MCP2  0x01
#define MCP3  0x02
#define MCP4  0x03
#define MCP5  0x04
#define MCP6  0x05
//#define MCP7  0x06
//#define MCP8  0x07
//#define MCP9  0x08
//#define MCP10 0x09
//#define MCP11 0x0A
//#define MCP12 0x0B

/* Device OPCode Definition */
#define REG_WRITE           0x40 /* DEVICE WRITE OPCODE */
#define REG_READ            0x41 /* DEVICE READ  OPCODE */

/* REGISTER DEFAULT VALUE */
#define DEFAULT_VALUE       0x00 /* REGISTER DEFAULT VALUE                            */
#define IOCON_DEFAULT       0x44 /* IOCON REGISTER DEFAULT VALUE                      */
#define IODIR_INPUT_ALL     0xFF /* IODIR REGISTER INPUT  DEGAULT VALUE               */
#define IODIR_OUTPUT_ALL    0x00 /* IODIR REGISTER OUTPUT DEGAULT VALUE               */
#define IPOL_OPPOSITE_LOGIC 0xFF /* IPOL REGISTER DEGAULT VALUE,OUTPUT OPPOSITE LOGIC */
#define IPOL_SAME_LOGIC     0x00 /* IPOL REGISTER DEGAULT VALUE,OUTPUT SAME LOGIC     */
#define GPINT_ENABLE        0xFF /* ENABLE  GPIO FOR INTERRUPT-ON-CHANGE EVENT        */
#define GPINT_DISABLE       0x00 /* DISABLE GPIO FOR INTERRUPT-ON-CHANGE EVENT        */

/* REGISTER ADDRESS */
#define MCP23S17_IODIRA     0x00 /* IODIRA  :I/O A DIRECTION REGISTER                    */
#define MCP23S17_IODIRB     0x01 /* IODIRB  :I/O B DIRECTION REGISTER                    */
#define MCP23S17_IPOLA      0x02 /* IPOLA   :INPUT POLARITY PORT A REGISTER              */
#define MCP23S17_IPOLB      0x03 /* IPOLB   :INPUT POLARITY PORT B REGISTER              */
#define MCP23S17_GPINTENA   0x04 /* GPINTENA:INTERRUPT-ON-CHANGE PINS A                  */
#define MCP23S17_GPINTENB   0x05 /* GPINTENB:INTERRUPT-ON-CHANGE PINS B                  */
#define MCP23S17_DEFVALA    0x06 /* DEFVALA :DEFAULT VALUE REGISTER A                    */
#define MCP23S17_DEFVALB    0x07 /* DEFVALB :DEFAULT VALUE REGISTER B                    */
#define MCP23S17_INTCONA    0x08 /* INTCONA :INTERRUPT-ON-CHANGE CONTROL REGISTER A      */
#define MCP23S17_INTCONB    0x09 /* INTCONB :INTERRUPT-ON-CHANGE CONTROL REGISTER B      */
#define MCP23S17_IOCON      0x0A /* IOCON   :I/O EXPANDER CONFIGURATION REGISTER         */
#define MCP23S17_GPPUA      0x0C /* GPPUA   :GPIOA PULL-UP RESISTOR REGISTER             */
#define MCP23S17_GPPUB      0x0D /* GPPUB   :GPIOB PULL-UP RESISTOR REGISTER             */
#define MCP23S17_INTFA      0x0E /* INTFA   :INTERRUPT FLAG REGISTER A                   */
#define MCP23S17_INTFB      0x0F /* INTFB   :INTERRUPT FLAG REGISTER B                   */
#define MCP23S17_INTCAPA    0x10 /* INTCAPA :INTERRUPT CAPTURED VALUE REGISTER FOR GPIOA */
#define MCP23S17_INTCAPB    0x11 /* INTCAPB :INTERRUPT CAPTURED VALUE REGISTER FOR GPIOB */
#define MCP23S17_GPIOA      0x12 /* GPIOA   :GENERAL PURPOSE I/O PORT A REGISTER         */
#define MCP23S17_GPIOB      0x13 /* GPIOB   :GENERAL PURPOSE I/O PORT B REGISTER         */
#define MCP23S17_OLATA      0x14 /* OLATA   :OUTPUT LATCH A REGISTER0                    */
#define MCP23S17_OLATB      0x15 /* OLATB   :OUTPUT LATCH B REGISTER0                    */

/* IO Pin Address */
#define EXIO_Pin_None       0x00 /* MCP23S17 GPIO no Pin selected				  		*/
#define EXIO_Pin_0          0x01 /* MCP23S17 GPIO Pin 0 selected							*/
#define EXIO_Pin_1          0x02 /* MCP23S17 GPIO Pin 1 selected							*/
#define EXIO_Pin_2          0x04 /* MCP23S17 GPIO Pin 2 selected							*/
#define EXIO_Pin_3          0x08 /* MCP23S17 GPIO Pin 3 selected							*/
#define EXIO_Pin_4          0x10 /* MCP23S17 GPIO Pin 4 selected							*/
#define EXIO_Pin_5          0x20 /* MCP23S17 GPIO Pin 5 selected							*/
#define EXIO_Pin_6          0x40 /* MCP23S17 GPIO Pin 6 selected							*/
#define EXIO_Pin_7          0x80 /* MCP23S17 GPIO Pin 7 selected							*/
#define EXIO_Pin_All        0xFF /* MCP23S17 GPIO all Pin selected						*/
#define EXIOA               0x12
#define EXIOB               0x13

#define MCP_SET   GPIO_PIN_SET
#define MCP_RESET GPIO_PIN_RESET
/* Exported variables --------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/
typedef struct{
	
#if USE_SIM_SPI
	uint8_t SPI_CHx;
#else
#ifdef USE_HAL_DRIVER
	SPI_HandleTypeDef* SPI_CHx;
#else
#ifdef USE_STDPERIPH_DRIVER
	SPI_TypeDef* SPI_CHx;
#endif /* USE_STDPERIPH_DRIVER */
#endif /* USE_HAL_DRIVER       */
#endif /* USE_SIM_SPI          */
	uint16_t   CS_PIN;
	GPIO_TypeDef*   CS_PORT;
	
}MCP_TypeDef;
/* Exported macro ------------------------------------------------------------*/
#if MCP_DEBUGOUT
#define MCP_printf(x) printf(x)
#else
#define MCP_printf(x) ((void)(x))
#endif /* MCP_DEBUGOUT */

/* Exported function prototypes ----------------------------------------------*/
#define SIM_SPI_Delay(x) Delay_us(x)

#define MCP_WritePin(GPIOx,GPIO_PIN,STATUS) HAL_GPIO_WritePin(GPIOx,GPIO_PIN,STATUS)
#define MCP_ReadPin(GPIOx,GPIO_PIN)         HAL_GPIO_ReadPin(GPIOx,GPIO_PIN)

/* Exported functions ------------------------------------------------------- */


extern MCP_TypeDef MCP23S17[MAX_MCP23S17];

#if USE_SIM_SPI
void MCP23S17_Init(uint8_t ChipNum,uint8_t SPI_CHx,GPIO_TypeDef* CS_GPIOx,uint16_t CS_GPIO_Pin);
#else
#ifdef USE_HAL_DRIVER
void MCP23S17_Init(uint8_t ChipNum,SPI_HandleTypeDef* SPI_CHx,GPIO_TypeDef* CS_GPIOx,uint16_t CS_GPIO_Pin);
#else
#ifdef USE_STDPERIPH_DRIVER
void MCP23S17_Init(uint8_t ChipNum,SPI_TypeDef* SPI_CHx,GPIO_TypeDef* CS_GPIOx,uint16_t CS_GPIO_Pin);
#endif /* USE_STDPERIPH_DRIVER */
#endif /* USE_HAL_DRIVER       */
#endif /* USE_SIM_SPI          */

uint8_t MCP23S17_ReadReg(uint8_t ChipNum, uint8_t RegAddr);
void MCP23S17_WriteReg(uint8_t ChipNum,uint8_t RegAddr,uint8_t* pData,uint8_t Size);
void EXIO_InputConfig(uint8_t ChipNum, uint8_t EXIOx, uint8_t EXIO_Pin);
void EXIO_OutputConfig(uint8_t ChipNum, uint8_t EXIOx, uint8_t EXIO_Pin);
void EXIO_WriteBits(uint8_t ChipNum, uint8_t EXIOx, uint8_t EXIO_Pin, uint8_t NewStatus);
uint8_t EXIO_ReadEXIODataBit(uint8_t ChipNum, uint8_t EXIOx, uint8_t EXIO_Pin);

#endif /* JUNIOR_MCP23S17_H */
/******************* (C) COPYRIGHT 2016 Junior Yip *********END OF FILE********/
