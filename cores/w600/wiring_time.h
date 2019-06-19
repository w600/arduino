/**
 * @file    Wiring_time.h
 *
 * @brief   W600 time delay Module
 *
 * @author  WinnerMicro
 *
 * Copyright (c) 2019 Winner Microelectronics Co., Ltd.
 */
 

#ifndef __WIRING_TIME_H_
#define __WIRING_TIME_H_

#include "stdint.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup Math Math
 * @brief Math
 */

/**
 * @addtogroup Math
 * @{
 */

/**
 * @defgroup Math Math
 * @brief Math
 */

/**
 * @addtogroup Math
 * @{
 */

/**
 * @brief   This function is used to get milliseconds since system startup
 * 
 * @return  milliseconds
 *
 * @note    none
 */
extern unsigned int millis(void);

/**
 * @brief   Returns the number of microseconds since the Arduino board began running the current program.
 * 
 * @return  microseconds
 *
 * @note    none
 */
extern uint32_t micros(void);

/**
 * @brief   This function is used to delay by milliseconds
 * 
 * @param[in] ms: delay time, unit: ms
 *
 * @return  none
 *
 * @note    none
 */
extern void delay(unsigned long ms);

/**
 * @brief   This function is to delay by micro seconds.
 * 
 * @param[in] us: micro seconds
 *
 * @return  none
 *
 * @note    none
 */
extern void delayMicroseconds(unsigned int us);

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
