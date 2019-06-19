#include "Dhcp.h"

int DhcpClass::request_DHCP_lease()
{
}

void DhcpClass::reset_DHCP_lease()
{
}

void DhcpClass::presend_DHCP()
{
}

void DhcpClass::send_DHCP_MESSAGE(uint8_t, uint16_t)
{
}

void DhcpClass::printByte(char *, uint8_t)
{
}

uint8_t DhcpClass::parseDHCPResponse(unsigned long responseTimeout, uint32_t &transactionId)
{
}

uint32_t DhcpClass::getLocalIP()
{
}

uint32_t DhcpClass::getSubnetMask()
{
}

uint32_t DhcpClass::getGatewayIp()
{
}

uint32_t DhcpClass::getDhcpServerIp()
{
}

uint32_t DhcpClass::getDnsServerIp()
{
}

char * DhcpClass::getLocalIPStr()
{
}

char * DhcpClass::getSubnetMaskStr()
{
}

char * DhcpClass::getGatewayIpStr()
{
}

char * DhcpClass::getDhcpServerIpStr()
{
}

char * DhcpClass::getDnsServerIpStr()
{
}

int DhcpClass::beginWithDHCP(uint8_t *, unsigned long timeout=60000, unsigned long responseTimeout = 4000)
{
}

int DhcpClass::checkLease()
{
}
