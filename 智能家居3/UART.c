#include <reg52.h>


void Uart_Init()   //9600bps@11.0592MHz
{
	PCON |= 0x80;		//ʹ�ܲ����ʼӱ�	
	SCON = 0x50;		//8λ����
	TMOD &= 0x0F;		//�����ʱ��1ģʽ
	TMOD |= 0x20;		//�趨��ʱ��8Ϊ�Զ�
	TL1 = 0xFA;			//�趨��ʼֵ
	TH1 = 0xFA;			//�趨��ʼֵ
	ET1 = 0;		
    TR1 = 1;
    EA = 1;
    ES =1 ; 	
}

