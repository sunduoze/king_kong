
#include "bsp_at45db161.h"
#include "bsp_delay.h"
#include "main.h"
#include "stdio.h"


/* Private typedef -----------------------------------------------------------*/
#define SPI_FLASH_PageSize    0x200 //512Byte

/* Private define ------------------------------------------------------------*/
#define WRITE      0x82  /* Write to Memory instruction */
#define READ       0x52  /* Read from Memory instruction */
#define RDSR       0xD7  /* Read Status Register instruction  */
#define RDID       0x9F  /* Read identification */
#define PE         0x81  /* Page Erase instruction */
#define BE1        0xC7  /* Bulk Erase instruction */
#define BE2        0x94  /* Bulk Erase instruction */
#define BE3        0x80  /* Bulk Erase instruction */
#define BE4        0x9A  /* Bulk Erase instruction */

#define BUSY_Flag  0x80 /* Ready/busy status flag */

#define Dummy_Byte 0xA5

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
* Function Name  : SPI_FLASH_Init
* Description    : Initializes the peripherals used by the SPI FLASH driver.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SPI_FLASH_Init(void)
{
	#ifdef USE_LL_DRIVER
  SPI_InitTypeDef  SPI_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;

  /* Enable SPI1 and GPIO clocks */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1 | RCC_APB2Periph_GPIOA |
                         RCC_APB2Periph_GPIO_CS, ENABLE);

  /* Configure SPI1 pins: SCK, MISO and MOSI */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  /* Configure I/O for Flash Chip select */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_CS;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIO_CS, &GPIO_InitStructure);

  /* Deselect the FLASH: Chip Select high */
  EEPROM_CS_H;

  /* SPI1 configuration */
  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;

  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
  SPI_InitStructure.SPI_CRCPolynomial = 7;
  SPI_Init(SPI1, &SPI_InitStructure);

  /* Enable SPI1  */
  SPI_Cmd(SPI1, ENABLE);
	#endif
}

/*******************************************************************************
* 说明:	address 中(A20--A9)(Page Address) (A8--A0)(Byte Address)
*******************************************************************************/

/*******************************************************************************
* Function Name  : SPI_FLASH_PageErase
* Description    : Erases the specified FLASH Page.
* Input          : PageAddr: address of the sector to erase.
* Output         : None
* Return         : None
*******************************************************************************/
void SPI_FLASH_PageErase(uint32_t PageAddr)
{
  /* Sector Erase */
  /* Select the FLASH: Chip Select low */
  EEPROM_CS_L;
  /* Send Sector Erase instruction */
  SPI_FLASH_SendByte(PE);
  /* Send SectorAddr high nibble address byte */
  SPI_FLASH_SendByte((PageAddr & 0xFF0000) >> 16);
  /* Send SectorAddr medium nibble address byte */
  SPI_FLASH_SendByte((PageAddr & 0xFF00) >> 8);
  /* Send SectorAddr low nibble address byte */
  SPI_FLASH_SendByte(PageAddr & 0xFF);
  /* Deselect the FLASH: Chip Select high */
  EEPROM_CS_H;

  /* Wait the end of Flash writing */
  SPI_FLASH_WaitForWriteEnd();
}

/*******************************************************************************
* Function Name  : SPI_FLASH_BulkErase
* Description    : Erases the entire FLASH.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SPI_FLASH_BulkErase(void)
{
  /* Bulk Erase */
  /* Select the FLASH: Chip Select low */
  EEPROM_CS_L;
  /* Send Bulk Erase instruction  */
  SPI_FLASH_SendByte(BE1);
  /* Send Bulk Erase instruction  */
  SPI_FLASH_SendByte(BE2);
  /* Send Bulk Erase instruction  */
  SPI_FLASH_SendByte(BE3);
  /* Send Bulk Erase instruction  */
  SPI_FLASH_SendByte(BE4);
  /* Deselect the FLASH: Chip Select high */
  EEPROM_CS_H;

  /* Wait the end of Flash writing */
  SPI_FLASH_WaitForWriteEnd();
}

/*******************************************************************************
* Function Name  : SPI_FLASH_WriteSector
* Description    : Writes one Sector to the FLASH with a single WRITE
*                  cycle(Page WRITE sequence). The number of byte can't exceed
*                  the FLASH page size, But for FAT always 512 butes
* Input          : - pBuffer : pointer to the buffer  containing the data to be
*                    written to the FLASH.
*                  - SectorAddr : FLASH's internal Page address to write to.
*                  - NumByteToWrite : number of bytes to write to the FLASH,
*                    must be equal or less than "SPI_FLASH_PageSize" value.
* Output         : None
* Return         : None
*******************************************************************************/
void SPI_FLASH_WriteSector(uint8_t* pBuffer, uint32_t SectorAddr, uint16_t NumByteToWrite)
{
	uint16_t  uiPageAddress;
	uint8_t bytes[2];
	uiPageAddress  = (uint16_t)SectorAddr & 0x0FFF;
	uiPageAddress *= 4;
	bytes[0] = (uint8_t)(uiPageAddress>>8);					// msb
	bytes[1] = (uint8_t)(uiPageAddress & 0xFF);			// lsb
	
	/* Select the FLASH: Chip Select low */
	EEPROM_CS_L;
	/* Send "Write to Memory " instruction */
	SPI_FLASH_SendByte(WRITE);	
	/* Send WriteAddr high nibble address byte to write to */
	SPI_FLASH_SendByte(bytes[0]);
	/* Send WriteAddr medium nibble address byte to write to */
	SPI_FLASH_SendByte(bytes[1]);
	/* Send WriteAddr low nibble address byte to write to */
	SPI_FLASH_SendByte(0x00);

	/* while there is data to be written on the FLASH */
	while (NumByteToWrite--)
	{
		/* Send the current byte */
		SPI_FLASH_SendByte(*pBuffer);
		/* Point on the next byte to be written */
		pBuffer++;
	}
	/* Deselect the FLASH: Chip Select high */
	EEPROM_CS_H;

	/* Wait the end of Flash writing */
//	SPI_FLASH_WaitForWriteEnd();
}

/*******************************************************************************
* Function Name  : SPI_FLASH_ReadSector
* Description    : Reads a block of data from the FLASH.
* Input          : - pBuffer : pointer to the buffer that receives the data read
*                    from the FLASH.
*                  - ReadAddr : FLASH's internal Pages address to read from.
*                  - NumByteToRead : number of bytes to read from the FLASH.
* Output         : None
* Return         : None
*******************************************************************************/
void SPI_FLASH_ReadSector(uint8_t* pBuffer, uint32_t SectorAddr, uint16_t NumByteToRead)
{
	uint16_t  uiPageAddress;
	uint8_t bytes[2];

   	uiPageAddress  = (uint16_t)SectorAddr & 0x0FFF;
	uiPageAddress *= 4;

	bytes[0] = (uint8_t)(uiPageAddress>>8);					// msb
	bytes[1] = (uint8_t)(uiPageAddress & 0xFF);          	// lsb

	/* Select the FLASH: Chip Select low */
	EEPROM_CS_L;

	/* Send "Read from Memory " instruction */
	SPI_FLASH_SendByte(READ);

	
	/* Send WriteAddr high nibble address byte to write to */
	SPI_FLASH_SendByte(bytes[0]);
	/* Send WriteAddr medium nibble address byte to write to */
	SPI_FLASH_SendByte(bytes[1]);
	/* Send WriteAddr low nibble address byte to write to */
	SPI_FLASH_SendByte(0x00);


	/* Send a dummy byte to generate the clock needed by the FLASH */
	SPI_FLASH_SendByte(Dummy_Byte);
	/* Send a dummy byte to generate the clock needed by the FLASH */
	SPI_FLASH_SendByte(Dummy_Byte);
	/* Send a dummy byte to generate the clock needed by the FLASH */
	SPI_FLASH_SendByte(Dummy_Byte);
	/* Send a dummy byte to generate the clock needed by the FLASH */
	SPI_FLASH_SendByte(Dummy_Byte);

	while (NumByteToRead--) /* while there is data to be read */
	{
	/* Read a byte from the FLASH */
	*pBuffer = SPI_FLASH_SendByte(Dummy_Byte);
	/* Point to the next location where the byte read will be saved */
	pBuffer++;
	}

	/* Deselect the FLASH: Chip Select high */
	EEPROM_CS_H;
}


/*******************************************************************************
* Function Name  : SPI_FLASH_ReadID
* Description    : Reads FLASH identification.
* Input          : None
* Output         : None
* Return         : FLASH identification
*******************************************************************************/
uint32_t SPI_FLASH_ReadID(void)
{
  static uint32_t Temp, Temp0, Temp1, Temp2, Temp3;

  /* Select the FLASH: Chip Select low */
  EEPROM_CS_L;

  /* Send "RDID " instruction */
  SPI_FLASH_SendByte(0x9F);

  /* Read a byte from the FLASH */
  Temp0 = SPI_FLASH_SendByte(Dummy_Byte);

  /* Read a byte from the FLASH */
  Temp1 = SPI_FLASH_SendByte(Dummy_Byte);

  /* Read a byte from the FLASH */
  Temp2 = SPI_FLASH_SendByte(Dummy_Byte);

  /* Read a byte from the FLASH */
  Temp3 = SPI_FLASH_SendByte(Dummy_Byte);
  
  /* Deselect the FLASH: Chip Select high */
  EEPROM_CS_H;

  Temp = (Temp0 << 24) | (Temp1 << 16) | (Temp2<<8) | Temp3;

  return Temp;
}

/*******************************************************************************
* Function Name  : SPI_FLASH_ReadByte
* Description    : Reads a byte from the SPI Flash.
*                  This function must be used only if the Start_Read_Sequence
*                  function has been previously called.
* Input          : None
* Output         : None
* Return         : Byte Read from the SPI Flash.
*******************************************************************************/
uint8_t SPI_FLASH_ReadByte(void)
{
  return (SPI_FLASH_SendByte(Dummy_Byte));
}

/*******************************************************************************
* Function Name  : SPI_FLASH_SendByte
* Description    : Sends a byte through the SPI interface and return the byte
*                  received from the SPI bus.
* Input          : byte : byte to send.
* Output         : None
* Return         : The value of the received byte.
*******************************************************************************/
uint8_t SPI_FLASH_SendByte(uint8_t byte)/*CPHA = 1; CPOL = 1;*/
{
#if 0//  0x08001915
	static uint8_t i,Temp; 
	for(i=0;i<8;i++)                      
	{
		EEPROM_SCK_L;                          
		if(byte&0x80) EEPROM_MOSI_H;           
		else          EEPROM_MOSI_L;           
		byte <<= 1;   
//			delay_us(10);		
		EEPROM_SCK_H;                          
		Temp <<= 1;                          
		if(EEPROM_MISO) Temp++;    
//			delay_us(10);		
		EEPROM_SCK_L;                               
	}
	Temp = Temp;//For Debug
	return (Temp);  
	
#else////  0x08001931   1909 无delay
    static uint8_t byteRcv;
    uint8_t bit;
    for (bit = 0x80; bit; bit >>= 1)  		/* Shift-out a bit to the MOSI line */
		{
			if(byte & bit)			EEPROM_MOSI_H;/* Shift-in a bit from the MISO line */
			else								EEPROM_MOSI_L;
//			delay_us(10);
			EEPROM_SCK_H;
			if(EEPROM_MISO)			byteRcv |= bit; 
//			delay_us(10);
			EEPROM_SCK_L;
    }
    return byteRcv;
#endif
		
		
#ifdef USE_LL_DRIVER	
  /* Loop while DR register in not emplty */
  while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);

  /* Send byte through the SPI1 peripheral */
  SPI_I2S_SendData(SPI1, byte);

  /* Wait to receive a byte */
  while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);

  /* Return the byte read from the SPI bus */
  return SPI_I2S_ReceiveData(SPI1);
#endif
}

/*******************************************************************************
* Function Name  : SPI_FLASH_WaitForWriteEnd
* Description    : Polls the status of the Write In Progress (WIP) flag in the
*                  FLASH's status  register  and  loop  until write  opertaion
*                  has completed.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SPI_FLASH_WaitForWriteEnd(void)
{
  uint8_t FLASH_Status = 0;

  /* Select the FLASH: Chip Select low */
  EEPROM_CS_L;

  /* Send "Read Status Register" instruction */
  SPI_FLASH_SendByte(RDSR);
  /* Loop as long as the memory is busy with a write cycle */
  do
  {
    /* Send a dummy byte to generate the clock needed by the FLASH
    and put the value of the status register in FLASH_Status variable */
    FLASH_Status = SPI_FLASH_SendByte(Dummy_Byte);
		printf("0x%x \r\n",FLASH_Status);

  }
  while ((FLASH_Status & BUSY_Flag) == RESET); /* Write in progress */
  /* Deselect the FLASH: Chip Select high */
  EEPROM_CS_H;
}
