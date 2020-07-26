#ifndef __I2C_H
#define __I2C_H

void delay(void);
void i2c_init(void);
void i2c_start(void);
void i2c_stop(void);
void i2c_write(unsigned char dat);
unsigned char i2c_read(void);
bit i2c_getack(void);
void i2c_putack(bit ack);
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
char *dat);
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
char *dat);


#endif