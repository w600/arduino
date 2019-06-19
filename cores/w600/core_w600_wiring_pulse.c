/**
 * @file    core_w600_wiring_pulse.c
 *
 * @brief   Pulse Driver Module
 *
 * @author  fanwl
 *
 * Copyright (c) 2019 Winner Microelectronics Co., Ltd.
 */
#include <stdint.h>
#include "pins_arduino.h"
#include "wiring_digital.h"

extern uint32_t micros(void);
extern unsigned long xTaskGetTickCount( void );

#define WAIT_FOR_PIN_STATE(state) \
    while (digitalRead(pin) != (state)) { \
        if (micros() - startMicros > timeout) { \
            return 0; \
        } \
    }

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
unsigned long pulseIn(uint8_t pin, uint8_t state, unsigned long timeout)
{
    uint32_t startMicros = micros();
    
    WAIT_FOR_PIN_STATE(!state);
    WAIT_FOR_PIN_STATE(state);
    uint32_t start = micros();
    WAIT_FOR_PIN_STATE(!state);

    return (micros() - start);
}
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
unsigned long pulseInLong(uint8_t pin, uint8_t state, unsigned long timeout)
{
    return pulseIn(pin, state, timeout);
}
