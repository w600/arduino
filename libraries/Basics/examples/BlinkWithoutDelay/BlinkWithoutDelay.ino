/*
  W600 BlinkWithoutDelay 
  GPIO define  in "hardware\w600\0.2.4\variants\tb_01("The board type")\pins_arduino.h"
*/
#include <Arduino.h>
#include <W600WiFi.h>
int ledState = LOW;

unsigned long previousMillis = 0;
const long interval = 1000;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    if (ledState == LOW) {
      ledState = HIGH;  // Note that this switches the LED *off*
    } else {
      ledState = LOW;  // Note that this switches the LED *on*
    }
    digitalWrite(LED_BUILTIN, ledState);
  }
}
