#ifndef __DHT11_H_
#define __DHT11_H_

/**********************************包含头文件**********************************/
#include <reg52.h>
#include "DHT11.h"
/**********************************PIN口定义**********************************/
sbit Data= P0^0;//读取温湿度管脚
/**********************************函数声明**********************************/
//延时微秒函数
void DHT11_delay_us(unsigned char n);
void DHT11_delay_ms(unsigned int z);
//开始函数
void DHT11_start();
//读取一个字节函数
unsigned char DHT11_rec_byte();//
//接收40位的数据
void DHT11_receive();//


//---加入全局变量--//
extern unsigned char humi_value,temp_value;	//定义全局变量温湿度整形

#endif

