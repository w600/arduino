#include "twi.h"
#include "pins_arduino.h"
#include "wiring_private.h"
#include "wm_i2c.h"
#include "wm_gpio_afsel.h"


unsigned int preferred_si2c_clock = 100000;
static unsigned char twi_sda, twi_scl;
static uint32_t twi_clockStretchLimit;

/**
  * @brief  used to set frequency of i2c
  * @param[in]  freq : frequency to be set
  * @retval none
  */
void twi_setClock(unsigned int freq){
  preferred_si2c_clock = freq;
}

/**
  * @brief  Default init and setup GPIO and I2C peripheral
  * @param[in]  sda : gpio number that used as sda wire
  * @param[in]  scl : gpio number that used as scl wire
  * @retval none
  */
void twi_init(unsigned char sda, unsigned char scl){
  twi_sda = sda;
  twi_scl = scl;
  
  wm_i2c_scl_config(twi_scl);
  wm_i2c_sda_config(twi_sda);
  tls_i2c_init(preferred_si2c_clock);
}

/**
  * @brief  used to stop i2c
  * @param[in]  none
  * @retval none
  */
void twi_stop(void){
  tls_i2c_stop();
}

/**
  * @brief  used to stop i2c and return true
  * @param[in]  none
  * @retval none
  */
static bool twi_write_stop(void){
    
  twi_stop();
  tls_os_time_delay(1);
  return true;
}

/**
  * @brief  Write one byte to slave
  * @param  byte: data to be written
  * @param  ifstart: with start bits or not, 1->with, 0->without.
  * @retval status, 0->succ, 1->fail
  */
static int twi_write_byte(unsigned char byte, unsigned char ifstart) {

  int ret;

  tls_i2c_write_byte(byte, ifstart);
  ret = tls_i2c_wait_ack();
  return ret;
}

/**
 * @brief	get the data stored in data register of I2C module
 * @param[in] ifack	when one send ack after reading the data register,when zero don't
 * @param[in] ifstop when one send stop signal after read, when zero do not send stop
 * @retval	the received data 
 */
static unsigned char twi_read_byte(bool nack) {

  unsigned char byte = 0;
  bool ack = !nack;
  
  if(ack)
	byte = tls_i2c_read_byte(ack, 0);
  else
	byte = tls_i2c_read_byte(ack, 1);
  return byte;
}

/**
  * @brief  Write bytes to slave device
  * @param  address: device address
  * @param  buf: data to be written
  * @param  len: data bytes to be written
  * @param  sendStop: with stop bits or not, 1->with, 0->without.
  * @retval status, 0->succ, others->fail
  */
unsigned char twi_writeTo(unsigned char address, unsigned char * buf, unsigned int len, unsigned char sendStop){
  unsigned int i;

  if(twi_write_byte(address, 1)) {
    if (sendStop) 
      twi_write_stop();
    return 2; //received NACK on transmit of address
  }
  for(i=0; i<len; i++) {
    if(twi_write_byte(buf[i], 0)) {
      if (sendStop) 
        twi_write_stop();
      return 3;//received NACK on transmit of data
    }
  }
  if(sendStop) 
    twi_write_stop();

  return 0;
}

/**
  * @brief  Read bytes from slave device
  * @param  address: device address
  * @param  buf: buffer to hold the bytes to be read
  * @param  len: bytes to be read
  * @param  sendStop: with stop bits or not, 1->with, 0->without.
  * @retval status, 0->succ, others->fail
  */
unsigned char twi_readFrom(unsigned char address, unsigned char* buf, unsigned int len, unsigned char sendStop){
  unsigned int i;

  if(twi_write_byte(address, 1)) {
    if (sendStop) 
      twi_write_stop();
    return 2;//received NACK on transmit of address
  }
  for(i=0; i<(len-1); i++) 
    buf[i] = twi_read_byte(false);
  buf[len-1] = twi_read_byte(true);

  return 0;
}

/**
  * @brief  not used for now
  * @param[in]  none
  * @retval none
  */
uint8_t twi_status() {           
    return I2C_OK;                       //all ok
}

