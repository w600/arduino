

/**
 * @file W600WiFiOneshot.cpp
 *
 * @brief   Winner Micro Configuration network
 *
 * @author  muqing
 *
 * Copyright (c) 2019 Winner Microelectronics Co., Ltd.
 */


#include <stdio.h>
#include <string.h>

#include "wiring_time.h"
#include "W600WiFiOneshot.h"
#include "W600WiFi.h"

extern "C" {
#include "wm_wifi.h"
#include "wm_wifi_oneshot.h"
#include "wm_mem.h"
#include "wm_osal.h"
}


/**
 * @brief         	This function is used to start oneshot configuration network
 *
 * @param[in]		None
 *
 * @param[out]	None
 *
 * @return 		None 
 * 
 * @note 
 */ 
int WiFiOneshotClass::oneshotStart()
{
	tls_wifi_set_oneshot_flag(1);
}

/**
 * @brief         	This function is used to stop oneshot configuration network
 *
 * @param[in]		None
 *
 * @param[out]	None
 *
 * @return 		None 
 * 
 * @note 
 */ 
int WiFiOneshotClass::oneshotStop()
{
	tls_wifi_set_oneshot_flag(0);
}

/**
 * @brief         	This function is used to get oneshot state
 *
 * @param[in]		None
 *
 * @param[out]	None
 *
 * @retval 		0: is in oneshot state
 *				1: is not in oneshot state
 * 
 * @note 
 */
int WiFiOneshotClass::oneshotGetState()
{
	return tls_wifi_get_oneshot_flag();
}

/**
 * @brief         	This function is used to get oneshot state
 *
 * @param[in]		mode  0: UDP MODE   1: AP+SOCKET MODE   2: AP+WEBSEVER MODE
 *							
 * @param[out]	None
 *
 * @return 		None 
 * 
 * @note 
 */
int WiFiOneshotClass::oneshotSetMode(ONESHOT_MODE mode)
{
	tls_wifi_set_oneshot_config_mode(mode);
}

/**
 * @brief         	This function is used to get oneshot mode
 *
 * @param[in]		None
 *
 * @param[out]	None
 *
 * @retval 		0: UDP MODE 
 *				1: AP+SOCKET MODE
 *				2: AP+WEBSEVER MODE
 * 
 * @note 
 */
int WiFiOneshotClass::oneshotGetMode()
{
	return tls_wifi_get_oneshot_config_mode();
}


