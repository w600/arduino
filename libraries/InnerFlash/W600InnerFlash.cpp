/**
 * @file    W600InnerFlash.cpp
 *
 * @brief   WiFi InnerFlash operation Module
 *
 * @author  WinnerMicro
 *
 * Copyright (c) 2019 Winner Microelectronics Co., Ltd.
 */

#include <string.h>
#include <stdio.h>

#include "W600InnerFlash.h"

extern "C" {
#include "wm_internal_flash.h"
#include "wm_params.h"
}

/** W600InnerFlashClass instance definition*/
W600InnerFlashClass  InnerFlash;

/** Define Flash base address*/
#define INNER_FLASH_BASE_ADDR (0x8000000)

/** Define Flash Sector size*/
#define INNER_FLASH_SECTOR_SIZE  (0x1000)

/**
 * @brief      This function is used to inialize inner flash driver
 *
 *
 * @param[in]    None
 *
 * @param[out]  None
 *
 * @return	     None
 * 
 * @note 
 */
int W600InnerFlashClass::begin()
{
	int rc = tls_fls_init();
	return rc == 0;
}

/**
 * @brief       This function is used to erase flash by sectors
 *
 *
 * @param[in]    sector: 240-251, other sector can not be erased for special usage
 *
 * @param[out]  None
 *
 * @return         None
 * 
 * @note           Only sectors from 240 to 251 can be used to user operation. 
 */
bool W600InnerFlashClass::flashEraseSector(uint32_t sector)
{
    int rc = tls_fls_erase((sector)
                | (INNER_FLASH_BASE_ADDR / INNER_FLASH_SECTOR_SIZE));
    return rc == 0;
}

/**
 * @brief      This function is used to write data to flash 
 *
 *
 * @param[in]    offset :range from 0xF0000 to 0xFBFFF
 *
 * @param[in]    data   : data to be written to flash
 *
 * @param[in]    size   : data length to be written to flash
 *
 * @param[out]  None
 *
 * @return	     None
 * 
 * @note           Only area from 0xF0000 to 0xFBFFF can be written. 
 */
bool W600InnerFlashClass::flashWrite(uint32_t offset, uint8_t *data, size_t size)
{
    int rc = tls_fls_write(offset | INNER_FLASH_BASE_ADDR,
                (uint8_t*)data, size);
    return rc == 0;
}

/**
 * @brief       This function is used to read data from flash 
 *
 *
 * @param[in]          offset: range from 0x00000 to 0xFFFFF
 *
 * @param[in/out]    data  : data to be read from flash
 *
 * @param[in]          size  :  data length to be written to flash
 *
 * @param[out] 	     None
 *
 * @return               None
 * 
 * @note          
 */
bool W600InnerFlashClass::flashRead(uint32_t offset, uint8_t *data, size_t size)
{
    int rc = tls_fls_read(offset | INNER_FLASH_BASE_ADDR,
                (uint8_t*)data, size);
    return rc == 0;
}


