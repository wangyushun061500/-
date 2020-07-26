#ifndef __CONFIG_H
#define __CONFIG_H

#include "15w.h"
#include "intrins.h"

/***�ܽŶ�����***/
/**ָʾled��**/
#define wled P36
#define gled P37
/**��������**/
#define rg1 P11
/**��Ӧ����Թ�**/
#define i_led P10
#define o_led P35
/**����ͨѶ**/
/*74HC164*/
#define clk P25
#define dat P24
#define all P55
/*LM75**/
#define sda P26
#define scl P27
/***����ܶ���***/
#define g1 P20
#define g2 P21
#define g3 P22
#define g4 P23
#define display P2
#define ddp P34
/***��������***/
#define key1 P32
#define key2 P33
#define key3 P54
/***�������ݹܽŶ���***/
#define p_txd P31
/***ADC����***/
#define adc ADC_CONTR  //adc�ܿ���
#define adc_datah ADC_RES  //adcת�������8λ
#define adc_datal ADC_RESL  //adcת�������8λ
#define adc_power 0x80 //��Ϊadc_contr������λѰַ�����Ծ�Ҫ
#define adc_flag 0x10  //����Ӧÿ��λ�Ŀ���д�ϣ�Ȼ���ٽ�д��
#define adc_start 0x08 //��ʱ��ÿ��ֵ��򣨼����ĸ����ĸ���
#define adc_speedh 0x60
#define adc_speedl 0x00

#define fosc 22118400L
#define MAIN_Fosc		22118400L	//������ʱ��	 220 ~ 19200

#if (MAIN_Fosc >= 24000000L)
	#define		ISP_WAIT_FREQUENCY	ISP_WAIT_30MHZ
#elif (MAIN_Fosc >= 20000000L)
	#define		ISP_WAIT_FREQUENCY	ISP_WAIT_24MHZ
#elif (MAIN_Fosc >= 12000000L)
	#define		ISP_WAIT_FREQUENCY	ISP_WAIT_20MHZ
#elif (MAIN_Fosc >= 6000000L)
	#define		ISP_WAIT_FREQUENCY	ISP_WAIT_12MHZ
#elif (MAIN_Fosc >= 3000000L)
	#define		ISP_WAIT_FREQUENCY	ISP_WAIT_6MHZ
#elif (MAIN_Fosc >= 2000000L)
	#define		ISP_WAIT_FREQUENCY	ISP_WAIT_3MHZ
#elif (MAIN_Fosc >= 1000000L)
	#define		ISP_WAIT_FREQUENCY	ISP_WAIT_2MHZ
#else
	#define		ISP_WAIT_FREQUENCY	ISP_WAIT_1MHZ
	
#endif