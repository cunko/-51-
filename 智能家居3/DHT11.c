#include "DHT11.h"

unsigned char humi_value,temp_value;//����ȫ�ֱ�����ʪ������
void DHT11_delay_us(unsigned char n)
{
    while(--n);
}

void DHT11_delay_ms(unsigned int z)
{
   unsigned int i,j;
   for(i=z;i>0;i--)
      for(j=110;j>0;j--);
}

void DHT11_start()
{
   Data=1;
   DHT11_delay_us(2);
   Data=0;
   DHT11_delay_ms(30);   //��ʱ18ms����
   Data=1;
   DHT11_delay_us(30);
}

unsigned char DHT11_rec_byte()      //����һ���ֽ�
{
   unsigned char i,dat=0;
  for(i=0;i<8;i++)    //�Ӹߵ������ν���8λ����
   {
      while(!Data);   ////�ȴ�50us�͵�ƽ��ȥ
      DHT11_delay_us(8);     //��ʱ60us�������Ϊ��������Ϊ1������Ϊ0
      dat<<=1;           //��λʹ��ȷ����8λ���ݣ�����Ϊ0ʱֱ����λ
      if(Data==1)    //����Ϊ1ʱ��ʹdat��1����������1
         dat+=1;
      while(Data);  //�ȴ�����������
    }
    return dat;
}

void DHT11_receive()      //����40λ������
{
    unsigned char R_H,R_L,T_H,T_L,RH,RL,TH,TL,revise;
    DHT11_start();
    if(Data==0)
    {
        while(Data==0);   //�ȴ�����
        DHT11_delay_us(40);  //���ߺ���ʱ80us
        R_H=DHT11_rec_byte();    //����ʪ�ȸ߰�λ
        R_L=DHT11_rec_byte();    //����ʪ�ȵͰ�λ
        T_H=DHT11_rec_byte();    //�����¶ȸ߰�λ
        T_L=DHT11_rec_byte();    //�����¶ȵͰ�λ
        revise=DHT11_rec_byte(); //����У��λ

        DHT11_delay_us(25);    //����

        if((R_H+R_L+T_H+T_L)==revise)      //У��
        {
            RH=R_H;
            RL=R_L;
            TH=T_H;
            TL=T_L;
				
        }
		humi_value = RH;
    temp_value = TH-1;//��ds18b20�¶ȸ�1�����Լ�ȥ1��У׼
    }
}