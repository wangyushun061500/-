#include "H Group/config.h"
#include "adc.h"

/***adc��ʼ������***/
void adc_init(void)
{
	P2M1 = 0x00;
	P2M0 = 0x02;
	P1ASF = 0x03;//����P1��1.0��1.1Ϊ����λ
	adc_datah = adc_datal = 0;  //�������
	adc  = adc_power |adc_speedh;
  //��ʱ�����ɹ������ֵ
}
/**adc���ݹܽ���ֵȡ��**/
unsigned int get_adc(unsigned char channel)
{
	unsigned char i;
	adc_datah = adc_datal = 0;
	adc = (adc & 0xe0) | adc_start | channel;
	for(i=0; i<250; i++){
		if(adc & adc_flag)
		{
			adc &= ~adc_flag;
			return(adc_datah<<2 | adc_datal);
		}
	}
	return 1024;
}
#endif