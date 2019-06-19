/*
  W600 Blink Demo
  GPIO define  in "hardware\w600\0.2.4\variants\tb_01("The board type")\pins_arduino.h"
*/

#include <Arduino.h>
#include <W600WiFi.h>

#define LED_PIN  PB_14

void setup() {
    Serial.println("Blink Demo Start ...");
      Serial.begin(115200);    // Initialize the UART0 TX PA4 RX PA5
//    SerialM1.begin(115200);
    delay(1000);
  pinMode(LED_PIN, OUTPUT);     // Initialize the LED_BUILTIN pin as an output
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(LED_PIN, LOW);   // Turn the LED on (Note that LOW is the voltage level
  // but actually the LED is on; this is because
  // it is active low on the ESP-01)
  delay(1000);                      // Wait for a second
  digitalWrite(LED_PIN, HIGH);  // Turn the LED off by making the voltage HIGH
  delay(2000);                      // Wait for two seconds (to demonstrate the active low LED)
}
