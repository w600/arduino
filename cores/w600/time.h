
/**
 * @file time.h 
 *
 * @brief   ntp time Module
 *
 * @author  muqing
 *
 * Copyright (c) 2019 Winner Microelectronics Co., Ltd.
 */

#ifndef TIME_H_
#define TIME_H_


#ifdef __cplusplus
extern "C" {
#endif

#define time_t long

/**
 * @defgroup time time
 * @brief time
 */

/**
 * @addtogroup time
 * @{
 */

/**
 * @defgroup time time
 * @brief time
 */

/**
 * @addtogroup time
 * @{
 */

/**
 * @brief         	This function is used to config ntp param
 *
 * @param[in]		timezone		Beijing is the east 8th district[8].
 * @param[in] 	daylightOffset_sec     sec offset, Can correct network delay.
 * @param[in] 	server1    NTP server domain name or IP address.
 * @param[in] 	server2    NTP server domain name or IP address.
 * @param[in] 	server3    NTP server domain name or IP address.
 *
 * @param[out]	None
 *
 * @return 		None 
 * 
 * @note 
 */ 
void configTime(int timezone, int daylightOffset_sec, const char* server1, const char* server2, const char* server3);

/**
 * @brief         	This function is used to get the time after calibration.
 *
 * @param[out] 	*t      The variable pointer to get the time value, Unit seconds.
 *
 * @retval 		the ntp time value,  Unit seconds.
 * 
 * @note 
 */ 
time_t time(time_t * t);

#ifdef __cplusplus
}
#endif

#endif /* TIME_H_ */
