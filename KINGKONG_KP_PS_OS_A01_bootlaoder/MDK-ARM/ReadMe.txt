 /*
 * ReadMe
 * Created on: 2018��6��3��
 * Author: Enzo
 */
 
KINGKONG_KP_PS_A01 

20180603	��ɹ���ģ�彨��
20180603	����ڲ�DAC���������ⲿdac�����������⣡���������Դպ���
20180608	��ɵ�·�������㣬��Ҫʵ�ʵ��Բ���
20180621	��·���У��������⣬����Tx Rx���ڿӡ�
20180621	1.��Ҫ��ֲ����IAP���� 		2.��Ҫ��FLASH��Ԥ�������洢�ռ� 
20180704	���ADC ad7124 TempSensor mcp9805������ֲ�������� ������
20180704	��ɴ���IAP BootLoader �� APP ������
��20180731	���FreeRTOS  IAP����OK
20180731	���FreeRTOS + IWDG + IAP ���� ����ok'
20180819	��������FreeRtos  Memory management settings -> TOTAL_HEAP_SIZE ->15360(3072)  �������ͻBUG���
20180819	��������FreeRtos  ����vTaskDelayUntil -> Enable    
20180819	�޸Ŀ��Ź����� ʱ��40Khz 16��Ƶ  ����ֵΪ2500   ��ʱʱ��2s  ����1.5s ι��
20180819	����USART1 ��Ҫ��it�������HAL���ɵ��ж�   �޸��ں˶�ʱ��ΪTIM7��Systick��
20180819	��������������ӣ����Ч��һ�㣬����ƫ��
20190604:	�����ⲿDAC���õ�ѹ����

BUG
����������
�޸��ں˶�ʱ��ΪTIM7��Systick�� �޷�IAP


Current		Task Target�� 

2.���ڿ���ָ��
3.AD7124 Reg COnfig
4. AD5683 BUG ʱ����ܴ������⣬��Ҫ���д��

#define USER_FLASH_END_ADDRESS      0x08040000 ����û�㶮��������ã�






bin Files
MAC
D:\Program Files (x86)\Keil\ARM\ARMCC\bin\fromelf.exe --bin -o ./bin/STM32F103_512K_APP.bin ./KINGKONG_KP_PS_A01/KINGKONG_KP_PS_A01.axf
WIN
D:\Program Files (x86)\Keil_v5\ARM\ARMCC\bin\fromelf.exe --bin -o ./bin/STM32F103_512K_APP.bin ./KINGKONG_KP_PS_A01/KINGKONG_KP_PS_A01.axf


Flash MAP
BootLoader:		0x08000000 - 0x08002000
PrefMemory:		0x08002001 - 0x08003000
MainMemory:		0x08003001 - 0x08040000

RealOffset:		0x08000000 + 0x00001050 BootLoader Code Size

double 150*8*10=1200












Changed:

���¼����·������
Rfbt��100K
Rfbb��11K
Rfbda��2.2K

Comp Mark��
(34.8KOhm+100pF)//8.2pF

Vdac��0.5-0.95V
Vout��23-1V



