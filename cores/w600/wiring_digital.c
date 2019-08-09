#include "Arduino.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "wm_gpio.h"

uint32_t check_ulPin(uint32_t ulPin)
{
    uint32_t w60x_pin = DIGITAL_PIN_MAX;

    if (0 <= ulPin && ulPin <= 32)
    {
        w60x_pin = get_w60x_pin_via_digitalPin(ulPin);
    } else if ( WM_IO_PB_06 == ulPin
                || WM_IO_PB_07 == ulPin
                || WM_IO_PB_08 == ulPin
                || WM_IO_PB_09 == ulPin
                || WM_IO_PB_10 == ulPin
                || WM_IO_PB_11 == ulPin
                || WM_IO_PB_12 == ulPin
                || WM_IO_PB_13 == ulPin
                || WM_IO_PB_14 == ulPin
                || WM_IO_PB_15 == ulPin
                || WM_IO_PB_16 == ulPin
                || WM_IO_PB_17 == ulPin
                || WM_IO_PB_18 == ulPin)
    {
        w60x_pin = ulPin;
    }
    return w60x_pin;
}

void pinMode(uint32_t ulPin, uint32_t ulMode)
{
    uint32_t w60x_pin = check_ulPin(ulPin);
    if (0 <= w60x_pin && w60x_pin < DIGITAL_PIN_MAX)
    {
    	tls_gpio_cfg(w60x_pin,
            ulMode == INPUT 
            	? WM_GPIO_DIR_INPUT 
            	: WM_GPIO_DIR_OUTPUT, 
            	WM_GPIO_ATTR_PULLHIGH);
    } else {
        printf("{%d} M NOT Support the function in W600_EV BOARD_V1.0\n", w60x_pin);
    }
}

void digitalWrite(uint32_t ulPin, uint32_t ulVal)
{
    uint32_t w60x_pin = check_ulPin(ulPin);
    if (0 <= w60x_pin && w60x_pin < DIGITAL_PIN_MAX)
    {
	    tls_gpio_write(w60x_pin, ulVal);
    } else {
        printf("{%d} W NOT Support the function in W600_EV BOARD_V1.0\n", w60x_pin);
    }
}

int digitalRead(uint32_t ulPin)
{
    uint32_t w60x_pin = check_ulPin(ulPin);
    if (0 <= w60x_pin && w60x_pin < DIGITAL_PIN_MAX)
    {
	    return tls_gpio_read(w60x_pin);
    } else {
        printf("{%d} R NOT Support the function in W600_EV BOARD_V1.0\n", w60x_pin);
        return -1;
    }
}

#ifdef __cplusplus
}
#endif
