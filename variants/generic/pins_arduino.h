#ifndef _PINS_ARDUINO_H_
#define _PINS_ARDUINO_H_
#include "Arduino.h"
#include "wm_io.h"

#include "variant.h"

#define PIN_A0  WM_IO_PA_00

#if NUM_ANALOG_INPUTS > 0
#define PIN_A1	WM_IO_PA_01   /* D3 */
#endif

#if NUM_ANALOG_INPUTS > 1
#define PIN_A4	(WM_IO_PA_04)   /* D4 */
#endif

#if NUM_ANALOG_INPUTS > 2
#define PIN_A5	(WM_IO_PA_05)   /* D5 */
#endif

#define PIN_A6  WM_IO_PA_06
#define PIN_A7  WM_IO_PA_07
#define PIN_A8  WM_IO_PA_08
#define PIN_A9  WM_IO_PA_09
#define PIN_A10 WM_IO_PA_10
#define PIN_A11 WM_IO_PA_11
#define PIN_A12 WM_IO_PA_12
#define PIN_A13 WM_IO_PA_13
#define PIN_A14 WM_IO_PA_14
#define PIN_A15 WM_IO_PA_15

#if NUM_ANALOG_INPUTS > 3
#define PIN_B6	(WM_IO_PB_06)   /* D0 */
#endif

#if NUM_ANALOG_INPUTS > 4
#define PIN_B7	(WM_IO_PB_07)   /* D1 */
#endif

#if NUM_ANALOG_INPUTS > 5
#define PIN_B8	(WM_IO_PB_08)
#endif

#if NUM_ANALOG_INPUTS > 6
#define PIN_B9	(WM_IO_PB_09)
#endif

#if NUM_ANALOG_INPUTS > 7
#define PIN_B10	(WM_IO_PB_10)
#endif

#if NUM_ANALOG_INPUTS > 8
#define PIN_B11	(WM_IO_PB_11)
#endif

#if NUM_ANALOG_INPUTS > 9
#define PIN_B12	(WM_IO_PB_12)
#endif

#define PIN_B13 WM_IO_PB_13
#define PIN_B14 WM_IO_PB_14
#define PIN_B15 WM_IO_PB_15
#define PIN_B16 WM_IO_PB_16
#define PIN_B17 WM_IO_PB_17
#define PIN_B18 WM_IO_PB_18
#define PIN_B19 WM_IO_PB_19
#define PIN_B20 WM_IO_PB_20
#define PIN_B21 WM_IO_PB_21
#define PIN_B22 WM_IO_PB_22
#define PIN_B23 WM_IO_PB_23
#define PIN_B24 WM_IO_PB_24
#define PIN_B25 WM_IO_PB_25
#define PIN_B26 WM_IO_PB_26
#define PIN_B27 WM_IO_PB_27
#define PIN_B28 WM_IO_PB_28
#define PIN_B29 WM_IO_PB_29
#define PIN_B30 WM_IO_PB_30
#define PIN_B31 WM_IO_PB_31

#define PA_0        PIN_A0
#define PA_1        PIN_A1   /* D3 */
#define PA_4        PIN_A4   /* D4 */
#define PA_5        PIN_A5   /* D5 */
#define GPIOA0      PA_0
#define GPIOA1      PA_1
#define GPIOA4      PA_4
#define GPIOA5      PA_5

#define PB_6        PIN_B6   /* D0 */
#define PB_7        PIN_B7   /* D1 */
#define PB_8        PIN_B8
#define PB_9        PIN_B9
#define PB_10       PIN_B10
#define PB_11       PIN_B11
#define PB_12       PIN_B12
#define PB_13       PIN_B13  /* D17 */
#define PB_14       PIN_B14  /* D16 */
#define PB_15       PIN_B15  /* D10 */
#define PB_16               PIN_B16
//#define PB_16         /* D13 */
#define PB_17               PIN_B17
//#define PB_17         /* D12 */
#define PB_18               PIN_B18
//#define PB_18       11    /* D11 */

#define GPIOPB6     PB_6
#define GPIOPB7     PB_7
#define GPIOPB8     PB_8
#define GPIOPB9     PB_9
#define GPIOPB10    PB_10
#define GPIOPB11    PB_11
#define GPIOPB12    PB_12
#define GPIOPB13    PB_13
#define GPIOPB14    PB_14
#define GPIOPB15    PB_15
#define GPIOPB16    PB_16
#define GPIOPB17    PB_17
#define GPIOPB18    PB_18

#define LED_BUILTIN         PB_17
#define LED_RED             PB_16
#define LED_BLUE            PB_18
#define LED_GREEN           LED_BUILTIN

#define USER_BTN            PIN_B7
#ifndef USER_BTN_PRESS
#define USER_BTN_PRESS      0
#define USER_BTN_RELEASE    1
#endif
#define USER                USER_BTN
#define SW2                 USER_BTN

#define TLS_UART1_MUL_RX	PB_17
#define TLS_UART1_MUL_TX	PB_18

#define PWM1    PB_18
#define PWM2    PB_17
#define PWM3    PB_16
#define PWM4    PB_15
#define PWM5    PB_14

#if defined(WM_W600_ARDUINO_EVB_V_1_0)
static int get_w60x_pin_via_digitalPin_v_1_0(uint32_t ulPin)
{
    uint32_t w60x_pin = DIGITAL_PIN_MAX;
    switch(ulPin)
    {
        case 0: return PIN_B6;                      /* 22 */
        case 1: return PIN_B7;                      /* 23 */
        case 2: break;                    /* NC */
        case 3: return PIN_A1;                      /* 1 */
        case 4: return PIN_A4;                      /* 4 */
        case 5: return PIN_A5;                      /* 5 */
        case 6: break;                    /* NC */
        case 7: break;                    /* NC */
        case 8: break;
        case 9: break;
        case 10: return WM_IO_PB_15;     /* SPI_CS */    /* 31 */
        case 11: return WM_IO_PB_18;     /* SPI_DO */    /* 34 */
        case 12: return WM_IO_PB_17;     /* SPI_DI */    /* 33 */
        case 13: return WM_IO_PB_16;     /* SPI_CK */    /* 32 */
        case 14: break;                   /* GND */
        case 15: break;                   /* NC */
        case 16: return WM_IO_PB_14;     /* I2C_SDA */   /* 30 */
        case 17: return WM_IO_PB_13;     /* I2C_SCL */   /* 29 */
    }
    return w60x_pin;
}
#endif
#if defined(WM_W600_ARDUINO_EVB_V_2_0)
static int get_w60x_pin_via_digitalPin_v_2_0(uint32_t ulPin)
{
    uint32_t w60x_pin = DIGITAL_PIN_MAX;
    switch(ulPin)
    {
        case 0: return PIN_A5;
        case 1: return PIN_A4;
        case 2: return PIN_B12;
        case 3: return PIN_B6;
        case 4: return PIN_A1;
        case 5: return PIN_B7;
        case 6: return PIN_B11;
        case 7: return PIN_B10;
        case 8: return PIN_B9;
        case 9: return PIN_B8;
        case 10: return WM_IO_PB_15;
        case 11: return WM_IO_PB_18;
        case 12: return WM_IO_PB_17;
        case 13: return WM_IO_PB_16;
        case 14: break;
        case 15: break;
        case 16: return WM_IO_PB_14;
        case 17: return WM_IO_PB_13;
    }
    return w60x_pin;
}

#endif

#if defined(WM_W600_ARDUINO_EVB_V_1_0)
    #ifndef get_w60x_pin_via_digitalPin
        //#warning "Use WinnerMicro Arduino Development Board with V1.0"
        #define get_w60x_pin_via_digitalPin get_w60x_pin_via_digitalPin_v_1_0
    #endif
#elif defined(WM_W600_ARDUINO_EVB_V_2_0)
    #ifndef get_w60x_pin_via_digitalPin
        //#warning "Use WinnerMicro Arduino Development Board with V2.0"
        #define get_w60x_pin_via_digitalPin get_w60x_pin_via_digitalPin_v_2_0
    #endif
#else
    #error  "Not Support the version on the WinnerMicro Arduino Development Board"
#endif

#endif
