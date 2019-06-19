/**
 * @file W600WiFiAP.h
 *
 * @brief   WiFiAPClass Module
 *
 * @author Huang Leilei
 *
 * Copyright (c) 2019 Winner Microelectronics Co., Ltd.
 */
#ifndef _WIRING_WIFI_AP_H_
#define _WIRING_WIFI_AP_H_

#include <stdint.h>

class WiFiAPClass
{
public:
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
    bool softAP(const char * ssid, const char *passphrase = NULL,
            int channel = 1, int ssid_hidden = 0, int max_connection = 4);
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
    bool softAPConfig(uint32_t local_ip, uint32_t gateway, uint32_t subnet);
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
    bool softAPConfig(const char * local_ip, const char *gateway, const char *subnet);
    /**
     * @brief         This function is used to disconnect the ap function.
     * @param[in] wifioff Specify the wifioff.
     *
     * @return      true - operate successfully, false - operate failure.  
     * 
     * @note 
     */ 
    bool softAPdisconnect(bool wifioff = false);
    /**
     * @brief         This function is used to destrory the AP function.
     * @param[in] None
     *
     * @return      true - operate successfully, false - operate failure.   
     * 
     * @note 
     */ 
    bool softAPdestroy();

    /**
     * @brief         This function is used to get the number of station.
     * @param[in] None
     *
     * @return      The number of station.
     * 
     * @note 
     */ 
    uint8_t softAPgetStationNum();

    /**
     * @brief         This function is used to get AP's IP.
     * @param[in] None
     *
     * @return      The local AP's IPv4 address.
     * 
     * @note 
     */ 
    char * softAPIP();

    /**
     * @brief         This function is used to get AP's MAC address.
     * @param[in] mac Specify the mac buffer.
     *
     * @return      The AP's MAC address.
     * 
     * @note 
     */ 
    uint8_t * softAPmacAddress(uint8_t *mac);
    /**
     * @brief         This function is used to get the AP's MAC address.
     * @param[in] None
     * @return    The string of the AP's MAC address.
     * 
     * @note 
     */ 
    char * softAPmacAddress(void);

    /**
     * @brief         This function is used to get AP's SSID.
     * @param[in] None
     * @return    The AP's SSID is returned. 
     * 
     * @note 
     */ 
    char * softAPSSID() const;
    /**
     * @brief         This function is used to get AP's PSK.
     * @param[in] None
     *
     * @return      The AP's PSK is returned. 
     * 
     * @note 
     */ 
    char * softAPPSK() const;
};

#endif
