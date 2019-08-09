/**
 * @file    wm_pwm.h
 *
 * @brief   pwm driver module
 *
 * @author  dave
 *
 * Copyright (c) 2014 Winner Microelectronics Co., Ltd.
 */
#ifndef WM_PWM_H
#define WM_PWM_H

#include "wm_type_def.h"


/** pwm channel's maximum number */
#define PWM_CHANNEL_MAX_NUM        5

/** pwm work mode for signal generate */
enum tls_pwm_out_mode
{
    WM_PWM_OUT_MODE_BRAKE = 0, /**< brake mode */
    WM_PWM_OUT_MODE_ALLSYC,    /**< all synchronous mode */
    WM_PWM_OUT_MODE_2SYC,      /**< two channel synchronous mode */
    WM_PWM_OUT_MODE_MC,        /**< complementary mode */
    WM_PWM_OUT_MODE_INDPT      /**< independent mode */
};

/** interrupt type for capture mode */
enum tls_pwm_cap_int_type{
    WM_PWM_CAP_RISING_EDGE_INT,         /**< rising edge arises the interrupt */
    WM_PWM_CAP_FALLING_EDGE_INT,        /**< falling edge arises the interrupt */
    WM_PWM_CAP_RISING_FALLING_EDGE_INT, /**< both rising edge and falling edge arise the interrupt */
    WM_PWM_CAP_DMA_INT                  /**< dma request */
};

/** pwm output status */
enum tls_pwm_out_en_state{
    WM_PWM_OUT_EN_STATE_TRI,    /**< set tristate status */
    WM_PWM_OUT_EN_STATE_OUT     /**< set output status */
};

/** pwm count mode */
enum tls_pwm_cnt_type{
    WM_PWM_CNT_TYPE_EDGE_ALLGN_CAP,     /**< edge alignment(only capture mode) */
    WM_PWM_CNT_TYPE_EDGE_ALIGN_OUT,     /**< edge alignment(only output mode) */
    WM_PWM_CNT_TYPE_CENTER_ALIGN        /**< central alignment */
};

/** pwm cycle type */
enum tls_pwm_loop_type{
    WM_PWM_LOOP_TYPE_SINGLE,    /**< single mode */
    WM_PWM_LOOP_TYPE_LOOP       /**< auto load */
};

/** pwm waveform inversion mode */
enum tls_pwm_waveform_inversion{
    WM_PWM_WAVEFORM_NOINVERSION,    /**< not inverse */
    WM_PWM_WAVEFORM_INVERSION       /**< inversion */
};

/** pwm output level in the brake mode */
enum tls_pwm_brake_out_level{
    WM_PWM_BRAKE_OUT_HIGH,          /**< output high level */
    WM_PWM_BRAKE_OUT_LOW            /**< output low  level */
};

/** pwm initial parameters */
typedef struct _pwm_init_param{
    enum tls_pwm_out_mode mode;         /**< work mode */
    uint8_t channel;                         /**< channel id 0~4 */
    uint16_t clkdiv;                         /**< clock divided value */
    uint8_t period;                          /**< period value(output frequency F = CLK/CLK_DIV/PERIOD) */
    uint8_t duty;                            /**< duty radio (range 0~255, high level or low level by out_inversion decided */
    bool dten;                          /**< enable dead zone time (ENABLE or DISABLE) */
    uint8_t dtclkdiv;                        /**< dead zone clock divided value (0~3) */
    uint8_t dtcnt;                           /**< period number of dead zone time  (0~255) */
    enum tls_pwm_cnt_type cnt_type;     /**< count type */
    enum tls_pwm_loop_type loop_type;   /**< cycle type */
    bool inverse_en;                    /**< output is inverse */
    uint8_t pnum;                            /**< generate interrupt after pnum period */
    bool pnum_int;                      /**< period interrupt is enable */
}pwm_init_param;

/**
 * @defgroup Driver_APIs Driver APIs
 * @brief Driver APIs
 */

/**
 * @addtogroup Driver_APIs
 * @{
 */

/**
 * @defgroup PWM_Driver_APIs PWM Driver APIs
 * @brief PWM driver APIs
 */

/**
 * @addtogroup PWM_Driver_APIs
 * @{
 */

/**
 * @brief          This function is used to register the pwm interrupt callback function
 *
 * @param[in]      callback     the pwm interrupt callback function
 *
 * @return         None
 *
 * @note           None
 */
void tls_pwm_isr_register(void (*callback)(void));

/**
 * @brief          This function is used to set duty radio
 *
 * @param[in]      channel    pwm channel NO.,range form 0 to 4
 * @param[in]      duty       Number of active levels
 *
 * @retval         WM_SUCCESS success
 * @retval         WM_FAILED  failed
 *
 * @note           None
 */
int tls_pwm_duty_config(uint8_t channel, uint8_t duty);

/**
 * @brief          This function is used to set frequency
 *
 * @param[in]      channel    pwm channel NO., range form 0 to 4
 * @param[in]      clkdiv     clock divider, range 0 to 65535
 * @param[in]      period     the number of the counting clock cycle
 *
 * @retval         WM_SUCCESS success
 * @retval         WM_FAILED  failed
 *
 * @note           None
 */
int tls_pwm_freq_config(uint8_t channel, uint16_t clkdiv, uint8_t period);

/**
 * @brief          This function is used to set the output mode
 *
 * @param[in]      channel    pwm channel NO., range form 0 to 4
 * @param[in]      mode       pwm work mode for signal generate
 *
 * @retval         WM_SUCCESS success
 * @retval         WM_FAILED  failed
 *
 * @note           None
 */
int tls_pwm_out_mode_config(uint8_t channel, enum tls_pwm_out_mode mode);

/**
 * @brief          This function is used to set the counting mode
 *
 * @param[in]      channel     pwm channel NO.,range form 0 to 4
 * @param[in]      cnt_type    counting mode
 *
 * @retval         WM_SUCCESS  success
 * @retval         WM_FAILED   failed
 *
 * @note           None
 */
int tls_pwm_cnt_type_config(uint8_t channel, enum tls_pwm_cnt_type cnt_type);

/**
 * @brief          This function is used to set whether to loop
 *
 * @param[in]      channel      pwm channel NO.,range form 0 to 4
 * @param[in]      loop_mode    whether to loop
 *
 * @retval         WM_SUCCESS   success
 * @retval         WM_FAILED    failed
 *
 * @note           None
 */
int tls_pwm_loop_mode_config(uint8_t channel, enum tls_pwm_loop_type loop_mode);

/**
 * @brief          This function is used to set whether to inverse the output

 *
 * @param[in]      channel    pwm channel NO.,range form 0 to 4
 * @param[in]      en         ENABLE or DISABLE
 *
 * @retval         WM_SUCCESS success
 * @retval         WM_FAILED  failed
 *
 * @note           None
 */
int tls_pwm_out_inverse_cmd(uint8_t channel, bool en);

/**
 * @brief          This function is used to set the number of period to be generated
 *
 * @param[in]      channel    pwm channel NO.,range form 0 to 4
 * @param[in]      pnum       the number of period to be generated,range from 0 to 255
 *
 * @retval         WM_SUCCESS success
 * @retval         WM_FAILED  failed
 *
 * @note           None
 */
int tls_pwm_stoptime_by_period_config(uint8_t channel, uint8_t pnum);

/**
 * @brief          This function is used to set output enable
 *
 * @param[in]      channel    pwm channel NO.,channel 0 or channel 4
 * @param[in]      en         ENABLE or DISABLE
 *
 * @retval         WM_SUCCESS success
 * @retval         WM_FAILED  failed
 *
 * @note           None
 */
int tls_pwm_output_en_cmd(uint8_t channel, bool en);

/**
 * @brief          This function is used to set the dead time
 *
 * @param[in]      channel     pwm channel NO.,channel 0 or channel 2
 * @param[in]      dten        whether enalbe the deat time, ENABLE or DISABLE
 * @param[in]      dtclkdiv    dead zone clock divider, range 0 to 3
 * @param[in]      dtcnt       the number of the counting clock cycle, range 0 to 255
 *
 * @retval         WM_SUCCESS  success
 * @retval         WM_FAILED   failed
 *
 * @note           None
 */
int tls_pwm_deadzone_config(uint8_t channel, bool dten, uint8_t dtclkdiv, uint8_t dtcnt);

/**
 * @brief          This function is used to set whether to inverse the capture input
 *
 * @param[in]      channel    pwm channel NO.,channel 0 or channel 4
 * @param[in]      en         ENABLE or DISABLE
 *
 * @retval         WM_SUCCESS success
 * @retval         WM_FAILED  failed
 *
 * @note           None
 */
int tls_pwm_capture_inverse_cmd(uint8_t channel, bool en);

/**
 * @brief          This function is used to set break mode
 *
 * @param[in]      channel    pwm channel NO.,channel 0 or channel 4
 * @param[in]      en         whether enable the break mode,ENABLE or DISABLE
 * @param[in]      brok       when break
 *
 * @retval         WM_SUCCESS success
 * @retval         WM_FAILED  failed
 *
 * @note           None
 */
int tls_pwm_brake_mode_config(uint8_t channel, bool en, enum tls_pwm_brake_out_level brok);

/**
 * @brief          This function is used to enable the capture mode
 *
 * @param[in]      channel    pwm channel NO.,channel 0 or channel 4
 *
 * @retval         WM_SUCCESS success
 * @retval         WM_FAILED  failed
 *
 * @note           None
 */
int tls_pwm_capture_mode_config(uint8_t channel);

/**
 * @brief          This function is used to set the interrupt about the number of period
 *
 * @param[in]      channel    pwm channel,range from 0 to 4
 * @param[in]      en         enble or disable
 *
 * @retval         WM_SUCCESS success
 * @retval         WM_FAILED  failed
 *
 * @note           None
 */
int tls_pwm_stoptime_irq_cmd(uint8_t channel, bool en);

/**
 * @brief          This function is used to set the interrupt about the
                   capture
 *
 * @param[in]      channel     pwm channel,channel 0 or channel 4
 * @param[in]      int_type    interrupt type
 *
 * @retval         WM_SUCCESS  success
 * @retval         WM_FAILED   failed
 *
 * @note           None
 */
int tls_pwm_capture_irq_type_config(uint8_t channel, enum tls_pwm_cap_int_type int_type);

/**
 * @brief          This function is used to initial pwm(out mode)
 *
 * @param[in]      pwm_param    structure containing the initialization parameters
 *
 * @retval         WM_SUCCESS   success
 * @retval         WM_FAILED    failed
 *
 * @note           None
 */
int tls_pwm_out_init(pwm_init_param pwm_param);

/**
 * @brief          This function is used to initial pwm(capture mode)
 *
 * @param[in]      channel       pwm channel, channel 0 or channel 4
 * @param[in]      clkdiv        clock divider, range 0 to 65535
 * @param[in]      inverse_en    whether the input signal is reversed
 * @param[in]      int_type      interrupt type
 *
 * @retval         WM_SUCCESS    success
 * @retval         WM_FAILED     failed
 *
 * @note           None
 */
int tls_pwm_cap_init(uint8_t channel, uint16_t clkdiv, bool inverse_en, enum tls_pwm_cap_int_type int_type);

/**
 * @brief          This function is used to start pwm
 *
 * @param[in]      channel    pwm channel, range from 0 to 4
 *
 * @retval         WM_SUCCESS success
 * @retval         WM_FAILED  failed
 *
 * @note           None
 */
int tls_pwm_start(uint8_t channel);

/**
 * @brief          This function is used to stop pwm
 *
 * @param[in]      channel    pwm channel no, range form 0 to 4
 * @param[in]      freq       frequency, range from 1 to 156250
 *
 * @return         None
 *
 * @note           None
 */
void tls_pwm_freq_set(uint8_t channel, uint32_t freq);

/**
 * @brief          This function is used to set duty radio
 *
 * @param[in]      channel    pwm channel NO., range form 0 to 4
 * @param[in]      duty       duty radio, range from 0 to 255
 *
 * @return         None
 *
 * @note           None
 */
void tls_pwm_duty_set(uint8_t channel, uint8_t duty);

/**
 * @brief          This function is used to initial pwm
 *
 * @param[in]      channel    pwm channel, range from 0 to 4
 * @param[in]      freq       is a pointer to frequency, freq range from 1 to 156250
 * @param[in]      duty       is a pointer to duty radio, duty range from 0 to 255
 *
 * @retval         WM_SUCCESS success
 * @retval         WM_FAILED  failed
 *
 * @note           None
 */
int tls_pwm_init(uint8_t channel,uint32_t freq, uint8_t duty, uint8_t pnum);

/**
 * @brief          This function is used to stop pwm
 *
 * @param[in]      channel    pwm channel, range from 0 to 4
 *
 * @retval         WM_SUCCESS success
 * @retval         WM_FAILED  failed
 *
 * @note           None
 */
int tls_pwm_stop(uint8_t channel);

/**
 * @}
 */

/**
 * @}
 */

#endif /* WM_PWM_H */
