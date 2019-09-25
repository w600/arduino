#include <stdio.h>
#include "debug.h"

extern void setup();
extern void loop();

#ifdef __cplusplus
extern "C" {
#endif

extern "C" int sendchar(int ch);
extern "C" void wm_swd_config(bool);

#if 0
void SystemInit()
{
}
#endif

#ifdef WIO_W600
void power_output_startup()
{
    pinMode(PB_7, OUTPUT);
    digitalWrite(PB_7, HIGH);
}
#endif

int user_main_task()
{
    wm_swd_config(1);
#ifdef WIO_W600
	 power_output_startup();
#endif    
    setup();
    
    while (1)
    {
        loop();
    }
    
    return 0;
}

#ifdef __cplusplus
}
#endif
