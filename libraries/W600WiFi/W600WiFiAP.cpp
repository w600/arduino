/**
 * @file W600WiFiAP.cpp
 *
 * @brief   WiFiAPClass Module
 *
 * @author Huang Leilei
 *
 * Copyright (c) 2019 Winner Microelectronics Co., Ltd.
 */
#include <stdio.h>
#include <string.h>

#include "W600WiFiAP.h"
#include "W600WiFiType.h"

extern "C" {
#include "wm_efuse.h"
#include "wm_mem.h"
#include "wm_wifi.h"
#include "wm_netif2.0.3.h"
#include "wm_osal.h"
}

#ifndef disable
#define disable 0
#endif
#ifndef enable
#define enable 1
#endif

static unsigned int _local_ip = 0x0101A8C0;    // 192.168.1.1
static char * _local_ip_str[20] = {0};
static unsigned int _gateway = 0;
static char * _gateway_str[20] = {0};
static unsigned int _subnet = 0x00FFFFFF;      // 255.255.255.0
static char * _subnet_str[20] = {0};
static char _ssid[33] = {0};
static char _passphrase[66] = {0};

static tls_os_timer_t * _sta_monitor_timer = NULL;
static u32 _total_sta_num = 0;
static unsigned char _sap_mac[64] = {0};

extern WiFiMode_t WiFiMode;


bool _set_work_mode_softap()
{
    u8 wi_protocol = 0;
    tls_param_get(TLS_PARAM_ID_WPROTOCOL, (void *)&wi_protocol, true);
    if (TLS_PARAM_IEEE80211_SOFTAP != wi_protocol)
    {
        wi_protocol = TLS_PARAM_IEEE80211_SOFTAP;
        tls_param_set(TLS_PARAM_ID_WPROTOCOL, (void *)&wi_protocol, false);
    }
    return true;
}

bool _set_broadcast_flag()
{
    u8 ssid_set = 0;
    tls_param_get(TLS_PARAM_ID_BRDSSID, (void *)&ssid_set, false);
    if (0 == ssid_set)
    {
        ssid_set = 1;
        tls_param_set(TLS_PARAM_ID_BRDSSID, (void *)&ssid_set, true);
    }
    return true;
}

void _query_sta_info(void *ptmr, void *parg)
{
    unsigned char *stabuf = NULL;
    unsigned int stanum = 0;

    stabuf = (unsigned char *)tls_mem_alloc(1024);
    if (stabuf)
    {
        memset(stabuf, 0, 1024);
        tls_wifi_get_authed_sta_info(&stanum, stabuf, 1024);
        if (_total_sta_num != stanum)
        {
            int i = 0;
            printf("sta mac:\n");
            for (i = 0; i < stanum; i++)
            {
                printf("\t%02X:%02X:%02X:%02X:%02X:%02X\n",
                    stabuf[i * 6], stabuf[i * 6 + 1], stabuf[i * 6 + 2], 
                    stabuf[i * 6 + 3], stabuf[i * 6 + 4], stabuf[i * 6 + 5]);
            }
            _total_sta_num = stanum;
        }
        tls_mem_free(stabuf);
        stabuf = NULL;
    }
}

bool _start_os_timer_for_sta_mgmt()
{
    if (_sta_monitor_timer)
    {
    	tls_os_timer_stop(_sta_monitor_timer);
        tls_os_timer_delete(_sta_monitor_timer);
        _sta_monitor_timer = NULL;
    }
    tls_os_timer_create(&_sta_monitor_timer,
        _query_sta_info, NULL, 500, true, NULL);
    tls_os_timer_start(_sta_monitor_timer);
}

bool _stop_os_timer_for_sta_mgmt()
{
    if (_sta_monitor_timer)
    {
    	tls_os_timer_stop(_sta_monitor_timer);
        tls_os_timer_delete(_sta_monitor_timer);
        _sta_monitor_timer = NULL;
    }
}

bool _start_softap(const char *ssid, const char *passphrase,
        int channel, int ssid_hidden, int max_connection)
{
    struct tls_softap_info_t ap_info;
    struct tls_ip_info_t ip_info;
    int ret = 0;

    memset(&ap_info, 0, sizeof(ap_info));
    memset(&ip_info, 0, sizeof(ip_info));

    if (NULL != ssid)
        memcpy(ap_info.ssid, ssid, strlen(ssid));
    ap_info.channel = channel;
    if (NULL != passphrase)
    {
        ap_info.encrypt = 6;
        ap_info.keyinfo.format = 1;
        ap_info.keyinfo.index = 1;
        ap_info.keyinfo.key_len = strlen(passphrase);
        memcpy(ap_info.keyinfo.key, passphrase, ap_info.keyinfo.key_len);
    }
    memcpy(ip_info.ip_addr, &_local_ip, 4);
    memcpy(ip_info.netmask, &_subnet, 4);
    memcpy(ip_info.dnsname, "local.wm", strlen("local.wm"));

    ret = tls_wifi_softap_create(&ap_info, &ip_info);
    if(WM_SUCCESS == ret)
    {
    	char * p = NULL;
		
		p = inet_ntoa(_local_ip);
		memcpy(_local_ip_str, p, strlen(p));
		p = inet_ntoa(_local_ip);
		memcpy(_gateway_str, p, strlen(p));
		p = inet_ntoa(_subnet);
		memcpy(_subnet_str, p, strlen(p));
		
        memset(_ssid, 0, sizeof(_ssid));
        memset(_passphrase, 0, sizeof(_passphrase));
        if (NULL != ssid)
            memcpy(_ssid, ssid, strlen(ssid));
        if (NULL != passphrase)
            memcpy(_passphrase, passphrase, strlen(passphrase));
		_total_sta_num = 0;
        _start_os_timer_for_sta_mgmt();
        WiFiMode = WIFI_AP;
        return true;
    }
    printf("[%s %d] <AP> create soft AP error!\n",
        __func__, __LINE__);
    
    return false;
}

bool _cfg_softAP(const char *ssid, const char *passphrase,
        int channel, int ssid_hidden, int max_connection)
{
    _set_work_mode_softap();
    
    tls_wifi_set_oneshot_flag(disable);
    
    _set_broadcast_flag();
    
    tls_wifi_disconnect();
    
    return _start_softap(ssid, passphrase,
                channel, ssid_hidden, max_connection);
}

/**
 * @brief         This function is used to start wifi module as AP mode.
 * @param[in] ssid Specify the SSID.
 * @param[in] passphrase Specify the passphrase.
 * @param[in] channel Specify the channel.
 * @param[in] ssid_hidden Specify the ssid_hidden flag.
 * @param[in] max_connection Specify the max_connection.
 *
 * @return      true - operate successfully, false - operate failure.
 * 
 * @note 
 */ 
bool WiFiAPClass::softAP(const char * ssid, const char *passphrase,
        int channel, int ssid_hidden, int max_connection)
{
    if (!ssid || strlen(ssid) == 0 || strlen(ssid) > 32)
    {
        printf("[%s %d] <AP> SSID too long or missing!\n",
            __func__, __LINE__);
        return false;
    }

    if (passphrase
        && strlen(passphrase) > 0
        && (strlen(passphrase) > 64
            || strlen(passphrase) < 8))
    {
        printf("[%s %d] <AP> fail passphrase to long or short!\n",
            __func__, __LINE__);
        return false;
    }

    return _cfg_softAP(ssid, passphrase,
                channel, ssid_hidden, max_connection);
}

/**
 * @brief         This function is used to config soft AP parameters.
 * @param[in] local_ip Specify the local_ip.
 * @param[in] gateway Specify the gateway.
 * @param[in] subnet Specify the subnet.
 *
 * @return      true - operate successfully, false - operate failure.  
 * 
 * @note 
 */ 
bool WiFiAPClass::softAPConfig(
        uint32_t local_ip, uint32_t gateway, uint32_t subnet)
{
    char * p = NULL;
    
    _local_ip = local_ip;
    _gateway = gateway;
    _subnet = subnet;
    
    memset(&_local_ip_str, 0, sizeof(_local_ip_str));
    memset(&_gateway_str, 0, sizeof(_gateway_str));
    memset(&_subnet_str, 0, sizeof(_subnet_str));
    p = inet_ntoa(local_ip);
    memcpy(_local_ip_str, p, strlen(p));
    p = inet_ntoa(gateway);
    memcpy(_gateway_str, p, strlen(p));
    p = inet_ntoa(subnet);
    memcpy(_subnet_str, p, strlen(p));

    return true;
}

/**
 * @brief         This function is used to config soft AP parameters.
 * @param[in] local_ip Specify the local_ip.
 * @param[in] gateway Specify the gateway.
 * @param[in] subnet Specify the subnet.
 *
 * @return      true - operate successfully, false - operate failure. 
 * 
 * @note 
 */ 
bool WiFiAPClass::softAPConfig(
        const char * local_ip, const char *gateway, const char *subnet)
{
    memset(_local_ip_str, 0, sizeof(_local_ip_str));
    memset(_gateway_str, 0, sizeof(_gateway_str));
    memset(_subnet_str, 0, sizeof(_subnet_str));
    memcpy(_local_ip_str, local_ip, strlen(local_ip));
    memcpy(_gateway_str, gateway, strlen(gateway));
    memcpy(_subnet_str, subnet, strlen(subnet));

    inet_aton(local_ip, &_local_ip);
    inet_aton(gateway, &_gateway);
    inet_aton(subnet, &_subnet);
    
    return true;
}

/**
 * @brief         This function is used to disconnect the ap function.
 * @param[in] wifioff Specify the wifioff.
 *
 * @return      true - operate successfully, false - operate failure.  
 * 
 * @note 
 */ 
bool WiFiAPClass::softAPdisconnect(bool wifioff)
{
	u8 wireless_protocol = IEEE80211_MODE_INFRA;

	_stop_os_timer_for_sta_mgmt();
	tls_wifi_softap_destroy();
	tls_param_set(TLS_PARAM_ID_WPROTOCOL, (void*) &wireless_protocol, TRUE);
    WiFiMode = WIFI_OFF;
	
    return true;
}

/**
 * @brief         This function is used to destrory the AP function.
 * @param[in] None
 *
 * @return      true - operate successfully, false - operate failure.   
 * 
 * @note 
 */ 
bool WiFiAPClass::softAPdestroy()
{
	u8 wireless_protocol = IEEE80211_MODE_INFRA;	
	
	_stop_os_timer_for_sta_mgmt();
	tls_wifi_softap_destroy();
	tls_param_set(TLS_PARAM_ID_WPROTOCOL, (void*) &wireless_protocol, TRUE);
    WiFiMode = WIFI_OFF;
	
    return true;
}

/**
 * @brief         This function is used to get the number of station.
 * @param[in] None
 *
 * @return      The number of station.
 * 
 * @note 
 */ 
uint8_t WiFiAPClass::softAPgetStationNum()
{
    unsigned char *stabuf = NULL;
    unsigned int stanum = 0;
    stabuf = (unsigned char *)tls_mem_alloc(1024);
    if (stabuf)
    {
        memset(stabuf, 0, 1024);
        tls_wifi_get_authed_sta_info(&stanum, stabuf, 1024);
        tls_mem_free(stabuf);
        stabuf = NULL;
        _total_sta_num = stanum;
    }
    return (uint8_t)_total_sta_num;
}

/**
 * @brief         This function is used to get AP's IP.
 * @param[in] None
 *
 * @return      The local AP's IPv4 address.
 * 
 * @note 
 */ 
char * WiFiAPClass::softAPIP()
{
    return (char *)_local_ip_str;
}

extern "C" u8 *hostapd_get_mac(void);
/**
 * @brief         This function is used to get AP's MAC address.
 * @param[in] mac Specify the mac buffer.
 *
 * @return      The AP's MAC address.
 * 
 * @note 
 */ 
uint8_t * WiFiAPClass::softAPmacAddress(uint8_t *mac)
{
	u8 *apmac = NULL;
	
	apmac = hostapd_get_mac();
	memcpy(mac, apmac, 6);
	
	return mac;
}

/**
 * @brief         This function is used to get the AP's MAC address.
 * @param[in] None
 * @return    The string of the AP's MAC address.
 * 
 * @note 
 */ 
char * WiFiAPClass::softAPmacAddress()
{
    unsigned char _mac[6] = {0};
    if (NULL != softAPmacAddress((uint8_t *)_mac))
    {
        sprintf((char*)_sap_mac, "%02X:%02X:%02X:%02X:%02X:%02X",
            _mac[0], _mac[1], _mac[2], _mac[3], _mac[4], _mac[5]);
        return (char *)_sap_mac;
    }
    return (char *)"";
}

/**
 * @brief         This function is used to get AP's SSID.
 * @param[in] None
 * @return    The AP's SSID is returned. 
 * 
 * @note 
 */ 
char * WiFiAPClass::softAPSSID() const
{
    return (char *)_ssid;
}

/**
 * @brief         This function is used to get AP's PSK.
 * @param[in] None
 *
 * @return      The AP's PSK is returned. 
 * 
 * @note 
 */ 
char * WiFiAPClass::softAPPSK() const
{
    return (char*)_passphrase;
}
