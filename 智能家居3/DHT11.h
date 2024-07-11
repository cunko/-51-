#ifndef __DHT11_H_
#define __DHT11_H_

/**********************************����ͷ�ļ�**********************************/
#include <reg52.h>
#include "DHT11.h"
/**********************************PIN�ڶ���**********************************/
sbit Data= P0^0;//��ȡ��ʪ�ȹܽ�
/**********************************��������**********************************/
//��ʱ΢�뺯��
void DHT11_delay_us(unsigned char n);
void DHT11_delay_ms(unsigned int z);
//��ʼ����
void DHT11_start();
//��ȡһ���ֽں���
unsigned char DHT11_rec_byte();//
//����40λ������
void DHT11_receive();//


//---����ȫ�ֱ���--//
extern unsigned char humi_value,temp_value;	//����ȫ�ֱ�����ʪ������

#endif

