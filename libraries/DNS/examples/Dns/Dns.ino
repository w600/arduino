#include <Arduino.h>
#include <W600WiFi.h>
#include <Dns.h>

int wifi_connect_as_sta()
{
    printf("WiFi.mac: %s\n", WiFi.macAddressStr());
    WiFi.begin((const char *)"123456789", (const char *)"kobe19780823");
    int status = 0;
    do
    {
        status = WiFi.status();
        delay(500);
        Serial.print(".");
    } while (WL_CONNECTED != status);
    Serial.println();
    delay(5000);
    
    Serial.print("IPv4 Address: "); Serial.println(WiFi.localIP());
    Serial.print("IPv4 Netmask: "); Serial.println(WiFi.subnetMask());
    Serial.print("IPv4 GateWay: "); Serial.println(WiFi.getwayIP());
    Serial.print("IPv4 DNS: ");     Serial.println(WiFi.dnsIP());
    Serial.print("IPv4 DNS1: ");    Serial.println(WiFi.dnsIP(1));
    
    printf("current SSID: %s\n", WiFi.SSID());
    printf("current Passphrase: %s\n", WiFi.psk());
    printf("connected BSSID(str): %s\n", WiFi.BSSIDstr());
    printf("current RSSI: %d\n", WiFi.RSSI());
    
    unsigned char *pbssid = (unsigned char *)(WiFi.BSSID());
    printf("connected BSSID: %02X:%02X:%02X:%02X:%02X:%02X\n",
        pbssid[0], pbssid[1], pbssid[2], pbssid[3], pbssid[4], pbssid[5]);
    printf("WiFi Connected ?[%s]\n", WiFi.isConnected() ? "true" : "false");
}

void w600_arduino_setup()
{
    printf("[%s %s %d]\n", __FILE__, __func__, __LINE__);
    Serial.println("xxxxxxxxxxxx");
    //Serial1.begin();
    SerialM1.begin();
    wifi_connect_as_sta();
}

void w600_arduino_loop()
{
    printf("loop()\n");
    DNSClient dns;
    char *resolve = NULL;
    if (dns.getHostByName("www.baidu.com", resolve))
    {
        printf("www.baidu.com: %s\n", resolve);
    }
    SerialM1.write('A');
    Serial.println("Hello From W600_EV Board Serial\n");
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

void setup() {
    printf("setup()\n");
    // put your setup code here, to run once:
    w600_arduino_setup();
}

void loop() {
    printf("[%s %s %d]\n", __FILE__, __func__, __LINE__);
    w600_arduino_loop();
}