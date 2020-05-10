/*
 * task_debug.c
 *
 * Created on: 2018年2月27日
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
//处理系统指令
//0,成功处理;其他,错误代码;
uint8_t usmart_sys_cmd_exe(uint8_t *str)
{
	uint8_t i;
//	uint8_t pnum;
//	uint8_t rval;
//	uint32_t res;  
//	res=usmart_get_cmdname(str,sfname,&i,MAX_FNAME_LEN);//得到指令及指令长度
//	if(res)return USMART_FUNCERR;//错误的指令 
//	str+=i;	 	 			    
//	for(i=0;i<sizeof(sys_cmd_tab)/4;i++)//支持的系统指令
//	{
//		if(usmart_strcmp(sfname,sys_cmd_tab[i])==0)break;
//	}
	switch(i)
	{					   
		case 0:
		case 1://帮助指令
			printf("\r\n");
#if USMART_USE_HELP
			printf("------------------命令列表-----------------------\r\n");
			printf("?:      获取帮助信息\r\n");
			printf("help:   获取帮助信息\r\n");
			printf("list:   可用的函数列表\r\n\n");
			printf("id:     可用函数的ID列表\r\n\n");
			printf("hex:    参数16进制显示,后跟空格+数字即执行进制转换\r\n\n");
			printf("dec:    参数10进制显示,后跟空格+数字即执行进制转换\r\n\n");
			printf("runtime:1,开启函数运行计时;0,关闭函数运行计时;\r\n\n");
			printf("请按照程序编写格式输入函数名及参数并以回车键结束.\r\n");
			printf("-------------------------------------------------\r\n");    
#else
			printf("Command Mask\r\n");
#endif
			break;
		case 2://查询指令
			printf("\r\n");

			printf("\r\n");
			break;	 
		case 3://查询ID
			printf("\r\n");

			printf("\r\n");
			break;
		case 4://hex指令
			printf("\r\n");

			printf("\r\n"); 
			break;
		case 5://dec指令
			printf("\r\n");

			printf("\r\n"); 
			break;	 
		case 6://runtime指令,设置是否显示函数执行时间
			printf("\r\n");

			printf("\r\n"); 
			break;	    
		default://非法指令
			return HAL_ERROR;
	}
	return 0;
}

