#include <stdint.h>
void Start();
void Stop();
void SendByte(uint8_t data);
uint8_t ReceiveAck();
uint8_t SendData(uint8_t data);
