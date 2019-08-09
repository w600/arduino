/**
 * @file    Wiring_time.c
 *
 * @brief   W600 time delay Module
 *
 * @author  WinnerMicro
 *
 * Copyright (c) 2019 Winner Microelectronics Co., Ltd.
 */

#include "wm_osal.h"
#include "stdint.h"
#include "wm_regs.h"
#include "wiring_time.h"

static inline uint32_t LL_SYSTICK_IsActiveCounterFlag(void)
{
  return ((SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk) == (SysTick_CTRL_COUNTFLAG_Msk));
}

/**
 * @brief   This function is used to get milliseconds since system startup
 * 
 * @return  milliseconds
 *
 * @note    none
 */
unsigned int millis(void)
{
    return tls_os_get_time()*2;
}
/**
 * @brief   Returns the number of microseconds since the Arduino board began running the current program.
 * 
 * @return  microseconds
 *
 * @note    none
 */
uint32_t micros(void)
{
  /* Ensure COUNTFLAG is reset by reading SysTick control and status register */
  LL_SYSTICK_IsActiveCounterFlag();
  uint32_t m = tls_os_get_time();
  uint32_t u = SysTick->LOAD - SysTick->VAL;
  if(LL_SYSTICK_IsActiveCounterFlag) {
    m = tls_os_get_time();
    u = SysTick->LOAD - SysTick->VAL;
  }
  return (uint32_t)( m * 2000 + (u * 2000) / SysTick->LOAD);
}

/**
 * @brief   This function is used to delay by milliseconds
 * 
 * @param[in] ms: delay time, unit: ms
 *
 * @return  none
 *
 * @note    none
 */
void delay(unsigned long ms)
{
	if (ms < 2)
	{
		ms = 2;
	}
    tls_os_time_delay(ms/2);
}

/**
 * @brief   This function is to delay by micro seconds.
 * 
 * @param[in] us: micro seconds
 *
 * @return  none
 *
 * @note    none
 */
void delayMicroseconds(unsigned int us)
{
    unsigned int value = 1;
    unsigned int RegValue;
    volatile int i = 0, j = 0;

    RegValue = *(unsigned int *)(HR_CLK_DIV_CTL);
    switch (RegValue & 0x0000000F)
    {
	    case 0x02: //80M
	        value = us * 2;
	        break;
	    case 0x04: //40M
	        value = us;
	        break;
    }
    for (i = 0; i < value; i++)
    {
        for (j = 0; j < 7; j++)
        {
        }
    }
}
