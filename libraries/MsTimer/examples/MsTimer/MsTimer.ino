#include <MsTimer.h>
#include "Arduino.h"
#include "stdlib.h"
#include "string.h"
#include "stdio.h"


void time_test_f(void)
{
  printf("time1 callback!\r\n");
}

void setup() {
  // put your setup code here, to run once:

  /*Timers 测试*/
  MsTimer1::set(1000, time_test_f);
  MsTimer1::start();

  /*PWM 测试*/
  analogWriteFreq(20000);
  analogWrite(PWM2, 40);
  
  /*方波测试*/
  tone(PWM1,100000);

 /*输入捕获测试*/
  pinMode(PIN_B12, INPUT); 
}

void loop() {

  delay(2000);
  
  /*输入捕获测试*/
  printf("Pulse:%d\r\n",pulseIn(PIN_B12, 0, 20000000));
}