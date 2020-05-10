
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
* ��������: ����ɨ��
* ���������
* ���������
* ����ֵ  ��
***************************************************************************/
static uint8_t Valt_Value = 1;//12V Vp-p

static void key_scan( void )
{
	static bool key_lock = 0;  //������������
	
	if(Key1In == KEY_YES || Key2In == KEY_YES || Key3In == KEY_YES )  //�а������£�
	{
		if(key_lock == 0)
		{
			key_lock = 1;  //�������������ּ��
			HAL_Delay(10);  //������ʱ			
			/*ϵͳʹ�ܰ���*/
			if(Key1In == KEY_YES)  //ϵͳʹ�ܰ���
			{
				Key_st.Key_En = !Key_st.Key_En; //ϵͳʹ���л�
				Led2Con = ~Led2Con; //ʹ�ܵ�
			}		
			/*ϵͳδʹ�ܣ�����ģʽ������Ч*/
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
			/*ϵͳʹ�ܰ������£�ʹ�ܶ�ӦPWM����оƬ, �͵�ƽ��Ч*/
			else
			{
				TIM1->CR1|=1<<0;
				if(Key_st.Key_Mode == Volt_Adj_Mode) //  Led3Con = LED_ON;  //
				{
				}
				else if(Key_st.Key_Mode == Freq_Adj_Mode)//��Ƶģʽ
				{
				}	
				
			}
		}
	}
	else
	{
		key_lock = 0;  //�ް������£��򰴼�����
	}
}	


 


