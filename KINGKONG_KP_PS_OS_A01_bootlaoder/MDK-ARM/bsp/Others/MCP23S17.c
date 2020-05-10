/**
  ******************************************************************************
  * @file    MCP23S17.c 
  * @author  Junior Yip
  * @version 2.0.0
  * @date    20-July-2016
  * @modify  2017-08-06
  * @brief   MCP23S17 Driver
  ******************************************************************************
  * @History
	* ------------------------------------
	* V1.0
  * ST Library version 3.5.0
  * SPI INTERFACE MAX SPEED :10 MHz
  * I/O PIN DEFAULT TO INPUT
  * WORK MODE : SEQUENTIAL MODE
	* ------------------------------------
	* V2.0
	* 
  * <h2><center>&copy; COPYRIGHT 2016 Junior Yip</center></h2>
  ******************************************************************************
  */  

/* Includes ------------------------------------------------------------------*/
#include "MCP23S17.h"
#include "bsp_delay.h"

#if USE_SIM_SPI
#include "JR_SPI_IF.h"
#endif /* USE_SIM_SPI */

/** @addtogroup STM32F10x_Periph_Driver
  * @{
  */

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
MCP_TypeDef MCP23S17[MAX_MCP23S17]={0};

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
static void MCP_ChipSelect(uint8_t ChipNum);
static void MCP_DeselectAll(void);
static void MCP_Transmit(uint8_t ChipNum,uint8_t *pTxData,uint8_t TxSize);
static void MCP_Receive (uint8_t ChipNum,uint8_t *pRxData,uint8_t RxSize);
/* Private functions ---------------------------------------------------------*/
/**
  * @brief  Chip Select Function
  * @param  ChipNum:MCP23S17 chip number
  * @retval None
  */
static void MCP_ChipSelect(uint8_t ChipNum) {

	MCP_DeselectAll();
	MCP_WritePin(MCP23S17[ChipNum].CS_PORT,MCP23S17[ChipNum].CS_PIN,MCP_RESET);
	delay_us(10);

}

/**
  * @brief  Chip Deselect Function
  * @param  None
  * @retval None
  */
static void MCP_DeselectAll(void) {
	uint8_t i;
	for (i = 0;i<MAX_MCP23S17;i++) {
		if(MCP23S17[i].CS_PORT!=0)
			MCP_WritePin(MCP23S17[i].CS_PORT,MCP23S17[i].CS_PIN,MCP_SET);	
	}
}


/**
  * @brief  Transmit an amount of data from MCP23S17
  * @param  ChipNum:MCP23S17 chip number
  * @param  pTxData: pointer to transmission data buffer
  * @param  TxSize: amount of data will be sent
  * @retval None
  */
static void MCP_Transmit(uint8_t ChipNum,uint8_t *pTxData,uint8_t TxSize) {

//	MCP_ChipSelect(ChipNum);

#if USE_SIM_SPI
	SIM_SPI_Transmit(MCP23S17[ChipNum].SPI_CHx,pTxData,TxSize);
#else
#ifdef USE_HAL_DRIVER
	HAL_SPI_Transmit(MCP23S17[ChipNum].SPI_CHx,pTxData,TxSize,MCP_TIME_OUT);
#else
#ifdef USE_STDPERIPH_DRIVER
	MCP23S17[ChipNum].SPI_CHx->DR = pTxData[0];
#endif /* USE_STDPERIPH_DRIVER */
#endif /* USE_HAL_DRIVER       */
#endif /* USE_SIM_SPI          */

}

/**
  * @brief  Receive an amount of data from MCP23S17
  * @param  ChipNum:MCP23S17 chip number
  * @param  pRxData: pointer to reception data buffer to be
  * @param  RxSize: amount of data will be receive
  * @retval None
  */
static void MCP_Receive(uint8_t ChipNum,uint8_t *pRxData,uint8_t RxSize) {

//	MCP_ChipSelect(ChipNum);

#if USE_SIM_SPI
	SIM_SPI_Receive(MCP23S17[ChipNum].SPI_CHx,pRxData,RxSize);
#else
#ifdef USE_HAL_DRIVER
	HAL_SPI_Receive(MCP23S17[ChipNum].SPI_CHx,pRxData,RxSize,MCP_TIME_OUT);
#else
#ifdef USE_STDPERIPH_DRIVER
	uint8_t i;
	for(i=0;i<RxSize;i++){
		*(pRxData+i) = MCP23S17[ChipNum].SPI_CHx->DR;
	}
#endif /* USE_STDPERIPH_DRIVER */
#endif /* USE_HAL_DRIVER       */
#endif /* USE_SIM_SPI          */
	
}
/**
  * @brief  MCP23S17 Initial
  * @param  ChipNum    :MCP23S17 chip number
  * @param  CS_GPIOx   :MCP23S17 chip select GPIO Port
  * @param  CS_GPIO_Pin:MCP23S17 chip select GPIO Pin
  * @retval	None
  */
#if USE_SIM_SPI
void MCP23S17_Init(uint8_t ChipNum,uint8_t SPI_CHx,GPIO_TypeDef* CS_GPIOx,uint16_t CS_GPIO_Pin) {
#else
#ifdef USE_HAL_DRIVER
void MCP23S17_Init(uint8_t ChipNum,SPI_HandleTypeDef* SPI_CHx,GPIO_TypeDef* CS_GPIOx,uint16_t CS_GPIO_Pin){
#else
#ifdef USE_STDPERIPH_DRIVER
void MCP23S17_Init(uint8_t ChipNum,SPI_TypeDef* SPI_CHx,GPIO_TypeDef* CS_GPIOx,uint16_t CS_GPIO_Pin){
#endif /* USE_STDPERIPH_DRIVER */
#endif /* USE_HAL_DRIVER       */
#endif /* USE_SIM_SPI          */
	
	uint8_t WriteVal;
	WriteVal = IOCON_DEFAULT;
	MCP23S17[ChipNum].SPI_CHx = SPI_CHx;
	MCP23S17[ChipNum].CS_PORT = CS_GPIOx;
	MCP23S17[ChipNum].CS_PIN  = CS_GPIO_Pin;
	MCP23S17_WriteReg(ChipNum, MCP23S17_IOCON, &WriteVal, 1);
	/* Cancel below step because Register value at POR can satisfy the condition */
	//MCP23S17_WriteReg(MCP23S17[DeviceCount], MCP23S17_IODIRA, RegDefaultValue, sizeof(RegDefaultValue));
	//MCP23S17_WriteReg(MCP23S17[DeviceCount], MCP23S17_GPPUA, &RegDefaultValue[8], 2);
		
}

/**
  * @brief  Reads the specified Register data port.
  * @param  ChipNum:MCP23S17 chip number
  * @param  RegAddr:Register Address
  * @retval	Register data port value.
  */
uint8_t MCP23S17_ReadReg(uint8_t ChipNum, uint8_t RegAddr) {

//	uint8_t ret;
	uint8_t TxBuf,RxBuf=0;
	MCP_ChipSelect(ChipNum);
	TxBuf=REG_READ;
	MCP_Transmit(ChipNum,&TxBuf,1);
//	
//	MCP_Receive(ChipNum,&RxBuf,1);
	TxBuf=RegAddr;
//	
	MCP_Transmit(ChipNum,&TxBuf,1);
//	
//	MCP_Receive(ChipNum,&RxBuf,1);
	TxBuf=0xFF;
//	
	MCP_Transmit(ChipNum,&TxBuf,1);		/* Read all Bit */
//	
	MCP_Receive(ChipNum,&RxBuf,1);
	MCP_DeselectAll();
	return RxBuf;
}

/**
  * @brief  MCP23S17 Write Register Function
  * @param  ChipNum:MCP23S17 chip number
  * @param  RegAddr:Register Address
  * @param  pData  :pointer to transmission data buffer
  * @param  Size   :amount of data will be sent
  * @retval	None
  */
void MCP23S17_WriteReg(uint8_t ChipNum,uint8_t RegAddr,uint8_t* pData,uint8_t Size) {

	uint8_t TxBuf;
//	uint8_t RxBuf=0;
	MCP_ChipSelect(ChipNum);
	TxBuf=REG_WRITE;

	MCP_Transmit(ChipNum,&TxBuf,1);
//	
//	MCP_Receive(ChipNum,&RxBuf,1);
	TxBuf=RegAddr;
//	
	MCP_Transmit(ChipNum,&TxBuf,1);
//	
//	MCP_Receive(ChipNum,&RxBuf,1);
//	
	MCP_Transmit(ChipNum,pData,Size);
	MCP_DeselectAll();

}

/**
  * @brief  Set/Reset EXIO_Pin of ChipNum's EXIOx
  * @param  ChipNum  :MCP23S17 chip number
  * @param  EXIOx    :IO Channel in MCP23S17
  * @arg    EXIOA    :Channnel A
  * @arg    EXIOB    :Channnel B
  * @param  EXIO_Pin :IO Pin number
  * @param  NewStatus:New Status of IO
  * @retval	None
  */
void EXIO_WriteBits(uint8_t ChipNum, uint8_t EXIOx, uint8_t EXIO_Pin, uint8_t NewStatus) {

	uint8_t RegVal, WriteVal;
	RegVal = MCP23S17_ReadReg(ChipNum, EXIOx);
	if (NewStatus)
		WriteVal = RegVal | EXIO_Pin;
	else
		WriteVal = RegVal & ~EXIO_Pin;
	MCP23S17_WriteReg(ChipNum, EXIOx, &WriteVal, 1);

}


/**
  * @brief 	Reads the specified Register data pin.
  * @param  ChipNum  :MCP23S17 chip number
  * @param  EXIOx    :IO Channel in MCP23S17
  * @arg    EXIOA    :Channnel A
  * @arg    EXIOB    :Channnel B
  * @param  EXIO_Pin :IO Pin number
  * @retval	1 OR 0
  *				  IF JUST SELECTED ONE PIN
  *				  1:LOGIC HIGH
  *			  	0:LOGIC LOW
  *			  	IF SELECTED MORE THAN ONE PIN
  *			  	1:AT LEASET HAVE ONE OF SELECTED PIN IS LOGIC HIGH
  *				  0:ALL SELECTED PIN ARE LOGIC LOW
  */
uint8_t EXIO_ReadEXIODataBit(uint8_t ChipNum, uint8_t EXIOx, uint8_t EXIO_Pin) {

	uint8_t RegVal, ret;
	RegVal = MCP23S17_ReadReg(ChipNum, EXIOx);
	ret = RegVal&EXIO_Pin;
	if (ret)
		return 1;
	else
		return 0;
}

/**
  * @brief  	Config EXIO_Pin of ChipNum's EXIOx to Output
  * @param  ChipNum  :MCP23S17 chip number
  * @param  EXIOx    :IO Channel in MCP23S17
  * @arg    EXIOA    :Channnel A
  * @arg    EXIOB    :Channnel B
  * @param  EXIO_Pin :IO Pin number
  * @retval	 	None
  * @attention 	None
  * @remark		None
  */
void EXIO_OutputConfig(uint8_t ChipNum, uint8_t EXIOx, uint8_t EXIO_Pin) {

	uint8_t RegVal, WriteVal;
	if (EXIOx == EXIOA) {
		RegVal   = MCP23S17_ReadReg(ChipNum, MCP23S17_IODIRA);
		WriteVal = RegVal & (~EXIO_Pin);
		//MCP23S17_WriteReg(ChipNum, MCP23S17_IODIRA, (uint8_t*)(&WriteVal), 1);
		MCP23S17_WriteReg(ChipNum, MCP23S17_IODIRA, &WriteVal, 1);
	}
	else if (EXIOx == EXIOB) {
		RegVal   = MCP23S17_ReadReg(ChipNum, MCP23S17_IODIRB);
		WriteVal = RegVal & (~EXIO_Pin);
		//MCP23S17_WriteReg(ChipNum, MCP23S17_IODIRB, (uint8_t*)(&WriteVal), 1);
		MCP23S17_WriteReg(ChipNum, MCP23S17_IODIRB, &WriteVal, 1);
	}
	else {
		MCP_printf("Error: Invaild EXIO Config Parameter!\r\n");
	}
}

/**
  * @brief 	Config EXIO_Pin of ChipNum's EXIOx to Input
  * @param  ChipNum  :MCP23S17 chip number
  * @param  EXIOx    :IO Channel in MCP23S17
  * @arg    EXIOA    :Channnel A
  * @arg    EXIOB    :Channnel B
  * @param  EXIO_Pin :IO Pin number
  * @retval	None
  */
void EXIO_InputConfig(uint8_t ChipNum, uint8_t EXIOx, uint8_t EXIO_Pin) {
	
	uint8_t RegVal, WriteVal;
	if (EXIOx == EXIOA) {
		RegVal   = MCP23S17_ReadReg(ChipNum, MCP23S17_IODIRA);
		WriteVal = RegVal | EXIO_Pin;
		//MCP23S17_WriteReg(ChipNum, MCP23S17_IODIRA, (uint8_t*)(&WriteVal), 1);
		MCP23S17_WriteReg(ChipNum, MCP23S17_IODIRA, &WriteVal, 1);
	}
	else if (EXIOx == EXIOB) {
		RegVal   = MCP23S17_ReadReg(ChipNum, MCP23S17_IODIRB);
		WriteVal = RegVal | EXIO_Pin;
		//MCP23S17_WriteReg(ChipNum, MCP23S17_IODIRB, (uint8_t*)(&WriteVal), 1);
		MCP23S17_WriteReg(ChipNum, MCP23S17_IODIRB, &WriteVal, 1);
	}
	else
		MCP_printf("Error: Invaild EXIO Config Parameter!\r\n");

}

/**
  * @}
  */

/******************* (C) COPYRIGHT 2016 Junior Yip *********END OF FILE********/
