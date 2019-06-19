/**
 * @file Dns.cpp
 *
 * @brief   DNSClient Module
 *
 * @author Huang Leilei
 *
 * Copyright (c) 2019 Winner Microelectronics Co., Ltd.
 */
#include <string.h>

#include "Dns.h"
#include "W600WiFi.h"

extern "C" {
#include "wm_socket2.0.3.h"
}

static unsigned char _Result[INET_ADDRSTRLEN] = {0};

void DNSClient::begin(unsigned int aDNSServer)
{

}

void DNSClient::begin(const char *aDNSServer)
{

}

/**
 * @brief         This function is used to resolve the hostname.
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
int DNSClient::getHostByName(const char *aHostname, unsigned int &aResult)
{
    struct hostent *phost;
    
    if (NULL == aHostname)
    {
        printf("[%s %d] <DNSClient> aHostname is NULL\n", __func__, __LINE__);
        return false;
    }
    
    if (WL_CONNECTED != WiFi.status())
    {
        printf("[%s %d] <DNSClient> WiFi is %d\n", __func__, __LINE__, WiFi.status());
        return false;
    }
    
    phost = gethostbyname(aHostname);
    if (NULL == phost)
    {
        printf("[%s %d] <DNSClient> resolve %s error\n", __func__, __LINE__, aHostname);
        return false;
    }
    
    if ((AF_INET == phost->h_addrtype
        || AF_INET6 == phost->h_addrtype)
        && NULL != phost->h_addr_list)
    {
        //aResult = (unsigned int)phost->h_addr_list;
        memcpy(&aResult, phost->h_addr_list[0], sizeof(aResult));
    }
    
    return true;    
}

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
int DNSClient::getHostByName(const char *aHostname, char *&aResult)
{
    ip4_addr_t _result;
    char *pa = NULL;
    if (getHostByName(aHostname, (u32_t&)(_result.addr)))
    {
        pa = inet_ntoa(_result);
        if (NULL != pa)
        {
            memset(_Result, 0, sizeof(_Result));
            memcpy(_Result, pa, strlen(pa));
            aResult = (char *)_Result;
            return true;
        }
    }
    
    return false;
}

uint16_t DNSClient::BuildRequest(const char *aName)
{

}

uint16_t DNSClient::ProcessResponse(uint16_t aTimeout, uint32_t &aAddress)
{

}

