/**
 * @file    Tone.cpp
 *
 * @brief   Tone Driver Module
 *
 * @author  fanwl
 *
 * Copyright (c) 2019 Winner Microelectronics Co., Ltd.
 */
extern "C" {
    #include "wm_pwm.h"
    #include "wm_gpio_afsel.h"
    #include "wm_gpio.h"
}
/**
 * @brief          Generates a square wave of the specified frequency (and 50% duty cycle) on a pin
 *
 * @param[in]      _pin    gpio pin
 * 
 * @param[in]      frequency  the frequency of the tone in hertz(1 to 156250)
 * 
 * @return         none
 *
 * @note           none
 */
void tone(uint8_t _pin, unsigned int frequency)
{
    if(frequency >= 156250)
    {
        frequency = 156250;
    }
    switch (_pin)
    {
    case WM_IO_PB_18:
        wm_pwm1_config(WM_IO_PB_18);
        tls_pwm_init(0, frequency, 127, 0);
        tls_pwm_start(0);
        break;
    case WM_IO_PB_17:
        wm_pwm2_config(WM_IO_PB_17);
        tls_pwm_init(1, frequency, 127, 0);
        tls_pwm_start(1);
        break;
    case WM_IO_PB_16:
        wm_pwm3_config(WM_IO_PB_16);
        tls_pwm_init(2, frequency, 127, 0);
        tls_pwm_start(2);
        break;
    case WM_IO_PB_15:
        wm_pwm4_config(WM_IO_PB_15);
        tls_pwm_init(3, frequency, 127, 0);
        tls_pwm_start(3);
        break;
    case WM_IO_PB_14:
        wm_pwm5_config(WM_IO_PB_14);
        tls_pwm_init(4, frequency, 127, 0);
        tls_pwm_start(4);
        break;
    default:
        break;
    }
}

/**
 * @brief          Stops the generation of a square wave triggered by tone().
 *
 * @param[in]      _pin    gpio pin
 * 
 * @return         none
 *
 * @note           none
 */
void noTone(uint8_t _pin) {
    switch (_pin)
    {
    case WM_IO_PB_18:
        tls_pwm_stop(0);
        tls_gpio_cfg(WM_IO_PB_18, WM_GPIO_DIR_OUTPUT, WM_GPIO_ATTR_PULLLOW);
        tls_gpio_write(WM_IO_PB_18, 0);
        break;
    case WM_IO_PB_17:
        tls_pwm_stop(1);
        tls_gpio_cfg(WM_IO_PB_17, WM_GPIO_DIR_OUTPUT, WM_GPIO_ATTR_PULLLOW);
        tls_gpio_write(WM_IO_PB_17, 0);
        break;
    case WM_IO_PB_16:
        tls_pwm_stop(2);
        tls_gpio_cfg(WM_IO_PB_16, WM_GPIO_DIR_OUTPUT, WM_GPIO_ATTR_PULLLOW);
        tls_gpio_write(WM_IO_PB_16, 0);
        break;
    case WM_IO_PB_15:
        tls_pwm_stop(3);
        tls_gpio_cfg(WM_IO_PB_15, WM_GPIO_DIR_OUTPUT, WM_GPIO_ATTR_PULLLOW);
        tls_gpio_write(WM_IO_PB_15, 0);
        break;
    case WM_IO_PB_14:
        tls_pwm_stop(4);
        tls_gpio_cfg(WM_IO_PB_14, WM_GPIO_DIR_OUTPUT, WM_GPIO_ATTR_PULLLOW);
        tls_gpio_write(WM_IO_PB_14, 0);
        break;
    default:
        break;
    }
}
