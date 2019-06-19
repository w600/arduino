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

int user_main_task()
{
    wm_swd_config(1);
    
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
