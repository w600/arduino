#include <Arduino.h>

#define W600_INNERFLASH_EXAMPLE  1   /*set this macro to test inner flash operation*/
#if W600_INNERFLASH_EXAMPLE
#include <W600InnerFlash.h>
#endif

#if W600_INNERFLASH_EXAMPLE
void innerflash_setup()
{
    InnerFlash.begin();
}
#endif

void w600_arduino_setup()
{
    printf("[%s %s %d]\n", __FILE__, __func__, __LINE__);
#if W600_INNERFLASH_EXAMPLE
    innerflash_setup();
#endif
    Serial.println("xxxxxxxxxxxx");
    SerialM1.begin();
}

#if W600_INNERFLASH_EXAMPLE
void innerflash_loop()
{
    u8 data[4096];
    int i = 0;

    InnerFlash.flashRead(240*4096, &data[0], 4096);
    if (data[0] == 0xAA)
    {
        InnerFlash.flashEraseSector(240);
        memset(&data[0], 0xAA, 4096);
        InnerFlash.flashRead(240*4096, &data[0], 4096);
        for (i = 0; i< 4096; i++)
        {
            if (data[i] == 0xFF)
            {
                continue;
            }
        }
        if (i == 4096)
        {
            printf("erase ok\n");
        }
    }else{
        memset(&data[0], 0xAA, 4096);
        InnerFlash.flashWrite(240*4096, &data[0], 4096);
        memset(&data[0], 0xFF, 4096);
        InnerFlash.flashRead(240*4096, &data[0], 4096);
        for (i = 0; i< 4096; i++)
        {
            if (data[i] == 0xAA)
            {
                continue;
            }
        }
        if (i == 4096)
        {
            printf("write ok\n");
        }
    }
}
#endif

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
#if W600_INNERFLASH_EXAMPLE
    innerflash_loop();
#endif  
    sleep_cnt(60);
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
