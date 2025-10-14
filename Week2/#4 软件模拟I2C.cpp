#include <RM.h>
#include <i2c.h>
#include <stdint.h>
void Start()		//SCL置高时，SDA由高置低，表示起始
{
	SDA_High();
	SCL_High();
	SDA_Low();
	SCL_Low();
}
void Stop()			//SCL置高时，SDA由低置高，表示停止
{
	SDA_Low();
	SCL_High();
	SDA_High();
}
void SendByte(uint8_t data)			//传输过程中，SCL置高时，SDA数据稳定。则SCL置低时SDA数据可变化
{
	uint8_t i;
	for(i = 0;i < 8;i++)
	{
		if(data & 0b10000000)		//与运算：仅当同为1返回1，其余返回0。利用该性质，data中为1的位经与运算后仍为1，为0的位仍为0
		{							//为便于程序取10000000，配以循环和左移使得data动态化地进行与运算可控制SDA电平
			SDA_High();				//实际可取任一数，因位移操作是单向的，所以用10000000或00000001可简便程序，此处取前者
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
uint8_t ReceiveAck();				//ack为应答信号，为0表示输入，为1表示输出
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
uint8_t SendData(uint8_t data)			//一整个流程
{
	uint8_t condition;
	Start();
	SendByte(data);
	condition = ReceiveAck();
	Stop();
	return condition;
}
