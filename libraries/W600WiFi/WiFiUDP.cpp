/**
 * @file    WiFiUDP.cpp
 *
 * @brief   WiFiUDP Module
 *
 * @author  WinnerMicro
 *
 * Copyright (c) 2019 Winner Microelectronics Co., Ltd.
 */
#ifdef __cplusplus
extern "C"
{
	#include "wm_type_def.h"
	#include "wm_socket.h"
}
#endif

#include "wiring_time.h"
#include "debug.h"
#include "W600WiFi.h"
#include "WiFiUdp.h"
#include "lwip/opt.h"
#include "lwip/udp.h"
#include "lwip/inet.h"
#include "lwip/igmp.h"
#include "lwip/mem.h"
#include "UdpContext.h"

template<>
WiFiUDP* SList<WiFiUDP>::_s_first = 0;

/**
 * @brief      This function is constructor, 
 *             it's used to creates a named instance of the WiFiUDP class that can send and receive UDP messages.
 *
 * @param[in]  None
 *
 * @param[out] None
 *
 * @return     None
 * 
 * @note 
 */
WiFiUDP::WiFiUDP() : _ctx(0)
{
    WiFiUDP::_add(this);
}

WiFiUDP::WiFiUDP(const WiFiUDP& other)
{
    _ctx = other._ctx;
    if (_ctx)
        _ctx->ref();
    WiFiUDP::_add(this);
}

WiFiUDP& WiFiUDP::operator=(const WiFiUDP& rhs)
{
    _ctx = rhs._ctx;
    if (_ctx)
        _ctx->ref();
    return *this;
}

/**
 * @brief      This function is deconstructor, it's used to release WiFiUDP class.
 *
 * @param[in]  None
 *
 * @param[out] None
 *
 * @return     None
 * 
 * @note 
 */
WiFiUDP::~WiFiUDP()
{
    WiFiUDP::_remove(this);
    if (_ctx)
        _ctx->unref();
}

/**
 * @brief      This function is used to initializes the WiFiUDP library 
 *             and network settings, Starts UDP socket, listening at local port.
 *
 * @param[in]  the local port to listen on
 *
 * @param[out] None
 *
 * @retval     1   successful
 * @retval     0   there are no sockets available to use
 * 
 * @note 
 */
uint8_t WiFiUDP::begin(uint16_t port)
{
    if (_ctx) {
        _ctx->unref();
        _ctx = 0;
    }

    _ctx = new UdpContext;
    _ctx->ref();
    ip_addr_t addr;
    addr.addr = INADDR_ANY;
    return (_ctx->listen(addr, port)) ? 1 : 0;
}

/**
 * @brief      This function is used to join a multicast group and listen on the given port.
 *
 * @param[in]  interfaceAddress   the local IP address of the interface that should be used,
 *                                use WiFi.localIP() or WiFi.softAPIP() depending on the interface you need
 * @param[in]  multicast          multicast group
 * @param[in]  port               port number
 *
 * @param[out] None
 *
 * @retval     1   successful
 * @retval     0   failed
 * 
 * @note 
 */
uint8_t WiFiUDP::beginMulticast(IPAddress interfaceAddr, IPAddress multicast, uint16_t port)
{
    if (_ctx) {
        _ctx->unref();
        _ctx = 0;
    }

    ip_addr_t ifaddr;
    ifaddr.addr = (uint32_t) interfaceAddr;
    ip_addr_t multicast_addr;
    multicast_addr.addr = (uint32_t) multicast;

    if (igmp_joingroup(&ifaddr, &multicast_addr)!= ERR_OK) {
        return 0;
    }

    _ctx = new UdpContext;
    _ctx->ref();
    if (!_ctx->listen(*IP_ADDR_ANY, port)) {
        return 0;
    }

    return 1;
}

/**
 * @brief      Get the number of bytes (characters) available for reading from the buffer. 
 *             This is is data that's already arrived.
 *
 * @param[in]  None
 *
 * @param[out] None
 *
 * @retval     0       parsePacket hasn't been called yet
 * @retval     other   the number of bytes available in the current packet
 * 
 * @note       This function can only be successfully called after parsePacket().
 *             available() inherits from the Stream utility class.
 */
int WiFiUDP::available() {
    int result = 0;

    if (_ctx) {
        result = static_cast<int>(_ctx->getSize());
    }

    if (!result) {
        // yielding here will not make more data "available",
        // but it will prevent the system from going into WDT reset
        delay(4);
    }

    return result;
}

/**
 * @brief      This function is used to disconnect from the server.
 *             Release any resource being used during the UDP session.
 *
 * @param[in]  None
 *
 * @param[out] None
 *
 * @return     None
 * 
 * @note 
 */
void WiFiUDP::stop()
{
    if (_ctx) {
        _ctx->disconnect();
        _ctx->unref();
    }
    _ctx = 0;
}

/**
 * @brief      This function is used to starts a connection to write UDP data to the remote connection.
 *
 * @param[in]  host   the address of the remote host. It accepts a character string or an IPAddress
 * @param[in]  port   the port of the remote connection (int)
 *
 * @param[out] None
 *
 * @retval     1   successful
 * @retval     0   there was a problem with the supplied IP address or port
 * 
 * @note 
 */
int WiFiUDP::beginPacket(const char *host, uint16_t port)
{
    IPAddress remote_addr;
    if (WiFi.hostByName(host, remote_addr))
    {
        return beginPacket(remote_addr, port);
    }
    return 0;
}

/**
 * @brief      This function is used to starts a connection to write UDP data to the remote connection.
 *
 * @param[in]  ip     the IP address of the remote connection (4 bytes)
 * @param[in]  port   the port of the remote connection (int)
 *
 * @param[out] None
 *
 * @retval     1   successful
 * @retval     0   there was a problem with the supplied IP address or port
 * 
 * @note 
 */
int WiFiUDP::beginPacket(IPAddress ip, uint16_t port)
{
    ip_addr_t addr;
    addr.addr = ip;

    if (!_ctx) {
        _ctx = new UdpContext;
        _ctx->ref();
    }
    return (_ctx->connect(addr, port)) ? 1 : 0;
}

/**
 * @brief	   This function is used to start building up a packet to send to the multicast address.
 *
 * @param[in]  multicastAddress   muticast address to send to
 * @param[in]  port 			  port number
 * @param[in]  interfaceAddress   the local IP address of the interface that should be used,
 *								  use WiFi.localIP() or WiFi.softAPIP() depending on the interface you need
 * @param[in]  ttl				  multicast packet TTL (default is 1)
 *
 * @param[out] None
 *
 * @retval	   1   successful
 * @retval	   0   there was a problem with the supplied IP address or port
 * 
 * @note 
 */
int WiFiUDP::beginPacketMulticast(IPAddress multicastAddress, uint16_t port,
    IPAddress interfaceAddress, int ttl)
{
    ip_addr_t mcastAddr;
    mcastAddr.addr = multicastAddress;
    ip_addr_t ifaceAddr;
    ifaceAddr.addr = interfaceAddress;

    if (!_ctx) {
        _ctx = new UdpContext;
        _ctx->ref();
    }
    if (!_ctx->connect(mcastAddr, port)) {
        return 0;
    }
    _ctx->setMulticastInterface(ifaceAddr);
    _ctx->setMulticastTTL(ttl);
    return 1;
}

/**
 * @brief      This function is used to called after writing UDP data to the remote connection. 
 *             It finishes off the packet and send it.
 *
 * @param[in]  None
 *
 * @param[out] None
 *
 * @retval     1   the packet was sent successfully
 * @retval     0   there was an error
 * 
 * @note 
 */
int WiFiUDP::endPacket()
{
    if (!_ctx)
        return 0;

    return (_ctx->send()) ? 1 : 0;
}

/**
 * @brief      This function is used to writes UDP data to the remote connection.
 *
 * @param[in]  the outgoing byte
 *
 * @param[out] None
 *
 * @retval     single byte into the packet
 * 
 * @note       Must be wrapped between beginPacket() and endPacket(). 
 *             beginPacket() initializes the packet of data, 
 *             it is not sent until endPacket() is called.
 */
size_t WiFiUDP::write(uint8_t byte)
{
    return write(&byte, 1);
}

/**
 * @brief      This function is used to writes UDP data to the remote connection.
 *
 * @param[in]  buffer   the outgoing message
 * @param[in]  size     the size of the buffer
 *
 * @param[out] None
 *
 * @retval     bytes size from buffer into the packet
 * 
 * @note       Must be wrapped between beginPacket() and endPacket(). 
 *             beginPacket() initializes the packet of data, 
 *             it is not sent until endPacket() is called.
 */
size_t WiFiUDP::write(const uint8_t *buffer, size_t size)
{
    if (!_ctx)
        return 0;

    return _ctx->append(reinterpret_cast<const char*>(buffer), size);
}

/**
 * @brief      It starts processing the next available incoming packet, 
 *             checks for the presence of a UDP packet, and reports the size.
 *
 * @param[in]  None
 *
 * @param[out] None
 *
 * @retval     0       no packets are available
 * @retval     other   the size of the packet in bytes
 * 
 * @note       parsePacket() must be called before reading the buffer with read().
 */
int WiFiUDP::parsePacket()
{
    if (!_ctx)
        return 0;

    if (!_ctx->next()) {
        delay(4);
        return 0;
    }

    return _ctx->getSize();
}

/**
 * @brief      Reads UDP data from the specified buffer. 
 *             If no arguments are given, it will return the next character in the buffer.
 *
 * @param[in]  None
 *
 * @param[out] None
 *
 * @retval     -1      no buffer is available
 * @retval     other   the characters in the buffer (char)
 * 
 * @note 
 */
int WiFiUDP::read()
{
    if (!_ctx)
        return -1;

    return _ctx->read();
}

/**
 * @brief      Reads UDP data from the specified buffer. 
 *             If no arguments are given, it will return the next character in the buffer.
 *
 * @param[in]  buffer   buffer to hold incoming packets (unsigned char*)
 * @param[in]  len      maximum size of the buffer (int)
 *
 * @param[out] None
 *
 * @retval     -1      no buffer is available
 * @retval     other   the size of the buffer
 * 
 * @note 
 */
int WiFiUDP::read(unsigned char* buffer, size_t len)
{
    if (!_ctx)
        return 0;

    return _ctx->read(reinterpret_cast<char*>(buffer), len);
}

/**
 * @brief      Read a byte from the file without advancing to the next one.  
 *             That is, successive calls to peek() will return the same value, 
 *             as will the next call to read().
 *
 * @param[in]  None
 *
 * @param[out] None
 *
 * @retval     -1      none is available
 * @retval     other   the next byte or character
 * 
 * @note       This function inherited from the Stream class. 
 *             See the Stream class main page for more information.
 */
int WiFiUDP::peek()
{
    if (!_ctx)
        return -1;

    return _ctx->peek();
}

/**
 * @brief      Discard any bytes that have been written to the client but not yet read.
 *
 * @param[in]  None
 *
 * @param[out] None
 *
 * @return     None
 * 
 * @note       flush() inherits from the Stream utility class.
 */
void WiFiUDP::flush()
{
    endPacket();
}

/**
 * @brief      This function is used to gets the IP address of the remote connection.
 *
 * @param[in]  None
 *
 * @param[out] None
 *
 * @retval     the IP address of the host who sent the current incoming packet(4 bytes)
 * 
 * @note       This function must be called after parsePacket().
 */
IPAddress WiFiUDP::remoteIP()
{
    if (!_ctx)
        return IPAddress();

    return IPAddress(_ctx->getRemoteAddress());
}

/**
 * @brief      This function is used to gets the port of the remote UDP connection.
 *
 * @param[in]  None
 *
 * @param[out] None
 *
 * @retval     The port of the host who sent the current incoming packet
 * 
 * @note       This function must be called after parsePacket().
 */
uint16_t WiFiUDP::remotePort()
{
    if (!_ctx)
        return 0;

    return _ctx->getRemotePort();
}

/**
 * @brief      This function is used to distinguish multicast and ordinary packets
 *
 * @param[in]  None
 *
 * @param[out] None
 *
 * @retval     the destination address for incoming packets
 * 
 * @note
 */
IPAddress WiFiUDP::destinationIP()
{
    IPAddress addr;

    if (!_ctx)
        return addr;

    addr = _ctx->getDestAddress();
    return addr;
}

/**
 * @brief      This function is used to gets the port of the local UDP connection.
 *
 * @param[in]  None
 *
 * @param[out] None
 *
 * @retval     the local port for outgoing packets
 * 
 * @note
 */
uint16_t WiFiUDP::localPort()
{
    if (!_ctx)
        return 0;

    return _ctx->getLocalPort();
}

/**
 * @brief      This function is used to stop all WiFiUDP session.
 *
 * @param[in]  None
 *
 * @param[out] None
 *
 * @retval     None
 * 
 * @note
 */
void WiFiUDP::stopAll()
{
    for (WiFiUDP* it = _s_first; it; it = it->_next) {
        //AR_DBG("%s %08x %08x\n", __func__, (uint32_t) it, (uint32_t) _s_first);
        it->stop();
    }
}

/**
 * @brief      This function is used to stop all WiFiUDP session without exC.
 *
 * @param[in]  None
 *
 * @param[out] None
 *
 * @retval     None
 * 
 * @note
 */
void WiFiUDP::stopAllExcept(WiFiUDP * exC) {
    for (WiFiUDP* it = _s_first; it; it = it->_next) {
        if (it->_ctx != exC->_ctx) {
            //AR_DBG("%s %08x %08x\n", __func__, (uint32_t) it, (uint32_t) _s_first);
            it->stop();
        }
    }
}

