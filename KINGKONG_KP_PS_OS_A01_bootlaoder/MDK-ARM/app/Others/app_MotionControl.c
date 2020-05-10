/*
 * app_MotionControl.c
 *
 * Created on: 2017年11月14日
 * Author: Enzo
 */
 
#include "app_MotionControl.h"
#include "bsp_StepMotor.h"

/*****************Sensor Location**Description*******************
																										+(Y_LIM+)
																										|(4.0mm)
																										|
																										|
																										|
																										|
																										+(Y_ORG)
																										|(-2.0mm)
																										+(Y_LIM-)
																										|
																										_
																										M
								14.0mm		   												-			-3.0mm
*--|M|--(X_LIM-)---------<--DirP------------(X_ORG)-------(X_LIM+)
*****************************************************************/
float MyAbs(float f)
{
	if (f >= 0.0f)
	{
		return f;
	}

	return -f;
}

/*
*Eg：SPR=6400， if Length = P then go 1 round；
*Alpha1 Alpha2  [0.1 rad/s^2] 
*Length [mm] Speed [0.1mm/s]
*/
void X_AxixMove(__IO float Length, __IO uint32_t Alpha1, __IO uint32_t Alpha2, __IO uint32_t Speed)
{
	__IO int32_t Steps, Omega;
//	Steps = Length[mm]/(P[mm/2*PAI] / SPR[Number of steps per round);
	Steps = (int32_t)(Length * SPR / P);
//	Omega[0.1 rad/s] * P*2*PAI[mm/rad] = Speed[mm/s]
	Omega = Speed / (P * 2*3.14);
	X_AxisMoveRelative(Steps, Alpha1, Alpha2, Omega);
}
void Y_AxixMove(__IO float Length, __IO uint32_t Alpha1, __IO uint32_t Alpha2, __IO uint32_t Speed)
{
	__IO int32_t Steps, Omega;
//	Steps = Length[mm]/(P[mm/2*PAI] / SPR[Number of steps per round);
	Steps = (int32_t)(Length * SPR / P);
//	Omega[0.1 rad/s] * P*2*PAI[mm/rad] = Speed[mm/s]
	Omega = Speed / (P * 2*3.14);
	Y_AxisMoveRelative(Steps, Alpha1, Alpha2, Omega);
}

/*X轴绝对位置移动*/
void X_AxisMoveAbsolute(__IO int32_t PositionDesire,__IO uint32_t Alpha1, __IO uint32_t Alpha2,__IO uint32_t Omega)
{
	__IO int32_t RealSteps;
	__IO int8_t Dir = -1;
	RealSteps = (int32_t)(X_Axis_StepPosition - PositionDesire * SPR / P);
	if(RealSteps == 0)	
	{
		Dir = 0;
	}
	else Dir = -1;
	X_AxisMoveRelative(Dir * RealSteps, Alpha1, Alpha2, Omega);//
}


void Y_AxisMoveAbsolute(__IO int32_t PositionDesire,__IO uint32_t Alpha1, __IO uint32_t Alpha2,__IO uint32_t Omega)
{
	__IO int32_t RealSteps;
	__IO int8_t Dir = -1;
	RealSteps = (int32_t)(Y_Axis_StepPosition - PositionDesire * SPR / P);
	if(RealSteps == 0)	
	{
		Dir = 0;
	}
	else Dir = -1;
	Y_AxisMoveRelative(Dir * RealSteps, Alpha1, Alpha2, Omega);//
}


/*两坐标共同绝对位置移动*/
void CoordinateMoveAbsolute(__IO int32_t X_Position,__IO uint32_t X_Alpha1, __IO uint32_t X_Alpha2,__IO uint32_t X_Omega,
													 __IO int32_t Y_Position,__IO uint32_t Y_Alpha1, __IO uint32_t Y_Alpha2,__IO uint32_t Y_Omega)
{
	__IO int32_t X_AxisRealSteps, Y_AxisRealSteps;
	__IO int32_t X_AxisRealStepsAbs, Y_AxisRealStepsAbs;
	__IO int8_t X_AxisDir = -1;
	__IO int8_t Y_AxisDir = -1;
	
	X_AxisRealSteps = (int32_t)(X_Position * SPR / P - X_Axis_StepPosition);
	Y_AxisRealSteps = (int32_t)(Y_Position * SPR / P - Y_Axis_StepPosition);
	X_AxisRealStepsAbs = MyAbs(X_AxisRealSteps);
	Y_AxisRealStepsAbs = MyAbs(Y_AxisRealSteps);
	if(X_AxisRealSteps >= 0)	X_AxisDir = 1;
	else 											X_AxisDir =-1;
	if(Y_AxisRealSteps >= 0)	Y_AxisDir = 1;
	else 											Y_AxisDir =-1;
	
	if(X_AxisRealStepsAbs > Y_AxisRealStepsAbs)/* X > Y Min Steps Y use common start steps*/
	{
		X_AxisMoveRelative(X_AxisDir * Y_AxisRealStepsAbs, X_Alpha1, X_Alpha2, X_Omega);//
		Y_AxisMoveRelative(Y_AxisRealSteps               , Y_Alpha1, Y_Alpha2, Y_Omega);//
		while(!EXT_X_STOP_FLAG && !EXT_Y_STOP_FLAG)
		{
			StepMotor_X_INTTask();
			StepMotor_Y_INTTask();
		}
//		delay_us(1000);/*步子不连续，存在震动失步*/
		X_AxisMoveRelative(X_AxisDir * (X_AxisRealStepsAbs - Y_AxisRealStepsAbs), X_Alpha1, X_Alpha2, X_Omega);//
		while(!EXT_X_STOP_FLAG)
		{
			StepMotor_X_INTTask();
		}
	}
	else if(X_AxisRealStepsAbs < Y_AxisRealStepsAbs)/* X <= Y     Min Steps X use common start steps*/
	{
		X_AxisMoveRelative(X_AxisRealSteps               , X_Alpha1, X_Alpha2, X_Omega);//
		Y_AxisMoveRelative(Y_AxisDir * X_AxisRealStepsAbs, Y_Alpha1, Y_Alpha2, Y_Omega);//
		while(!EXT_X_STOP_FLAG && !EXT_Y_STOP_FLAG)
		{
			StepMotor_X_INTTask();
			StepMotor_Y_INTTask();
		}
//		delay_us(100000);
		Y_AxisMoveRelative(Y_AxisDir * (Y_AxisRealStepsAbs - X_AxisRealStepsAbs), Y_Alpha1, Y_Alpha2, Y_Omega);//
		while(!EXT_Y_STOP_FLAG)
		{
			StepMotor_Y_INTTask();
		}
	}
	else
	{
		X_AxisMoveRelative(X_AxisRealSteps            , X_Alpha1, X_Alpha2, X_Omega);//
		Y_AxisMoveRelative(Y_AxisRealSteps            , Y_Alpha1, Y_Alpha2, Y_Omega);//
		while(!EXT_X_STOP_FLAG && !EXT_Y_STOP_FLAG)
		{
			StepMotor_X_INTTask();
			StepMotor_Y_INTTask();
		}
	}
}
/*搜索X轴原点*/
uint8_t SearchOrg_X_Axis(__IO int32_t Omega,__IO uint32_t Alpha1, __IO uint32_t Alpha2)
{
	while(1)
	{
		X_AxisSensorDetect();
		if(X_AxisStatus)//A Sensor is detect sth.
		{
			X_AxisSensorDetect();
			if(X_AxisSensorFlag == LimNeg)/*Negative Limit*/
			{
				/*1*/
				X_StepMotorDirN();//----
				DIR_DELAY();
				X_AxisSensorDetect();
				while(X_AxisSensorFlag != OrginP)/* X_AxisSensorDetect   Rtn 0:Normal 1:Detected */
				{
					X_AxisSensorDetect();
					Tog_X_Axis(SEEKFAST_DELAY_TIME,SEEKFAST_DELAY_TIME);/*Seek Fast*/
				}
				/*2*/
				uint32_t i = 3000;/******************TIME OUT***1******************/
				while(--i)
				{
					Tog_X_Axis(SEEKSLOW_DELAY_TIME,SEEKSLOW_DELAY_TIME);/*Seek Slow*/
				}
				/*3*/
				X_StepMotorDirP();//++++
				DIR_DELAY();
				X_AxisSensorDetect();
				while(X_AxisStatus!=1&&X_AxisSensorFlag != OrginP)/* X_AxisSensorDetect   Rtn 0:Normal 1:Detected */
				{
					X_AxisSensorDetect();
					Tog_X_Axis(SEEKSLOW_DELAY_TIME,SEEKSLOW_DELAY_TIME);/*Seek Slow*/
				}
				break;
			}
			X_AxisSensorDetect();
			if(X_AxisSensorFlag == LimPos)/*Positive Limit*/
			{
				/*1*/
				X_StepMotorDirP();//++++
				DIR_DELAY();
				X_AxisSensorDetect();
				while(X_AxisSensorFlag != OrginP)/* X_AxisSensorDetect   Rtn 0:Normal 1:Detected */
				{
					X_AxisSensorDetect();
					Tog_X_Axis(SEEKSLOW_DELAY_TIME,SEEKSLOW_DELAY_TIME);/*Seek Slow*/
				}
				break;				
			}
			X_AxisSensorDetect();
			if(X_AxisSensorFlag == OrginP)/*Orginal Point*/
			{
				/*1*/
				X_StepMotorDirN();//----
				DIR_DELAY();
				uint32_t i = 3000;/******************TIME OUT***2******************/
				while(--i)
				{
					Tog_X_Axis(SEEKSLOW_DELAY_TIME,SEEKSLOW_DELAY_TIME);/*Seek Slow*/
				}
				/*2*/
				X_StepMotorDirP();//++++
				DIR_DELAY();
				X_AxisSensorDetect();
				while(X_AxisSensorFlag != OrginP)/* X_AxisSensorDetect   Rtn 0:Normal 1:Detected */
				{
					X_AxisSensorDetect();
					Tog_X_Axis(SEEKSLOW_DELAY_TIME,SEEKSLOW_DELAY_TIME);/*Seek Slow*/
				}
				break;
			}
			X_Axis_StepPosition     = 0;           // 当前位置
			return 1;
		}
		else//	Normal Location
		{
				X_AxisSensorDetect();
				X_StepMotorDirN();//----
				DIR_DELAY();
				X_AxisSensorDetect();
				while(X_AxisStatus!=1&&X_AxisSensorFlag != OrginP)/* X_AxisSensorDetect   Rtn 0:Normal 1:Detected */
				{
					X_AxisSensorDetect();
					Tog_X_Axis(SEEKFAST_DELAY_TIME,SEEKFAST_DELAY_TIME);/*Seek Fast*/
				}
		}
	}

}

/*搜索Y轴原点*/
uint8_t SearchOrg_Y_Axis(__IO int32_t Omega,__IO uint32_t Alpha1, __IO uint32_t Alpha2)
{
	while(1)
	{
		Y_AxisSensorDetect();
		if(Y_AxisStatus)//A Sensor is detect sth.
		{
			Y_AxisSensorDetect();
			if(Y_AxisSensorFlag == LimPos)/*Positive Limit*/
			{
				/*1*/
				Y_StepMotorDirN();//----
				DIR_DELAY();
				Y_AxisSensorDetect();
				while(Y_AxisSensorFlag != OrginP)/* X_AxisSensorDetect   Rtn 0:Normal 1:Detected */
				{
					Y_AxisSensorDetect();
					Tog_Y_Axis(SEEKFAST_DELAY_TIME,SEEKFAST_DELAY_TIME);/*Seek Fast*/
				}
				/*2*/
				uint32_t i = 3000;/******************TIME OUT***1******************/
				while(--i)
				{
					Tog_Y_Axis(SEEKSLOW_DELAY_TIME,SEEKSLOW_DELAY_TIME);/*Seek Slow*/
				}
				/*3*/
				Y_StepMotorDirP();//++++
				DIR_DELAY();
				Y_AxisSensorDetect();
				while(Y_AxisStatus!=1&&Y_AxisSensorFlag != OrginP)/* X_AxisSensorDetect   Rtn 0:Normal 1:Detected */
				{
					Y_AxisSensorDetect();
					Tog_Y_Axis(SEEKSLOW_DELAY_TIME,SEEKSLOW_DELAY_TIME);/*Seek Slow*/
				}
				break;
			}
			Y_AxisSensorDetect();
			if(Y_AxisSensorFlag == LimNeg)/*Negative Limit*/
			{
				/*1*/
				Y_StepMotorDirP();//++++
				DIR_DELAY();
				Y_AxisSensorDetect();
				while(Y_AxisSensorFlag != OrginP)/* X_AxisSensorDetect   Rtn 0:Normal 1:Detected */
				{
					Y_AxisSensorDetect();
					Tog_Y_Axis(SEEKSLOW_DELAY_TIME,SEEKSLOW_DELAY_TIME);/*Seek Slow*/
				}
				break;				
			}
			Y_AxisSensorDetect();
			if(Y_AxisSensorFlag == OrginP)/*Orginal Point*/
			{
				/*1*/
				Y_StepMotorDirN();//----
				DIR_DELAY();
				uint32_t i = 3000;/******************TIME OUT***2******************/
				while(--i)
				{
					Tog_Y_Axis(SEEKSLOW_DELAY_TIME,SEEKSLOW_DELAY_TIME);/*Seek Slow*/
				}
				/*2*/
				Y_StepMotorDirP();//++++
				DIR_DELAY();
				Y_AxisSensorDetect();
				while(Y_AxisSensorFlag != OrginP)/* X_AxisSensorDetect   Rtn 0:Normal 1:Detected */
				{
					Y_AxisSensorDetect();
					Tog_Y_Axis(SEEKSLOW_DELAY_TIME,SEEKSLOW_DELAY_TIME);/*Seek Slow*/
				}
				break;
			}
			Y_Axis_StepPosition     = 0;           // 当前位置
			return 1;
		}
		else//	Normal Location
		{
				Y_AxisSensorDetect();
				Y_StepMotorDirN();//----
				DIR_DELAY();
				Y_AxisSensorDetect();
				while(Y_AxisStatus!=1&&Y_AxisSensorFlag != OrginP)/* X_AxisSensorDetect   Rtn 0:Normal 1:Detected */
				{
					Y_AxisSensorDetect();
					Tog_Y_Axis(SEEKFAST_DELAY_TIME,SEEKFAST_DELAY_TIME);/*Seek Fast*/
				}
		}
	}
	
}





