/***********************************************************************************************************
LCD12864Һ����ʾģ��
����:11.0592
ʱ�䣺2020/12/20   
***********************************************************************************************************/
#ifndef __LCD12864_H__
#define	__LCD12864_H__
 
/**********************************����ͷ�ļ�**********************************/
#include <reg52.h>
#include "stdio.h"
#include "lcd12864.h"

/**********************************�ض���ؼ���**********************************/
#ifndef uchar
#define uchar unsigned char
#endif

#ifndef uint 
#define uint unsigned int
#endif

#ifndef ulong
#define ulong unsigned long
#endif
	
/**********************************PIN�ڶ���**********************************/
#define LCD12864_DATAPINS P2//Һ���������ݽӿ�
sbit LCD12864_E=P0^5;//Һ��ʹ���ź�
sbit LCD12864_RW=P0^6;//Һ����д�ź�
sbit LCD12864_RS=P0^7;//Һ��ָ�������ź�

/**********************************��������**********************************/

void Lcd12864_Delay1ms(uint c);   /*��51��Ƭ��12MHZʱ���µ���ʱ����*/

void LcdWriteCom(uchar com);      /*LCD12864��д��һ���ֽڵ�����*/

void LcdWriteData(uchar dat);     /*LCD12864д��һ���ֽڵ�����*/

void LcdInit();                   /*LCD12864��ʼ���ӳ���*/

void wri_string(uchar y,uchar x,uchar a[]); /* ָ��λ����ʾ�ַ��� ע�� (1/4 0-16��"��ʾ�ַ���") */

void lcd_write_char(uchar y, uchar x, uchar dat);/*LCD1602д��λ��*/


#endif
