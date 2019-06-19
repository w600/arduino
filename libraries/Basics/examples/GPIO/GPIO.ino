#include <Arduino.h>
/*
  W600 GPIO Demo
  GPIO define  in "hardware\w600\0.2.4\variants\tb_01("The board type")\pins_arduino.h"
*/
int test_pin_ab_out(const char *name, int pin)
{
        Serial.println(String("set pin ") + String(name) + String(" OUTPUT"));
        pinMode(pin, OUTPUT);
        Serial.println(String("  LOW ") + String(name) + String(" for 10 seconds ..."));
        digitalWrite(pin, LOW);
        delay(10000);
        Serial.println(String("  HIGH ") + String(name) + String(" for 10 seconds ..."));
        digitalWrite(pin, HIGH);
        delay(10000);
        Serial.println(String("  LOW ") + String(name) + String(" for 10 seconds ..."));
        digitalWrite(pin, LOW);
        delay(10000);
        Serial.println(String("  HIGH ") + String(name));
        digitalWrite(pin, HIGH);
        delay(9000);
}

int test_pin_all_out()
{
        test_pin_ab_out("PIN_A1", PIN_A1);
        /*
         * Suggest:
         *  You should not use PA4/WM_IO_PA_04/4 PA5/WM_IO_PA_05/5 as GPIO pin,
         *  which will confusing uart0.
         */
        //test_pin_ab_out("PIN_A4", PIN_A4);
        //test_pin_ab_out("PIN_A5", PIN_A5);
        test_pin_ab_out("PIN_B6", PIN_B6);
        test_pin_ab_out("PIN_B7", PIN_B7);
}

int test_pin_ab_input(const char *name, int pin)
{
        int val;
        Serial.println(String("set pin ") + String(name) + String(" INPUT after 5 seconds"));
        delay(5000);
        Serial.println(String("set pin PIN_A1 HIGH & sleep 3 seconds"));
        digitalWrite(PIN_A1, HIGH);
        delay(3000);
        pinMode(pin, INPUT);
        val = digitalRead(pin);
        Serial.println(String(" read pin ") + String(name) + String(" value: ") + String(val));
        delay(10000);
        Serial.println(String("set pin PIN_A1 LOW & sleep 3 seconds"));
        digitalWrite(PIN_A1, LOW);
        delay(3000);
        val = digitalRead(pin);
        Serial.println(String(" read pin ") + String(name) + String(" value: ") + String(val));
        delay(9000);
}

int test_pin_ab_pa1(int pin)
{
        int val;
        char *name = NULL;
        name = (char *)"PIN_A1";
        pin = PIN_A1;
        Serial.println(String("set pin PIN_A5 OUTPUT for PA1"));
        pinMode(PIN_A5, OUTPUT);
        Serial.println(String("set pin ") + String(name) + String(" INPUT after 5 seconds"));
        delay(5000);
        Serial.println(String("  set pin PIN_A5 HIGH & sleep 3 seconds"));
        digitalWrite(PIN_A5, HIGH);
        delay(3000);
        pinMode(pin, INPUT);
        val = digitalRead(pin);
        Serial.println(String(" read pin ") + String(name) + String(" value: ") + String(val));
        delay(10000);
        Serial.println(String("set pin PIN_A5 LOW & sleep 3 seconds"));
        digitalWrite(PIN_A5, LOW);
        delay(3000);
        val = digitalRead(pin);
        Serial.println(String(" read pin ") + String(name) + String(" value: ") + String(val));
        delay(9000);
}

int test_all_pin_input()
{
        //test_pin_ab_input("PIN_A4", PIN_A4);
        //test_pin_ab_input("PIN_A5", PIN_A5);
        test_pin_ab_input("PIN_B6", PIN_B6);
        test_pin_ab_input("PIN_B7", PIN_B7);
}

int test_pin_input()
{
        test_pin_ab_pa1(PIN_A1);
        Serial.println(String("set pin PIN_A1 OUTPUT for PXx ..."));
        pinMode(PIN_A1, OUTPUT);
        digitalWrite(PIN_A1, HIGH);
        test_all_pin_input();
}


void setup() {
      // put your setup code here, to run once:
      Serial.begin(115200);
}

void loop() {
      printf("[%s %s %d]\n", __FILE__, __func__, __LINE__);
      Serial.println("Hello From W600_EV Board Serial\n");
      // put your main code here, to run repeatedly:
      test_pin_all_out();

      int sleep_cnt = 60;
      int i = 0;
      for (i = 1; i <= sleep_cnt ; i++)
      {
            if ((i - 1) % 20 == 0)
            {
                  Serial.println();
            }
            else if ((i-1) % 10 == 0)
            {
                  Serial.print("   ");
            }
            else if ((i-1) % 5 == 0)
            {
                  Serial.print(' ');
            }
            Serial.print('.');
            delay(1000);
      }
      Serial.println();
}
