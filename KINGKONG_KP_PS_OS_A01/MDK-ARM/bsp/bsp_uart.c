/*
 * bsp_uart.c
 *
 * Created on: 2018��2��27��
 * Author: Enzo
 */
 
#include "bsp_uart.h"
#include "task_uart.h"

#ifdef SWUST_FREESCALE_LIB_Enzo

__IO uint8_t arrUPPER_COM_Buf[UPPER_COM_BUF_LEN];
__IO uint8_t arrPWR0204_1_Buf[PWR0204_1_BUF_LEN];
__IO uint8_t arrPWR0204_2_Buf[PWR0204_2_BUF_LEN];
__IO uint8_t arrDAQ0010_1_Buf[DAQ0010_1_BUF_LEN];
__IO uint8_t arrDAQ3003_1_Buf[DAQ3003_1_BUF_LEN];

uint16_t arrUPPER_COM_RX_STA = 0;       //����״̬���	 
uint16_t arrPWR0204_1_RX_STA = 0;       //����״̬���	 
uint16_t arrPWR0204_2_RX_STA = 0;       //����״̬���	 
uint16_t arrDAQ0010_1_RX_STA = 0;       //����״̬���	 
uint16_t arrDAQ3003_1_RX_STA = 0;       //����״̬���	 



#endif
/**
  * @brief  Init
  * @param  void
  * @param  void
  * @retval None
  */
void HAL_UART_All_Init(void)
{
	REG_UART1_Init(115200);
//	REG_UART2_Init(115200);
//	REG_UART3_Init(115200);
//	REG_UART4_Init(115200);
//	REG_UART5_Init(115200);
//	//	LL_UART_Receive_IT(&UPPER_COM_HUART, arrUPPER_COM_Buf, UPPER_COM_BUF_LEN);//huart1
//	__HAL_UART_ENABLE_IT(&UPPER_COM_HUART, UART_IT_IDLE);
//	HAL_UART_Receive_DMA(&UPPER_COM_HUART, (uint8_t *)arrUPPER_COM_Buf, UPPER_COM_BUF_LEN);//huart1
//	
//		__HAL_UART_ENABLE_IT(&PWR0204_1_HUART, UART_IT_IDLE);
//	HAL_UART_Receive_DMA(&PWR0204_1_HUART, (uint8_t *)arrPWR0204_1_Buf, PWR0204_1_BUF_LEN);//huart1
//	
//		__HAL_UART_ENABLE_IT(&PWR0204_2_HUART, UART_IT_IDLE);
//	HAL_UART_Receive_DMA(&PWR0204_2_HUART, (uint8_t *)arrPWR0204_2_Buf, PWR0204_2_BUF_LEN);//huart1
//	
//		__HAL_UART_ENABLE_IT(&DAQ0010_1_HUART, UART_IT_IDLE);
//	HAL_UART_Receive_DMA(&DAQ0010_1_HUART, (uint8_t *)arrDAQ0010_1_Buf, DAQ0010_1_BUF_LEN);//huart1
//	
//	
//	LL_UART_Receive_IT(&PWR0204_1_HUART, arrPWR0204_1_Buf, PWR0204_1_BUF_LEN);//huart2
//	LL_UART_Receive_IT(&PWR0204_2_HUART, arrPWR0204_2_Buf, PWR0204_2_BUF_LEN);//huart3
//	LL_UART_Receive_IT(&DAQ0010_1_HUART, arrDAQ0010_1_Buf, DAQ0010_1_BUF_LEN);//huart4
}

/**
  * @brief  Init
  * @param  void
  * @param  void
  * @retval None
  */
void REG_UART1_Init(uint32_t band)
{
//	float temp;
//	uint16_t mantissa;
//	uint16_t fraction;	   
//	temp=(float)(72000000)/(band*16);//�õ�USARTDIV
//	mantissa=temp;				 //�õ���������
//	fraction=(temp-mantissa)*16; //�õ�С������	 
//    mantissa<<=4;
//	mantissa+=fraction; 
//	RCC->APB2ENR|=1<<2;   //ʹ��PORTA��ʱ��  
//	RCC->APB2ENR|=1<<14;  //ʹ�ܴ���ʱ�� 
//	GPIOA->CRH&=0XFFFFF00F;//IO״̬����
//	GPIOA->CRH|=0X000008B0;//IO״̬����
//		  
//	RCC->APB2RSTR|=1<<14;   //��λ����1
//	RCC->APB2RSTR&=~(1<<14);//ֹͣ��λ	   	   
//	//����������
// 	USART1->BRR=mantissa; // ����������	 
//	USART1->CR1|=0X200C;  //1λֹͣ,��У��λ.
	//ʹ�ܽ����ж�
	USART1->CR1|=1<<8;    //PE�ж�ʹ��
	USART1->CR1|=1<<5;    //���ջ������ǿ��ж�ʹ��	    	
//	MY_NVIC_Init(3,3,USART1_IRQn,2);//��2��������ȼ� 
}

/**
  * @brief  REG_UART2_Init
  * @param  void
  * @param  void
  * @retval None
  */
void REG_UART2_Init(uint32_t band)
{
//	float temp;
//	uint16_t mantissa;
//	uint16_t fraction;	   
//	temp=(float)(72000000)/(band*16);
//	mantissa=temp;				 
//	fraction=(temp-mantissa)*16;
//	mantissa<<=4;
//	mantissa+=fraction;
//	
//	RCC->APB2ENR|=1<<5;   //ʹ��PORTD��ʱ��  PD5->Tx PD6->Rx
//	GPIOD->CRL &= 0xF00FFFFF;
//	GPIOD->CRL |= 0x08B00000;
//	
//	RCC->APB1ENR|=1<<17;  //ʹ�ܴ���2ʱ�� 
////	RCC->APB1RSTR|=1<<17;   //��λ����2
////	RCC->APB1RSTR&=~(1<<17);//ֹͣ��λ	   	   
//	//����������
// 	USART2->BRR=mantissa; // ����������	 
//	USART2->CR1|=0X200C;  //1λֹͣ,��У��λ.
	
	//ʹ�ܽ����ж�
	USART2->CR1|=1<<8;    //PE�ж�ʹ��
	USART2->CR1|=1<<5;    //���ջ������ǿ��ж�ʹ��	    	
//	MY_NVIC_Init(3,3,USART1_IRQn,2);//��2��������ȼ� 
}
/**
  * @brief  Init
  * @param  void
  * @param  void
  * @retval None
  */
void REG_UART3_Init(uint32_t band)
{
//	float temp;
//	uint16_t mantissa;
//	uint16_t fraction;	   
//	temp=(float)(72000000)/(band*16);//�õ�USARTDIV
//	mantissa=temp;				 //�õ���������
//	fraction=(temp-mantissa)*16; //�õ�С������	 
//    mantissa<<=4;
//	mantissa+=fraction; 
//	RCC->APB2ENR|=1<<2;   //ʹ��PORTA��ʱ��  
//	RCC->APB2ENR|=1<<14;  //ʹ�ܴ���ʱ�� 
//	GPIOA->CRH&=0XFFFFF00F;//IO״̬����
//	GPIOA->CRH|=0X000008B0;//IO״̬����
//		  
//	RCC->APB2RSTR|=1<<14;   //��λ����1
//	RCC->APB2RSTR&=~(1<<14);//ֹͣ��λ	   	   
//	//����������
// 	USART1->BRR=mantissa; // ����������	 
//	USART1->CR1|=0X200C;  //1λֹͣ,��У��λ.
	//ʹ�ܽ����ж�
	USART3->CR1|=1<<8;    //PE�ж�ʹ��
	USART3->CR1|=1<<5;    //���ջ������ǿ��ж�ʹ��	    	
//	MY_NVIC_Init(3,3,USART1_IRQn,2);//��2��������ȼ� 
}
/**
  * @brief  Init
  * @param  void
  * @param  void
  * @retval None
  */
void REG_UART4_Init(uint32_t band)
{
//	float temp;
//	uint16_t mantissa;
//	uint16_t fraction;	   
//	temp=(float)(72000000)/(band*16);//�õ�USARTDIV
//	mantissa=temp;				 //�õ���������
//	fraction=(temp-mantissa)*16; //�õ�С������	 
//    mantissa<<=4;
//	mantissa+=fraction; 
//	RCC->APB2ENR|=1<<2;   //ʹ��PORTA��ʱ��  
//	RCC->APB2ENR|=1<<14;  //ʹ�ܴ���ʱ�� 
//	GPIOA->CRH&=0XFFFFF00F;//IO״̬����
//	GPIOA->CRH|=0X000008B0;//IO״̬����
//		  
//	RCC->APB2RSTR|=1<<14;   //��λ����1
//	RCC->APB2RSTR&=~(1<<14);//ֹͣ��λ	   	   
//	//����������
// 	USART1->BRR=mantissa; // ����������	 
//	USART1->CR1|=0X200C;  //1λֹͣ,��У��λ.
	//ʹ�ܽ����ж�
	UART4->CR1|=1<<8;    //PE�ж�ʹ��
	UART4->CR1|=1<<5;    //���ջ������ǿ��ж�ʹ��	    	
//	MY_NVIC_Init(3,3,USART1_IRQn,2);//��2��������ȼ� 
}
/**
  * @brief  Init
  * @param  void
  * @param  void
  * @retval None
  */
void REG_UART5_Init(uint32_t band)
{
//	float temp;
//	uint16_t mantissa;
//	uint16_t fraction;	   
//	temp=(float)(72000000)/(band*16);//�õ�USARTDIV
//	mantissa=temp;				 //�õ���������
//	fraction=(temp-mantissa)*16; //�õ�С������	 
//    mantissa<<=4;
//	mantissa+=fraction; 
//	RCC->APB2ENR|=1<<2;   //ʹ��PORTA��ʱ��  
//	RCC->APB2ENR|=1<<14;  //ʹ�ܴ���ʱ�� 
//	GPIOA->CRH&=0XFFFFF00F;//IO״̬����
//	GPIOA->CRH|=0X000008B0;//IO״̬����
//		  
//	RCC->APB2RSTR|=1<<14;   //��λ����1
//	RCC->APB2RSTR&=~(1<<14);//ֹͣ��λ	   	   
//	//����������
// 	USART1->BRR=mantissa; // ����������	 
//	USART1->CR1|=0X200C;  //1λֹͣ,��У��λ.
	//ʹ�ܽ����ж�
	UART5->CR1|=1<<8;    //PE�ж�ʹ��
	UART5->CR1|=1<<5;    //���ջ������ǿ��ж�ʹ��	    	
//	MY_NVIC_Init(3,3,USART1_IRQn,2);//��2��������ȼ� 
}


void USART1_IRQHandler(void)
{
	HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET);
	uint8_t res;
	if(USART1->SR&(1<<5))//���յ�����
	{	 
		res=USART1->DR; 
		if((arrUPPER_COM_RX_STA&0x8000)==0)//����δ���
		{
			if(arrUPPER_COM_RX_STA&0x4000)//���յ���0x0d
			{
				if(res!=0x0a)arrUPPER_COM_RX_STA=0;//���մ���,���¿�ʼ
				else arrUPPER_COM_RX_STA|=0x8000;	//��������� 
			}else //��û�յ�0X0D
			{	
				if(res==0x0d)arrUPPER_COM_RX_STA|=0x4000;
				else
				{
					arrUPPER_COM_Buf[arrUPPER_COM_RX_STA&0X3FFF]=res;
					arrUPPER_COM_RX_STA++;
					if(arrUPPER_COM_RX_STA>(UPPER_COM_BUF_LEN-1))arrUPPER_COM_RX_STA=0;//�������ݴ���,���¿�ʼ����	  
				}		 
			}
		}  		 									     
	}	
}
//void My_USART_Handler(USART_TypeDef* USARTx , uint8_t arrDAQ3003_1_RX_STA, uint8_t Rx_Flag)
//{
//			if(USART_RX_STA&0x8000) __NOP();
//	
//	    uint8_t res;
//    if(USARTx->SR & (1 << 5)) //���յ�����
//    {
//        res = USARTx->DR;
//        if((arrUPPER_COM_RX_STA & 0x8000) == 0) //����δ���
//        {
//            if(arrUPPER_COM_RX_STA & 0x4000) //���յ���0x0d
//            {
//                if(res != 0x0a)	arrUPPER_COM_RX_STA = 0; //���մ���,���¿�ʼ
//                else arrUPPER_COM_RX_STA |= 0x8000;	//���������
//            }
//            else  //��û�յ�0X0D
//            {
//                if(res == 0x0d)	arrUPPER_COM_RX_STA |= 0x4000;
//                else
//                {
//                    arrUPPER_COM_Buf[arrUPPER_COM_RX_STA & 0X3FFF] = res;
//                    arrUPPER_COM_RX_STA++;
//                    if(arrUPPER_COM_RX_STA > (UPPER_COM_BUF_LEN - 1))	arrUPPER_COM_RX_STA = 0; //�������ݴ���,���¿�ʼ����
//                }
//            }
//        }
//    }
//}


/**
  * @brief  ���ڴ�ӡ����
  * @param  UART_HandleTypeDef *huart
  * @param  void* fmt, ...
  * @retval None
  */
void UART_Printf(UART_HandleTypeDef *huart, const char* fmt, ...)
{
#ifdef SWUST_FREESCALE_LIB_Enzo
  uint8_t buff[512] = {0};
	uint8_t *p = buff;
	va_list ap;

	va_start(ap, fmt);
	vsprintf((char *)buff, fmt, ap);
	
	uint8_t size=0;
	while(*p++)
  {
		size++;
	}
	HAL_UART_Transmit(huart, buff, size, 0xff);

#ifdef RTT_MASTER	
	if(huart == &UPPER_COM_HUART)
	{
		SEGGER_RTT_printf(0, "[1:]%s", buff);
	}
  else if(huart == &PWR0204_1_HUART)
  {
		SEGGER_RTT_printf(0, "[2:]%s", buff);
  }
	else if(huart == &PWR0204_2_HUART)
  {
		SEGGER_RTT_printf(0, "[3:]%s", buff);
  }
	else if(huart == &DAQ0010_1_HUART)
  {		
		SEGGER_RTT_printf(0, "[4:]%s", buff);
  }
	
#endif
	va_end(ap);
#endif
}


/**
  * @brief  Ϊ���ڿ���û���жϵ�DMA���䣬Ϊ�˼����жϴ���Ϊ�����жϿճ���Դ��
  *         ����HAL��ĺ���(�˴���main�����е���)
  * @param  hdma: ָ��DMA_HandleTypeDef�ṹ���ָ�룬����ṹ�������DMA����������Ϣ.  
  * @retval HAL status
  */
HAL_StatusTypeDef LL_UART_Receive_DMA(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size)
{
#ifdef SWUST_FREESCALE_LIB_Enzo
  uint32_t *tmp;
  uint32_t tmp1 = 0;
  tmp1 = huart->gState;//  tmp1 = huart->State;

  if((tmp1 == HAL_UART_STATE_READY) || (tmp1 == HAL_UART_STATE_BUSY_TX))
  {
    if((pData == NULL ) || (Size == 0)) 
    {
      return HAL_ERROR;
    }
    
    /* Process Locked */
    __HAL_LOCK(huart);
    
    huart->pRxBuffPtr = pData;
    huart->RxXferSize = Size;
    
    huart->ErrorCode = HAL_UART_ERROR_NONE;
    /* Check if a transmit process is ongoing or not */
    if(huart->gState == HAL_UART_STATE_BUSY_TX)
    {
      huart->gState = HAL_UART_STATE_BUSY_TX_RX;
    }
    else
    {
      huart->gState = HAL_UART_STATE_BUSY_RX;
    }
    
    /* Enable the DMA Stream */
    tmp = (uint32_t*)&pData;
    HAL_DMA_Start(huart->hdmarx, (uint32_t)&huart->Instance->DR, *(uint32_t*)tmp, Size);
    
    /* Enable the DMA transfer for the receiver request by setting the DMAR bit 
    in the UART CR3 register */
    huart->Instance->CR3 |= USART_CR3_DMAR;
    
    /* Process Unlocked */
    __HAL_UNLOCK(huart);
    
    return HAL_OK;
  }
  else
  {
    return HAL_BUSY; 
  }
#endif
}


/**
  * @brief  ͨ����������ʽ�������ݣ����ݳ���������޶ȣ�����������޶�֮�ڿ��Խ������ⳤ�ȵ����� DMADMA
  * @param  huart: ָ��UART_HandleTypeDef�ṹ���ָ�룬��ָ�������UART��������Ϣ
  * @param  pData: ָ��������ݻ�������ָ��
  * @param  Size: �ɽ������ݵ���󳤶�
  * @retval HAL status
  */
HAL_StatusTypeDef LL_UART_Receive_IT(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size)
{
	__HAL_UART_ENABLE_IT(huart, UART_IT_IDLE);//�������ڿ����ж�
	
	LL_UART_Receive_DMA(huart,pData,Size);//����DMA��������

	return HAL_OK;
}


///**
//  * @brief  ���ڿ����ж�DMA���ջص�����
//  * @param  ����ͨ����ַ UART_HandleTypeDef *
//  * @retval None
//  */
//void UART_IdleRxCallback(UART_HandleTypeDef *huart)
//{
//	if(huart == &UPPER_COM_HUART)
//	{

//		UART_Printf(&UPPER_COM_HUART, "DBG1:arrUPPER_COM_Buf\r\n");
//		UART_Printf(&UPPER_COM_HUART, (const char*)arrUPPER_COM_Buf);
//		UART_Printf(&UPPER_COM_HUART, "\r\n");
//		
////			__HAL_UART_ENABLE_IT(huart, UART_IT_IDLE);//�������ڿ����ж�
////		HAL_UART_Transmit_DMA(&UPPER_COM_HUART,UPPER_COM_BUF_LEN);
////		Dma_Callback_RC_Handle(&tRC_Data, arrRC_Buf);
////    UPDATE_CHECKTIME(&tRC_Data);
//	}
//  else if(huart == &PWR0204_1_HUART)
//  {

//		UART_Printf(&UPPER_COM_HUART, "DBG2:arrPWR0204_1_Buf\r\n");
//		UART_Printf(&UPPER_COM_HUART, (const char*)arrPWR0204_1_Buf);
//		UART_Printf(&UPPER_COM_HUART, "\r\n");
////		&PWR0204_1_HUART, arrPWR0204_1_Buf, PWR0204_1_BUF_LEN)
////    judgementDataHandler();
//  }
//	else if(huart == &PWR0204_2_HUART)
//  {
////				UART_Printf(&UPPER_COM_HUART, "___________________________________\r\n");
//		UART_Printf(&UPPER_COM_HUART, "DBG3:arrPWR0204_2_Buf\r\n");
//		UART_Printf(&UPPER_COM_HUART, (const char*)arrPWR0204_2_Buf);
//		UART_Printf(&UPPER_COM_HUART, "\r\n");
////    judgementDataHandler();
//  }
//	else if(huart == &DAQ0010_1_HUART)
//  {
//		UART_Printf(&UPPER_COM_HUART, "DBG4:arrDAQ0010_1_Buf\r\n");
//		UART_Printf(&UPPER_COM_HUART, (const char*)arrDAQ0010_1_Buf);
//		UART_Printf(&UPPER_COM_HUART, "\r\n");
////    judgementDataHandler();
//  }
////	else if(huart == &DAQ3003_1_HUART)// UART5 ����
////  {
////		UART_Printf(&UPPER_COM_HUART, "DBG5:arrDAQ3003_1_Buf\r\n");
////		UART_Printf(&UPPER_COM_HUART, (const char*)arrDAQ3003_1_Buf);
////		UART_Printf(&UPPER_COM_HUART, "\r\n");
//////    BT_RxDataHandler();
////  }  
//}

/**
  * @brief  ͨ����������ʽ�������ݣ����ݳ���������޶ȣ�����������޶�֮�ڿ��Խ������ⳤ�ȵ����� 
  * @param  huart: ָ��UART_HandleTypeDef�ṹ���ָ�룬��ָ�������UART��������Ϣ
  * @param  Size: �ɽ������ݵ���󳤶�
  * @retval None
  */
void LL_UsartIdleHanlder(UART_HandleTypeDef *huart,uint16_t Size)
{
#ifdef SWUST_FREESCALE_LIB_Enzo
	uint32_t DMA_FLAGS;//���ݴ��ڵĲ�ͬ��ѡ�������ͬ��DMA��־λ
//  uint32_t tmp;
	
	if(__HAL_UART_GET_FLAG(huart, UART_FLAG_IDLE))
  {
		/*���IDLE��־λ*/
    __HAL_UART_CLEAR_IDLEFLAG(huart);
    
		DMA_FLAGS = __HAL_DMA_GET_TC_FLAG_INDEX(huart->hdmarx);

    UART_IdleRxCallback(huart);
		//����DMA
	  __HAL_DMA_DISABLE(huart->hdmarx);
		__HAL_DMA_CLEAR_FLAG(huart->hdmarx,DMA_FLAGS);

		huart->hdmarx->Instance->CNDTR = (uint16_t)Size;//		__HAL_DMA_SET_COUNTER(huart->hdmarx,Size);

		__HAL_DMA_ENABLE(huart->hdmarx);
	}
#endif
}


#define IS_09(c)  ((c >= '0') && (c <= '9'))
/**
  * @brief  Extract parameters from a string
  * @param  inputStr : The input string
  * @param  tarNum   : The pointer of parameter
  * @param  ParaType : Type of parameter
  *   @arg  'i'  : int32_t
  *   @arg  'f'  : float
  * @param  ParaNum  : amount of parameter
  *   @arg  0    : not specify parameter number,end with '\0'
  *   @arg  1~255: amount of parameter
  * @param  Separator: Separator of parameter
  * @retval 1: Correct
  *         0: Error
  *         by Junior Yip
  */
uint8_t Extract_Parameter(uint8_t *inputStr,void *tarNum, uint8_t ParaType,uint8_t ParaNum,uint8_t Separator){
	
	uint16_t i=0;
	uint8_t j=0,Len=0;
	int32_t NumSign=0;
	uint8_t NumFlag=0,DotFlag=0;
	
	//convert to int32_t
	if(ParaType=='i'){
		
		int32_t *intNum;
		int32_t NumBuf=0;
		intNum=tarNum;
		
		while(ParaNum==0?inputStr[i]!='\0':j<ParaNum){
			
			//Symbol check
			if(NumSign==0){
				if(inputStr[i]=='-'){
					NumSign = -1;
					i++;
				}
				else
					NumSign = 1;
			}
			
			if(IS_09(inputStr[i])){
				if(Len>10){
					return 0;
				}
				NumBuf=NumBuf*10 + inputStr[i]-'0';
				Len++;
			}
			else if(inputStr[i]==Separator){
				
				intNum[j]=NumBuf*NumSign;
				NumBuf=0;
				j++;
				Len=0;
				NumSign=0;
			}
			else{
		//String format error
				return 0;
			}
			if(inputStr[++i]=='\0'){
				intNum[j]=NumBuf*NumSign;
				j++;
				NumSign=0;
				NumBuf=0;
				Len=0;
			}
		}
		
	}
	//convert to float
	else if(ParaType=='f'){
		
		float *floatNum;
		floatNum=tarNum;
		float NumBuf=0;
		float temp=10;
		
		while(ParaNum==0?inputStr[i]!='\0':j<ParaNum){
			
			//Symbol check
			if(NumSign==0){
				if(inputStr[i]=='-'){
					NumSign = -1;
					i++;
				}
				else
					NumSign = 1;
			}
			
			if(IS_09(inputStr[i])){
				if(Len>10){
					return 0;
				}
				if(DotFlag==0){
					NumBuf=NumBuf*10 + inputStr[i]-'0';
				}
				else{
					NumBuf = NumBuf + ((float)((int32_t)inputStr[i]-'0'))/temp;
					temp=temp*10;
				}
				Len++;
				NumFlag=1;
			}
			else if(inputStr[i]=='.' && DotFlag==0 && NumFlag==1){
				Len=0;
				NumFlag=0;
				DotFlag=1;
			}
			else if(inputStr[i]==Separator&&NumFlag==1){
				Len=0;
				floatNum[j]=NumBuf*NumSign;
				j++;
				temp=10;
				NumBuf=0;
				NumSign=0;
				NumFlag=0;
				DotFlag=0;
			}
			else{
		//String format error
				return 0;
			}
			
			if(inputStr[++i]=='\0'){
				Len=0;
				floatNum[j]=NumBuf*NumSign;
				j++;
				temp=10;
				NumBuf=0;
				NumSign=0;
				NumFlag=0;
				DotFlag=0;
			}
		}
	}
	else{
		//Error Type
		return 0;
	}
		
	if(ParaNum==0 || j==ParaNum)
		return 1;
	else 
		//ParaNum error
		return 0;
}

