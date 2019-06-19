/**
 * @file    twi.h
 *
 * @brief   twi header
 *
 * @author  
 *
 * Copyright (c) 2019 Winner Microelectronics Co., Ltd.
 */

#ifndef SI2C_h
#define SI2C_h
#include "Arduino.h"

#ifdef __cplusplus
extern "C" {
#endif

#define I2C_OK                      0
#define I2C_SCL_HELD_LOW            1
#define I2C_SCL_HELD_LOW_AFTER_READ 2
#define I2C_SDA_HELD_LOW            3
#define I2C_SDA_HELD_LOW_AFTER_INIT 4

#define PIN_WIRE_SCL (WM_IO_PB_13)
#define PIN_WIRE_SDA (WM_IO_PB_14)

/**
 * @defgroup I2C I2C
 * @brief I2C
 */

/**
 * @addtogroup I2C
 * @{
 */

/**
 * @defgroup I2C I2C
 * @brief I2C
 */

/**
 * @addtogroup I2C
 * @{
 */

/**
  * @brief  Default init and setup GPIO and I2C peripheral
  * @param[in]  sda : gpio number that used as sda wire
  * @param[in]  scl : gpio number that used as scl wire
  * @retval none
  */
void twi_init(unsigned char sda, unsigned char scl);

/**
  * @brief  used to stop i2c
  * @param[in]  none
  * @retval none
  */
void twi_stop(void);

/**
  * @brief  used to set frequency of i2c
  * @param[in]  freq : frequency to be set
  * @retval none
  */
void twi_setClock(unsigned int freq);

void twi_setClockStretchLimit(uint32_t limit);

/**
  * @brief  Write bytes to slave device
  * @param  address: device address
  * @param  buf: data to be written
  * @param  len: data bytes to be written
  * @param  sendStop: with stop bits or not, 1->with, 0->without.
  * @retval status, 0->succ, others->fail
  */
uint8_t twi_writeTo(unsigned char address,
            unsigned char * buf, unsigned int len, unsigned char sendStop);
			
/**
  * @brief  Read bytes from slave device
  * @param  address: device address
  * @param  buf: buffer to hold the bytes to be read
  * @param  len: bytes to be read
  * @param  sendStop: with stop bits or not, 1->with, 0->without.
  * @retval status, 0->succ, others->fail
  */
uint8_t twi_readFrom(unsigned char address,
            unsigned char * buf, unsigned int len, unsigned char sendStop);

/**
  * @brief  not used for now
  * @param[in]  none
  * @retval none
  */			
uint8_t twi_status();

#ifdef __cplusplus
}
#endif

#endif