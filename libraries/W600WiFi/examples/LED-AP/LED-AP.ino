#include <Arduino.h>
#include <W600WiFi.h>

#define USE_LED_MACRO         1
#define USE_PA_x_PB_x_MACRO   0

#define USER_BUTTON_MACRO           1
#define USER_BUTTON_PAx_PBx_MACRO   0
#define USER_BUTTON_SW_MACRO        0

#ifdef WIO_W600
int power_output_startup()
{
    pinMode(3, OUTPUT);
    digitalWrite(3, HIGH);
}
#endif

#if USE_LED_MACRO
    int led_red_pin = LED_RED;
    int led_green_pin = LED_GREEN;
    int led_blue_pin = LED_BLUE;
#elif USE_PA_x_PB_x_MACRO
    int led_red_pin = PB_16;
    int led_green_pin = PB_17;
    int led_blue_pin = PB_18;
#endif

#if USER_BUTTON_MACRO
    int user_button_pin = USER_BTN;
#elif USER_BUTTON_PAx_PBx_MACRO
    int user_button_pin = PB_7;
#elif USER_BUTTON_SW_MACRO
    int user_button_pin = SW2;
#endif

void w600_arduino_setup()
{
    printf("[%s %s %d]\n", __FILE__, __func__, __LINE__);
    Serial.println("xxxxxxxxxxxx");
    SerialM1.begin();
    delay(1000);
}

int only_light_r()
{
    digitalWrite(led_red_pin, LOW);
    digitalWrite(led_green_pin, HIGH);
    digitalWrite(led_blue_pin, HIGH);
}

int only_light_g()
{
    digitalWrite(led_red_pin, HIGH);
    digitalWrite(led_green_pin, LOW);
    digitalWrite(led_blue_pin, HIGH);
}

int only_light_b()
{
    digitalWrite(led_red_pin, HIGH);
    digitalWrite(led_green_pin, HIGH);
    digitalWrite(led_blue_pin, LOW);
}
  
int get_AP_info()
{
    Serial.println("-----------------------------------------");
    Serial.println(String("STANUM: ") + String(WiFi.softAPgetStationNum()));
    Serial.println(String("AP IP: ") + String(WiFi.softAPIP()));
    Serial.println(String("AP MAC: ") + String(WiFi.softAPmacAddress()));
    Serial.println(String("AP SSID: ") + String(WiFi.softAPSSID()));
    Serial.println(String("AP PSK: ") + String(WiFi.softAPPSK()));
}
  
int test_USER_BTN()
{
    pinMode(user_button_pin, INPUT);
    int val = 1;
    int val_prev = 2;
    pinMode(led_green_pin, OUTPUT);
    pinMode(led_red_pin, OUTPUT);
    pinMode(led_blue_pin, OUTPUT);
    int start_ap = 0;
    while (1)
    {
        val = digitalRead(user_button_pin);
        if (val != val_prev)
        {
            printf("USET BTN: %d/%s\n", val, val == USER_BTN_PRESS ? "Press" : "Release");
            val_prev = val;
        }
        if (USER_BTN_PRESS == val)
        {
            if ( 0 == start_ap ) {
                WiFi.softAP("ABCDEFG", "1234567890");
                start_ap = 1;
            }
            only_light_r();
            delay(800);
            only_light_g();
            delay(800);
            only_light_b();
            delay(800);
            get_AP_info();
        }
        else
        {
            if (1 == start_ap)
            {
                Serial.println("Disconnect AP");
                WiFi.softAPdestroy();
                start_ap = 0;
            }
            digitalWrite(led_red_pin, HIGH);
            digitalWrite(led_green_pin, HIGH);
            digitalWrite(led_blue_pin, HIGH);
            delay(100);
        }
    }    
}

int sleep_cnt(int cnt)
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
void w600_arduino_loop()
{
    printf("loop()\n");
    Serial.println("Hello From W600_EV Board Serial\n");
    test_USER_BTN();
    sleep_cnt(60);
}

void setup() {
#ifdef WIO_W600
    power_output_startup();
#endif
    printf("setup()\n");
    // put your setup code here, to run once:
    w600_arduino_setup();
}

void loop() {
    printf("[%s %s %d]\n", __FILE__, __func__, __LINE__);
    w600_arduino_loop();
}
