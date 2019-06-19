#ifndef _ETHERNET_DHCP_H_
#define _ETHERNET_DHCP_H_

class DhcpClass
{
private:
    int request_DHCP_lease();
    void reset_DHCP_lease();
    void presend_DHCP();
    void send_DHCP_MESSAGE(uint8_t, uint16_t);
    void printByte(char *, uint8_t);
    uint8_t parseDHCPResponse(unsigned long responseTimeout, uint32_t &transactionId);
public:
    uint32_t getLocalIP();
    uint32_t getSubnetMask();
    uint32_t getGatewayIp();
    uint32_t getDhcpServerIp();
    uint32_t getDnsServerIp();
    char * getLocalIPStr();
    char * getSubnetMaskStr();
    char * getGatewayIpStr();
    char * getDhcpServerIpStr();
    char * getDnsServerIpStr();
    int beginWithDHCP(uint8_t *, unsigned long timeout=60000, unsigned long responseTimeout = 4000);
    int checkLease();
};

#endif
