#include "H Group/config.h"
#include "i2c.h"

/**i2c��ʱ����**/
void delay(void)//delay
{
	char i = 2;
	while(i--);
}
/**i2c��ʼ��**/
void i2c_init(void)
{
	scl = 1;
	sda = 1;
	delay();
	delay();
}
/**i2c��ʼ�ź�**/
void i2c_start(void)
{
	sda = 1;
	delay();
	scl = 1;
	delay();
	sda = 0;
	delay();
	scl = 0;
	delay();
}
/**i2c��ֹ�ź�**/
void i2c_stop(void)
{
	sda = 0;
	delay();
	scl = 1;
	delay();
	sda = 1;
	delay();
}
/**i2cдһ�ֽ�����**/
void i2c_write(unsigned char dat)
{
	unsigned char t = 8;
	do{
		sda = (bit)(dat & 0x80);
		dat <<= 1;
		scl = 1;
		delay();
		scl = 0;
		delay();
	}while(--t != 0);
}
/**i2c��һ�ֽ�����**/
unsigned char i2c_read(void)
{
	unsigned char dat;
	unsigned char t = 8;
	sda = 1;
	do{
		scl = 1;
		delay();
		dat <<= 1;
		if(sda){
			dat |= 0x01;
		}
		scl = 0;
		delay();
	}while(--t != 0);
	return dat;
}
/**i2c��ȡ�ӻ�Ӧ��λ**/
bit i2c_getack(void)
{
	bit ack;
	sda = 1;
	delay();
	scl = 1;
	delay();
	ack = sda;
	scl = 0;
	delay();
	return ack;
}
/**i2c��������Ӧ��λ**/
void i2c_putack(bit ack)
{
	sda = ack;
	delay();
	scl = 1;
	delay();
	scl = 0;
	delay();
}
/**i2c���Ͷ���ֽڵ�����
���ܣ�����ͨ��I2C������ӻ����Ͷ���ֽڵ�����
������
	SlaveAddr���ӻ���ַ����7λ�Ǵӻ���ַ�����λ��д��־0��
	SubAddr���ӻ����ӵ�ַ
	*dat��Ҫ���͵�����
���أ�
	0�����ͳɹ�
	1���ڷ��͹����г����쳣
**/
bit i2c_send(unsigned char slaveaddr,
unsigned char subaddr,
unsigned char Size,
char *dat)
{
	i2c_init();
	delay();
	delay();
	slaveaddr &= 0xfe;
	i2c_start();
	i2c_write(slaveaddr);
	if(i2c_getack()){
		i2c_stop();
		return 1;
	}
	i2c_write(subaddr);
	if(i2c_getack()){
		i2c_stop();
		return 1;
	}
	do{
		i2c_write(*dat++);
		if(i2c_getack()){
			i2c_stop();
			return 1;
		}
	}while(--Size != 0);
	i2c_stop();
	return 0;
}
/**i2c���ն���ֽڵ�����
���ܣ�����ͨ��I2C���ߴӴӻ����ն���ֽڵ�����
������
	SlaveAddr���ӻ���ַ����7λ�Ǵӻ���ַ�����λ�Ƕ���־1��
	SubAddr���ӻ����ӵ�ַ
	Size�����ݵ��ֽ���
	*dat��������յ�������
���أ�
	0�����ճɹ�
	1���ڽ��չ����г����쳣
**/
bit i2c_gets(unsigned char slaveaddr,
unsigned char subaddr,
unsigned char Size,
char *dat)
{
	i2c_init();
	delay();
	delay();
	slaveaddr &= 0xfe;
	i2c_start();
	i2c_write(slaveaddr);
	if(i2c_getack()){
		i2c_stop();
		return 1;
	}
	i2c_write(subaddr);
	if(i2c_getack()){
		i2c_stop();
		return 1;
	}
	i2c_start();
	slaveaddr |= 0x01;
	i2c_write(slaveaddr);
	if(i2c_getack()){
		i2c_stop();
		return 1;
	}
	for(;;){
		*dat++ = i2c_read();
		if(--Size == 0){
			i2c_putack(1);
			break;
		}
		i2c_putack(0);
	}
	i2c_stop();
	return 0;
}
#endif