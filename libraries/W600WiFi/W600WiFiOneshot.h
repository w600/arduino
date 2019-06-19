
/**
 * @file W600WiFiOneshot.h 
 *
 * @brief   Winner Micro Configuration network
 *
 * @author  muqing
 *
 * Copyright (c) 2019 Winner Microelectronics Co., Ltd.
 */


#ifndef _WIRING_WIFIONESHOT_H_
#define _WIRING_WIFIONESHOT_H_

#include <stdint.h>

enum ONESHOT_MODE {  
        ONESHOT_UDP  = 0,
        ONESHOT_SOCKET = 1,			/*AP+socket*/
        ONESHOT_WEBSERVER = 2,		/*AP+WEBSERVER*/
};

class WiFiOneshotClass
{
public:
	
/**
 * @brief			This function is used to start oneshot configuration network
 *
 * @param[in]		None
 *
 * @param[out]	None
 *
 * @return		None 
 * 
 * @note 
 */ 
    int oneshotStart();

/**
 * @brief			This function is used to stop oneshot configuration network
 *
 * @param[in]		None
 *
 * @param[out]	None
 *
 * @return		None 
 * 
 * @note 
 */
	int oneshotStop();
/**
 * @brief			This function is used to get oneshot state
 *
 * @param[in]		None
 *
 * @param[out]	None
 *
 * @retval		0: is in oneshot state
 *				1: is not in oneshot state
 * 
 * @note 
 */
	int oneshotGetState();
/**
 * @brief			This function is used to get oneshot state
 *
 * @param[in]		mode  0: UDP MODE	1: AP+SOCKET MODE	2: AP+WEBSEVER MODE
 *							
 * @param[out]	None
 *
 * @return		None 
 * 
 * @note 
 */
	int oneshotSetMode(ONESHOT_MODE mode);
/**
 * @brief			This function is used to get oneshot mode
 *
 * @param[in]		None
 *
 * @param[out]	None
 *
 * @retval		0: UDP MODE 
 *				1: AP+SOCKET MODE
 *				2: AP+WEBSEVER MODE
 * 
 * @note 
 */
	int oneshotGetMode();
};

#endif
