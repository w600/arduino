/**
 * @file DNSServer.cpp
 *
 * @brief   DNSServer Module
 *
 * @author Huang Leilei
 *
 * Copyright (c) 2019 Winner Microelectronics Co., Ltd.
 */
#include <string.h>

#include "DNSServer.h"
//#include "WiFiUDP.h"
#include "W600WiFi.h"

extern "C" {
#include "wm_dns_server.h"
}

#define DOMAIN_LEN  (128)

//static WiFiUDP _udp;
//uint16_t _port;
char _domainName[DOMAIN_LEN] = {0};
//unsigned char _resolvedIP[4];
//int _currentPacketSize;
//DNSHeader * _dnsHeader;
//uint32_t _ttl = htonl(60);
//DNSReplyCode _errorReplyCode = DNSReplyCode::NonExistentDomain;
/*
void DNSServer::processNextRequest()
{
}

void DNSServer::setErrorReplyCode(const DNSReplyCode &replyCode)
{
}

void DNSServer::setTTL(const uint32_t &ttl)
{
}
*/

/**
 * @brief         This function is used to start DNS Server.
 *
 * @param[in] port Specify the server's dns port
 * @param[in] domainName Sepcify the server's dns name
 * @param[in] resolvedIP Unused arguement.
 *
 * @return      If the operation executes success, true is returned,
 *              otherwise, false is returned.
 * 
 * @note 
 */ 
bool DNSServer::start(const uint16_t &port,
            const char *domainName,
            const char *resolvedIP)
{
    stop();
    memcpy(_domainName, domainName,
        strlen(domainName) > DOMAIN_LEN - 1
            ? DOMAIN_LEN - 1
            : strlen(domainName));
    if (WIFI_AP != WiFi.getMode())
    {
        printf("[%s %d] <DNSServer> SoftAP is down\n",
            __func__, __LINE__); 
    } else {
        if (WM_SUCCESS == tls_dnss_start((u8*)_domainName))
        {
            return true;
        } else {
            printf("[%s %d] <DNSServer> Start DNSServer failure!!!\n",
                __func__, __LINE__);
        }
    }
    
    return false;
}

/**
 * @brief         This function is used to start DNS Server with some 
 *                default arguements in port and resolvedIP.
 * @param[in] domainName specify the server's dns name
 *
 * @return      If the operation executes success, true is returned,
 *              otherwise, false is returned.
 * 
 * @note 
 */ 
bool DNSServer::start(const char *domainName)
{
    return start(53, domainName, "127.0.0.1");
}

/**
 * @brief         This function is used to Stop DNS Server.
 * @return      None 
 * 
 * @note 
 */ 
void DNSServer::stop()
{
    tls_dnss_stop();
}
/*
void DNSServer::downcaseAndRemoveWwwPrefix(const char *domainName)
{
}

char *DNSServer::getDomainNameWithoutWwwPrefix()
{
}

bool DNSServer::requestIncludesOnlyOneQuestion()
{
}

void DNSServer::replyWithIP()
{
}

void DNSServer::replyWithCustomCode()
{
}
*/
