 /*
 * ReadMe
 * Created on: 2018年6月3日
 * Author: Enzo
 */
 
KINGKONG_KP_PS_A01 

20180603	完成工程模板建立
20180603	完成内部DAC的驱动，外部dac驱动存在问题！！！！可以凑合用
20180608	完成电路参数计算，需要实际调试测试
20180621	电路板中，存在问题，串口Tx Rx存在坑。
20180621	1.需要移植串口IAP构架 		2.需要在FLASH中预留参数存储空间 
20180704	完成ADC ad7124 TempSensor mcp9805驱动移植，待测试 ！！！
20180704	完成串口IAP BootLoader 和 APP 框架设计
！20180731	添加FreeRTOS  IAP测试OK
20180731	完成FreeRTOS + IWDG + IAP 测试 测试ok'
20180819	重新设置FreeRtos  Memory management settings -> TOTAL_HEAP_SIZE ->15360(3072)  多任务冲突BUG解除
20180819	重新设置FreeRtos  增加vTaskDelayUntil -> Enable    
20180819	修改看门狗参数 时钟40Khz 16分频  计数值为2500   定时时间2s  现在1.5s 喂狗
20180819	增加USART1 需要在it里边屏蔽HAL生成的中断   修改内核定时器为TIM7（Systick）
20180819	增加线性拟合算子，拟合效果一般，存在偏差
20190604:	增加外部DAC设置电压函数

BUG
！！！！！
修改内核定时器为TIM7（Systick） 无法IAP


Current		Task Target： 

2.串口控制指令
3.AD7124 Reg COnfig
4. AD5683 BUG 时序可能存在问题，需要多次写入

#define USER_FLASH_END_ADDRESS      0x08040000 含义没搞懂？如何配置？






bin Files
MAC
D:\Program Files (x86)\Keil\ARM\ARMCC\bin\fromelf.exe --bin -o ./bin/STM32F103_512K_APP.bin ./KINGKONG_KP_PS_A01/KINGKONG_KP_PS_A01.axf
WIN
D:\Program Files (x86)\Keil_v5\ARM\ARMCC\bin\fromelf.exe --bin -o ./bin/STM32F103_512K_APP.bin ./KINGKONG_KP_PS_A01/KINGKONG_KP_PS_A01.axf


Flash MAP
BootLoader:		0x08000000 - 0x08002000
PrefMemory:		0x08002001 - 0x08003000
MainMemory:		0x08003001 - 0x08040000

RealOffset:		0x08000000 + 0x00001050 BootLoader Code Size

double 150*8*10=1200












Changed:

重新计算电路参数：
Rfbt：100K
Rfbb：11K
Rfbda：2.2K

Comp Mark：
(34.8KOhm+100pF)//8.2pF

Vdac：0.5-0.95V
Vout：23-1V



