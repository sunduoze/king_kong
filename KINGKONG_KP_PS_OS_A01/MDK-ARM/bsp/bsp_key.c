
#include "bsp_key.h"
#include "App_Sequence.h"


static void key_scan( void);
Key_ST Key_st = 
{
	.Key_En = 0,
	.Key_Mode = 0,
	.Key_Scan = key_scan,
};

/****************************************************************************
* 函数功能: 按键扫描
* 输入参数：
* 输出参数：
* 返回值  ：
***************************************************************************/
static uint8_t Valt_Value = 1;//12V Vp-p

static void key_scan( void )
{
	static bool key_lock = 0;  //按键自锁变量
	
	if(Key1In == KEY_YES || Key2In == KEY_YES || Key3In == KEY_YES )  //有按键按下？
	{
		if(key_lock == 0)
		{
			key_lock = 1;  //按键自锁，松手检测
			HAL_Delay(10);  //按键延时			
			/*系统使能按键*/
			if(Key1In == KEY_YES)  //系统使能按键
			{
				Key_st.Key_En = !Key_st.Key_En; //系统使能切换
				Led2Con = ~Led2Con; //使能灯
			}		
			/*系统未使能，其他模式按键有效*/
			if(Key_st.Key_En == 0) 
			{
				if(Key2In == KEY_YES)
				{
						Led4Con = LED_OFF;
				}
				if(Key3In == KEY_YES)
				{				
						Led4Con = LED_ON;
				}
			}
			/*系统使能按键按下，使能对应PWM驱动芯片, 低电平有效*/
			else
			{
				TIM1->CR1|=1<<0;
				if(Key_st.Key_Mode == Volt_Adj_Mode) //  Led3Con = LED_ON;  //
				{
				}
				else if(Key_st.Key_Mode == Freq_Adj_Mode)//调频模式
				{
				}	
				
			}
		}
	}
	else
	{
		key_lock = 0;  //无按键按下，则按键解锁
	}
}	


 


