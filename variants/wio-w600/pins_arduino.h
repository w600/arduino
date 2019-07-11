#ifndef _PINS_WIO_W600_H_
#define _PINS_WIO_W600_H_

#include "Arduino.h"

#ifdef __cplusplus
extern "C" {
#endif
#include "wm_io.h"

#define PIN_A0      WM_IO_PA_00
#define PIN_A1      WM_IO_PA_01
#define PIN_A4      WM_IO_PA_04
#define PIN_A5      WM_IO_PA_05

#define PIN_B6      WM_IO_PB_06
#define PIN_B7      WM_IO_PB_07
#define PIN_B8      WM_IO_PB_08
#define PIN_B9      WM_IO_PB_09
#define PIN_B10     WM_IO_PB_10
#define PIN_B11     WM_IO_PB_11
#define PIN_B12     WM_IO_PB_12
#define PIN_B13     WM_IO_PB_13
#define PIN_B14     WM_IO_PB_14
#define PIN_B15     WM_IO_PB_15
#define PIN_B16     WM_IO_PB_16
#define PIN_B17     WM_IO_PB_17
#define PIN_B18     WM_IO_PB_18


#define PA_0        PIN_A0
#define PA_1        PIN_A1
#define PA_4        PIN_A4
#define PA_5        PIN_A5

#define GPIOA0      PIN_A0
#define GPIOA1      PIN_A1
#define GPIOA4      PIN_A4
#define GPIOA5      PIN_A5


#define PB_6        PIN_B6
#define PB_7        PIN_B7
#define PB_8        PIN_B8
#define PB_9        PIN_B9
#define PB_10       PIN_B10
#define PB_11       PIN_B11
#define PB_12       PIN_B12
#define PB_13       PIN_B13
#define PB_14       PIN_B14
#define PB_15       PIN_B15
#define PB_16       PIN_B16
#define PB_17       PIN_B17
#define PB_18       PIN_B18

#define GPIOPB6     PIN_B6
#define GPIOPB7     PIN_B7
#define GPIOPB8     PIN_B8
#define GPIOPB9     PIN_B9
#define GPIOPB10    PIN_B10
#define GPIOPB11    PIN_B11
#define GPIOPB12    PIN_B12
#define GPIOPB13    PIN_B13
#define GPIOPB14    PIN_B14
#define GPIOPB15    PIN_B15
#define GPIOPB16    PIN_B16
#define GPIOPB17    PIN_B17
#define GPIOPB18    PIN_B18


#define USER_BTN    PIN_A1
#define USER        PIN_A1
#define SW2         PIN_A1


#define PWM1        PIN_B18
#define PWM2        PIN_B17
#define PWM3        PIN_B16
#define PWM4        PIN_B15
#define PWM5        PIN_B14


#define LED_RED     PIN_B16
#define LED_BUILTIN PIN_B17
#define LED_GREEN   PIN_B17
#define LED_BLUE    PIN_B18


#define TLS_UART1_MUL_RX    PIN_B17
#define TLS_UART1_MUL_TX    PIN_B18

static int get_w60x_pin_via_digitalPin(uint32_t ulPin)
{
    uint32_t w60x_pin = DIGITAL_PIN_MAX;
    switch(ulPin)
    {
        case 0:
        case 1:
            break;
        case 2:
            return PIN_B6;
        case 3:
            return PIN_A1;                      /* 1 */
        case 4:
            return PIN_A4;                      /* 4 */
        case 5:
            return PIN_A5;                      /* 5 */
        case 6:
            return PIN_B7;
        case 7:                     /* NC */
            return PIN_B8;
        case 8:
            return PIN_B9;
        case 9:
            return PIN_B10;
        case 10:
            return PIN_B15;    /* 31 */
        case 11:
            return PIN_B18;    /* 34 */
        case 12:
            return PIN_B17;    /* 33 */
        case 13:
            return PIN_B16;    /* 32 */
        case 14 ... 17:
            break;
        case 18:
            return PIN_B14;   /* 30 */
        case 19:
            return PIN_B13;   /* 29 */
    }
    return w60x_pin;
}


#ifdef __cplusplus
}
#endif

#endif
