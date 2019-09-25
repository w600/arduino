#include "SPI.h"

void setup() {
    SPI.begin();
}

void loop() {
    uint8_t buf[100],i;
    for(i = 0; i < 100; i++)
        buf[i] = i;
    SPI.transferWrite(buf,100);
    delay(1000);
}
