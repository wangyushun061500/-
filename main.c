#include "H Group/config.h"
#include "H Group/lm75a.h"
#include "H Group/74hc164.h"
#include "H Group/display_led.h"
#include "base Group/adc.h"

extern u16 shine;
extern bit dp; 
bit TempF = 0,cor_bit = 0,space_bit = 0,off_bit = 0;
u8 ss,mm,hh;
u8 menu = 1,keyvalue,dis_set,cor_all;
u16 space,space_temp = 400,addr = 0;
int temperature;


void delayms(u16 c);//ms��ʱ������Ӧ
void delayus(u16 c);//us��ʱ
void timer0_init(void);//timer0��ʼ����20msÿ��
void timer2_init(void);//timer2��ʼ����5msÿ��
u16 adc_avg(void);//��ȡ�����Ӧ������ֵ���ҽ��п������㷨
void KeyHandle(void);//�԰������������ж�

void main(void){
	/***����main�����ڱ���***/
	/***���ų�ʼ��***/
	gled = wled = 1;
	g1 = g2 = g3 = g4 = 1;
	key1 = key2 = key3 = 1;
	gled = 0;
	delayms(100);
	gled = 1;
	wled = 0;
	/***������ʼ��***/
	hh = 11;
	mm = 1;
	ss = 0;
	/***��������ʼ��***/
	timer0_init();
	timer2_init();
	adc_init();
	/***����Ĵ�����ʼ��***/
	EA = 1;//�������ж�
	ET0 = 1;//����ʱ��0�ж�
	PT0 = 1;//��ʱ��0�ж����ȼ����
	IE2 = 0x04;//����ʱ2�����ж�
	delayms(100);//��ʱ�ȴ������ȶ�
	/***�����ų�ʼ��***/
	space_temp = space;//�ض�һ�ο���������
	/***��ʽ����***/
	while(1){//��ѭ��
		KeyHandle();
	}
}
/**1ms��ʱ����**/
void delayms(u16 c)
{
	u8 i,j;
	for(c;c>0;c--){
		_nop_();
		_nop_();
		i = 22;
		j = 128;
		do
		{
			while (--j);
		} while (--i);
	}
}
/**1us��ʱ����**/
void delayus(u16 c)
{
	u8 i;
	for(c;c>0;c--){
		i = 3;
		while (--i);
	}
}

/**��ʱ��T0��ʼ��**/
void timer0_init(void)//20ms
{
	AUXR &= 0x7F;		//��ʱ��ʱ��12Tģʽ
	TMOD &= 0xF0;		//���ö�ʱ��ģʽ
	TL0 = 0x00;		//���ö�ʱ��ֵ
	TH0 = 0x70;		//���ö�ʱ��ֵ
	TF0 = 0;		//���TF0��־
	TR0 = 1;		//��ʱ��0��ʼ��ʱ
}

void timer2_init(void)		//5ms
{
	AUXR &= 0xFB;		//��ʱ��ʱ��12Tģʽ
	T2L = 0x00;		//���ö�ʱ��ֵ
	T2H = 0xDC;		//���ö�ʱ��ֵ
	AUXR |= 0x10;		//��ʱ��2��ʼ��ʱ
}

u16 adc_avg(void)
{
	u16 shine_led,night_led;
	if(space_bit == 0){
		o_led = 1;
		wled = 1;
		delayus(200);
		night_led = get_adc(0);
		o_led = 0;
		wled = 0;
		delayus(40);
		shine_led = get_adc(0);
		o_led = 1;
		wled = 1;
	}
	return (shine_led - night_led);
}
/**�����жϳ���**/
void KeyHandle(void)
{
	if((~key1 || ~key2 || ~key3) && (keyvalue == 0)){//�жϰ���������־�����������־Ϊδ����״̬����ִ�е�������ȷ��
		if(~key1){
			keyvalue = 1;//��λ��Ӧ��ֵ
			while(~key1);//�����ɿ��������������
		}else if(~key2){
			keyvalue = 2;//��λ��Ӧ��ֵ
			while(~key2);
		}else if(~key3){
			keyvalue = 3;//��λ��Ӧ��ֵ
			while(~key3);
		}
	}
		if(keyvalue == 1){//���Ϊ��һ������״̬
			menu = 1;
			if(dis_set == 0){//�ж��Ƿ�Ϊ�գ����ҽ��г�ʼ��
				dis_set = 1;//Ĭ��Ϊ��һ����������
			}
			if((~key1) && (dis_set != 0)){ //��������˳�ʼ�������Ұ�����Ч
				dis_set++;//��Ӧ������һ
				if(dis_set == 5){//ÿ4��λһ��
					dis_set = 1;//ÿ�μ�һ��������0����״̬��ת��
				}
				while(~key1);//���а����ȴ�
			}
			if((~key2) && (dis_set != 0)){//�������2��Ч
				switch(dis_set){//�ж������λ����ֵ
					case 1: hh = hh+10;break;//ÿʮ����һ
					case 2: hh++;break;//�Լ�һ
					case 3: mm = mm+10;break;
					case 4: mm++;break;
					default: break;//û�в��������˳�
				}
				while(~key2);//�ж�����ٽ��еȴ�
			}
			if(~key3){//ȷ�ϰ���
				dis_set = 0;//��λλ����λΪ��
				keyvalue = 0;//��λ��ǰ���ñ�־Ϊ��
				while(~key3);//���еȴ�
				menu = 1;
			}
		}
		if(keyvalue == 2){
			menu = 2;
			if(~key1 || ~key2){
				TempF = ~TempF;
				while(~key1 || ~key2);//����1�Ͱ���2�����Խ����޸�
			}
			if(~key3){//ȷ�ϰ���
				keyvalue = 0;//��λ��ǰ���ñ�־Ϊ��
				while(~key3);//���еȴ�
				menu = 2;
			}
		}
		if(keyvalue == 3){
			menu = 3;
			if(~key1){
				if(cor_all == 0){//���жϷ�ֹ���ָ�ֵ
					cor_all = 3;
				}else{
					cor_all--;
					if(cor_all == 0){//���жϷ�ֹ���ָ�ֵ
					cor_all = 4;
					}
				}
				while(~key1);
			}
			if(~key2){
				cor_all++;
				if(cor_all == 5){
					cor_all = 1;
				}
				while(~key2);
			}
			if(~key3){//ȷ�ϰ���
				keyvalue = 0;//��λ��ǰ���ñ�־Ϊ��
				switch(cor_all){
					case 1:{space_bit = 1; cor_bit = 0; off_bit = 1;};break;
					case 2:{space_bit = 1; cor_bit = 1; off_bit = 0;};break;
					case 3:{space_bit = 0; cor_bit = 0; off_bit = 0;};break;
					case 4:{space_temp = space;};break;
					default: cor_all = 3;break;
				}
				while(~key3);//���еȴ�
				menu = 1;//�Զ��ض�
			}
		}
	
}
/**T0�жϳ���**/
void timer0(void) interrupt 1 
{
	u8 time,time1;
/**��ʱ���ж�**/
	time++;
	if((menu != 0) && (keyvalue == 0) && (off_bit == 0)){//�Զ��ض��ж�
		time1++;
		if(time1 == 250){//�ж�ѭ��λ�Ƿ�Ϊ��
			if(cor_bit == 0){
				menu = 0;
			}else{
				if(menu == 1){//ÿ�����л�һ��״̬
					menu = 2;
				}else{
					menu = 1;
				}
			}
		}
	}
	/**С�����ж�**/
	if((time > 25) && (menu == 1)){
		dp = (bit)1;
	}else{
		dp = (bit)0;
	}
	if(time == 50){//ÿһ��s
		time = 0;
		ss++;//�Լ�
		if(ss == 60){//���Ӽ�һ
			ss = 0;
			mm++;
			if(mm == 60){//Сʱ��һ
				mm = 0;
				hh++;
				if(hh == 24){//�賿��λ
					hh = 0;//24Сʱ��
				}
			}
		}
	}
	if(ss > 59){//����59�Զ���λ��
		ss = 0;//����ʱ�䲻���й������
	}
	if(mm > 59){
		mm = 0;
	}
	if(hh > 23){
		hh = 0;
	}
}
/***T2�жϳ���***/
void timer2_isr(void) interrupt 12 
{
	bit time_out;
	u8 count1,count2,timer,t;
	u16 Temp;
	timer++;
	if(timer == 10){
		timer = 0;
		t++;
		if(t == 10){
			t = 0;
			if(menu == 2){
				temperature = lm75_get();//��ȡ�¶�
				temperature = temperature*125;
			}
		}
		/*��ȡadc����*/
		space = adc_avg();//��ȡ����
		shine = get_adc(1);//��ȡ���ն���Ϣ
		
		if(((hh > 6) && (mm > 30)) && ((hh < 18) && (mm <30)) && (shine > 500)){
			shine = shine + 200;
		}
		else if(shine < 200){
			wled = 0;
		};
		
		if(shine > 1010)shine = 1010;
		if(shine < 100)shine = 100;
		/*��Ӧ���ؿ�����*/
		if(space_bit == 0){
			if(space > (space_temp+20)){//��������
				count1++;
				count2 = 0;
				if(count1 == 3){
					count1 = 0;
					if(time_out == 0){
						if(menu == 1){
							menu = 2;
						}else{
							menu = 1;
						}
						time_out = 1;
					}
				}
			}
			if(space < (space_temp+10)){//�رվ���
				count2++;
				count1 = 0;
				if(count2 == 3){
					count2 = 0;
					time_out = 0;
				}
			}		
		}
	}
	if(menu == 1){//ʱ����ʾ
		if(keyvalue == 1){//�����ڶ�ʱ�����棬��ֹ������İ����жϵȴ���ʱ����ֲ���ʾ������
			if(dis_set == 1){//��ʾλ1
				if(~dp){
					dis_led(0,hh/10);
				}else{
					dis_led(0,20);
				}
			}else{
				dis_led(0,hh/10);
			}
			
			if(dis_set == 2){//��ʾλ2
				if(~dp){
					dis_led(1,hh%10);
				}else{
					dis_led(0,20);
				}
			}else{
				dis_led(1,hh%10);
			}
			
			if(dis_set == 3){//��ʾλ3
				if(~dp){
					dis_led(2,mm/10);
				}else{
					dis_led(0,20);
				}
			}else{
				dis_led(2,mm/10);
			}
			
			if(dis_set == 4){//��ʾλ4
				if(~dp){
					dis_led(3,mm%10);
				}else{
					dis_led(0,20);
				}
			}else{
				dis_led(3,mm%10);
			}
		}else{//������ʾ
			dis_led(0,hh/10);
			dis_led(1,hh%10);
			dis_led(2,mm/10);
			dis_led(3,mm%10);
		}
	}
	if(menu == 2){//�¶���ʾ
		if(TempF == 1){//��ʾΪ�����϶Ⱥ����϶ȵı�־λ
			Temp = ((temperature/100)*18/100)+32;//�޷������Զ������һ����������
			dis_led(0,Temp/100);
			dis_led(1,Temp%100/10);
			dis_led(2,Temp%10);
			dis_led(3,15);
		}else{
			dis_led(0,temperature/10000);
			dis_led(1,temperature%10000/1000);
			dis_led(1,19);
			dis_led(2,temperature%1000/100);
			dis_led(3,12);
		}
	}
	if(menu == 3){//��ʾall
		if(cor_all != 0){
		switch(cor_all){
			case 1: {dis_led(0,18);dis_led(1,0);dis_led(2,1);dis_led(3,18);};break;
			case 2: {dis_led(0,18);dis_led(1,0);dis_led(2,2);dis_led(3,18);};break;
			case 3: {dis_led(0,18);dis_led(1,0);dis_led(2,3);dis_led(3,18);};break;
			case 4: {
				dis_led(0,space_temp/1000);
				dis_led(1,(space_temp%1000)/100);
				dis_led(2,(space_temp%100)/10);
				dis_led(3,space_temp%10);
			}
			default: break;
		}
	}else{
		dis_led(0,20);
		dis_led(1,10);
		dis_led(2,17);
		dis_led(3,17);
		}
	}
}
#endif
/*===========================���������================================*/
//test���Գ���
/*
		dis_led(0,space/1000);
		dis_led(1,(space%1000)/100);
		dis_led(2,(space%100)/10);
		dis_led(3,space%10);*/

/*	
		dis_led(0,shine/1000);
		dis_led(1,(shine%1000)/100);
		dis_led(2,(shine%100)/10);
		dis_led(3,shine%10);*/