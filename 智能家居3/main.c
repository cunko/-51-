#include <reg52.h>		   		// ͷ�ļ�����
#include <intrins.h>
#include "Uart.h"
#include "DHT11.h"
#include "lcd12864.h"


#define uchar unsigned char	// �Ժ�unsigned char�Ϳ�����uchar����
#define uint  unsigned int	// �Ժ�unsigned int �Ϳ�����uint ����

sbit guang = P1^0;
sbit led1 = P1^1;
sbit led2 = P1^2;
sbit led3 = P1^3;

sbit key1 = P3^5;
sbit key2 = P3^4;
sbit key3 = P3^3;
sbit key4 = P3^2;

char zhuangtai = 0;			//ģʽ�л�
char dianji = 0;			//ģʽ�л�

char flag1=0;

sbit SG_PWM=P1^4;							//�źſ�������
unsigned char count=0;					     //�ƴ�  ����ֵΪ0
unsigned char PWM_count=0;                  //0--0�ȣ�2--45�ȣ�4--90�ȣ�6--135�ȣ�8--180��

int shoudao;

int a;
int pos = 50;				//Ĭ����ʱ0.5ms �Ƕ�0�ȣ���λֵ

sbit PWM_OUT=P1^4;				//PWM�����

void chuli();
void moshi();

void delay(uint i)
{
	while(i--);
}

/*********************************************************/
// ������
/*********************************************************/
void main()
{
	LcdInit();							// Һ�����ܵĳ�ʼ��
	Uart_Init();
	
	
	wri_string(1,2,"���ܼҾ�");
	wri_string(2,0,"�¶ȣ�");
	wri_string(3,0,"ʪ�ȣ�");
	
	while(1)
	{
		DHT11_receive();
		lcd_write_char(2,3,temp_value);
		lcd_write_char(3,3,humi_value);
		wri_string(2,4,"��");
		wri_string(3,4,"%");
		
		chuli();
		
		if(key1 == 0)
		{
			delay(1000);
			zhuangtai++;
			
		}
		if(zhuangtai == 2)
		{
			zhuangtai = 0;
		}
		
		moshi();
					
	}
}

void UART_Routine()  interrupt 4
{	
	if(RI==1)
	{	
		shoudao =SBUF;					   //���͵�����SBUF������P2
		flag1 = 1;
	  RI=0;
	}
}


void chuli()
{
	if(flag1 == 1)
	{
						//========================================================================
		flag1 = 0;
		if(shoudao==0X01)				   //0x01���ֵ����ͨ�������������༭ģʽ����
		{
			pos = 50;
			for(a = 0;a < 6;a++)
			{
				PWM_OUT = 1;
				delay(pos);
				PWM_OUT = 0;
				delay(2000-pos);
			}
		}else
//		if(shoudao==0X03)				   //0x03���ֵ����ͨ�������������༭ģʽ����
//		{
//		 pos = 75;
//			for(a = 0;a < 6;a++)
//			{
//				PWM_OUT = 1;
//				delay(pos);
//				PWM_OUT = 0;
//				delay(2000-pos);
//			}
//		}
//		if(shoudao==0X07)				   //0x07���ֵ����ͨ�������������༭ģʽ����
//		{
//		 pos = 150;
//			for(a = 0;a < 6;a++)
//			{
//				PWM_OUT = 1;
//				delay(pos);
//				PWM_OUT = 0;
//				delay(2000-pos);
//			}
//		}
		if(shoudao==0X09)				   //0x09���ֵ����ͨ�������������༭ģʽ����
		{
		 pos = 250;
			for(a = 0;a < 6;a++)
			{
				PWM_OUT = 1;
				delay(pos);
				PWM_OUT = 0;
				delay(2000-pos);
			}
		}
		//========================================================================
		if(shoudao==0X00)				   //0x09���ֵ����ͨ�������������༭ģʽ����
		{
		led1=1;
		} else
		if(shoudao==0X02)				   //0x09���ֵ����ͨ�������������༭ģʽ����
		{
		led1=0;
		} else
		if(shoudao==0X04)				   //0x09���ֵ����ͨ�������������༭ģʽ����
		{
		led2=1;
		} else
		if(shoudao==0X05)				   //0x09���ֵ����ͨ�������������༭ģʽ����
		{
		led2=0;
		} else
		if(shoudao==0X06)				   //0x09���ֵ����ͨ�������������༭ģʽ����
		{
		led3=1;
		} else	
		if(shoudao==0X08)				   //0x09���ֵ����ͨ�������������༭ģʽ����
		{
		led3=0;
		}
	}
}


void moshi()
{
	if(zhuangtai == 1)
	{
		wri_string(4,2,"����ģʽ");
		if(temp_value == 26)
		{
			pos = 250;
			for(a = 0;a < 6;a++)
			{
				PWM_OUT = 1;
				delay(pos);
				PWM_OUT = 0;
				delay(2000-pos);
			}
		}
		else
		if(temp_value == 24)
		{
			pos = 50;
			for(a = 0;a < 6;a++)
			{
				PWM_OUT = 1;
				delay(pos);
				PWM_OUT = 0;
				delay(2000-pos);
			}
		}
		
		if(guang == 1)
		{
			led1 = 1;
		}
		else
		{
			led1 = 0;
		}
		if(key3 == 0)
		{
			delay(100);
			temp_value=24;
		}else
		if(key4 == 0)
		{
			delay(100);
			temp_value=26;
		}
		
	}
	if(zhuangtai == 0)
	{
		wri_string(4,2,"��ͨģʽ");
		
		if(key2 == 0)
		{
			
			led1 = !led1;
			Lcd12864_Delay1ms(100);
		}else
		if(key3 == 0)
		{
			led2 = !led2;
			Lcd12864_Delay1ms(100);
		}else
		if(key4 == 0)
		{
			led3 = !led3;
			Lcd12864_Delay1ms(100);
		}
		
		
		
		
		
	}
}

