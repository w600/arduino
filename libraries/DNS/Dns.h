/**
 * @file Dns.h
 *
 * @brief   DNSClient Module
 *
 * @author Huang Leilei
 *
 * Copyright (c) 2019 Winner Microelectronics Co., Ltd.
 */
#ifndef _DNS_CLIENT_H_
#define _DNS_CLIENT_H_

#include <stdint.h>

class DNSClient
{
public:
    void begin(unsigned int aDNSServer);
    void begin(const char *aDNSServer);
    
    /**
     * @brief         This function is used to resolve the hostname .
     *
     * @param[in] aHostname The hostname which user want to resolve.
     * @param[out] aResult The first IPv4 address which resolve via DNS
     *                     protocol that display as a 32-bits value.
     *
     * @return      If the operation executes success, true is returned,
     *              otherwise, false is returned.
     * 
     * @note 
     */ 
    int getHostByName(const char *aHostname, unsigned int &aResult);
    
    /**
     * @brief         This function is used to resolve the hostname.
     *
     * @param[in] aHostname The hostname which user want to resolve.
     * @param[out] aResult The first IPv4 address which resolve via DNS
     *                     protocol that display as a Dotted Decimal Notation
     *                     string.
     *
     * @return      If the operation executes success, true is returned,
     *              otherwise, false is returned.
     * 
     * @note 
     */ 
    int getHostByName(const char *aHostname, char *&aResult);

protected:
    uint16_t BuildRequest(const char *aName);
    uint16_t ProcessResponse(uint16_t aTimeout, uint32_t &aAddress);
};

#endif
