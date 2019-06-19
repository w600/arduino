#include "SPI.h"

#ifdef WIO_W600
int power_output_startup()
{
    pinMode(3, OUTPUT);
    digitalWrite(3, HIGH);
}
#endif

void setup() {
#ifdef WIO_W600
    power_output_startup();
#endif
    SPI.begin();
}

void loop() {
    uint8_t buf[100],i;
    for(i = 0; i < 100; i++)
        buf[i] = i;
    SPI.transferWrite(buf,100);
    delay(1000);
}
