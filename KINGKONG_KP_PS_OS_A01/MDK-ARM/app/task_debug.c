/*
 * task_debug.c
 *
 * Created on: 2018��2��27��
 * Author: Enzo
 */
 
#include "task_debug.h"


/**
  * @brief  To Upper Computer
  * @param  
  * @retval None
  */
void debugSendFrame(UART_HandleTypeDef *huart, RcTableType id, float data)
{
  FloatConvertType	tmp;
  debugFrame[Head1]   = 0x55;
  debugFrame[Head2]   = 0xAA;
  debugFrame[DataID]  = id;
 
  tmp.fType = data;

  debugFrame[Byte0]   = tmp.u8Type[0];
  debugFrame[Byte1]   = tmp.u8Type[1];
  debugFrame[Byte2]   = tmp.u8Type[2];
  debugFrame[Byte3]   = tmp.u8Type[3];
  
  debugFrame[SumCheck]=   (uint8_t)(debugFrame[DataID] 
                                      + debugFrame[Byte0] 
                                      + debugFrame[Byte1]  
                                      + debugFrame[Byte2] 
                                      + debugFrame[Byte3]); 
  debugFrame[Tail]    = 0xFF;
  
  HAL_UART_Transmit(huart, debugFrame, FrameLength,100);  
  //use blocking mode transmit
}


uint8_t *sys_cmd_tab[]=
{
(uint8_t *)"?",
(uint8_t *)"help",
(uint8_t *)"list",
(uint8_t *)"id",
(uint8_t *)"hex",
(uint8_t *)"dec",
(uint8_t *)"runtime",	   
};	    
//����ϵͳָ��
//0,�ɹ�����;����,�������;
uint8_t usmart_sys_cmd_exe(uint8_t *str)
{
	uint8_t i;
//	uint8_t pnum;
//	uint8_t rval;
//	uint32_t res;  
//	res=usmart_get_cmdname(str,sfname,&i,MAX_FNAME_LEN);//�õ�ָ�ָ���
//	if(res)return USMART_FUNCERR;//�����ָ�� 
//	str+=i;	 	 			    
//	for(i=0;i<sizeof(sys_cmd_tab)/4;i++)//֧�ֵ�ϵͳָ��
//	{
//		if(usmart_strcmp(sfname,sys_cmd_tab[i])==0)break;
//	}
	switch(i)
	{					   
		case 0:
		case 1://����ָ��
			printf("\r\n");
#if USMART_USE_HELP
			printf("------------------�����б�-----------------------\r\n");
			printf("?:      ��ȡ������Ϣ\r\n");
			printf("help:   ��ȡ������Ϣ\r\n");
			printf("list:   ���õĺ����б�\r\n\n");
			printf("id:     ���ú�����ID�б�\r\n\n");
			printf("hex:    ����16������ʾ,����ո�+���ּ�ִ�н���ת��\r\n\n");
			printf("dec:    ����10������ʾ,����ո�+���ּ�ִ�н���ת��\r\n\n");
			printf("runtime:1,�����������м�ʱ;0,�رպ������м�ʱ;\r\n\n");
			printf("�밴�ճ����д��ʽ���뺯�������������Իس�������.\r\n");
			printf("-------------------------------------------------\r\n");    
#else
			printf("Command Mask\r\n");
#endif
			break;
		case 2://��ѯָ��
			printf("\r\n");

			printf("\r\n");
			break;	 
		case 3://��ѯID
			printf("\r\n");

			printf("\r\n");
			break;
		case 4://hexָ��
			printf("\r\n");

			printf("\r\n"); 
			break;
		case 5://decָ��
			printf("\r\n");

			printf("\r\n"); 
			break;	 
		case 6://runtimeָ��,�����Ƿ���ʾ����ִ��ʱ��
			printf("\r\n");

			printf("\r\n"); 
			break;	    
		default://�Ƿ�ָ��
			return HAL_ERROR;
	}
	return 0;
}

