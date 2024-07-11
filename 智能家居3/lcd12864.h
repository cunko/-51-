/***********************************************************************************************************
LCD12864液晶显示模块
晶振:11.0592
时间：2020/12/20   
***********************************************************************************************************/
#ifndef __LCD12864_H__
#define	__LCD12864_H__
 
/**********************************包含头文件**********************************/
#include <reg52.h>
#include "stdio.h"
#include "lcd12864.h"

/**********************************重定义关键词**********************************/
#ifndef uchar
#define uchar unsigned char
#endif

#ifndef uint 
#define uint unsigned int
#endif

#ifndef ulong
#define ulong unsigned long
#endif
	
/**********************************PIN口定义**********************************/
#define LCD12864_DATAPINS P2//液晶并行数据接口
sbit LCD12864_E=P0^5;//液晶使能信号
sbit LCD12864_RW=P0^6;//液晶读写信号
sbit LCD12864_RS=P0^7;//液晶指令数据信号

/**********************************函数声明**********************************/

void Lcd12864_Delay1ms(uint c);   /*在51单片机12MHZ时钟下的延时函数*/

void LcdWriteCom(uchar com);      /*LCD12864向写入一个字节的命令*/

void LcdWriteData(uchar dat);     /*LCD12864写入一个字节的数据*/

void LcdInit();                   /*LCD12864初始化子程序*/

void wri_string(uchar y,uchar x,uchar a[]); /* 指定位置显示字符串 注意 (1/4 0-16，"显示字符串") */

void lcd_write_char(uchar y, uchar x, uchar dat);/*LCD1602写两位数*/


#endif
