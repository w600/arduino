/**
 * @file    SPI.h
 *
 * @brief   SPI Driver Module
 *
 * @author  fanwl
 *
 * Copyright (c) 2019 Winner Microelectronics Co., Ltd.
 */
#ifndef _SPI_H_INCLUDED
#define _SPI_H_INCLUDED

#include "Arduino.h"
#include <stdio.h>

extern "C" {
#include "wm_hostspi.h"
#include "wm_gpio_afsel.h"
#include "wm_spi_hal.h"
}

#define SPI_SPEED_CLOCK_DEFAULT     2000000

// SPI mode parameters for SPISettings
#define SPI_MODE0 0x00
#define SPI_MODE1 0x01
#define SPI_MODE2 0x02
#define SPI_MODE3 0x03

class SPISettings {
public:
    SPISettings(uint32_t clock, BitOrder bitOrder, uint8_t dataMode) {
      clk = clock;

      bOrder = bitOrder;

      if(SPI_MODE0 == dataMode) {
        dMode = TLS_SPI_MODE_0;
      } else if(SPI_MODE1 == dataMode) {
        dMode = TLS_SPI_MODE_1;
      } else if(SPI_MODE2 == dataMode) {
        dMode = TLS_SPI_MODE_2;
      } else if(SPI_MODE3 == dataMode) {
        dMode = TLS_SPI_MODE_3;
      }

    }
    SPISettings() {
      clk = SPI_SPEED_CLOCK_DEFAULT;
      bOrder = MSBFIRST;
      dMode = TLS_SPI_MODE_0;
    }
private:
    uint32_t clk;       //specifies the spi bus maximum clock speed
    BitOrder bOrder;    //bit order (MSBFirst or LSBFirst)
    uint8_t dMode;      //one of the data mode
                        //Mode          Clock Polarity (CPOL)   Clock Phase (CPHA)
                        //SPI_MODE0             0                     0
                        //SPI_MODE1             0                     1
                        //SPI_MODE2             1                     0
                        //SPI_MODE3             1                     1
    friend class SPIClass;
};

class SPIClass {
public:

/**
 * @defgroup SPI_library SPI_library
 * @brief SPI library
 */

/**
 * @addtogroup SPI_library
 * @{
 */

/**
 * @defgroup SPI_library SPI_library
 * @brief SPI library
 */

/**
 * @addtogroup SPI_library
 * @{
 */

    void begin(void);
    void end(void);
    
    void beginTransaction(SPISettings settings);
    void endTransaction(void);

    uint8_t transfer(uint8_t _data);
    uint16_t transfer16(uint16_t _data);
    void transferWrite(void *_buf, size_t _count);
    void transferRead(void *_buf, size_t _count);
    void transfer(void *_buf, size_t _count);
    void transfer(void *_bufout, void *_bufin, size_t _count);

    void setBitOrder(BitOrder);
    void setDataMode(uint8_t _mode);
    void setFrequency(uint32_t freq);

/**
 * @}
 */

/**
 * @}
 */

private:
    SPISettings spiSettings;
};

extern SPIClass SPI;

#endif
