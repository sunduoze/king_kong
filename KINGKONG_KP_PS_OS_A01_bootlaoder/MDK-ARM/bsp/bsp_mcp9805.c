/*
 * bsp_mcp9805.c
 *
 * Created on: 2018Äê07ÔÂ02ÈÕ
 * Author: Enzo
 */

#include "bsp_iic1.h"
#include "bsp_mcp9805.h"


static unsigned short MCP9805_Read_Byte(unsigned char readaddr);
static void MCP9805_Write_Byte(unsigned char writeaddr, unsigned short data);

/**
  * @brief  This function initialize MCP9805.
  * @param None
  * @retval None
  */
void MCP9805_Init(void)
{
    MCP9805_Write_Byte((unsigned char)NATURE_REG, 0x0003);
    MCP9805_Write_Byte((unsigned char)CTRL_REG, 0x0018);
}

/**
  * @brief  This function read the data on the i2c bus.
  * @param  readaddr: Read the address
  * @retval 16-bit register variables
  */
static unsigned short MCP9805_Read_Byte(unsigned char readaddr)
{
    unsigned short temp = 0;
    unsigned char value = 0;
    IIC1_Start();
    IIC1_Send_Byte(0x30);
    IIC1_Wait_Ack();
    IIC1_Send_Byte(readaddr);
    IIC1_Wait_Ack();
    IIC1_Start();
    IIC1_Send_Byte(0x31);
    IIC1_Wait_Ack();
    value = IIC1_Read_Byte(1);/**********!!!!!!!!!!!!!!!!!!!!!***************/
    IIC1_Ack();
    temp =(((unsigned short)value)<<8);
    value = IIC1_Read_Byte(1);
    IIC1_NAck();
    temp |= (unsigned short)value;
    IIC1_Stop();
    
    return temp;
}

/**
  * @brief  This function writ data to the i2c bus.
  * @param  writeaddr: Write the address.
  * @param  data     : Data is written to the register.
  * @retval None
  */
static void MCP9805_Write_Byte(unsigned char writeaddr, unsigned short data)
{
    IIC1_Start();
    IIC1_Send_Byte(0x30);
    IIC1_Wait_Ack();
    IIC1_Send_Byte(writeaddr);
    IIC1_Wait_Ack();
    IIC1_Send_Byte(data/256);
    IIC1_Wait_Ack();
    IIC1_Send_Byte(data%256);
    IIC1_Wait_Ack();
    IIC1_Stop();
}

/**
  * @brief  This function detect whether MCP9805 can work or not.
  * @param  None
  * @retval Can work return 0, else return 1.
  */
unsigned char MCP9805_Check(void)
{
    unsigned short temp;
    
    temp = MCP9805_Read_Byte((unsigned char)MANU_REG);
    if(temp == 0x0054)
        return 0;
    else 
        return 1;
}

/**
  * @brief  This function read the temperature code
  * @param  None
  * @retval Temperature code.
  */
unsigned short MCP9805_Read_Temperature_Code(void)
{
    return MCP9805_Read_Byte(TEMPER_REG);
}

/**
  * @brief  This function read the temperature
  * @param  None
  * @retval Temperature value.
  */
float MCP9805_Read_Temperature(void)
{
    return (float)((MCP9805_Read_Byte(TEMPER_REG) & 0x0FFC) >> 2) / 4.0f;
}

