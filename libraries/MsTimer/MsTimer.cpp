/**
 * @file    MsTimer.cpp
 *
 * @brief   MsTimer Driver Module
 *
 * @author  fanwl
 *
 * Copyright (c) 2019 Winner Microelectronics Co., Ltd.
 */
#include <MsTimer.h>

volatile unsigned char MsTimer1::timer_id;
volatile unsigned char MsTimer2::timer_id;

/**
 * @brief          this function sets a time on ms for the overflow.
 *
 * @param[in]      ms    gpio pin
 * 
 * @param[in]      f     callback function
 * 
 * @return         none
 * 
 * @note           none
 */
void MsTimer1::set(unsigned long ms, void (*f)()) {

    struct tls_timer_cfg timer_cfg;
    
    timer_cfg.unit = TLS_TIMER_UNIT_MS;
    timer_cfg.timeout = ms;
    timer_cfg.is_repeat = 1;
    timer_cfg.callback = (tls_timer_irq_callback)f;
    timer_cfg.arg = NULL;
    timer_id = tls_timer_create(&timer_cfg);
}
/**
 * @brief          enables the timer1.
 *
 * @param[in]      none
 * 
 * @return         none
 * 
 * @note           none
 */
void MsTimer1::start() {

    tls_timer_start(timer_id);
}
/**
 * @brief          disable the timer1.
 *
 * @param[in]      none
 * 
 * @return         none
 * 
 * @note           none
 */
void MsTimer1::stop() {

    tls_timer_stop(timer_id);
}
/**
 * @brief          this function sets a time on ms for the overflow.
 *
 * @param[in]      ms    gpio pin
 * 
 * @param[in]      f     callback function
 * 
 * @return         none
 * 
 * @note           none
 */
void MsTimer2::set(unsigned long ms, void (*f)()) {

    struct tls_timer_cfg timer_cfg;
    
    timer_cfg.unit = TLS_TIMER_UNIT_MS;
    timer_cfg.timeout = ms;
    timer_cfg.is_repeat = 1;
    timer_cfg.callback = (tls_timer_irq_callback)f;
    timer_cfg.arg = NULL;
    timer_id = tls_timer_create(&timer_cfg);
}
/**
 * @brief          enables the timer2.
 *
 * @param[in]      none
 * 
 * @return         none
 * 
 * @note           none
 */
void MsTimer2::start() {

    tls_timer_start(timer_id);
}
/**
 * @brief          disable the timer2.
 *
 * @param[in]      none
 * 
 * @return         none
 * 
 * @note           none
 */
void MsTimer2::stop() {

    tls_timer_stop(timer_id);
}


