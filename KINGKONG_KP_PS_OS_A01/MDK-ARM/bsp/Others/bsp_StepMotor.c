
#include "bsp_StepMotor.h"
#include <math.h>

#define DEBUG_TEST


__IO uint8_t X_AxisSensorFlag = Normal;
__IO uint8_t Y_AxisSensorFlag = Normal;
__IO uint8_t X_AxisStatus = 0;
__IO uint8_t Y_AxisStatus = 0;
__IO uint8_t EXT_X_STOP_FLAG = 0;
__IO uint8_t EXT_Y_STOP_FLAG = 0;

__IO uint8_t TimerFlag = 0;
__IO uint8_t NonDecelMode = 0;// 0:正常减速模式 1：非正常减速【走一定距离后直接加到更高的速度或者降低速度】


#define FALSE                      	0
#define TRUE                        1
//THETA:步距角 T1_FREQ：定时频率 
#define T1_FREQ                     (SystemCoreClock/(STEPMOTOR_TIM_PRESCALER+1)) // 频率ft值
#define THETA                       ((float)(2*3.14159/SPR))       // α= 2*pi/spr StepAngle
#define A_T_x10                     ((float)(10*THETA*T1_FREQ))
#define T1_FREQ_148                 ((float)((T1_FREQ*0.676)/10))  // 0.6776为误差修正值
#define A_SQ                        ((float)(2*100000*THETA)) 
#define A_x200                      ((float)(200*THETA))
#define MAX_NUM_LAP 						    INT32_MAX
#define MAX_NUM_STEP 						    UINT32_MAX

#define IDLE	   						        0	 // 搜索原点状态:空闲
#define MOVETOZERO 							    3  // 搜索原点状态:捕获原点

#define PositiveDir                 1  
#define NegitiveDir                 -1
#define FASTSEEK   							    1  // 搜索原点状态:快速搜索
#define SLOWSEEK 							      2  // 搜索原点状态:慢速搜索

typedef struct {
  __IO uint8_t  State ;  			// 电机旋转状态
  __IO int8_t   Dir ;        	
  __IO uint32_t DecelStartPos;// 启动减速位置
  __IO int32_t  StepDelay;  	// 下个脉冲周期（时间间隔），启动时为加速度
  __IO int32_t  StepsDecel;   // 减速阶段步数
  __IO int32_t  MinDelay;   	// 最小脉冲周期(最大速度，即匀速段速度)
  __IO int32_t  AccelCnt; 		// 加减速阶段计数值
}StepMotorMotionControl;


StepMotorMotionControl StepMotor1    = {STOP,PositiveDir,0,0,0,0,0};   //X
StepMotorMotionControl StepMotor2    = {STOP,PositiveDir,0,0,0,0,0};   //Y

__IO uint8_t  ZeroStep = IDLE;	//搜索原点状态机
__IO uint8_t  LimPosi = FALSE ; //正方向极限标志位  True:到达极限位  False:未到达极限位
__IO uint8_t  LimNega = FALSE ; //负方向极限标志位

__IO int32_t  X_Axis_StepPosition     = 0;           // 当前位置
__IO int32_t  Y_Axis_StepPosition     = 0;           // 当前位置


#ifdef DEBUG_TEST
	float temp[5];	
#endif


void X_AxisMoveRelative(__IO int32_t Steps, __IO uint32_t Alpha1, __IO uint32_t Alpha2, __IO uint32_t Omega)
{  
	__IO uint32_t StepsAccel;
	__IO uint32_t StepsNonDecel; 
	if(Steps < 0) 
	{
		StepMotor1.Dir = NegitiveDir;
		X_StepMotorDirN();	
		Steps = -Steps; 
	}
	else
	{
		StepMotor1.Dir = PositiveDir; 
		X_StepMotorDirP();
	}
	if(Steps == 1)    
	{
		StepMotor1.AccelCnt = -1;  
		StepMotor1.State = DECELERATE; 
		StepMotor1.StepDelay = 1000;	
	}
	else if(Steps != 0)
	{
		StepMotor1.MinDelay = (int32_t)(A_T_x10 / Omega);
		StepMotor1.StepDelay = (int32_t)((T1_FREQ_148 * sqrt(A_SQ / Alpha1))/10);//C0,初始速度的定时器值		
		StepsAccel = (uint32_t)(Omega * Omega / (A_x200 * Alpha1 / 10));
		if(StepsAccel == 0)
		{
		  StepsAccel = 1;
		}
		StepsNonDecel = (uint32_t)(Steps * Alpha2 / (Alpha1 + Alpha2));
		temp[0] = StepsNonDecel;
		if(StepsNonDecel == 0)
		{
		  StepsNonDecel = 1;
		}
		if(StepsNonDecel <= StepsAccel)	//Trapezoid
		{
				StepMotor1.StepsDecel = StepsNonDecel - Steps;
				temp[1] =StepMotor1.StepsDecel;
		}
		else														//Triangle
		{
			StepMotor1.StepsDecel = - (StepsAccel * Alpha1 / Alpha2);
			temp[2] = StepMotor1.StepsDecel;
		}
		if(StepMotor1.StepsDecel == 0)
		{
		  StepMotor1.StepsDecel = -1;
		}
		StepMotor1.DecelStartPos = Steps + StepMotor1.StepsDecel;
		if(StepMotor1.StepDelay <= StepMotor1.MinDelay)
		{
			StepMotor1.StepDelay = StepMotor1.MinDelay;
			StepMotor1.State = UNIFORM;
		}
		else
		{
			StepMotor1.State = ACCELERATE;
		}    
		StepMotor1.AccelCnt = 0;
	}
	
#ifdef DEBUG_TEST
	printf("\r\n%d,%d,%d,%d,%d,%d,",Steps,StepsNonDecel,StepMotor1.StepsDecel,StepsAccel,   StepMotor1.MinDelay,StepMotor1.StepDelay);
	printf("\r\n%d,%d,%d\r\n",Alpha1,Alpha2,Omega);
#endif
	EXT_X_STOP_FLAG = 0;//1:stop 0:others
	if(StepMotor1.MinDelay <= 50)	StepMotor1.MinDelay = 50;
//	__HAL_TIM_SET_COMPARE(&htimStepMotor, TIM_CHANNEL_1, STEPMOTOR_TIMx->CNT + StepMotor1.StepDelay);
//	TIM_CCxChannelCmd(STEPMOTOR_TIMx, TIM_CHANNEL_1, TIM_CCx_ENABLE);
//	StepMotorENABLE();
	
}

void Y_AxisMoveRelative(__IO int32_t Steps, __IO uint32_t Alpha1, __IO uint32_t Alpha2, __IO uint32_t Omega)
{  
	__IO uint32_t StepsAccel;
	__IO uint32_t StepsNonDecel; 
	if(Steps < 0) 
	{
		StepMotor2.Dir = NegitiveDir;
		Y_StepMotorDirN();	
		Steps = -Steps; 
	}
	else
	{
		StepMotor2.Dir = PositiveDir; 
		Y_StepMotorDirP();
	}
	if(Steps == 1)    
	{
		StepMotor2.AccelCnt = -1;  
		StepMotor2.State = DECELERATE; 
		StepMotor2.StepDelay = 1000;	
	}
	else if(Steps != 0)
	{
		StepMotor2.MinDelay = (int32_t)(A_T_x10 / Omega);
		StepMotor2.StepDelay = (int32_t)((T1_FREQ_148 * sqrt(A_SQ / Alpha1))/10);//C0,初始速度的定时器值		
		StepsAccel = (uint32_t)(Omega * Omega / (A_x200 * Alpha1 / 10));
		if(StepsAccel == 0)
		{
		  StepsAccel = 1;
		}
		StepsNonDecel = (uint32_t)(Steps * Alpha2 / (Alpha1 + Alpha2));
//		temp[0] = StepsNonDecel;
		if(StepsNonDecel == 0)
		{
		  StepsNonDecel = 1;
		}
		if(StepsNonDecel <= StepsAccel)	//Trapezoid
		{
				StepMotor2.StepsDecel = StepsNonDecel - Steps;
//				temp[1] =StepMotor2.StepsDecel;
		}
		else														//Triangle
		{
			StepMotor2.StepsDecel = - (StepsAccel * Alpha1 / Alpha2);
//			temp[2] = StepMotor2.StepsDecel;
		}
		if(StepMotor2.StepsDecel == 0)
		{
		  StepMotor2.StepsDecel = -1;
		}
		StepMotor2.DecelStartPos = Steps + StepMotor2.StepsDecel;
		if(StepMotor2.StepDelay <= StepMotor2.MinDelay)
		{
			StepMotor2.StepDelay = StepMotor2.MinDelay;
			StepMotor2.State = UNIFORM;
		}
		else
		{
			StepMotor2.State = ACCELERATE;
		}    
		StepMotor2.AccelCnt = 0;
	}
#ifdef DEBUG_TEST
printf("\r\n%d,%d,%d,%d,%d,%d,",Steps,StepsNonDecel,StepMotor2.StepsDecel,StepsAccel,   StepMotor2.MinDelay,StepMotor2.StepDelay);
printf("\r\n%d,%d,%d\r\n",Alpha1,Alpha2,Omega);
#endif
	EXT_Y_STOP_FLAG = 0;//1:stop 0:others
	if(StepMotor2.MinDelay <= 50)	StepMotor2.MinDelay = 50;
//	__HAL_TIM_SET_COMPARE(&htimStepMotor, TIM_CHANNEL_1, STEPMOTOR_TIMx->CNT + StepMotor2.StepDelay);
//	TIM_CCxChannelCmd(STEPMOTOR_TIMx, TIM_CHANNEL_1, TIM_CCx_ENABLE);
//	StepMotorENABLE();
}



void STEPMOTOR_TIMx_IRQHandler(void)
{ 
	__IO static uint8_t i=0;
  
	if(__HAL_TIM_GET_IT_SOURCE(&htimStepMotor, STEPMOTOR_TIM_IT_CCx) != RESET)
	{
		__HAL_TIM_CLEAR_IT(&htimStepMotor, STEPMOTOR_TIM_IT_CCx);
		__HAL_TIM_SET_COMPARE(&htimStepMotor, TIM_CHANNEL_1, STEPMOTOR_TIMx->CNT + 1);
//		__HAL_TIM_SET_COMPARE(&htimStepMotor, TIM_CHANNEL_1, STEPMOTOR_TIMx->CNT + StepMotor1.StepDelay);
		if(++i == 2) 
		{
			i = 0; 
			TimerFlag = 1;
		}
	}
}



void StepMotor_X_INTTask(void)
{
		uint16_t StepDelayNow = 0;
		__IO static uint16_t StepDelayAccelLast = 0;
		__IO static uint32_t Steps = 0;
		__IO static int32_t Remainder = 0;
	
			if(StepMotor1.State != STOP)
			{
					Tog_X_Axis(StepMotor1.StepDelay,StepMotor1.StepDelay);
			}
			
			if(StepMotor1.Dir == NegitiveDir)
			{
				if(LimNega == TRUE)		//Negative DirectionLimit->Stop
				{
					StepMotor1.State = STOP;
				}
				else 
				{
					LimPosi = FALSE;
          LimNega = FALSE; 
				}
			}
			else 
			{
				if(LimPosi == TRUE)	
				{
					StepMotor1.State = STOP;
				}
				else 
				{
          LimPosi = FALSE;
					LimNega = FALSE;  
				}
			}
			
			switch(StepMotor1.State) 
			{
				case STOP:
					EXT_X_STOP_FLAG = 1;//1:stop 0:others
					Steps = 0;  
					Remainder = 0;      
					StepDelayAccelLast = 0;
//					TIM_CCxChannelCmd(STEPMOTOR_TIMx, TIM_CHANNEL_1, TIM_CCx_DISABLE); //Disable   
//					__HAL_TIM_CLEAR_FLAG(&htimStepMotor, STEPMOTOR_TIM_FLAG_CCx);
//					StepMotorDISABLE();
					Stop_X_Axis();
					
					break;
					
				case ACCELERATE:
					Steps++;      		
					if(StepMotor1.Dir == PositiveDir)
					{		  	
						X_Axis_StepPosition++; 	 
					}
					else
					{
						X_Axis_StepPosition--; 	  
					}
					StepMotor1.AccelCnt++; 		
					
					StepDelayNow = StepMotor1.StepDelay - (((2 * StepMotor1.StepDelay) + Remainder)/(4 * StepMotor1.AccelCnt + 1));
					Remainder = ((2 * StepMotor1.StepDelay)+Remainder)%(4 * StepMotor1.AccelCnt + 1);
					
					if(Steps >= StepMotor1.DecelStartPos)				// Start decelerate ?
					{
						StepMotor1.AccelCnt = StepMotor1.StepsDecel; 	
						StepMotor1.State = DECELERATE;           
					}
					else if(StepDelayNow <= StepMotor1.MinDelay)////Max Speed ?
					{
						StepDelayAccelLast = StepDelayNow; 	
						StepDelayNow = StepMotor1.MinDelay;    
						Remainder = 0;                          
						StepMotor1.State = UNIFORM;               
					}	
					break;
					
				case UNIFORM:
					Steps++; 		
					if(StepMotor1.Dir==PositiveDir)
					{	  	
						X_Axis_StepPosition++;
					}
					else
					{
						X_Axis_StepPosition--; 
					}
							
					StepDelayNow = StepMotor1.MinDelay;      
					if(Steps >= StepMotor1.DecelStartPos)   
					{
						StepMotor1.AccelCnt = StepMotor1.StepsDecel;  
						StepDelayNow = StepDelayAccelLast;
						StepMotor1.State = DECELERATE;    
					}
					break;
					
				case DECELERATE:
					Steps++; 
					if(StepMotor1.Dir == PositiveDir)
					{		  	
						X_Axis_StepPosition++; 
					}
					else
					{
						X_Axis_StepPosition--;
					}
					StepMotor1.AccelCnt++;
					StepDelayNow = StepMotor1.StepDelay - (((2 * StepMotor1.StepDelay) + Remainder)/(4 * StepMotor1.AccelCnt + 1)); 
					Remainder = ((2 * StepMotor1.StepDelay)+Remainder)%(4 * StepMotor1.AccelCnt + 1);
				  
					
					if(StepMotor1.AccelCnt >= 0)//检查是否为最后一步
					{
							StepMotor1.State = STOP;
					}
//					if((DOG == TRUE)&&(HomeCapture == FALSE))
//					{
//						if(StepDelayNow >= StepMotor1.MinDelay )		
//						{
//							StepDelayNow = StepMotor1.MinDelay;
//							StepMotor1.DecelStartPos = MAX_NUM_STEP;
//							Remainder = 0;       
//							StepMotor1.State = UNIFORM;
//						}		
//					}
					break;
				default :break;
			}      
			StepMotor1.StepDelay = StepDelayNow;
}

void StepMotor_Y_INTTask(void)
{
		uint16_t StepDelayNow = 0;
		__IO static uint16_t StepDelayAccelLast = 0;
		__IO static uint32_t Steps = 0;
		__IO static int32_t Remainder = 0;
	
			if(StepMotor2.State != STOP)
			{
					Tog_Y_Axis(StepMotor2.StepDelay,StepMotor2.StepDelay);
			}
			
			if(StepMotor2.Dir == NegitiveDir)
			{
				if(LimNega == TRUE)		//Negative DirectionLimit->Stop
				{
					StepMotor2.State = STOP;
				}
				else 
				{
					LimPosi = FALSE;
          LimNega = FALSE; 
				}
			}
			else 
			{
				if(LimPosi == TRUE)	
				{
					StepMotor2.State = STOP;
				}
				else 
				{
          LimPosi = FALSE;
					LimNega = FALSE;  
				}
			}
			
			switch(StepMotor2.State) 
			{
				case STOP:
					EXT_Y_STOP_FLAG = 1;//1:stop 0:others
					Steps = 0;  
					Remainder = 0;      
					StepDelayAccelLast = 0;
//					TIM_CCxChannelCmd(STEPMOTOR_TIMx, TIM_CHANNEL_1, TIM_CCx_DISABLE); //Disable   
//					__HAL_TIM_CLEAR_FLAG(&htimStepMotor, STEPMOTOR_TIM_FLAG_CCx);
//					StepMotorDISABLE();
					Stop_Y_Axis();
					
					break;
					
				case ACCELERATE:
					Steps++;      		
					if(StepMotor2.Dir == PositiveDir)
					{		  	
						Y_Axis_StepPosition++; 	 
					}
					else
					{
						Y_Axis_StepPosition--; 	  
					}
					StepMotor2.AccelCnt++; 		
					
					StepDelayNow = StepMotor2.StepDelay - (((2 * StepMotor2.StepDelay) + Remainder)/(4 * StepMotor2.AccelCnt + 1));
					Remainder = ((2 * StepMotor2.StepDelay)+Remainder)%(4 * StepMotor2.AccelCnt + 1);
					
					if(Steps >= StepMotor2.DecelStartPos)				// Start decelerate ?
					{
						StepMotor2.AccelCnt = StepMotor2.StepsDecel; 	
						StepMotor2.State = DECELERATE;           
					}
					else if(StepDelayNow <= StepMotor2.MinDelay)////Max Speed ?
					{
						StepDelayAccelLast = StepDelayNow; 	
						StepDelayNow = StepMotor2.MinDelay;    
						Remainder = 0;                          
						StepMotor2.State = UNIFORM;               
					}	
					break;
					
				case UNIFORM:
					Steps++; 		
					if(StepMotor2.Dir==PositiveDir)
					{	  	
						Y_Axis_StepPosition++;
					}
					else
					{
						Y_Axis_StepPosition--; 
					}
							
					StepDelayNow = StepMotor2.MinDelay;      
					if(Steps >= StepMotor2.DecelStartPos)   
					{
						StepMotor2.AccelCnt = StepMotor2.StepsDecel;  
						StepDelayNow = StepDelayAccelLast;
						StepMotor2.State = DECELERATE;    
					}
					break;
					
				case DECELERATE:
					Steps++; 
					if(StepMotor2.Dir == PositiveDir)
					{		  	
						Y_Axis_StepPosition++; 
					}
					else
					{
						Y_Axis_StepPosition--;
					}
					StepMotor2.AccelCnt++;
					StepDelayNow = StepMotor2.StepDelay - (((2 * StepMotor2.StepDelay) + Remainder)/(4 * StepMotor2.AccelCnt + 1)); 
					Remainder = ((2 * StepMotor2.StepDelay)+Remainder)%(4 * StepMotor2.AccelCnt + 1);
				  
					
					if(StepMotor2.AccelCnt >= 0)//检查是否为最后一步
					{
							StepMotor2.State = STOP;
					}
//					if((DOG == TRUE)&&(HomeCapture == FALSE))
//					{
//						if(StepDelayNow >= StepMotor2.MinDelay )		
//						{
//							StepDelayNow = StepMotor2.MinDelay;
//							StepMotor2.DecelStartPos = MAX_NUM_STEP;
//							Remainder = 0;       
//							StepMotor2.State = UNIFORM;
//						}		
//					}
					break;
				default :break;
			}      
			StepMotor2.StepDelay = StepDelayNow;
}
void StepMotor_Y_INTTaskqweqewwq(void)
{
		uint16_t StepDelayNow = 0;
		__IO static uint16_t StepDelayAccelLast = 0;
		__IO static uint32_t Steps = 0;
		__IO static int32_t Remainder = 0;
	
			if(StepMotor2.State != STOP)
			{
					Tog_Y_Axis(StepMotor2.StepDelay,StepMotor2.StepDelay);
			}
			
			if(StepMotor2.Dir == NegitiveDir)
			{
				if(LimNega == TRUE)		//Negative DirectionLimit->Stop
				{
					StepMotor2.State = STOP;
				}
				else 
				{
					LimPosi = FALSE;
          LimNega = FALSE; 
				}
			}
			else 
			{
				if(LimPosi == TRUE)	
				{
					StepMotor2.State = STOP;
				}
				else 
				{
          LimPosi = FALSE;
					LimNega = FALSE;  
				}
			}
			
			switch(StepMotor2.State) 
			{
				case STOP:
					EXT_Y_STOP_FLAG = 1;//1:stop 0:others
					Steps = 0;  
					Remainder = 0;      
					StepDelayAccelLast = 0;
//					TIM_CCxChannelCmd(STEPMOTOR_TIMx, TIM_CHANNEL_1, TIM_CCx_DISABLE); //Disable   
//					__HAL_TIM_CLEAR_FLAG(&htimStepMotor, STEPMOTOR_TIM_FLAG_CCx);
//					StepMotorDISABLE();
					Stop_Y_Axis();
					
					break;
					
				case ACCELERATE:
					Steps++;      		
					if(StepMotor2.Dir == PositiveDir)
					{		  	
						Y_Axis_StepPosition++; 	 
					}
					else
					{
						Y_Axis_StepPosition--; 	  
					}
					StepMotor2.AccelCnt++; 		
					
					StepDelayNow = StepMotor2.StepDelay - (((2 * StepMotor2.StepDelay) + Remainder)/(4 * StepMotor2.AccelCnt + 1));
					Remainder = ((2 * StepMotor2.StepDelay)+Remainder)%(4 * StepMotor2.AccelCnt + 1);
					
					if(Steps >= StepMotor2.DecelStartPos)				// Start decelerate ?
					{
						StepMotor2.AccelCnt = StepMotor2.StepsDecel; 	
						StepMotor2.State = DECELERATE;           
					}
					else if(StepDelayNow <= StepMotor2.MinDelay)////Max Speed ?
					{
						StepDelayAccelLast = StepDelayNow; 	
						StepDelayNow = StepMotor2.MinDelay;    
						Remainder = 0;                          
						StepMotor2.State = UNIFORM;               
					}	
					break;
					
				case UNIFORM:
					Steps++; 		
					if(StepMotor2.Dir==PositiveDir)
					{	  	
						Y_Axis_StepPosition++;
					}
					else
					{
						Y_Axis_StepPosition--; 
					}
							
					StepDelayNow = StepMotor2.MinDelay;      
					if(Steps >= StepMotor2.DecelStartPos)   
					{
						StepMotor2.AccelCnt = StepMotor2.StepsDecel;  
						StepDelayNow = StepDelayAccelLast;
						StepMotor2.State = DECELERATE;    
					}
					break;
					
				case DECELERATE:
					Steps++; 
					if(StepMotor2.Dir == PositiveDir)
					{		  	
						Y_Axis_StepPosition++; 
					}
					else
					{
						Y_Axis_StepPosition--;
					}
					StepMotor2.AccelCnt++;
					StepDelayNow = StepMotor2.StepDelay - (((2 * StepMotor2.StepDelay) + Remainder)/(4 * StepMotor2.AccelCnt + 1)); 
					Remainder = ((2 * StepMotor2.StepDelay)+Remainder)%(4 * StepMotor2.AccelCnt + 1);
				  
					
					if(StepMotor2.AccelCnt >= 0)//检查是否为最后一步
					{
							StepMotor2.State = STOP;
					}
//					if((DOG == TRUE)&&(HomeCapture == FALSE))
//					{
//						if(StepDelayNow >= StepMotor2.MinDelay )		
//						{
//							StepDelayNow = StepMotor2.MinDelay;
//							StepMotor2.DecelStartPos = MAX_NUM_STEP;
//							Remainder = 0;       
//							StepMotor2.State = UNIFORM;
//						}		
//					}
					break;
				default :break;
			}      
			StepMotor2.StepDelay = StepDelayNow;
}

void X_AxisSensorDetect(void)/* Rtn 0:Normal 1:Detected */
{

	if(HAL_GPIO_ReadPin(X_AXIS_SENSOR_ORIGINAL_GPIO_Port,X_AXIS_SENSOR_ORIGINAL_Pin)==ORI_DOWNLEVEL)
	{						
		X_AxisSensorFlag = OrginP;
		X_AxisStatus = 1;		
	}
	else if(HAL_GPIO_ReadPin(X_AXIS_SENSOR_LIM_P_GPIO_Port,X_AXIS_SENSOR_LIM_P_Pin) == LIM_POS_LEVEL)	//正方向位的极限引脚
	{
			X_AxisSensorFlag = 	LimPos;	
			X_AxisStatus = 1;
			LimPosi	= TRUE;     
			StepMotor1.State = STOP;		//碰到极限停下来			
	}
	else if(HAL_GPIO_ReadPin(X_AXIS_SENSOR_LIM_N_GPIO_Port,X_AXIS_SENSOR_LIM_N_Pin) == LIM_NEG_LEVEL)	//反方向位的极限引脚
	{
			X_AxisSensorFlag = 	LimNeg;	
			X_AxisStatus = 1;
			LimNega = TRUE;  
			StepMotor1.State = STOP;		   	
	}	
	else
	{
		X_AxisSensorFlag = 	Normal;
		X_AxisStatus = 0;		
	}
}

void Y_AxisSensorDetect(void)
{
	if(HAL_GPIO_ReadPin(Y_AXIS_SENSOR_ORIGINAL_GPIO_Port,Y_AXIS_SENSOR_ORIGINAL_Pin)==ORI_DOWNLEVEL)
	{						
		Y_AxisSensorFlag = OrginP;
		Y_AxisStatus = 1;		
	}
	else if(HAL_GPIO_ReadPin(Y_AXIS_SENSOR_LIM_P_GPIO_Port,Y_AXIS_SENSOR_LIM_P_Pin) == LIM_POS_LEVEL)	//正方向位的极限引脚
	{
			Y_AxisSensorFlag = 	LimPos;	
			Y_AxisStatus = 1;
			LimPosi	= TRUE;     
			StepMotor2.State = STOP;		//碰到极限停下来			
	}
	else if(HAL_GPIO_ReadPin(Y_AXIS_SENSOR_LIM_N_GPIO_Port,Y_AXIS_SENSOR_LIM_N_Pin) == LIM_NEG_LEVEL)	//反方向位的极限引脚
	{
			Y_AxisSensorFlag = 	LimNeg;	
			Y_AxisStatus = 1;
			LimNega = TRUE;  
			StepMotor2.State = STOP;		   	
	}	
	else
	{
		Y_AxisSensorFlag = 	Normal;
		Y_AxisStatus = 0;		
	}
}
