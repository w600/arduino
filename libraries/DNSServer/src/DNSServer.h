/**
 * @file DNSServer.h
 *
 * @brief   DNSServer Module
 *
 * @author Huang Leilei
 *
 * Copyright (c) 2019 Winner Microelectronics Co., Ltd.
 */
#ifndef _DNS_SERVER_H_
#define _DNS_SERVER_H_

#include <stdint.h>

class DNSServer
{
public:
    //void processNextRequest();
    //void setErrorReplyCode(const DNSReplyCode &replyCode);
    //void setTTL(const uint32_t &ttl);
    
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
    bool start(const uint16_t &port,
                const char *domainName,
                const char *resolvedIP);
                
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
    bool start(const char *domainName);
    
    /**
     * @brief         This function is used to Stop DNS Server.
     * @return      None 
     * 
     * @note 
     */ 
    void stop();

private:
    //void downcaseAndRemoveWwwPrefix(const char *domainName);
    //char *getDomainNameWithoutWwwPrefix();
    //bool requestIncludesOnlyOneQuestion();
    //void replyWithIP();
    //void replyWithCustomCode();
};
#endif
