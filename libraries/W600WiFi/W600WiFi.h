/**
 * @file W600WiFi.h
 *
 * @brief   WiFi Module
 *
 * @author Huang Leilei
 *
 * Copyright (c) 2019 Winner Microelectronics Co., Ltd.
 */
#ifndef _WIRING_WIFI_H_
#define _WIRING_WIFI_H_

#include "W600WiFiGeneric.h"
#include "W600WiFiSTA.h"
#include "W600WiFiScan.h"
#include "W600WiFiAP.h"
#include "W600WiFiOneshot.h"
#include "WiFiClient.h"
#include "WiFiUDP.h"

class WiFiClass
    : public WiFiGenericClass,
      public WiFiSTAClass,
      public WiFiScanClass,
      public WiFiAPClass,
      public WiFiOneshotClass
{
public:
    
    using WiFiSTAClass::SSID;
    using WiFiSTAClass::BSSID;
    using WiFiSTAClass::BSSIDstr;
    using WiFiSTAClass::RSSI;
    
    using WiFiScanClass::SSID;
    using WiFiScanClass::BSSID;
    using WiFiScanClass::BSSIDstr;
    using WiFiScanClass::RSSI;
    using WiFiScanClass::channel;
};

extern WiFiClass WiFi;

#endif