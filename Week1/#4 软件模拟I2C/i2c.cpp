#include <RM.h>
#include <i2c.h>
#include <stdint.h>
void Start()
{
	SDA_High();
	SCL_High();
	SDA_Low();
	SCL_Low();
}
void Stop()
{
	SDA_Low();
	SCL_High();
	SDA_High();
}
void SendByte(uint8_t data)
{
	uint8_t i;
	for(i = 0;i < 8;i++)
	{
		if(data & 0x80)
		{
			SDA_High();
		}
		else
		{
			SDA_Low();
		}
		SCL_High();
		SCL_Low();
		data <<= 1;
	}
}
uint8_t ReceiveAck();
{
	uint8_t ack;
	SDA_High();
	SCL_High();
	if(SDA_Read() == 0)
	{
		ack = 0;
	}
	else
	{
		ack = 1;
	}
	SCL_Low();
	return ack;
}
uint8_t SendData(uint8_t data)
{
	uint8_t condition;
	Start();
	SendByte(data);
	condition = ReceiveAck();
	Stop();
	return condition;
}


