/*
 * app_KeyStroke.c
 *
 * Created on: 2017Äê11ÔÂ14ÈÕ
 * Author: Enzo
 */
 
#include "app_KeyStroke.h"
#include "stm32f1xx_hal.h"

#include "app_Communication.h"
#include "MCP23S17.h"
#include "bsp_delay.h"

void KeyStroke(uint8_t bX, uint16_t tRise, uint16_t tFall, uint8_t Num)
{
	uint8_t i;
	for(i = 0;i < Num; i++)
	{
			EXIO_WriteBits(
					CurrentBoard.Btn[bX].Drv[0].MCP23S17Cs, 
					CurrentBoard.Btn[bX].Drv[0].MCP23S17Port,//EXIO_Pin_All,1);
					CurrentBoard.Btn[bX].Drv[0].MCP23S17Io, 1);
//			HAL_Delay(100);
			delay_ms(tFall);//Time of fall
	
				EXIO_WriteBits(
					CurrentBoard.Btn[bX].Drv[0].MCP23S17Cs, 
					CurrentBoard.Btn[bX].Drv[0].MCP23S17Port,//EXIO_Pin_All,0);
					CurrentBoard.Btn[bX].Drv[0].MCP23S17Io, 0);
//			HAL_Delay(100);
			delay_ms(tRise);//Time of Rise
			if((bX + 8) % 8 == 7 && bX!=BUTTON_NUM)	
			{
					EXIO_WriteBits(
					CurrentBoard.Btn[bX].Drv[0].MCP23S17Cs, 
					CurrentBoard.Btn[bX].Drv[0].MCP23S17Port,//EXIO_Pin_All,0);
					CurrentBoard.Btn[bX].Drv[0].MCP23S17Io, 0);	
			}
	}
}

