/*
 * bsp_mcp9805.h
 *
 * Created on: 2018Äê07ÔÂ02ÈÕ
 * Author: Enzo
 */
 
#ifndef BSP_MCP9805_H_
#define BSP_MCP9805_H_

#define NATURE_REG                                                                   0x00
#define CTRL_REG                                                                     0x01
#define POLICE_REG                                                                   0x02
#define FLOOR_REG                                                                    0x03
#define CRISIS_REG                                                                   0x04
#define TEMPER_REG                                                                   0x05
#define MANU_REG                                                                     0x06
#define DEVICE_REG                                                                   0x07

extern void MCP9805_Init(void);
extern unsigned short MCP9805_Read_Temperature_Code(void);
extern float MCP9805_Read_Temperature(void);
extern unsigned char MCP9805_Check(void);


#endif

