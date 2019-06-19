/**
 * @file W600WiFiGeneric.h
 *
 * @brief   WiFiGenericClass Module
 *
 * @author Huang Leilei
 *
 * Copyright (c) 2019 Winner Microelectronics Co., Ltd.
 */
#ifndef _WIRING_WIFI_GENERIC_H_
#define _WIRING_WIFI_GENERIC_H_

#include <stdint.h>

#include "W600WiFiType.h"
#include "IPAddress.h"

class WiFiGenericClass
{
public:
    //int32_t channel(void);
    //bool setSleepMode();
    
    /**
     * @brief         This function is used to Get the WiFi's work mode.\
     * @return      enum of WiFiMode: WIFI_OFF, WIFI_STA or WIFI_AP
     * 
     * @note 
     */ 
    WiFiMode_t getMode();

    //bool enableSTA(bool enable);
    //bool enableAP(bool enable);

    //bool forceSleepBegin(uint32_t sleepUs = 0);
    //bool forceSleepWake();
    
    /**
     * @brief         This function is used to resolve hostname .
     *
     * @param[in] aHostname The hostname which you want to resolve.
     * @param[out] aResult The result of resove the hostname.
     *
     * @return      1 - success, 0 - failure.
     * 
     * @note 
     */ 
    int hostByName(const char* aHostname, IPAddress& aResult);
    
    /**
     * @brief         This function is used to resolve hostname .
     *
     * @param[in] aHostname The hostname which you want to resolve.
     * @param[in] timeout_ms The timeout when resolve.
     * @param[out] aResult The result of resove the hostname.
     *
     * @return      1 - success, 0 - failure.
     * 
     * @note 
     */ 
    int hostByName(const char* aHostname, IPAddress& aResult, uint32_t timeout_ms);
};

#endif
