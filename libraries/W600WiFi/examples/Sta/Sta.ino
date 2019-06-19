#include <Arduino.h>
#include <W600WiFi.h>
#include <Dns.h>

int wifi_connect_as_sta()
{
    Serial.println(String("WiFi.mac: ") + String(WiFi.macAddressStr()));
    WiFi.setAutoReconnect(true);
    WiFi.begin((const char *)"123456789", (const char *)"kobe19780823");
    int status = 0;
    do
    {
        status = WiFi.status();
        delay(500);
        Serial.print(".");
        //printf("status: %d\n", status);
    } while (WL_CONNECTED != status);
    Serial.println();
    delay(1000);

    Serial.println(String("IPv4 Address: ") + WiFi.localIP().toString());
    Serial.println(String("IPv4 Netmask: ") + WiFi.subnetMask().toString());
    Serial.println(String("IPv4 GateWay: ") + WiFi.getwayIP().toString());
    Serial.println(String("IPv4 DNS: ") + WiFi.dnsIP().toString());
    Serial.println(String("IPv4 DNS1: ") + WiFi.dnsIP(1).toString());
    Serial.println(String("connected BSSID(str): ") + String(WiFi.BSSIDstr()));
    Serial.println(String("current RSSI: ") + String(WiFi.RSSI()));
}

void w600_arduino_setup()
{
    printf("[%s %s %d]\n", __FILE__, __func__, __LINE__);
    wifi_connect_as_sta();
    delay(1000);
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
    Serial.println("Hello From W600_EV Board Serial\n");
    DNSClient dns;
    char *resolve = NULL;
    if (dns.getHostByName("www.baidu.com", resolve))
    {
        printf("www.baidu.com: %s\n", resolve);
    }
    sleep_cnt(60);
}

void setup() {
    printf("setup()\n");
    // put your setup code here, to run once:
    w600_arduino_setup();
}

void loop() {
    w600_arduino_loop();
}
