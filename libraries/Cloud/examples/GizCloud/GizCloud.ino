#include <Arduino.h>
#include "Cloud.h"

#ifdef WIO_W600
int power_output_startup()
{
    pinMode(6, OUTPUT);
    digitalWrite(6, HIGH);
}
#endif

void cloud_setup()
{
  myCloud.CloudInit();
}

void cloud_loop(unsigned char duty_ratio)
{
}

void setup()
{
#ifdef WIO_W600
    power_output_startup();
#endif
    Serial.println("setup()");
    cloud_setup();
}

unsigned char duty_ratio = 0;
void loop()
{
    //Serial.println("loop()");
    cloud_loop(duty_ratio);
    delay(1000);
    duty_ratio++;
}
