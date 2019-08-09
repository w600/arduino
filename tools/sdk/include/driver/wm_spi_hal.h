/***************************************************************************** 
* 
* File Name : wm_spi_hal.h 
* 
* Description: host spi Driver Module 
* 
* Copyright (c) 2014 Winner Microelectronics Co., Ltd. 
* All rights reserved. 
* 
* Author : dave
* 
* Date : 2014-6-6
*****************************************************************************/ 
#include "wm_regs.h"
#include "list.h"
#include "wm_hostspi.h"
#include "wm_cpu.h"


static __inline void spi_set_mode(uint8_t mode);


static __inline void spi_set_mode(uint8_t mode)
{
	uint32_t reg_val;

	reg_val = tls_reg_read32(HR_SPI_SPICFG_REG);
	
	switch (mode) {
		case TLS_SPI_MODE_0:
			reg_val &= ~(0x03U);
			reg_val |= (SPI_SET_CPOL(0) | SPI_SET_CPHA(0));
			break;

		case TLS_SPI_MODE_1:
			reg_val &= ~(0x03U);
			reg_val |= (SPI_SET_CPOL(0) | SPI_SET_CPHA(1));
			break;

		case TLS_SPI_MODE_2:
			reg_val &= ~(0x03U);
			reg_val |= (SPI_SET_CPOL(1) | SPI_SET_CPHA(0));
			break;

		case TLS_SPI_MODE_3:
			reg_val &= ~(0x03U);
			reg_val |= (SPI_SET_CPOL(1) | SPI_SET_CPHA(1));
			break;

		default:
			break;
	}

	tls_reg_write32(HR_SPI_SPICFG_REG, reg_val);
}

static __inline void spi_set_endian(uint8_t endian)
{
	uint32_t reg_val;

	reg_val = tls_reg_read32(HR_SPI_SPICFG_REG);

	if (endian == 0) {
		reg_val &= ~(0x01U << 3);
		reg_val |= SPI_LITTLE_ENDIAN;
	} else if(endian == 1) {
		reg_val &= ~(0x01U << 3);
		reg_val |= SPI_BIG_ENDIAN;
	}

	tls_reg_write32(HR_SPI_SPICFG_REG, reg_val);
}

static __inline void spi_set_chipselect_mode(uint8_t cs_active)
{
	uint32_t reg_val;

	reg_val = tls_reg_read32(HR_SPI_CHCFG_REG);

	if (cs_active == 0) {
		reg_val &= ~(0x01U << 2);
		reg_val |= SPI_CS_LOW;
	} else if(cs_active == 1) {
		reg_val &= ~(0x01U << 2);
		reg_val |= SPI_CS_HIGH;
	}

	tls_reg_write32(HR_SPI_CHCFG_REG, reg_val);
}

static __inline void spi_clear_fifo(void)
{
	uint32_t reg_val;

	reg_val = tls_reg_read32(HR_SPI_CHCFG_REG);
	
	reg_val |= SPI_CLEAR_FIFOS;

	tls_reg_write32(HR_SPI_CHCFG_REG, reg_val);
}

static __inline void spi_set_rx_channel(uint8_t on_off)
{
	uint32_t reg_val;

	reg_val = tls_reg_read32(HR_SPI_CHCFG_REG);

	if (on_off == 0) {
		reg_val &= ~(0x01U << 20);
		reg_val |= SPI_RX_CHANNEL_OFF;
	} else if(on_off == 1) {
		reg_val &= ~(0x01U << 20);
		reg_val |= SPI_RX_CHANNEL_ON;
	}

	tls_reg_write32(HR_SPI_CHCFG_REG, reg_val);
}

static __inline void spi_set_tx_channel(uint8_t on_off)
{
	uint32_t reg_val;

	reg_val = tls_reg_read32(HR_SPI_CHCFG_REG);

	if (on_off == 0) {
		reg_val &= ~(0x01U << 19);
		reg_val |= SPI_TX_CHANNEL_OFF;
	} else if(on_off == 1) {
		reg_val &= ~(0x01U << 19);
		reg_val |= SPI_TX_CHANNEL_ON;
	}

	tls_reg_write32(HR_SPI_CHCFG_REG, reg_val);
}

static __inline void spi_set_sclk_length(uint16_t sclk_num, uint8_t invalid_rx_sclk_num)
{
	uint32_t reg_val;

	reg_val = tls_reg_read32(HR_SPI_CHCFG_REG);

	reg_val &= ~((0xffU << 23) | (0xffff << 3));
	reg_val |= SPI_VALID_CLKS_NUM(sclk_num) | SPI_RX_INVALID_BITS(invalid_rx_sclk_num);

	tls_reg_write32(HR_SPI_CHCFG_REG, reg_val);
}

static __inline void spi_force_cs_out(uint8_t enable)
{
	uint32_t reg_val;

	reg_val = tls_reg_read32(HR_SPI_CHCFG_REG);

	if (enable) {
		reg_val |= SPI_FORCE_SPI_CS_OUT;
	} else {
		reg_val &= ~SPI_FORCE_SPI_CS_OUT;
	}

	tls_reg_write32(HR_SPI_CHCFG_REG, reg_val);
}

static __inline void spi_sclk_start(void)
{
	uint32_t reg_val;

	reg_val = tls_reg_read32(HR_SPI_CHCFG_REG);

	reg_val |= SPI_START;

	tls_reg_write32(HR_SPI_CHCFG_REG, reg_val);
}

static __inline void spi_set_sclk(uint32_t fclk)
{
	uint32_t reg_val;
	tls_sys_clk sysclk;

	tls_sys_clk_get(&sysclk);			

	reg_val = tls_reg_read32(HR_SPI_CLKCFG_REG);		
	
	reg_val &= ~(0xffffU);
	reg_val |= sysclk.apbclk*UNIT_MHZ/(fclk*2) - 1;

	tls_reg_write32(HR_SPI_CLKCFG_REG, reg_val);
}

static __inline void spi_set_tx_trigger_level(uint8_t level)
{
	uint32_t reg_val;

	reg_val = tls_reg_read32(HR_SPI_MODECFG_REG);

	reg_val &= ~(0x07U << 2);
	reg_val |= SPI_TX_TRIGGER_LEVEL(level);

	tls_reg_write32(HR_SPI_MODECFG_REG, reg_val);
}

static __inline void spi_set_rx_trigger_level(uint8_t level)
{
	uint32_t reg_val;

	reg_val = tls_reg_read32(HR_SPI_MODECFG_REG);

	reg_val &= ~(0x07U << 6);
	reg_val |= SPI_RX_TRIGGER_LEVEL(level);

	tls_reg_write32(HR_SPI_MODECFG_REG, reg_val);
}

static __inline void spi_set_timeout(uint32_t timeout, uint8_t enable)
{
	uint32_t reg_val;

	reg_val = SPI_TIME_OUT(timeout);
	reg_val |= enable ? SPI_TIMER_EN : 0;

	tls_reg_write32(HR_SPI_TIMEOUT_REG, reg_val);
}

static __inline void spi_get_status(uint8_t *busy, uint8_t *rx_fifo_level, uint8_t *tx_fifo_level)
{
	uint32_t reg_val;

	reg_val = tls_reg_read32(HR_SPI_STATUS_REG);

	if (busy) {*busy = SPI_IS_BUSY(reg_val);}
	if (rx_fifo_level) {*rx_fifo_level = SPI_GET_RX_FIFO_CNT(reg_val);}
	if (tx_fifo_level) {*tx_fifo_level = 32 - SPI_GET_TX_FIFO_CNT(reg_val);}
}

static __inline uint32_t spi_int_mask(void)
{
	uint32_t reg_val;

	reg_val = tls_reg_read32(HR_SPI_INT_MASK_REG);

	return reg_val & SPI_INT_MASK_ALL;
}

static __inline void spi_mask_int(uint32_t mask)
{
	uint32_t reg_val;

	reg_val = tls_reg_read32(HR_SPI_INT_MASK_REG);

	reg_val |= mask & SPI_INT_MASK_ALL;

	tls_reg_write32(HR_SPI_INT_MASK_REG, reg_val);
}

static __inline void spi_unmask_int(uint32_t mask)
{
	uint32_t reg_val;

	reg_val = tls_reg_read32(HR_SPI_INT_MASK_REG);

	reg_val &= ~(mask & SPI_INT_MASK_ALL);

	tls_reg_write32(HR_SPI_INT_MASK_REG, reg_val);
} 

static __inline uint32_t spi_get_int_status(void)
{
	uint32_t reg_val;

	reg_val = tls_reg_read32(HR_SPI_INT_STATUS_REG);

	return reg_val;
}

static __inline void spi_clear_int_status(uint32_t int_srcs)
{
	uint32_t reg_val;

	reg_val = tls_reg_read32(HR_SPI_INT_STATUS_REG);

	reg_val &= ~(int_srcs & SPI_INT_CLEAR_ALL);
	reg_val |= int_srcs & SPI_INT_CLEAR_ALL;

	tls_reg_write32(HR_SPI_INT_STATUS_REG, reg_val);
}

static __inline void spi_data_put(uint32_t data)
{
	tls_reg_write32(HR_SPI_TXDATA_REG, data);
}

static __inline uint32_t spi_data_get(void)
{
	return tls_reg_read32(HR_SPI_RXDATA_REG);
}

