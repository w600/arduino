
#include <Arduino.h>

unsigned short average;
unsigned char channel = 0;
float voltage = 0.00;

void setup() {
  // put your setup code here, to run once:
}

void loop() {
  // put your main code here, to run repeatedly:
  average = analogRead(channel);
  voltage = ((average-8192.0)/8192*2.25/1.2 + 1.584);
  printf("\r\nchannel %d, voltage::%.3f\r\n", channel, voltage);
  delay(5000);
}

