/*
 * task_ChannelCtrl.c
 *
 * Created on: 2018��2��27��
 * Author: Enzo
 */
 
#include "task_ChannelCtrl.h"


/**
  * @brief  PWR0204_1_Handler  Just for Send not Read
  * @param  Control PWR
  * @retval None
  */


/**********�̵�������**********
����:2 line �̵��������(���Ե㵼ͨ)
�汾:V1.00   ����:13.07.01
�޸�:xiaodong.liu
����:value
���������A B D,E 4��
 ************************/

//void ReadTestPoint(uint16_t ReadData,uint8_t ControlBit)   //0XA001
//{
//	uint8_t BUS,Point;
//	BUS=ReadData>>12;
//	Point=((ReadData&0XF00)>>8)*100+((ReadData&0X0F0)>>4)*10+(ReadData&0X00F);
//	switch(BUS)
//	{
//     case 0x0A:
//			 if((1<=Point)&&(Point<=16))
//			 { CAT9555_WriteOneBit(0x00,Point-1,ControlBit);}
//			 else if((17<=Point)&&(Point<=32))
//			   CAT9555_WriteOneBit(0x01,Point-17,ControlBit);
//			 break;
//			 
//		 case 0x0B:
//			 if((1<=Point)&&(Point<=16))
//			   CAT9555_WriteOneBit(0x02,Point-1,ControlBit);
//			 else if((17<=Point)&&(Point<=32))
//			   CAT9555_WriteOneBit(0x03,Point-17,ControlBit);
//			 break;
//			 
//		 case 0x0D:
//			 if((1<=Point)&&(Point<=16))
//			   CAT9555_WriteOneBit(0x04,Point-1,ControlBit);
//			 else if((17<=Point)&&(Point<=32))
//			   CAT9555_WriteOneBit(0x05,Point-17,ControlBit);
//			 break;
//			 			 
//		 case 0x0E:
//			 if((1<=Point)&&(Point<=16))
//			   CAT9555_WriteOneBit(0x06,Point-1,ControlBit);
//			 else if((17<=Point)&&(Point<=32))
//			   CAT9555_WriteOneBit(0x07,Point-17,ControlBit);
//			 break;
//  }
//}

#if 0
/**********�̵�������**********
����:2 line �̵��������(���Ե㵼ͨ)
�汾:V1.00   ����:13.07.01
�޸�:xiaodong.liu
����:xiaodong.liu
���������A B D,E 4��
 ************************/
void TestPointON2lineOpposite(uint HPoint, uint LPoint)
{
		unsigned char HPointT;
		ReadTestPoint(HPoint,1);//��ͨ�ߵ�
//    ReadTestPoint(LPoint,1);//��ͨ�͵�
		HPointT=HPoint>>12;//ȡ��0X0A 0X0B...
//	  LPointT=LPoint>>12;//ȡ��0X0A 0X0B...
		if(HPointT==0x0A)//�ߵ�input A line
		{
			 DIS_KWAA;
			 EN_KWAB; EN_KB;
			 EN_KWAD;  
			 EN_KWAE; 
 
			 EN_KGNDA; 
			 EN_KWBA;	 
		}
		else if(HPointT==0x0B)//�ߵ�input B line
		{
			 EN_KWAA;EN_KA;
			 DIS_KWAB; 
			 EN_KWAD;  
			 EN_KWAE; 
 
			 EN_KGNDB; 
			 EN_KWBB;				
		}
		else if(HPointT==0x0D)//�ߵ�input D line
		{
			 EN_KWAA;EN_KA;
			 EN_KWAB; 
			 DIS_KWAD;  
			 EN_KWAE; 
 
			 EN_KGNDD; 
			 EN_KWBD;			
		}
		else if(HPointT==0x0E)//�ߵ�input E line
		{
			 EN_KWAA;EN_KA;
			 EN_KWAB; 
			 EN_KWAD;  
			 DIS_KWAE; 
			 EN_KGNDE; 
			 EN_KWBE;			 
		}
 }
/**********�̵�������**********
����:2 line �̵��������(���Ե㵼ͨ)
�汾:V1.00   ����:13.07.01
�޸�:xiaodong.liu
����:xiaodong.liu
���������A B D,E 4��
 ************************/
void TestPointON2lineOffLPoint(uint HPoint, uint LPoint)
{
		unsigned char HPointT;//,LPointT;
		ReadTestPoint(HPoint,1);//��ͨ�ߵ�
//    ReadTestPoint(LPoint,1);//��ͨ�͵�
		HPointT=HPoint>>12;//ȡ��0X0A 0X0B...
//	  LPointT=LPoint>>12;//ȡ��0X0A 0X0B...
		if(HPointT==0x0A)//�ߵ�input A line
		{
			 DIS_KGNDA; 
			 EN_KGNDB; 
			 EN_KGNDD;  
			 EN_KGNDE; 

			 EN_KA; EN_KWAA; EN_KWBB;    		 
		}
		else if(HPointT==0x0B)//�ߵ�input B line
		{
				 EN_KGNDA;  
				 DIS_KGNDB; 
				 EN_KGNDD;  
				 EN_KGNDE; 

				 EN_KB;  EN_KWAB; EN_KWBA;				
		}
		else if(HPointT==0x0D)//�ߵ�input D line
		{
				EN_KGNDA; 
				EN_KGNDB; 
				DIS_KGNDD; 
				EN_KGNDE;
				EN_KD;  EN_KWAD; EN_KWBA;		
		}
		else if(HPointT==0x0E)//�ߵ�input E line
		{
				EN_KGNDA;  
				EN_KGNDB;  
				EN_KGNDD; 
				DIS_KGNDE; 
				EN_KE;  EN_KWAE; EN_KWBA;			 
		}
 }

/**********�̵�������**********
����:2 line �̵��������(���Ե㵼ͨ)
�汾:V1.00   ����:13.07.01
�޸�:xiaodong.liu
����:xiaodong.liu
���������A B D,E 4��
 ************************/
void TestPointON2line(uint HPoint, uint LPoint)
{
		unsigned char HPointT,LPointT;
		ReadTestPoint(HPoint,1);//��ͨ�ߵ�
		ReadTestPoint(LPoint,1);//��ͨ�͵�
		HPointT=HPoint>>12;//ȡ��0X0A 0X0B...
		LPointT=LPoint>>12;//ȡ��0X0A 0X0B...
		if(HPointT==0x0A)//�ߵ�input A line
		{
			 if(LPointT==0x0A);//���ܲ�
			 else if(LPointT==0x0B)//B
			 {
					 EN_KA; EN_KGNDB; EN_KWAA; EN_KWBB;	
			 }
			 else if(LPointT==0x0D)//D
			 {
					EN_KA;  EN_KGNDD; EN_KWAA; EN_KWBD;
			 }
			 else if(LPointT==0x0E)//E
			 {
					EN_KA;  EN_KGNDE; EN_KWAA; EN_KWBE;
			 } 
//       else 
//       {EN_KGNDE;EN_KGNDE;EN_KWBE;}				 
		}
		else if(HPointT==0x0B)//�ߵ�input B line
		{
				if(LPointT==0x0B);//���ܲ�
				else if(LPointT==0x0A)//A
				{
					 EN_KB;  EN_KGNDA; EN_KWAB; EN_KWBA;
				}
				else if(LPointT==0x0D)//D
				{
					 EN_KB;  EN_KGNDD; EN_KWAB; EN_KWBD;
				}
				else if(LPointT==0x0E)//E
				{
					 EN_KB;  EN_KGNDE; EN_KWAB; EN_KWBE;
				} 
//        else 
//       {EN_KGNDE;EN_KGNDE;EN_KWBE;}				
		}
		else if(HPointT==0x0D)//�ߵ�input D line
		{
				if(LPointT==0x0D);//���ܲ�
				else if(LPointT==0x0A)//A
				{
						EN_KD;  EN_KGNDA; EN_KWAD; EN_KWBA;
				}
				else if(LPointT==0x0B)//B
				{
					 EN_KD;  EN_KGNDB; EN_KWAD; EN_KWBB;
				}
				else if(LPointT==0x0E)//E
				{
					 EN_KD;  EN_KGNDE; EN_KWAD; EN_KWBE;
				} 
//         else 
//       {EN_KGNDE;EN_KGNDE;EN_KWBE;}				
		}
		else if(HPointT==0x0E)//�ߵ�input E line
		{
			 if(LPointT==0x0E);//���ܲ�
			 else if(LPointT==0x0A)//A
			 {
					EN_KE;  EN_KGNDA; EN_KWAE; EN_KWBA;
			 }
			 else if(LPointT==0x0B)//B
			 {
					EN_KE;  EN_KGNDB; EN_KWAE; EN_KWBB;
			 }
			 else if(LPointT==0x0D)//D
			 {
					EN_KE;  EN_KGNDD; EN_KWAE; EN_KWBD;
			 }
//        else 
//       {EN_KGNDA;EN_KWAE;EN_KWBA;}			 
		}
}


/**********�̵�������**********
����:2 line2 �̵��������(���Ե㵼ͨ)
�汾:V1.00   ����:13.07.01
�޸�:xiaodong.liu
����:xiaodong.liu
���������A B D,E 4��
 ************************/
void TestPointON2line2(uint HPoint, uint LPoint)
{
		unsigned char HPointT,LPointT;
		ReadTestPoint(HPoint,1);//��ͨ�ߵ�
		ReadTestPoint(LPoint,1);//��ͨ�͵�
		HPointT=HPoint>>12;//ȡ��0X0A 0X0B...
		LPointT=LPoint>>12;//ȡ��0X0A 0X0B...
		if(HPointT==0x0A)//�ߵ�input A line
		{
			 if(LPointT==0x0A);//���ܲ�
			 else if(LPointT==0x0B)//B
			 {
					 EN_KA; EN_KGNDB;
			 }
			 else if(LPointT==0x0D)//D
			 {
					EN_KA;  EN_KGNDD; 
			 }
			 else if(LPointT==0x0E)//E
			 {
					EN_KA;  EN_KGNDE; 
			 }   
		}
		else if(HPointT==0x0B)//�ߵ�input B line
		{
				if(LPointT==0x0B);//���ܲ�
				else if(LPointT==0x0A)//A
				{
					 EN_KB;  EN_KGNDA; 
				}
				else if(LPointT==0x0D)//D
				{
					 EN_KB;  EN_KGNDD;
				}
				else if(LPointT==0x0E)//E
				{
					 EN_KB;  EN_KGNDE;
				}   
		}
		else if(HPointT==0x0D)//�ߵ�input D line
		{
				if(LPointT==0x0D);//���ܲ�
				else if(LPointT==0x0A)//A
				{
						EN_KD;  EN_KGNDA; 
				}
				else if(LPointT==0x0B)//B
				{
					 EN_KD;  EN_KGNDB; 
				}
				else if(LPointT==0x0E)//E
				{
					 EN_KD;  EN_KGNDE; 
				}   
		}
		else if(HPointT==0x0E)//�ߵ�input E line
		{
			 if(LPointT==0x0E);//���ܲ�
			 else if(LPointT==0x0A)//A
			 {
					EN_KE;  EN_KGNDA;
			 }
			 else if(LPointT==0x0B)//B
			 {
					EN_KE;  EN_KGNDB; 
			 }
			 else if(LPointT==0x0D)//D
			 {
					EN_KE;  EN_KGNDD; 
			 }   
		}
 }


/**********�̵�������**********
����:2 line2 �̵��������(���Ե㵼ͨ)
�汾:V1.00   ����:13.07.01
�޸�:xiaodong.liu
����:xiaodong.liu
���������A B D,E 4��
 ************************/
void TestPointON2line3(uint HPoint, uint LPoint)
{
		unsigned char HPointT,LPointT;
		ReadTestPoint(HPoint,1);//��ͨ�ߵ�
		ReadTestPoint(LPoint,1);//��ͨ�͵�
		HPointT=HPoint>>12;//ȡ��0X0A 0X0B...
		LPointT=LPoint>>12;//ȡ��0X0A 0X0B...
		switch(HPointT)
		{
				case 0x0A:EN_KA;break;
				case 0x0B:EN_KB;break;
				case 0x0D:EN_KD;break;
				case 0x0E:EN_KE;break;
				default: break;
		 }
			 switch(LPointT)
		{
				case 0x0A:EN_KV2A;break;
				case 0x0B:EN_KV2B;break;
				case 0x0D:EN_KV2D;break;
				case 0x0E:EN_KV2E;break;
				default: break;
		 }
 }

/********************
����:4 test sensor wire 
�汾:V1.00   ����:13.07.01
�޸�:xiaodong.liu
����:xiaodong.liu
���������A B D,E 4��
 ************************/
void  SensorOnset(unsigned int lineNumA,unsigned int lineNumB)
{
		 switch(lineNumA)
		 {
				case 0x0A:
						EN_KWAA; break;
				case 0x0B:
						EN_KWAB; break;
				case 0x0D:
						EN_KWAD; break;
				case 0x0E:
						EN_KWAE; break;
		 }

		 switch(lineNumB)
		 {
				case 0x0A:
						EN_KWBA; break;
				case 0x0B:
						EN_KWBB; break;
				case 0x0D:
						EN_KWBD; break;
				case 0x0E:
						EN_KWBE; break;
		 }
	 
} 

 /***********************
����:4 line �̵��������(���Ե㵼ͨ)
�汾:V1.00   ����:13.07.01
�޸�:xiaodong.liu
����:xiaodong.liu
���������A B D,E 4��
 *************************/
void TestPointON4line(uint HPoint, uint LPoint,uint SensorH,uint SensorL)
{
		unsigned char HPointT,LPointT,SensorHT,SensorLT;
		ReadTestPoint(HPoint,1);  //��ͨ�ߵ�
		ReadTestPoint(LPoint,1);//��ͨ�͵�
		ReadTestPoint(SensorH,1);//��ͨSensorH
		ReadTestPoint(SensorL,1); //��ͨSensorL

		HPointT=HPoint>>12;
		LPointT=LPoint>>12;
		SensorHT=SensorH>>12;
		SensorLT=SensorL>>12; 
		//��ʱû���ж�SensorH,SensorL��Ĭ��ֵ����
		if(HPointT==0x0A)//�ߵ�input A line
	 {
				 if(LPointT==0x0A);//���ܲ�
				 else if(LPointT==0x0B)//B
				 {
						 EN_KA;  EN_KGNDB;
						 SensorOnset(SensorHT,SensorLT);
				 }
				 else if(LPointT==0x0D)//D
				 {
						 EN_KA;  EN_KGNDD;
						 SensorOnset(SensorHT,SensorLT);
				 }
				 else if(LPointT==0x0E)//E
				 {
						EN_KA;  EN_KGNDE;
						SensorOnset(SensorHT,SensorLT);
				 }   
		}
		else if(HPointT==0x0B)//�ߵ�input B line
		{
				 if(LPointT==0x0B);//���ܲ�
				 else if(LPointT==0x0A)//A
				 {
						 EN_KB;  EN_KGNDA;
						 SensorOnset(SensorHT,SensorLT);
				 }
				 else if(LPointT==0x0D)//D
				 {
						 EN_KB;  EN_KGNDD;
						 SensorOnset(SensorHT,SensorLT);
				 }
				 else if(LPointT==0x0E)//E
				 {
						 EN_KB;  EN_KGNDE;
						 SensorOnset(SensorHT,SensorLT);
				 }   
		 }
		 else if(HPointT==0x0D)//�ߵ�input D line
		 {
				 if(LPointT==0x0D);//���ܲ�
				 else if(LPointT==0x0A)//A
				 {
							 EN_KD;  EN_KGNDA;
							 SensorOnset(SensorHT,SensorLT);
				 }
				 else if(LPointT==0x0B)//B
				 {
							EN_KD;  EN_KGNDB;
							SensorOnset(SensorHT,SensorLT);
				 }
				 else if(LPointT==0x0E)//E
				 {
						 EN_KD;  EN_KGNDE;
						 SensorOnset(SensorHT,SensorLT);
				 }   
		 }
		 else if(HPointT==0x0E)//�ߵ�input E line
		 {
				 if(LPointT==0x0E);//���ܲ�
				 else if(LPointT==0x0A)//A
				 {
						EN_KE;  EN_KGNDA;
						SensorOnset(SensorHT,SensorLT);
				 }
				 else if(LPointT==0x0B)//B
				 {
						EN_KE;  EN_KGNDB;
						SensorOnset(SensorHT,SensorLT);
				 }
				 else if(LPointT==0x0D)//D
				 {
						EN_KE;  EN_KGNDD;
						SensorOnset(SensorHT,SensorLT);
				 }   
			}
}
#endif
