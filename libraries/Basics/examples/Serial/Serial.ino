/*
  W600 Serial Demo
  GPIO define  in "hardware\w600\0.2.4\variants\tb_01("The board type")\pins_arduino.h"
*/
#include <Arduino.h>

int test_println_i()
{
    int inum = 10;
    Serial.println("** test_println_i **");
    Serial.println(inum);
    Serial.println(inum, DEC);
    Serial.println(inum, HEX);
    Serial.println(inum, OCT);
    Serial.println(inum, BIN);
}

int test_println_ui()
{
    unsigned int uinum = 10;
    Serial.println("** test_println_ui **");
    Serial.println(uinum);
    Serial.println(uinum, DEC);
    Serial.println(uinum, HEX);
    Serial.println(uinum, OCT);
    Serial.println(uinum, BIN);
}

int test_println_l()
{
    long lnum = 10;
    Serial.println("** test_println_l **");
    Serial.println(lnum);
    Serial.println(lnum, DEC);
    Serial.println(lnum, HEX);
    Serial.println(lnum, OCT);
    Serial.println(lnum, BIN);
}

int test_println_ul()
{
    unsigned ulnum = 10;
    Serial.println("** test_println_ul **");
    Serial.println(ulnum);
    Serial.println(ulnum, DEC);
    Serial.println(ulnum, HEX);
    Serial.println(ulnum, OCT);
    Serial.println(ulnum, BIN);
}

int test_println_f()
{
    double dnum = 123.456;
    Serial.println("** test_println_f **");
    Serial.println(dnum);
    Serial.println(dnum, DEC);
    Serial.println(dnum, HEX);
    Serial.println(dnum, OCT);
    Serial.println(dnum, BIN);
}


void Serial0_print()
{
    test_println_i();
    test_println_ui();
    test_println_l();
    test_println_ul();
    test_println_f();
}

void SerialM1_test()
{
    static int test_func_check = 0;
    Serial1.println('A');
    Serial1.read();
    SerialM1.write('A');
    char buf[10] = {0};
    printf("before read, SerialM1.available: %d\n", SerialM1.available());
    if (SerialM1.available()
        && (0 == (test_func_check % 6)))
    {
        printf("SerialM1.parseInt(): %d\n", SerialM1.parseInt());
    }
    else if (SerialM1.available()
        && (1 == (test_func_check % 6)))
    {
        printf("SerialM1.parseFloat(): %f\n", SerialM1.parseFloat());
    }
    else if (SerialM1.available()
        && 2 == (test_func_check % 6))
    {
        SerialM1.readBytes(buf, 9);
        buf[10 - 1] = '\0';
        printf("readBytes buf: %s\n", buf);
    } else if (SerialM1.available()
        && 3 == (test_func_check % 6))
    {
        SerialM1.readBytesUntil('A', buf, 10);
        buf[10 - 1] = '\0';
        printf("readBytesUntil buf: %s\n", buf);
    } else if (SerialM1.available()
        && 4 == (test_func_check % 6))
    {
        printf("SerialM1.find(\"12345\"): %d\n", SerialM1.find("12345"));
        printf("SerialM1.find(\"ABCDE\"): %d\n", SerialM1.find("ABCDE"));
    } else if (SerialM1.available()
        && (5 == (test_func_check % 6)))
    {
        while (0 != SerialM1.available())
        {
            Serial.println(String("----peek: ") + String(SerialM1.peek()));
            Serial.println(String("++++read: ") + String(SerialM1.read()));
        }
        printf("after read, SerialM1.available: %d\n", SerialM1.available());
    }
    test_func_check ++;
}
  

int sleep_count(int cnt)
{
    int sleep_cnt = cnt;
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

void setup() {
    // put your setup code here, to run once:
    printf("[%s %s %d]\n", __FILE__, __func__, __LINE__);
    Serial.println("xxxxxxxxxxxx");
    SerialM1.begin();
    delay(1000);  
}

void loop() {
    delay(3000);
    Serial0_print();
    SerialM1_test();
    sleep_count(20);
}
