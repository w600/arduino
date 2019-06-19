/**
 * @file W600WiFiScan.h
 *
 * @brief   WiFiScanClass Module
 *
 * @author Huang Leilei
 *
 * Copyright (c) 2019 Winner Microelectronics Co., Ltd.
 */
#ifndef _WIRING_WIFISCAN_H_
#define _WIRING_WIFISCAN_H_

#include <stdint.h>

/* Encryption modes */
enum wl_enc_type {  /* Values map to 802.11 encryption suites... */
    ENC_TYPE_WEP  = 5,
    ENC_TYPE_TKIP = 2,
    ENC_TYPE_CCMP = 4,
    /* ... except these two, 7 and 8 are reserved in 802.11-2007 */
    ENC_TYPE_NONE = 7,
    ENC_TYPE_AUTO = 8
};


class WiFiScanClass
{
public:
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
    int8_t scanNetworks(
                bool async = false, bool show_hidden = false,
                uint8_t channel = 0, uint8_t* ssid = NULL);
    /*
    void scanNetworksAsync(
                std::function<void(int)>onComplete, bool show_hidden = flase);
    */
    /**
     * @brief         This function is used to get the scan status.
     * @param[in] None
     *
     * @return  If during scanning, WM_WIFI_SCANNING_BUSY is returned. If finish
     *          scanning, the number of network is returned, otherwise, -1 is returned.
     * @note 
     */ 
    int8_t scanComplete();
    /**
     * @brief         This function is used to free the buffer of last scan result.
     * @param[in] None
     *
     * @return      None 
     * 
     * @note 
     */ 
    void scanDelete();

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
    bool getNetworkInfo(uint8_t networkItem, char *&ssid, uint8_t &encryptionType,
                int32_t &RSSI, uint8_t *&BSSID, int32_t &channel, bool &isHidden);
    /**
     * @brief         This function is used to get ssid.
     * @param[in] networkItem Specify the index of scan result.
     *
     * @return      The SSID of the target 
     * 
     * @note 
     */ 
    char * SSID(uint8_t networkItem);
    /**
     * @brief         This function is used to get encryption type.
     * @param[in] networkItem Specify the index of scan result.
     *
     * @return      The encryptionType of the target 
     * 
     * @note 
     */ 
    uint32_t encryptionType(uint8_t networkItem);
    /**
     * @brief         This function is used to get RSSI.
     * @param[in] networkItem Specify the index of scan result.
     *
     * @return      The RSSI of the target 
     * 
     * @note 
     */ 
    int32_t RSSI(uint8_t networkItem);
    /**
     * @brief         This function is used to get the bssid.
     * @param[in] networkItem Specify the index of scan result.
     *
     * @return      The bssid 
     * 
     * @note 
     */ 
    uint8_t * BSSID(uint8_t networkItem);
    /**
     * @brief         This function is used to get the bssid.
     * @param[in] networkItem Specify the index of scan result.
     *
     * @return      The string of the bssid.
     * 
     * @note 
     */ 
    char * BSSIDstr(uint8_t networkItem);
    /**
     * @brief         This function is used to get the bssid.
     * @param[in] networkItem Specify the index of scan result.
     *
     * @return      The channel of the target.
     * 
     * @note 
     */ 
    int32_t channel(uint8_t networkItem);
    /**
     * @brief         This function is used to get the hidden flag.
     * @param[in] networkItem Specify the index of scan result.
     *
     * @return    false
     * 
     * @note 
     */ 
    bool isHidden(uint8_t networkItem);

protected:
    static void _scanDone();
    static void * _getScanInfoByIndex(int i);
};

#endif
