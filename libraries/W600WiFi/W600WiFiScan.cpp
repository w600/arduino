/**
 * @file W600WiFiScan.cpp
 *
 * @brief   WiFiScanClass Module
 *
 * @author Huang Leilei
 *
 * Copyright (c) 2019 Winner Microelectronics Co., Ltd.
 */
#include <stdio.h>
#include <string.h>

#include "wiring_time.h"
#include "W600WiFiScan.h"
#include "W600WiFi.h"

extern "C" {
#include "wm_wifi.h"
#include "wm_mem.h"
#include "wm_osal.h"
}

static bool _scanAsync = false;
static bool _scanStarted = false;
static bool _scanComplete = false;
static unsigned char _bssid_str[64] = {0};

static size_t _scanCount = 0;
static void * _scanResult = 0;

//std::function<void(int)> _onComplete;

typedef void (* scan_done_cb_t)();

/**
 * @brief         This function is used to begin scan the WiFi network.
 * @param[in] async Specify the async.
 * @param[in] show_hidden Specify the show_hidden.
 * @param[in] channel Specify the channel.
 * @param[in] ssid Specify the ssid.
 *
 * @return      If not SUCCESS, user needs to call this function again
 *              to trigger scan
 * 
 * @note 
 */ 
int8_t WiFiScanClass::scanNetworks(
            bool async , bool show_hidden,
            uint8_t channel, uint8_t* ssid)
{
    int ret = 0;
    
    if (_scanStarted)
        return WM_WIFI_SCANNING_BUSY;
    
    scanDelete();
    
    tls_wifi_scan_result_cb_register(
        reinterpret_cast<scan_done_cb_t>(&WiFiScanClass::_scanDone)
        );
    
    ret = tls_wifi_scan();
    if (!(WM_WIFI_SCANNING_BUSY != ret
        || WM_FAILED != ret))
    {
        _scanComplete = false;
        _scanStarted = true;
        if (_scanAsync)
        {
            delay(0);
            return WM_WIFI_SCANNING_BUSY;
        }
        return _scanCount;
    }
    
    return ret;
}
/*
void WiFiScanClass::scanNetworksAsync(
            std::function<void(int)>onComplete, bool show_hidden)
{
    _onComplete = onComplete;
    scanNetworks(true, show_hidden);
}
*/

/**
 * @brief         This function is used to get the scan status.
 * @param[in] None
 *
 * @return  If during scanning, WM_WIFI_SCANNING_BUSY is returned. If finish
 *          scanning, the number of network is returned, otherwise, -1 is returned.
 * @note 
 */ 
int8_t WiFiScanClass::scanComplete()
{
    if (_scanStarted)
        return WM_WIFI_SCANNING_BUSY;
    if (_scanComplete)
        return _scanCount;
    return -1;
}

/**
 * @brief         This function is used to free the buffer of last scan result.
 * @param[in] None
 *
 * @return      None 
 * 
 * @note 
 */ 
void WiFiScanClass::scanDelete()
{
    if (_scanResult) {
        //delete[] reinterpret_cast<tls_bss_info_t*>(_scanResult);
        tls_mem_free(_scanResult);
        _scanResult = 0;
        _scanCount = 0;
    }
    _scanComplete = false;
}

/**
 * @brief         This function is used to get the network info via last scan.
 * @param[in] networkItem Specify the index of scan result.
 * @param[out] ssid The ssid in the scan result, indexed by networkItem.
 * @param[out] encryptionType The encryptionType in the scan result, indexed by networkItem.
 * @param[out] RSSI The RSSI in the scan result, indexed by networkItem.
 * @param[out] BSSID The BSSID in the scan result, indexed by networkItem.
 * @param[out] channel The channel in the scan result, indexed by networkItem.
 * @param[out] isHidden The isHidden flag in the scan result, indexed by networkItem.
 *
 * @return      None 
 * 
 * @note 
 */ 
bool WiFiScanClass::getNetworkInfo(uint8_t networkItem, char *&ssid,
            uint8_t &encryptionType,
            int32_t &RSSI, uint8_t *&BSSID, int32_t &channel, bool &isHidden)
{
    struct tls_bss_info_t *it = 
        reinterpret_cast<struct tls_bss_info_t*>(_getScanInfoByIndex(networkItem));

    if (!it)
        return false;

    switch (it->privacy)
    {
        case WM_WIFI_AUTH_MODE_OPEN:
            encryptionType = ENC_TYPE_NONE;
			break;
				
        case WM_WIFI_AUTH_MODE_WEP_AUTO:
            encryptionType = ENC_TYPE_WEP;
			break;
				
        case WM_WIFI_AUTH_MODE_WPA_PSK_TKIP:
		case WM_WIFI_AUTH_MODE_WPA2_PSK_TKIP:
		case WM_WIFI_AUTH_MODE_WPA_WPA2_PSK_TKIP:
			encryptionType = ENC_TYPE_TKIP;	
			break;

        case WM_WIFI_AUTH_MODE_WPA_PSK_CCMP:
		case WM_WIFI_AUTH_MODE_WPA2_PSK_CCMP:
		case WM_WIFI_AUTH_MODE_WPA_WPA2_PSK_CCMP:	
            encryptionType = ENC_TYPE_CCMP;
			break;
		
        case WM_WIFI_AUTH_MODE_WPA_PSK_AUTO:
		case WM_WIFI_AUTH_MODE_WPA2_PSK_AUTO:
		case WM_WIFI_AUTH_MODE_WPA_WPA2_PSK_AUTO:
            encryptionType = ENC_TYPE_AUTO;
			break;
    }	
    
    ssid = (char *)it->ssid;
    ssid[it->ssid_len] = '\0';
    RSSI = -(int32_t)(0x100 - it->rssi);
    BSSID = it->bssid;
    channel = it->channel;
    isHidden = false;

    return true;
}

/**
 * @brief         This function is used to get ssid.
 * @param[in] networkItem Specify the index of scan result.
 *
 * @return      The SSID of the target 
 * 
 * @note 
 */ 
char * WiFiScanClass::SSID(uint8_t networkItem)
{
    struct tls_bss_info_t *it = 
        reinterpret_cast<struct tls_bss_info_t*>(_getScanInfoByIndex(networkItem));
    
    if (!it)
        return (char*)"";
    
    it->ssid[it->ssid_len] = '\0';
    
    return (char *)(it->ssid);
}

/**
 * @brief         This function is used to get encryption type.
 * @param[in] networkItem Specify the index of scan result.
 *
 * @return      The encryptionType of the target 
 * 
 * @note 
 */ 
uint32_t WiFiScanClass::encryptionType(uint8_t networkItem)
{
    struct tls_bss_info_t *it = 
        reinterpret_cast<struct tls_bss_info_t*>(_getScanInfoByIndex(networkItem));
    if (!it)
        return 0;
    switch (it->privacy)
    {
        case WM_WIFI_AUTH_MODE_OPEN:
            return ENC_TYPE_NONE;
				
        case WM_WIFI_AUTH_MODE_WEP_AUTO:
            return ENC_TYPE_WEP;
				
        case WM_WIFI_AUTH_MODE_WPA_PSK_TKIP:
		case WM_WIFI_AUTH_MODE_WPA2_PSK_TKIP:
		case WM_WIFI_AUTH_MODE_WPA_WPA2_PSK_TKIP:
			return ENC_TYPE_TKIP;		

        case WM_WIFI_AUTH_MODE_WPA_PSK_CCMP:
		case WM_WIFI_AUTH_MODE_WPA2_PSK_CCMP:
		case WM_WIFI_AUTH_MODE_WPA_WPA2_PSK_CCMP:	
            return ENC_TYPE_CCMP;
		
        case WM_WIFI_AUTH_MODE_WPA_PSK_AUTO:
		case WM_WIFI_AUTH_MODE_WPA2_PSK_AUTO:
		case WM_WIFI_AUTH_MODE_WPA_WPA2_PSK_AUTO:
            return ENC_TYPE_AUTO;
    }
    return 0;
}

/**
 * @brief         This function is used to get RSSI.
 * @param[in] networkItem Specify the index of scan result.
 *
 * @return      The RSSI of the target 
 * 
 * @note 
 */ 
int32_t WiFiScanClass::RSSI(uint8_t networkItem)
{
    struct tls_bss_info_t *it = 
        reinterpret_cast<struct tls_bss_info_t*>(_getScanInfoByIndex(networkItem));
    if (!it)
        return 0;
    //return (int32_t)(it->rssi);
    return -(int32_t)(0x100 - it->rssi);
}

/**
 * @brief         This function is used to get the bssid.
 * @param[in] networkItem Specify the index of scan result.
 *
 * @return      The bssid.
 * 
 * @note 
 */ 
uint8_t * WiFiScanClass::BSSID(uint8_t networkItem)
{
    struct tls_bss_info_t *it = 
        reinterpret_cast<struct tls_bss_info_t*>(_getScanInfoByIndex(networkItem));
    if (!it)
        return NULL;
    return (uint8_t *)(it->bssid);
}

/**
 * @brief         This function is used to get the bssid.
 * @param[in] networkItem Specify the index of scan result.
 *
 * @return      The string of the bssid.
 * 
 * @note 
 */ 
char * WiFiScanClass::BSSIDstr(uint8_t networkItem)
{
    struct tls_bss_info_t *it = 
        reinterpret_cast<struct tls_bss_info_t *>(_getScanInfoByIndex(networkItem));

    if (!it)
        return (char*)"";
    
    memset(_bssid_str, 0, sizeof(_bssid_str));
    sprintf((char*)_bssid_str, "%02X:%02X:%02X:%02X:%02X:%02X",
        it->bssid[0], it->bssid[1], it->bssid[2],
        it->bssid[3], it->bssid[4], it->bssid[5]);
    return (char * )_bssid_str;
}

/**
 * @brief         This function is used to get the bssid.
 * @param[in] networkItem Specify the index of scan result.
 *
 * @return      The channel of the target.
 * 
 * @note 
 */ 
int32_t WiFiScanClass::channel(uint8_t networkItem)
{
    struct tls_bss_info_t *it = 
        reinterpret_cast<struct tls_bss_info_t *>(_getScanInfoByIndex(networkItem));
    if (!it)
        return 0;
    return (int32_t)(it->channel);
}

/**
 * @brief         This function is used to get the hidden flag.
 * @param[in] networkItem Specify the index of scan result.
 *
 * @return    false
 * 
 * @note 
 */ 
bool WiFiScanClass::isHidden(uint8_t networkItem)
{
    return false;
}

void WiFiScanClass::_scanDone()
{    
    int buf_len = 2000;
    int err = -1;
    //struct tls_bss_info_t *bss_info = NULL;
    
    _scanResult = tls_mem_alloc(buf_len);
    if (!_scanResult)
        return ;

    err = tls_wifi_get_scan_rslt((u8*)_scanResult, buf_len);
    if (err)
    {
        tls_mem_free(_scanResult);
        return ;
    }
    
    _scanCount = ((struct tls_scan_bss_t*)(_scanResult))->count;
    //if (NULL != _scanResult)
    //    tls_mem_free(_scanResult);
    //_scanResult = 0;

    _scanStarted = false;
    _scanComplete = true;
    if (_scanAsync)
    {
        tls_os_start_scheduler();
    } /*else if (_onComplete) {
        _onComplete(_scanCount);
    }*/
}

void * WiFiScanClass::_getScanInfoByIndex(int i)
{
    if (!_scanResult
        || (size_t)i > _scanCount)
        return NULL;
    struct tls_bss_info_t *begin = (struct tls_bss_info_t *)(((tls_scan_bss_t*)_scanResult)->bss);
    return reinterpret_cast<struct tls_bss_info_t*>(begin) + i;
}
