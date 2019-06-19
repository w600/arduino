#include <Arduino.h>
#include "Wire.h"

#ifdef WIO_W600
int power_output_startup()
{
    pinMode(3, OUTPUT);
    digitalWrite(3, HIGH);
}
#endif

static unsigned char AT24CXX_ReadOneByte(unsigned short addr)
{          
  unsigned char byte=0, ret=0;                                             
  Wire.beginTransmission(0x50);
  Wire.write(addr);
  Wire.endTransmission(0);
  ret = Wire.requestFrom(0x50, 1, 1);
  byte = Wire.read();
  //printf("ret=%d, byte=%x\r\n",ret, byte);
  return byte;
}

static void AT24CXX_WriteOneByte(unsigned short addr, unsigned char data)
{                                                     
  Wire.beginTransmission(0x50);
  Wire.write(addr);
  Wire.write(data);
  Wire.endTransmission(1);
  delay(1);
}

unsigned char AT24CXX_Check(void)
{
  unsigned char byte;
  AT24CXX_WriteOneByte(255, 0x55);
  delay(5);
  byte=AT24CXX_ReadOneByte(255);    
  if (byte==0x55) {
    return 0;
  }
  return 1;                    
}

void setup() {
#ifdef WIO_W600
    power_output_startup();
#endif
    // put your setup code here, to run once:
    Wire.setClock(100000);
    Wire.begin(WM_IO_PB_14, WM_IO_PB_13);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(AT24CXX_Check()){
    printf("\nAT24CXX check faild\n");
  }
  else{
    delay(1);
    printf("\nAT24CXX check success\n");
  }
  delay(5000);
}
