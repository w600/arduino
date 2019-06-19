/**
 * @file    MsTimer.h
 *
 * @brief   MsTimer Driver Module
 *
 * @author  famwl
 *
 * Copyright (c) 2019 Winner Microelectronics Co., Ltd.
 */
#ifndef MsTimer_h
#define MsTimer_h

#include <stdio.h>

extern "C" {
#include "wm_timer.h"
}

namespace MsTimer1 {
    extern volatile unsigned char timer_id;
    void set(unsigned long ms, void (*f)());
    void start();
    void stop();
}

namespace MsTimer2 {
    extern volatile unsigned char timer_id;
    void set(unsigned long ms, void (*f)());
    void start();
    void stop();
}

#endif
