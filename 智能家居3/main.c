#include <reg52.h>		   		// 头文件包含
#include <intrins.h>
#include "Uart.h"
#include "DHT11.h"
#include "lcd12864.h"


#define uchar unsigned char	// 以后unsigned char就可以用uchar代替
#define uint  unsigned int	// 以后unsigned int 就可以用uint 代替

sbit guang = P1^0;
sbit led1 = P1^1;
sbit led2 = P1^2;
sbit led3 = P1^3;

sbit key1 = P3^5;
sbit key2 = P3^4;
sbit key3 = P3^3;
sbit key4 = P3^2;

char zhuangtai = 0;			//模式切换
char dianji = 0;			//模式切换

char flag1=0;

sbit SG_PWM=P1^4;							//信号控制引脚
unsigned char count=0;					     //计次  赋初值为0
unsigned char PWM_count=0;                  //0--0度，2--45度，4--90度，6--135度，8--180度

int shoudao;

int a;
int pos = 50;				//默认延时0.5ms 角度0度，复位值

sbit PWM_OUT=P1^4;				//PWM输出口

void chuli();
void moshi();

void delay(uint i)
{
	while(i--);
}

/*********************************************************/
// 主函数
/*********************************************************/
void main()
{
	LcdInit();							// 液晶功能的初始化
	Uart_Init();
	
	
	wri_string(1,2,"智能家居");
	wri_string(2,0,"温度：");
	wri_string(3,0,"湿度：");
	
	while(1)
	{
		DHT11_receive();
		lcd_write_char(2,3,temp_value);
		lcd_write_char(3,3,humi_value);
		wri_string(2,4,"℃");
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
		shoudao =SBUF;					   //发送的数据SBUF，赋给P2
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
		if(shoudao==0X01)				   //0x01这个值可以通过蓝牙调试器编辑模式设置
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
//		if(shoudao==0X03)				   //0x03这个值可以通过蓝牙调试器编辑模式设置
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
//		if(shoudao==0X07)				   //0x07这个值可以通过蓝牙调试器编辑模式设置
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
		if(shoudao==0X09)				   //0x09这个值可以通过蓝牙调试器编辑模式设置
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
		if(shoudao==0X00)				   //0x09这个值可以通过蓝牙调试器编辑模式设置
		{
		led1=1;
		} else
		if(shoudao==0X02)				   //0x09这个值可以通过蓝牙调试器编辑模式设置
		{
		led1=0;
		} else
		if(shoudao==0X04)				   //0x09这个值可以通过蓝牙调试器编辑模式设置
		{
		led2=1;
		} else
		if(shoudao==0X05)				   //0x09这个值可以通过蓝牙调试器编辑模式设置
		{
		led2=0;
		} else
		if(shoudao==0X06)				   //0x09这个值可以通过蓝牙调试器编辑模式设置
		{
		led3=1;
		} else	
		if(shoudao==0X08)				   //0x09这个值可以通过蓝牙调试器编辑模式设置
		{
		led3=0;
		}
	}
}


void moshi()
{
	if(zhuangtai == 1)
	{
		wri_string(4,2,"智能模式");
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
		wri_string(4,2,"普通模式");
		
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

