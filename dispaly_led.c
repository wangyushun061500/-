#include "H Group/config.h"
#include "H Group/display_led.h"
#include "H Group/74hc164.h"

unsigned int shine;
bit dp;

/***��ʾ������ʱ����***/
void delay_display(unsigned int c)
{
	for(c;c>0;c--){
		_nop_();
	}
}
/***��ʾ����***/
void dis_led(unsigned char a,b)//��������ֵ���ֱ���λ�����ַ���
{
	unsigned char led_num[] = {
	0x0e,0x0d,0x0b,0x07
	};
	all = 1;
	display = led_num[a];  //��ʾλ
	send(b);//��ʾ����
	if(dp == 1){//�ж�С����λ�Ƿ�����
		ddp = 0;
	}else{
		ddp = 1;
	}
	delay_display(shine);  //ǰ��ʱ�������������ȵ���ʱ��
	all = 0;//���λ��ʾ
	display = ~led_num[a];
	ddp = 1;//�ض�ð��
	delay_display(1024-shine);  //����ʱ�������������ȵ���ʱ��
}
#endif