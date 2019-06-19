/**
 * @file W600WiFiSTA.h
 *
 * @brief   WiFiSTAClass Module
 *
 * @author Huang Leilei
 *
 * Copyright (c) 2019 Winner Microelectronics Co., Ltd.
 */
#ifndef _WIRING_WIFISTA_H_
#define _WIRING_WIFISTA_H_

#include <stdio.h>

extern "C" {
#include "wm_wifi.h"
}

#include "IPAddress.h"

typedef enum {
    WL_IDLE_STATUS      = 0,
    WL_NO_SSID_AVAIL    = 1,
    WL_SCAN_COMPLETED   = 2,
    WL_CONNECTED        = 3,
    WL_CONNECT_FAILED   = 4,
    WL_CONNECTION_LOST  = 5,
    WL_DISCONNECTED     = 6,
    WL_NO_SHIELD        = 7
} wl_status_t;

class WiFiSTAClass
{
public:

/**
 * @defgroup WiFi_library WiFi_library
 * @brief WiFi library
 */

/**
 * @addtogroup WiFi_library
 * @{
 */

/**
 * @defgroup WiFi_library WiFi_class
 * @brief WiFi class
 */

/**
 * @addtogroup WiFi_class
 * @{
 */
    /**
     * @brief         This function is used to start the wifi module as station mode.
     * @param[in] ssid Specify the SSID.
     * @param[in] passphrase Specify the passphrase.
     * @param[in] channel Specify the channel.
     * @param[in] bssid Specify the BSSID.
     * @param[in] connect Specify the connect.
     *
     * @return 	If the paraments is invalid, negative is returned. Otherwise, wifi status is returned.
     * 
     * @note 
     */ 
    int begin(const char *ssid, const char * passphrase = NULL,
        	unsigned int channel = 0, const unsigned char bssid[6] = NULL,
        	bool connect = true);
    /**
     * @brief         This function is used to start the wifi module as station mode.
     * @param[in] ssid Specify the SSID.
     * @param[in] passphrase Specify the passphrase.
     * @param[in] channel Specify the channel.
     * @param[in] bssid Specify the BSSID.
     * @param[in] connect Specify the connect.
     *
     * @return 	If the paraments is invalid, negative is returned. Otherwise, wifi status is returned.
     * 
     * @note 
     */ 
    int begin(char *ssid, char *passphrase = NULL,
        	int channel = 0, unsigned char bssid[6] = NULL,
        	bool connect = true);
    /**
     * @brief         This function is used to start the wifi module as station mode.
     * @param[in] None.
     *
     * @return 	If the paraments is invalid, negative is returned. Otherwise, wifi status is returned.
     * 
     * @note 
     */ 
    int begin();

#if USER_CONSTRUCTOR
    bool config(IPAddress local_ip, IPAddress gateway, IPAddress subnet,
       	    IPAddress dns1 = (unsigned int)0x00000000, IPAddress dns2 = (unsigned int)0x00000000);
#endif
    /**
     * @brief         This function is used to reconect the AP.
     * @param[in] None
     * @return 	If reconnect successfully, return true, otherwise, return false.
     * 
     * @note 
     */ 
    bool reconnect();
    /**
     * @brief         This function is used to disconnect the wifi.
     * @param[in] wifioff Specify the parameter.
     *
     * @return 	true is returned.
     * 
     * @note 
     */ 
	bool disconnect(bool wifioff = false);
    /**
     * @brief         This function is used to get the wifi mode connect status.
     * @param[in] None
     *
     * @return 	true - WiFi status is connected, otherwise, false.
     * 
     * @note 
     */ 
    bool isConnected();

    /**
     * @brief         This function is used to set auto connect flag.
     * @param[in] autoReconnect Specify the auto-connect flag.
     *
     * @return 		true - set successfully.
     * 
     * @note 
     */ 
    bool setAutoConnect(bool autoConnect);
    /**
     * @brief         This function is used to get auto connect flag.
     * @param[in] None
     * @return 	true - set the auto-connect flag, otherwise, return false.
     *
     * @note 
     */ 
    bool getAutoConnect();

    /**
     * @brief         This function is used to set auto reconnect flag.
     * @param[in] autoReconnect Specify the auto-reconnect flag.
     *
     * @return 		true - set successfully.
     * 
     * @note 
     */ 
    bool setAutoReconnect(bool autoReconnect);
    /**
     * @brief         This function is used to get auto reconnect flag.
     * @param[in] None
     * @return 	true - set the auto-reconnect flag, otherwise, return false.
     *
     * @note 
     */ 
    bool getAutoReconnect();
    
    /**
     * @brief         This function is used to suspend until the WiFi is connected.
     * @param[in] None
     *
     * @return 	WiFi status. 
     * 
     * @note 
     */ 
	uint8_t waitForConnectResult();

    /**
     * @brief         This function is used to get the local ip address.
     * @param[in] None
     *
     * @return 	The local IPv4 address configure on the Module.
     * 
     * @note 
     */ 
    IPAddress localIP();

    //uint8_t *macAddress(uint8_t *mac);
    /**
     * @brief         This function is used to get local MAC address used by the module.
     * @param[in] None
     *
     * @return 	The MAC address. 
     * 
     * @note 
     */ 
    char *macAddress();
    /**
     * @brief         This function is used to get local MAC address used by the module.
     * @param[in] None
     *
     * @return 	The string of the MAC address.
     * 
     * @note 
     */ 
    char *macAddressStr();
    //unsigned char *macAddress(unsigned char *mac);

    /**
     * @brief         This function is used to get subnet mask.
     * @param[in] None
     *
     * @return 		The sub-net mask. 
     * 
     * @note 
     */ 
    IPAddress subnetMask();
    /**
     * @brief         This function is used to get gateway IP address.
     * @param[in] None
     *
     * @return 	The gateway's IPv4 address. 
     * 
     * @note 
     */ 
    IPAddress getwayIP();
    /**
     * @brief         This function is used to get DNS IP address.
     * @param[in] dns_no The index of the dns.
     *
     * @return 	The DNS's IPv4 address.
     * 
     * @note 
     */ 
    IPAddress dnsIP(uint8_t dns_no = 0);

    char *hostname();
    bool hostname(char *aHostname);
    bool hostname(const char *aHostname);

    /**
     * @brief         This function is used to get the status during Station mode.
     * @param[in] None
     * @return 		The status of WiFi Mode
     * 
     * @note 
     */ 
    wl_status_t status();
    /**
     * @brief         This function is used to get the status during Station mode.
     * @param[in] None
     * @return 		The string of the status of WiFi Mode.
     * 
     * @note 
     */ 
    char *statusStr();
    /**
     * @brief         This function is used to get the SSID used by the module.
     * @param[in] none
     *
     * @return The string of the SSID.
     * 
     * @note 
     */ 
    char *SSID() const;
    /**
     * @brief         This function is used to get the psk used by the module.
     * @param[in] None
     *
     * @return The string of the PSK.
     * 
     * @note 
     */ 
    char *psk() const;

    /**
     * @brief         This function is used to get the BSSID which is connected by the module.
     *
     * @param[in] None
     *
     * @return 		The BSSID of the AP.
     * 
     * @note 
     */ 
    uint8_t *BSSID();
    /**
     * @brief         This function is used to get the BSSID which is connected by the module.
     *
     * @param[in] None
     *
     * @return 	The string of the BSSID of the AP.
     * 
     * @note 
     */ 
    char *BSSIDstr();

    /**
     * @brief         This function is used to get the RSSI.
     *
     * @param[in] None
     *
     * @return  the value of rssi in this connect.
     * 
     * @note 
     */ 
    int32_t RSSI();

/**
 * @}
 */

/**
 * @}
 */

private:
    wl_status_t wstatus;
};

#endif
