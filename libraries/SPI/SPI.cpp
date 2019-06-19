/**
 * @file    SPI.cpp
 *
 * @brief   SPI Driver Module
 *
 * @author  fanwl
 *
 * Copyright (c) 2019 Winner Microelectronics Co., Ltd.
 */
#include "SPI.h"

SPIClass SPI;

/**
 * @brief          Initialize the SPI instance.
 *
 * @param[in]      none
 * 
 * @return         none
 * 
 * @note           none
 */
void SPIClass::begin(void)
{
	wm_spi_cs_config(WM_IO_PB_15);
	wm_spi_ck_config(WM_IO_PB_16);
	wm_spi_di_config(WM_IO_PB_17);
	wm_spi_do_config(WM_IO_PB_18);
}

/**
 * @brief          This function should be used to configure the SPI instance in case you
 *                 don't use the default parameters set by the begin() function.
 *
 * @param[in]      settings     SPI settings(clock speed, bit order, data mode).
 * 
 * @return         none
 * 
 * @note           none
 */
void SPIClass::beginTransaction(SPISettings settings)
{
    tls_spi_setup(settings.dMode, TLS_SPI_CS_LOW, settings.clk);

    if (settings.bOrder == MSBFIRST)
    {
        spi_set_endian(1);
    }
    else
    {
        spi_set_endian(0);
    }
}

/**
 * @brief          settings associated to the SPI instance.
 *
 * @param[in]      none
 * 
 * @return         none
 * 
 * @note           none
 */
void SPIClass::endTransaction(void)
{
}

/**
 * @brief          Deinitialize the SPI instance and stop it.
 *
 * @param[in]      none
 * 
 * @return         none
 * 
 * @note           none
 */
void SPIClass::end(void)
{
    tls_gpio_cfg(WM_IO_PB_15, WM_GPIO_DIR_OUTPUT, WM_GPIO_ATTR_PULLLOW);
    tls_gpio_cfg(WM_IO_PB_16, WM_GPIO_DIR_OUTPUT, WM_GPIO_ATTR_PULLLOW);
    tls_gpio_cfg(WM_IO_PB_17, WM_GPIO_DIR_OUTPUT, WM_GPIO_ATTR_PULLLOW);
    tls_gpio_cfg(WM_IO_PB_18, WM_GPIO_DIR_OUTPUT, WM_GPIO_ATTR_PULLLOW);
}

/**
 * @brief          Deprecated function.
 *                 Configure the bit order: MSB first or LSB first.
 *
 * @param[in]       _bitOrder   MSBFIRST or LSBFIRST
 * 
 * @return         none
 * 
 * @note           none
 */
void SPIClass::setBitOrder(BitOrder _bitOrder)
{
    if (_bitOrder == MSBFIRST)
    {
        spi_set_endian(1);
    }
    else
    {
        spi_set_endian(0);
    }
}

/**
 * @brief          Deprecated function.
 *                 Configure the data mode (clock polarity and clock phase)
 *
 * @param[in]      _mode     SPI_MODE0, SPI_MODE1, SPI_MODE2 or SPI_MODE3
 * 
 * @return         none
 * 
 * @note           none
 */
void SPIClass::setDataMode(uint8_t _mode)
{
    uint8_t mode;

    if (SPI_MODE0 == _mode)
    {
        mode = TLS_SPI_MODE_0;
    }
    else if (SPI_MODE1 == _mode)
    {
        mode = TLS_SPI_MODE_1;
    }
    else if (SPI_MODE2 == _mode)
    {
        mode = TLS_SPI_MODE_2;
    }
    else if (SPI_MODE3 == _mode)
    {
        mode = TLS_SPI_MODE_3;
    }
    spi_set_mode(mode);
}
/**
 * @brief           Configure the spi frequency.
 *
 * @param[in]      freq   max 20MHz
 * 
 * @return         none
 * 
 * @note           none
 */
void SPIClass::setFrequency(uint32_t freq)
{
    spi_set_sclk(freq);
}

/**
 * @brief          Transfer one byte on the SPI bus.
 *
 * @param[in]      data     byte to send.
 * 
 * @return         byte     received from the slave
 * 
 * @note           none
 */
uint8_t SPIClass::transfer(uint8_t data)
{
    uint8_t rxdata = 0;

    tls_spi_write(&data, 1);
    tls_spi_read(&rxdata, 1);
    return rxdata;
}

/**
 * @brief          Transfer two bytes on the SPI bus in 16 bits format.
 *
 * @param[in]      data     bytes to send.
 * 
 * @return         bytes    received from the slave in 16 bits format.
 * 
 * @note           none
 */
uint16_t SPIClass::transfer16(uint16_t data)
{
    uint16_t rxdata = 0;

    tls_spi_write((uint8_t *)&data, 2);
    tls_spi_read((uint8_t *)&rxdata, 2);

    return rxdata;
}

/**
 * @brief          send several bytes.
 *
 * @param[in]      _buf     pointer to the bytes to send.
 * 
 * @param[in]      _count   number of bytes to send
 * 
 * @return         none
 * 
 * @note           none
 */
void SPIClass::transferWrite(void *_buf, size_t _count)
{
    tls_spi_write((uint8_t *)_buf, _count);
}
/**
 * @brief          receive several bytes.
 *
 * @param[in]      _buf     pointer to the bytes to received.
 * 
 * @param[in]      _count   number of bytes to received
 * 
 * @return         none
 * 
 * @note           none
 */
void SPIClass::transferRead(void *_buf, size_t _count)
{
    tls_spi_read((uint8_t *)_buf, _count);
}
/**
 * @brief          Transfer several bytes. Only one buffer used to send and receive data.
 *
 * @param[in]      _buf      pointer to the bytes to send. The bytes received are copy in
 *                           this buffer.
 * 
 * @param[in]      _count   number of bytes to send/receive
 * 
 * @return         none
 * 
 * @note           none
 */
void SPIClass::transfer(void *_buf, size_t _count)
{
    tls_spi_write((uint8_t *)_buf, _count);
    tls_spi_read((uint8_t *)_buf, _count);
}

/**
 * @brief          Transfer several bytes. One buffer contains the data to send and
 *                 another one will contains the data received.
 *
 * @param[in]      _bufout      pointer to the bytes to send.
 * 
 * @param[in]      _bufin       pointer to the bytes received.
 * 
 * @param[in]      _count       number of bytes to send/receive
 * 
 * @return         none
 * 
 * @note           none
 */
void SPIClass::transfer(void *_bufout, void *_bufin, size_t _count)
{
    if (_bufout != NULL)
    {
        tls_spi_write((uint8_t *)_bufout, _count);
    }
    if (_bufin != NULL)
    {
        tls_spi_read((uint8_t *)_bufin, _count);
    }
}
