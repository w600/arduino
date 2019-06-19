#include "wiring_private.h"
#include "pins_arduino.h"
#include "wm_adc.h"
#include "wm_gpio_afsel.h"

/**
  * @brief  Reads the value from the specified analog pin
  * @param  pin: the number of the analog input pin to read from 
  * @retval average: int (8192 -> 16384, look up for example to learn how to change it to voltage)
  */
int analogRead(unsigned char pin)
{
    unsigned short average;
    
    wm_adc_config(pin);
    average = adc_get_inputVolt(pin);
    return average;
}

