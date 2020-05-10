
/*
 * at45db161.c
 *
 * Created on: 2017.11.14
 * Author: Enzo
 */

#include "stm32f1xx_hal.h"
#include "AT45DB161.h"
#include "bsp_delay.h"

void AT45_WriteByte(uint8_t nbuf,uint16_t PageAddr,uint16_t BaseAddr,int16_t len, uint8_t *Writebuf);
void AT45_ReadByte(uint16_t pageaddr1, uint16_t baseaddr1,int16_t len2, uint8_t *readbuf);


void SPI_WriteByte(uint8_t ttdata)
{
	int8_t it;
	for(it=0;it<8;it++)
	{	
		SCK_L;
		delay_us(10);
		if((ttdata&0x80)!=0)
			MOSI_H;
		else
			MOSI_L;
//		
		delay_us(10);
		//for(id=0;id<4;id++);
		SCK_H;
		delay_us(10);
		//for(id=0;id<4;id++);
		ttdata=ttdata*2;
		
	}
}
uint8_t SPI_ReadByte()
{
	int8_t xc;
	uint8_t readdate=0;
	for(xc=0;xc<8;xc++)
	{
		SCK_L;
		delay_us(10);
		SCK_H;
		delay_us(10);
		if(MISO!=0)
			readdate=readdate*2+1;
		else
			readdate=readdate*2;
		delay_us(10);
	}
	return readdate;
}
uint8_t AT45_CheckBusy(void)
{
	uint8_t state;
	CS_L;
	delay_ms(2);
	SPI_WriteByte(0x57);
	state=SPI_ReadByte();
	CS_H;
	if((state&0x80)!=0)
		return 0;
	else
		return 1;
}
void BuffWriteByte(uint8_t comm,uint16_t BuffBaseAddr,int16_t len,uint8_t *Writebuf1)
{
	int16_t ii;
	while(AT45_CheckBusy());
	CS_L;
	delay_ms(2);
	switch(comm)
	{
		case 1:SPI_WriteByte(0x84);break;
		case 2:SPI_WriteByte(0x87);break;
	}
	SPI_WriteByte(0);
	SPI_WriteByte((uint8_t)(0x00|(BuffBaseAddr%0x0100)));
	SPI_WriteByte((uint8_t)(BuffBaseAddr));
	for(ii=0;ii<len;ii++)
	{
		SPI_WriteByte(Writebuf1[ii]);
	}
	CS_H;
}
void AT45_WriteByte(uint8_t nbuf,uint16_t PageAddr,uint16_t BaseAddr,int16_t len, uint8_t *Writebuf)
{
	int16_t ir;
	BuffWriteByte(nbuf,0,len,Writebuf);
	while(AT45_CheckBusy());
	CS_L;
	delay_ms(2);
	switch(nbuf)
	{
		case 1:SPI_WriteByte(0x83);break;
		case 2:SPI_WriteByte(0x86);break;
	}
	SPI_WriteByte((uint8_t)(PageAddr/64));
	SPI_WriteByte((uint8_t)((PageAddr*4)|(BaseAddr/0x0100)));
	SPI_WriteByte((uint8_t)(BaseAddr));
	for(ir=0;ir<len;ir++)
	{
		SPI_WriteByte(Writebuf[ir]);
	}
	CS_H;
}
void AT45_ReadByte(uint16_t pageaddr1, uint16_t baseaddr1,int16_t len2, uint8_t *readbuf)
{
	int16_t iu;
	while(AT45_CheckBusy());
	CS_L;
	delay_ms(2);
	SPI_WriteByte(0xe8);
	SPI_WriteByte((uint8_t)(pageaddr1/64));
	SPI_WriteByte((uint8_t)((pageaddr1*4)|(baseaddr1/0x0100)));
	SPI_WriteByte((uint8_t)(baseaddr1));
	SPI_WriteByte(0x01);
	SPI_WriteByte(0x02);
	SPI_WriteByte(0x03);
	SPI_WriteByte(0x04);
	for(iu=0;iu<len2;iu++)
	{
		readbuf[iu]=SPI_ReadByte();
	}
	CS_H;
}

uint8_t AT45_EEPROM_Check(void)
{
	uint8_t pagemem[5];
	uint8_t tempp[5]={0x12,0x34,0x56,0x67,0x89};
	int8_t i;
	RES_L;
	delay_ms(10);
	RES_H;
	delay_ms(5);
	AT45_WriteByte(1,2,0,5,tempp); //(x;page;base_offset;len;buff)
	delay_ms(10);
	AT45_ReadByte(2,0,5,pagemem);		//(page;base_offset;len;buf)
	for(i=0;i<5;i++)
	{
		if(pagemem[i]!=tempp[i])
		return 0;
	}
	return 1;
}

