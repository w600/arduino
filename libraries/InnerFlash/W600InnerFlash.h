/**
 * @file    W600InnerFlash.h
 *
 * @brief   WiFiInner Flash Module
 *
 * @author  WinnerMicro
 *
 * Copyright (c) 2019 Winner Microelectronics Co., Ltd.
 */

#ifndef _INNER_FLASH_H_
#define _INNER_FLASH_H_

#include <stdio.h>
#include <stdint.h>

extern "C" {
#include "wm_type_def.h"
}

class W600InnerFlashClass
{
    public:
	/**
	 * @brief      This function is used to inialize inner flash driver
	 *
	 *
	 * @param[in]   None
	 *
	 * @param[out] None
	 *
	 * @return	    None
	 * 
	 * @note 
	 */	
	int  begin();
	/**
	 * @brief      This function is used to erase flash by sectors
	 *
	 *
	 * @param[in]   sector: 240-251, other sector can not be erased for special usage
	 *
	 * @param[out]  None
	 *
	 * @return      None
	 * 
	 * @note        Only sectors from 240 to 251 can be used to user operation. 
	 */
    bool flashEraseSector(uint32_t sector);
	/**
	 * @brief      This function is used to write data to flash 
	 *
	 *
	 * @param[in]   offset: range from 0xF0000 to 0xFBFFF
	 *
	 * @param[in]   data  : data to be written to flash
	 *
	 * @param[in]   size  : data length to be written to flash
	 *
	 * @param[out]  None
	 *
	 * @return      None
	 * 
	 * @note        Only area from 0xF0000 to 0xFBFFF can be written. 
	 */
     bool flashWrite(uint32_t offset, uint8_t *data, size_t size);
	/**
	 * @brief      This function is used to read data from flash 
	 *
	 *
	 * @param[in]       offset: range from 0x00000 to 0xFFFFF
	 *
	 * @param[in/out]   data  : data to be read from flash
	 *
	 * @param[in]       size  :  data length to be written to flash
	 *
	 * @param[out]      None
	 *
	 * @return          None
	 * 
	 * @note          
	 */
    bool flashRead(uint32_t offset, uint8_t *data, size_t size);

};

/** W600InnerFlashClass instance */
extern W600InnerFlashClass  InnerFlash;
#endif