/*
 * bsp_delay.c
 *
 * Created on: 2017年11月14日
 * Author: Enzo
 */
 
#include "bsp_delay.h"
#include "stm32f1xx_hal.h"
/**
  * @brief  延时 
  * @param  nUs: n个微妙
  * @retval None
  */
void delay_us(uint32_t nUs)  
{  
 
   uint32_t i=0;  
   while(nUs--)
   {
       i=13;//12-13  
      while(i--) ;    
   }
//	uint32_t ticks;
//	uint32_t told,tnow,tcnt=0;
//	uint32_t reload=SysTick->LOAD;
//	ticks=nUs*fac_us;
//	told=SysTick->VAL;
//	
//	while(1){
//		tnow=SysTick->VAL;	
//		if(tnow!=told){
//			if(tnow<told)tcnt+=told-tnow;
//			else tcnt+=reload-tnow+told;	    
//			told=tnow;
//			if(tcnt>=ticks)break;
//		}
//	}

//	int32_t temp;  //delay 5000*2+IO us    Real 112.6Hz    8.8ms
//	SysTick->LOAD = 8*nUs;  
//	SysTick->VAL=0X00;//清空计数器  
//	SysTick->CTRL=0X01;//使能，减到零是无动作，采用外部时钟源  
//	do  
//	{  
//		temp=SysTick->CTRL;//读取当前倒计数值  
//	}while((temp&0x01)&&(!(temp&(1<<16))));//等待时间到达
//  
////	SysTick->CTRL=0x00; //关闭计数器  
//	SysTick->VAL =0X00; //清空计数器  
}  

/**
  * @brief  延时 
  * @param  nUs: n个微妙
  * @retval None
  */
void delay_ms(uint32_t nUs)  
{  
 
   uint32_t i=0;  
   while(nUs--)
   {
       i=10350;//12-13  
      while(i--) ;    
   }
}

