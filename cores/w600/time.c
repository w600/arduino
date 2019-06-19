/**
 * @file time.h 
 *
 * @brief   ntp time Module
 *
 * @author  muqing
 *
 * Copyright (c) 2019 Winner Microelectronics Co., Ltd.
 */

#include <string.h>

#include "wm_wifi.h"
#include "wm_ntp.h"
#include "wm_netif.h"
#include "time.h"

#define UTC_NTP 2208988800U     /* 1970 - 1900 ;Äê »»Ëã³ÉÃë */

int time_timezone = 8*3600;
int time_dayoff = 0;

static int isNetworkOk(void)
{
	struct tls_ethif* etherIf = tls_netif_get_ethif();

	return (WM_WIFI_JOINED == tls_wifi_get_state()
            && etherIf != NULL
            && etherIf->ip_addr.addr != 0);
}

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
void configTime(int timezone, int daylightOffset_sec,
        const char* server1,
        const char* server2,
        const char* server3)
{
	tls_ntp_set_server((char *)server1, 0);
	tls_ntp_set_server((char *)server1, 1);
	tls_ntp_set_server((char *)server1, 2);

	time_timezone = timezone;
	time_dayoff = daylightOffset_sec;
}

/**
 * @brief         	This function is used to get the time after calibration.
 *
 * @param[out] 	*t      The variable pointer to get the time value, Unit seconds.
 *
 * @retval 		the ntp time value,  Unit seconds.
 * 
 * @note 
 */ 
time_t time(time_t * t)
{
	time_t seconds;

    if(1 != isNetworkOk())
    {
       *t = -1;
       return -1;
    }

    seconds = tls_ntp_client();
	seconds = seconds
                - 8*3600
                + UTC_NTP
                + time_timezone
                + time_dayoff;
		
    if (t)
    {
        *t = seconds;
    }
    return seconds;
}
