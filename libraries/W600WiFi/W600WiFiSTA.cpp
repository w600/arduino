#include <string.h>
#include <stdio.h>

#include "W600WiFiSTA.h"
#include "wiring_time.h"
#include "W600WiFiType.h"

extern "C" {
#include "wm_efuse.h"
#include "wm_wifi.h"
#include "wm_netif2.0.3.h"
}

#define IPV4_ADDR_STR_LEN       16
static unsigned char _wifi_mac_str[20] = {0};
static unsigned char _wifi_mac[6] = {0};
static unsigned char _mask_str[IPV4_ADDR_STR_LEN] = {0};
static unsigned char _ipv4_str[IPV4_ADDR_STR_LEN] = {0};
static unsigned char _gw_str[IPV4_ADDR_STR_LEN] = {0};
static unsigned char _dns1_str[IPV4_ADDR_STR_LEN] = {0};
static unsigned char _dns2_str[IPV4_ADDR_STR_LEN] = {0};
static tls_curr_bss_t _bss;
static unsigned char _ssid[33] = {0};
static unsigned char _bssid_str[20] = {0};
static unsigned char _passphrase[65] = {0};

extern WiFiMode_t WiFiMode;

extern "C" int get_bss_info()
{
    memset(&_bss, 0, sizeof(_bss));
    tls_wifi_get_current_bss(&_bss);
    return 0;
}

extern "C" int sprintf_ipaddr(unsigned char *dst, unsigned int ipaddr)
{
    unsigned char * ptmp = (unsigned char *)&ipaddr;
    sprintf((char *)dst, "%d.%d.%d.%d",
        ptmp[0], ptmp[1], ptmp[2], ptmp[3]);
    return 0;
}

extern "C" struct tls_ethif * get_if_info()
{
    struct tls_ethif *pif = NULL;
    pif = tls_netif_get_ethif();
    return pif;
}

#if USER_CONSTRUCTOR
bool WiFiSTAClass::config(IPAddress local_ip, IPAddress gateway, IPAddress subnet,
        IPAddress dns1, IPAddress dns2)
{

}
#endif

/**
 * @brief         This function is used to start the wifi module as station mode.
 * @param[in] ssid Specify the SSID.
 * @param[in] passphrase Specify the passphrase.
 * @param[in] channel Specify the channel.
 * @param[in] bssid Specify the BSSID.
 * @param[in] connect Specify the connect.
 *
 * @return  If the paraments is invalid, negative is returned. Otherwise, wifi status is returned.
 * 
 * @note 
 */ 
int WiFiSTAClass::begin(const char *ssid, const char * passphrase,
        unsigned int channel, const unsigned char bssid[6],
        bool connect)
{
    int ret = 0;
    if (NULL == ssid
        || 0x00 == *ssid
        || strlen(ssid) > 32)
    {
        return -1;
    }

    if (passphrase && strlen(passphrase) > 64)
        return -2;
    
    tls_wifi_disconnect();

	if (WIFI_AP_STA != WiFiMode)
    	tls_wifi_softap_destroy();

    memset(_passphrase, 0, sizeof(_passphrase));
    if (NULL != passphrase)
        memcpy(_passphrase, passphrase, strlen(passphrase));
    memset(_ssid, 0, sizeof(_ssid));
    if (NULL != ssid)
        memcpy(_ssid, ssid, strlen(ssid));
    memset(_passphrase, 0, sizeof(_passphrase));
    if (NULL != passphrase)
        memcpy(_passphrase, passphrase, strlen(passphrase));

    setAutoConnect(connect);
	wstatus = WL_IDLE_STATUS;
    ret = tls_wifi_connect((uint8_t *)ssid, (uint8_t)strlen(ssid),
                (uint8_t *)passphrase, (uint8_t)strlen(passphrase));
	if (WM_WIFI_ERR_SSID == ret)
		wstatus = WL_NO_SSID_AVAIL;
    //printf("[%s %s %d] ret: %d\n", __FILE__, __func__, __LINE__, ret);
	if (WIFI_AP_STA != WiFiMode)
    	WiFiMode = WIFI_STA;
    return status();
}

/**
 * @brief         This function is used to start the wifi module as station mode.
 * @param[in] ssid Specify the SSID.
 * @param[in] passphrase Specify the passphrase.
 * @param[in] channel Specify the channel.
 * @param[in] bssid Specify the BSSID.
 * @param[in] connect Specify the connect.
 *
 * @return  If the paraments is invalid, negative is returned. Otherwise, wifi status is returned.
 * 
 * @note 
 */ 
int WiFiSTAClass::begin(char *ssid, char *passphrase,
        int channel, unsigned char bssid[6],
        bool connect)
{
    return begin((const char *)ssid, (const char *)passphrase,
                channel, bssid, connect);
}

/**
 * @brief         This function is used to start the wifi module as station mode.
 * @param[in] None.
 *
 * @return  If the paraments is invalid, negative is returned. Otherwise, wifi status is returned.
 * 
 * @note 
 */ 
int WiFiSTAClass::begin()
{
	wstatus = WL_IDLE_STATUS;
    int ret = tls_wifi_connect((uint8_t *)_ssid, (uint8_t)strlen((const char *)_ssid),
                (uint8_t *)_passphrase, (uint8_t)strlen((const char *)_passphrase));
	if (WM_WIFI_ERR_SSID == ret)
		wstatus = WL_NO_SSID_AVAIL;
    return status();
}

/**
 * @brief         This function is used to reconect the AP.
 * @param[in] None
 * @return  If reconnect successfully, return true, otherwise, return false.
 * 
 * @note 
 */ 
bool WiFiSTAClass::reconnect()
{
    disconnect();
	wstatus = WL_IDLE_STATUS;
    int ret = tls_wifi_connect((uint8_t *)_ssid, (uint8_t)strlen((const char *)_ssid),
        (uint8_t *)_passphrase, (uint8_t)strlen((const char *)_passphrase));
	if (WM_WIFI_ERR_SSID == ret)
		wstatus = WL_NO_SSID_AVAIL;
    return WM_SUCCESS == ret ? true : false;
}

/**
 * @brief         This function is used to disconnect the wifi.
 * @param[in] wifioff Specify the parameter.
 *
 * @return  true is returned.
 * 
 * @note 
 */ 
bool WiFiSTAClass::disconnect(bool wifioff)
{
    tls_wifi_disconnect();
	if (WIFI_AP_STA != WiFiMode)
	    WiFiMode = WIFI_OFF;
    return true;
}

/**
 * @brief         This function is used to get the wifi mode connect status.
 * @param[in] None
 *
 * @return  true - WiFi status is connected, otherwise, false.
 * 
 * @note 
 */ 
bool WiFiSTAClass::isConnected()
{
    return (WL_CONNECTED == status());//(WM_WIFI_JOINED == status());
}

/**
 * @brief         This function is used to set auto connect flag.
 * @param[in] autoReconnect Specify the auto-connect flag.
 *
 * @return      true - set successfully.
 * 
 * @note 
 */ 
bool WiFiSTAClass::setAutoConnect(bool autoConnect)
{
    tls_wifi_auto_connect_flag(WIFI_AUTO_CNT_FLAG_SET, (uint8_t*)&autoConnect);
    return true;
}

/**
 * @brief         This function is used to get auto connect flag.
 * @param[in] None
 * @return  true - set the auto-connect flag, otherwise, return false.
 *
 * @note 
 */ 
bool WiFiSTAClass::getAutoConnect()
{
    int auto_connect = WIFI_AUTO_CNT_OFF;
    tls_wifi_auto_connect_flag(WIFI_AUTO_CNT_FLAG_GET, (uint8_t*)&auto_connect);
    return (auto_connect == WIFI_AUTO_CNT_ON);
}

/**
 * @brief         This function is used to set auto reconnect flag.
 * @param[in] autoReconnect Specify the auto-reconnect flag.
 *
 * @return      true - set successfully.
 * 
 * @note 
 */ 
bool WiFiSTAClass::setAutoReconnect(bool autoReconnect)
{
    tls_wifi_auto_connect_flag(WIFI_AUTO_CNT_FLAG_SET, (uint8_t *)&autoReconnect);
    return true;
}

/**
 * @brief         This function is used to get auto reconnect flag.
 * @param[in] None
 * @return  true - set the auto-reconnect flag, otherwise, return false.
 *
 * @note 
 */ 
bool WiFiSTAClass::getAutoReconnect()
{
    uint8_t auto_reconnect = 0xff;
    tls_wifi_auto_connect_flag(WIFI_AUTO_CNT_FLAG_GET, &auto_reconnect);
    return (auto_reconnect == WIFI_AUTO_CNT_ON);
}

/**
 * @brief         This function is used to suspend until the WiFi is connected.
 * @param[in] None
 *
 * @return  WiFi status. 
 * 
 * @note 
 */ 
uint8_t WiFiSTAClass::waitForConnectResult()
{
    while (WL_CONNECTED != status())//(WM_WIFI_JOINED != status())
    {
        delay(100);
    }
    return status();
}

/**
 * @brief         This function is used to get the local ip address.
 * @param[in] None
 *
 * @return  The local IPv4 address configure on the Module.
 * 
 * @note 
 */ 
IPAddress WiFiSTAClass::localIP()
{
    struct tls_ethif *pif;
    
    pif = get_if_info();

    return IPAddress((uint32_t)(pif->ip_addr.addr));
}

/*
uint8_t * WiFiSTAClass::macAddress(uint8_t *mac)
{
    int ret = tls_get_mac_addr(mac);
    if (TLS_EFUSE_STATUS_OK == ret)
        return mac;
    else
        return NULL;
}
*/

/**
 * @brief         This function is used to get local MAC address used by the module.
 * @param[in] None
 *
 * @return  The MAC address. 
 * 
 * @note 
 */ 
char * WiFiSTAClass::macAddress()
{
    int ret = tls_get_mac_addr((uint8_t *)_wifi_mac);
    if (TLS_EFUSE_STATUS_OK == ret)
        return (char *)_wifi_mac;
    else
        return NULL;
}

/**
 * @brief         This function is used to get local MAC address used by the module.
 * @param[in] None
 *
 * @return  The string of the MAC address.
 * 
 * @note 
 */ 
char *WiFiSTAClass::macAddressStr()
{
    unsigned char *pmac = NULL;
    if ((pmac = (unsigned char *)macAddress()) != NULL)
    {
        memset(_wifi_mac_str, 0, sizeof(_wifi_mac_str));
        sprintf((char *)_wifi_mac_str, "%02X:%02X:%02X:%02X:%02X:%02X",
            pmac[0], pmac[1], pmac[2],
            pmac[3], pmac[4], pmac[5]);
        return (char *)_wifi_mac_str;
    }
    return NULL;
}

/*
unsigned char * WiFiSTAClass::macAddress(unsigned char *mac)
{
    int ret = tls_get_mac_addr(mac);
    if (TLS_EFUSE_STATUS_OK == ret)
        return mac;
    else
        return NULL;
}
*/

/**
 * @brief         This function is used to get subnet mask.
 * @param[in] None
 *
 * @return      The sub-net mask. 
 * 
 * @note 
 */ 
IPAddress WiFiSTAClass::subnetMask()
{
    struct tls_ethif *pif;
    
    pif = get_if_info();
    
    return IPAddress((uint32_t)(pif->netmask.addr));
}

/**
 * @brief         This function is used to get gateway IP address.
 * @param[in] None
 *
 * @return  The gateway's IPv4 address. 
 * 
 * @note 
 */ 
IPAddress WiFiSTAClass::getwayIP()
{
    struct tls_ethif *pif;
    
    pif = get_if_info();

    return IPAddress((uint32_t)(pif->gw.addr));
}

/**
 * @brief         This function is used to get DNS IP address.
 * @param[in] dns_no The index of the dns.
 *
 * @return  The DNS's IPv4 address 
 * 
 * @note 
 */ 
IPAddress WiFiSTAClass::dnsIP(uint8_t dns_no)
{
    struct tls_ethif *pif = NULL;
    unsigned int dns;
    unsigned char * pdns_str = NULL;
    
    pif = get_if_info();
    if (0 == dns_no)
    {
        dns = pif->dns1.addr;
    }
    else if (1 == dns_no)
    {
        dns = pif->dns2.addr;
    }
    
    return IPAddress((uint32_t)(dns));
}

char * WiFiSTAClass::hostname()
{

}

bool WiFiSTAClass::hostname(char *aHostname)
{

}
bool WiFiSTAClass::hostname(const char *aHostname)
{

}

/**
 * @brief         This function is used to get the status during Station mode.
 * @param[in] None
 * @return      The status of WiFi Mode
 * 
 * @note 
 */ 
wl_status_t WiFiSTAClass::status()
{
	if (WM_WIFI_JOINING == tls_wifi_get_state())
	{
		wstatus = WL_SCAN_COMPLETED;
	}
	else if (WM_WIFI_JOINED == tls_wifi_get_state())
	{
		struct tls_ethif *ethif = get_if_info();
		if (ethif->status)
			wstatus = WL_CONNECTED;
		else
			wstatus = WL_SCAN_COMPLETED;
	}
	else if (WM_WIFI_DISCONNECTED == tls_wifi_get_state())
	{
		if (WL_NO_SSID_AVAIL != wstatus)
			wstatus = WL_DISCONNECTED;
	}
	return wstatus;
}

/**
 * @brief         This function is used to get the status during Station mode.
 * @param[in] None
 * @return      The string of the status of WiFi Mode.
 * 
 * @note 
 */ 
char *WiFiSTAClass::statusStr()
{
    //enum tls_wifi_states st = (enum tls_wifi_states)0;
    wl_status_t st = status();
    switch (st)
    {
        case WL_DISCONNECTED:
            return (char *)"Disconnected";
        case WL_SCAN_COMPLETED:
            return (char *)"Scan completed";
        case WL_NO_SSID_AVAIL:
            return (char *)"SSID invalid";
        case WL_CONNECTED:
            return (char *)"Connected";
		case WL_IDLE_STATUS:
            return (char *)"WiFi idle";
    }
    return (char *)"";
}

/**
 * @brief         This function is used to get the SSID used by the module.
 * @param[in] None
 *
 * @return The string of the SSID.
 * 
 * @note 
 */ 
char * WiFiSTAClass::SSID() const
{
    get_bss_info();
    memset(_ssid, 0, sizeof(_ssid));
    memcpy(_ssid, _bss.ssid, _bss.ssid_len);
    return (char*)_ssid;
}

/**
 * @brief         This function is used to get the psk used by the module.
 * @param[in] None
 *
 * @return The string of the PSK.
 * 
 * @note 
 */ 
char * WiFiSTAClass::psk() const
{
    return (char *)_passphrase;
}

/**
 * @brief         This function is used to get the BSSID which is connected by the module.
 *
 * @param[in] none
 *
 * @return      The BSSID of the AP.
 * 
 * @note 
 */ 
uint8_t * WiFiSTAClass::BSSID()
{
    get_bss_info();
    return (uint8_t *)(_bss.bssid);
}

/**
 * @brief         This function is used to get the BSSID which is connected by the module.
 *
 * @param[in] None
 *
 * @return  The string of the BSSID of the AP.
 * 
 * @note 
 */ 
char * WiFiSTAClass::BSSIDstr()
{
    get_bss_info();
    memset(_bssid_str, 0, sizeof(_bssid_str));
    sprintf((char*)_bssid_str, "%02X:%02X:%02X:%02X:%02X:%02X",
        _bss.bssid[0], _bss.bssid[1], _bss.bssid[2],
        _bss.bssid[3], _bss.bssid[4], _bss.bssid[5]);
    return (char*)_bssid_str;
}

/**
 * @brief         This function is used to get the RSSI.
 *
 * @param[in] None
 *
 * @return  the value of rssi in this connect.
 * 
 * @note 
 */ 
int32_t WiFiSTAClass::RSSI()
{
    get_bss_info();
    return (int32_t)(-_bss.rssi - 1);
}
