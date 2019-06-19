/**
 * @file    Arduino.h
 *
 * @brief   Arduino header
 *
 * @author  fanwl
 *
 * Copyright (c) 2019 Winner Microelectronics Co., Ltd.
 */
#ifndef Arduino_h
#define Arduino_h

#include "wiring.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @mainpage WinnerMicro Arduino
 *
 * Welcome to use WinnerMicro Arduino.
 *
 * @endcode
 *
 * \n
 */

#define DIGITAL_PIN_MAX 64

#include "pins_arduino.h"

#define PWMRANGE 255
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
void analogWrite(uint8_t pin, int val);
/**
 * @brief          Change the PWM ware frequency
 *
 * @param[in]      freq   range from 1 to 156250
 * 
 * @return         none
 *  
 * @note           none
 */
void analogWriteFreq(uint32_t freq);
/**
 * @brief          Measures the length (in microseconds) of a pulse on the pin
 *
 * @param[in]      pin    gpio pin
 * 
 * @param[in]      state   state is HIGH or LOW, the type of pulse to measure
 * 
 * @param[in]      timeout  timeout time
 *
 * @return         the length of a pluse(in microseconds)
 *
 * @note           This function relies on micros() so cannot be used in noInterrupt() context.
 *                 Works on pulses from 2-3 microseconds to 3 minutes in length, but must be called at least a few dozen microseconds
 *                 before the start of the pulse.
 */
unsigned long pulseIn(uint8_t pin, uint8_t state, unsigned long timeout);
/**
 * @brief          Measures the length (in microseconds) of a pulse on the pin
 *
 * @param[in]      pin    gpio pin
 * 
 * @param[in]      state   state is HIGH or LOW, the type of pulse to measure
 * 
 * @param[in]      timeout  timeout time
 *
 * @return         the length of a pluse(in microseconds)
 *
 * @note           This function relies on micros() so cannot be used in noInterrupt() context.
 *                 Works on pulses from 2-3 microseconds to 3 minutes in length, but must be called at least a few dozen microseconds
 *                 before the start of the pulse.
 */
unsigned long pulseInLong(uint8_t pin, uint8_t state, unsigned long timeout);

#ifdef __cplusplus
}
#endif

/**
 * @defgroup IO IO
 * @brief Digital Analog and Advanced I/O
 */

/**
 * @addtogroup IO
 * @{
 */

/**
 * @defgroup IO IO
 * @brief Digital Analog and Advanced I/O
 */

/**
 * @addtogroup IO
 * @{
 */

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
void tone(uint8_t _pin, unsigned int frequency);
/**
 * @brief          Stops the generation of a square wave triggered by tone().
 *
 * @param[in]      _pin    gpio pin
 * 
 * @return         none
 *
 * @note           none
 */
void noTone(uint8_t _pin);

/**
 * @}
 */

/**
 * @}
 */

#endif 
