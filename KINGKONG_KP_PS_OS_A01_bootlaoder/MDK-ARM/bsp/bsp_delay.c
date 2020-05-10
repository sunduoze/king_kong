/*
 * bsp_delay.c
 *
 * Created on: 2017��11��14��
 * Author: Enzo
 */
 
#include "bsp_delay.h"
#include "stm32f1xx_hal.h"
/**
  * @brief  ��ʱ 
  * @param  nUs: n��΢��
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
//	SysTick->VAL=0X00;//��ռ�����  
//	SysTick->CTRL=0X01;//ʹ�ܣ����������޶����������ⲿʱ��Դ  
//	do  
//	{  
//		temp=SysTick->CTRL;//��ȡ��ǰ������ֵ  
//	}while((temp&0x01)&&(!(temp&(1<<16))));//�ȴ�ʱ�䵽��
//  
////	SysTick->CTRL=0x00; //�رռ�����  
//	SysTick->VAL =0X00; //��ռ�����  
}  

/**
  * @brief  ��ʱ 
  * @param  nUs: n��΢��
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

