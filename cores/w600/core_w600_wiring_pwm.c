/**
 * @file    core_w600_wiring_pwm.c
 *
 * @brief   PWM Driver Module
 *
 * @author  fanwl
 *
 * Copyright (c) 2019 Winner Microelectronics Co., Ltd.
 */
#include <Arduino.h>
#include "wm_pwm.h"
#include "wm_gpio_afsel.h"
#include "wm_gpio.h"

static uint32_t analogFreq = 10000;

/**
 * @brief          Change the PWM ware frequency
 *
 * @param[in]      freq   range from 1 to 156250
 * 
 * @return         none
 *  
 * @note           none
 */
extern void __analogWriteFreq(uint32_t freq)
{
    if (freq < 1)
    {
        analogFreq = 1;
    }
    else if (freq > 156250)
    {
        analogFreq = 156250;
    }
    else
    {
        analogFreq = freq;
    }
}

/**
 * @brief          Writes an analog value (PWM wave) to a pin
 *
 * @param[in]      pin    gpio pin
 * 
 * @param[in]      val    the duty cycle: between 0 to  255
 * 
 * @return         none
 * 
 * @note           none
 */
extern void __analogWrite(uint8_t _pin, int val)
{
    if (val < 0)
    {
        val = 0;
    }
    else if (val > PWMRANGE)
    {
        val = PWMRANGE;
    }
    switch (_pin)
    {
    case WM_IO_PB_18:
        if (val > 0)
        {
            wm_pwm1_config(WM_IO_PB_18);
            tls_pwm_init(0, analogFreq, val, 0);
            tls_pwm_start(0);
        }
        else
        {
            tls_pwm_stop(0);
            tls_gpio_cfg(WM_IO_PB_18, WM_GPIO_DIR_OUTPUT, WM_GPIO_ATTR_PULLLOW);
            tls_gpio_write(WM_IO_PB_18, 0);
        }
        break;
    case WM_IO_PB_17:
        if (val > 0)
        {
            wm_pwm2_config(WM_IO_PB_17);
            tls_pwm_init(1, analogFreq, val, 0);
            tls_pwm_start(1);
        }
        else
        {
            tls_pwm_stop(1);
            tls_gpio_cfg(WM_IO_PB_17, WM_GPIO_DIR_OUTPUT, WM_GPIO_ATTR_PULLLOW);
            tls_gpio_write(WM_IO_PB_17, 0);
        }
        break;
    case WM_IO_PB_16:
        if (val > 0)
        {
            wm_pwm3_config(WM_IO_PB_16);
            tls_pwm_init(2, analogFreq, val, 0);
            tls_pwm_start(2);
        }
        else
        {
            tls_pwm_stop(2);
            tls_gpio_cfg(WM_IO_PB_16, WM_GPIO_DIR_OUTPUT, WM_GPIO_ATTR_PULLLOW);
            tls_gpio_write(WM_IO_PB_16, 0);
        }
        break;
    case WM_IO_PB_15:
        if (val > 0)
        {
            wm_pwm4_config(WM_IO_PB_15);
            tls_pwm_init(3, analogFreq, val, 0);
            tls_pwm_start(3);
        }
        else
        {
            tls_pwm_stop(3);
            tls_gpio_cfg(WM_IO_PB_15, WM_GPIO_DIR_OUTPUT, WM_GPIO_ATTR_PULLLOW);
            tls_gpio_write(WM_IO_PB_15, 0);
        }
        break;
    case WM_IO_PB_14:
        if (val > 0)
        {
            wm_pwm5_config(WM_IO_PB_14);
            tls_pwm_init(4, analogFreq, val, 0);
            tls_pwm_start(4);
        }
        else
        {
            tls_pwm_stop(4);
            tls_gpio_cfg(WM_IO_PB_14, WM_GPIO_DIR_OUTPUT, WM_GPIO_ATTR_PULLLOW);
            tls_gpio_write(WM_IO_PB_14, 0);
        }
        break;
    default:
        break;
    }
}

extern void analogWrite(uint8_t pin, int val) __attribute__((weak, alias("__analogWrite")));
extern void analogWriteFreq(uint32_t freq) __attribute__((weak, alias("__analogWriteFreq")));
