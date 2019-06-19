/**
 * @file    WiFiClient.cpp
 *
 * @brief   WiFiClient Module
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

#include "debug.h"
#include "W600WiFi.h"
#include "WiFiClient.h"
#include "WiFiServer.h"
#include "lwip/opt.h"
#include "lwip/ip.h"
#include "lwip/tcp.h"
#include "lwip/inet.h"
#include "lwip/netif.h"
#include "ClientContext.h"

uint16_t WiFiClient::_localPort = 0;

template<>
WiFiClient* SList<WiFiClient>::_s_first = 0;

/**
 * @brief      This function is constructor, 
 *             it's used to creates a client that can connect to to a 
 *             specified internet IP address and port as defined in client.connect().
 *
 * @param[in]  None
 *
 * @param[out] None
 *
 * @return     None
 * 
 * @note 
 */
WiFiClient::WiFiClient()
: _client(0)
{
    _timeout = 5000;
    WiFiClient::_add(this);
}

WiFiClient::WiFiClient(ClientContext* client)
: _client(client)
{
    _timeout = 5000;
    _client->ref();
    WiFiClient::_add(this);
}

WiFiClient::WiFiClient(const WiFiClient& other)
{
    _client = other._client;
    _timeout = other._timeout;
    _localPort = other._localPort;
    if (_client)
        _client->ref();
    WiFiClient::_add(this);
}

WiFiClient& WiFiClient::operator=(const WiFiClient& other)
{
   if (_client)
        _client->unref();
    _client = other._client;
    _timeout = other._timeout;
    _localPort = other._localPort;
    if (_client)
        _client->ref();
    return *this;
}

/**
 * @brief      This function is deconstructor, it's used to release WiFiClient class.
 *
 * @param[in]  None
 *
 * @param[out] None
 *
 * @return     None
 * 
 * @note 
 */
WiFiClient::~WiFiClient()
{
    WiFiClient::_remove(this);
    if (_client)
        _client->unref();
}

/**
 * @brief      This function is used to connect to the IP address and port specified in the constructor.
 *
 * @param[in]  host   the domain name the client will connect to (string, ex.:"arduino.cc")
 * @param[in]  port   the port that the client will connect to (int)
 *
 * @param[out] None
 *
 * @retval     1   the connection succeeds
 * @retval     0   the connection failed
 * 
 * @note 
 */
int WiFiClient::connect(const char* host, uint16_t port)
{
    IPAddress remote_addr;
    if (WiFi.hostByName(host, remote_addr, _timeout))
    {
        return connect(remote_addr, port);
    }
    return 0;
}

int WiFiClient::connect(const String host, uint16_t port)
{
    return connect(host.c_str(), port);
}

/**
 * @brief      This function is used to connect to the IP address and port specified in the constructor.
 *
 * @param[in]  ip     the IP address that the client will connect to (array of 4 bytes)
 * @param[in]  port   the port that the client will connect to (int)
 *
 * @param[out] None
 *
 * @retval     1   the connection succeeds
 * @retval     0   the connection failed
 * 
 * @note 
 */
int WiFiClient::connect(IPAddress ip, uint16_t port)
{
    ip_addr_t addr;
    addr.addr = ip;

    if (_client) {
        stop();
        _client->unref();
        _client = nullptr;
    }

    // if the default interface is down, tcp_connect exits early without
    // ever calling tcp_err
    // http://lists.gnu.org/archive/html/lwip-devel/2010-05/msg00001.html
#if LWIP_VERSION_MAJOR == 1
    netif* interface = ip_route(&addr);
    if (!interface) {
        AR_DBG("no route to host\r\n");
        return 0;
    }
#endif

    tcp_pcb* pcb = tcp_new();
    if (!pcb)
        return 0;

    if (_localPort > 0) {
        pcb->local_port = _localPort++;
    }

    _client = new ClientContext(pcb, nullptr, nullptr);
    _client->ref();
    _client->setTimeout(_timeout);
    int res = _client->connect(&addr, port);
    if (res == 0) {
        _client->unref();
        _client = nullptr;
        return 0;
    }

    return 1;
}

/**
 * @brief      This function is used to set no delay for the tcp connection.
 *
 * @param[in]  None
 *
 * @param[out] None
 *
 * @retval     the local port number
 * 
 * @note
 */
void WiFiClient::setNoDelay(bool nodelay) {
    if (!_client)
        return;
    _client->setNoDelay(nodelay);
}

/**
 * @brief      This function is used to get whether no delay of the tcp connection.
 *
 * @param[in]  None
 *
 * @param[out] None
 *
 * @retval     true    no delay
 * @retval     false   delay
 * 
 * @note
 */
bool WiFiClient::getNoDelay() {
    if (!_client)
        return false;
    return _client->getNoDelay();
}

/**
 * @brief      This function is used to get the length that can be written.
 *
 * @param[in]  None
 *
 * @param[out] None
 *
 * @retval     the length that can be written
 * 
 * @note
 */
size_t WiFiClient::availableForWrite ()
{
    return _client? _client->availableForWrite(): 0;
}

/**
 * @brief      This function is used to write data to the server the client is connected to.
 *
 * @param[in]  the char to write
 *
 * @param[out] None
 *
 * @retval     the number of characters written. it is not necessary to read this value.
 * 
 * @note
 */
size_t WiFiClient::write(uint8_t b)
{
    return write(&b, 1);
}

/**
 * @brief      This function is used to write data to the server the client is connected to.
 *
 * @param[in]  buf    the byte to write
 * @param[in]  size   the size of the buf
 *
 * @param[out] None
 *
 * @retval     the number of characters written. it is not necessary to read this value.
 * 
 * @note
 */
size_t WiFiClient::write(const uint8_t *buf, size_t size)
{
    if (!_client || !size)
    {
        return 0;
    }
    _client->setTimeout(_timeout);
    return _client->write(buf, size);
}

size_t WiFiClient::write(Stream& stream, size_t unused)
{
    (void) unused;
    return WiFiClient::write(stream);
}

size_t WiFiClient::write(Stream& stream)
{
    if (!_client || !stream.available())
    {
        return 0;
    }
    _client->setTimeout(_timeout);
    return _client->write(stream);
}

size_t WiFiClient::write_P(PGM_P buf, size_t size)
{
    if (!_client || !size)
    {
        return 0;
    }
    _client->setTimeout(_timeout);
    return _client->write_P(buf, size);
}

/**
 * @brief      Returns the number of bytes available for reading 
 *             (That is, the amount of data that has been written to the client by the server it is connected to).
 *
 * @param[in]  None
 *
 * @param[out] None
 *
 * @retval     The number of bytes available
 * 
 * @note       available() inherits from the Stream utility class.
 */
int WiFiClient::available()
{
    if (!_client)
        return false;

    int result = _client->getSize();

    if (!result) {
        delay(4);
    }
    return result;
}

/**
 * @brief      Read the next byte received from the server 
 *             the client is connected to (after the last call to read()).
 *
 * @param[in]  None
 *
 * @param[out] None
 *
 * @retval     -1      none is available.
 * @retval     other   The next character
 * 
 * @note       read() inherits from the Stream utility class
 */
int WiFiClient::read()
{
    if (!available())
        return -1;

    return _client->read();
}

/**
 * @brief      Read the next byte received from the server 
 *             the client is connected to (after the last call to read()).
 *
 * @param[in]  buf    the byte to read
 * @param[in]  size   the size of the buf
 *
 * @param[out] None
 *
 * @retval     -1      none is available.
 * @retval     other   The next byte
 * 
 * @note       read() inherits from the Stream utility class
 */
int WiFiClient::read(uint8_t* buf, size_t size)
{
    return (int) _client->read(reinterpret_cast<char*>(buf), size);
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
int WiFiClient::peek()
{
    if (!available())
        return -1;

    return _client->peek();
}

size_t WiFiClient::peekBytes(uint8_t *buffer, size_t length) {
    size_t count = 0;

    if(!_client) {
        return 0;
    }

    _startMillis = millis();
    while((available() < (int) length) && ((millis() - _startMillis) < _timeout)) {
        delay(4);
    }

    if(available() < (int) length) {
        count = available();
    } else {
        count = length;
    }

    return _client->peekBytes((char *)buffer, count);
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
void WiFiClient::flush()
{
    if (_client)
        _client->wait_until_sent();
}

/**
 * @brief      This function is used to disconnect from the server.
 *
 * @param[in]  None
 *
 * @param[out] None
 *
 * @return     None
 * 
 * @note 
 */
void WiFiClient::stop()
{
    if (!_client)
        return;

    _client->close();
}

/**
 * @brief      Whether or not the client is connected. 
 *
 * @param[in]  None
 *
 * @param[out] None
 *
 * @retval     1   the client is connected
 * @retval     0   the client is disconnected
 * 
 * @note       that a client is considered connected if the connection 
 *             has been closed but there is still unread data.
 */
uint8_t WiFiClient::connected()
{
    if (!_client || _client->state() == CLOSED)
        return 0;

    return _client->state() == ESTABLISHED || available();
}

/**
 * @brief      return tcp status of WiFiClient. 
 *
 * @param[in]  None
 *
 * @param[out] None
 *
 * @retval     tcp status
 * 
 * @note
 */
uint8_t WiFiClient::status()
{
    if (!_client)
        return CLOSED;
    return _client->state();
}

WiFiClient::operator bool()
{
    return connected();
}

/**
 * @brief      This function is used to gets the IP address of the remote connection.
 *
 * @param[in]  None
 *
 * @param[out] None
 *
 * @retval     the IP address(4 bytes)
 * 
 * @note
 */
IPAddress WiFiClient::remoteIP()
{
    if (!_client)
        return IPAddress();

    return IPAddress(_client->getRemoteAddress());
}

/**
 * @brief      This function is used to gets the port of the remote connection.
 *
 * @param[in]  None
 *
 * @param[out] None
 *
 * @retval     The port number
 * 
 * @note
 */
uint16_t WiFiClient::remotePort()
{
    if (!_client)
        return 0;

    return _client->getRemotePort();
}

/**
 * @brief      This function is used to gets the IP address of the local tcp connection.
 *
 * @param[in]  None
 *
 * @param[out] None
 *
 * @retval     the IP address(4 bytes)
 * 
 * @note
 */
IPAddress WiFiClient::localIP()
{
    if (!_client)
        return IPAddress();

    return IPAddress(_client->getLocalAddress());
}

/**
 * @brief      This function is used to gets the port of the local tcp connection.
 *
 * @param[in]  None
 *
 * @param[out] None
 *
 * @retval     the local port number
 * 
 * @note
 */
uint16_t WiFiClient::localPort()
{
    if (!_client)
        return 0;

    return _client->getLocalPort();
}

/**
 * @brief      This function is used to stop all WiFiClient session.
 *
 * @param[in]  None
 *
 * @param[out] None
 *
 * @retval     None
 * 
 * @note
 */
void WiFiClient::stopAll()
{
    for (WiFiClient* it = _s_first; it; it = it->_next) {
        it->stop();
    }
}

/**
 * @brief      This function is used to stop all WiFiClient session without exC.
 *
 * @param[in]  None
 *
 * @param[out] None
 *
 * @retval     None
 * 
 * @note
 */
void WiFiClient::stopAllExcept(WiFiClient* except) 
{
    for (WiFiClient* it = _s_first; it; it = it->_next) {
        if (it != except) {
            it->stop();
        }
    }
}

/**
 * @brief      This function is used to set keep alive.
 *
 * @param[in]  idle_sec   idle time interval
 * @param[in]  intv_sec   keep alive time interval
 * @param[in]  count      keep alive count
 *
 * @param[out] None
 *
 * @retval     None
 * 
 * @note
 */
void WiFiClient::keepAlive (uint16_t idle_sec, uint16_t intv_sec, uint8_t count)
{
    _client->keepAlive(idle_sec, intv_sec, count);
}

/**
 * @brief      This function is used to get whether enable keep alive.
 *
 * @param[in]  None
 *
 * @param[out] None
 *
 * @retval     true    enable
 * @retval     false   disable
 * 
 * @note
 */
bool WiFiClient::isKeepAliveEnabled () const
{
    return _client->isKeepAliveEnabled();
}

/**
 * @brief      This function is used to get idle time interval.
 *
 * @param[in]  None
 *
 * @param[out] None
 *
 * @retval     idle time interval
 * 
 * @note
 */
uint16_t WiFiClient::getKeepAliveIdle () const
{
    return _client->getKeepAliveIdle();
}

/**
 * @brief      This function is used to get keep alive time interval.
 *
 * @param[in]  None
 *
 * @param[out] None
 *
 * @retval     keep alive time interval
 * 
 * @note
 */
uint16_t WiFiClient::getKeepAliveInterval () const
{
    return _client->getKeepAliveInterval();
}

/**
 * @brief      This function is used to get keep alive count.
 *
 * @param[in]  None
 *
 * @param[out] None
 *
 * @retval     keep alive count
 * 
 * @note
 */
uint8_t WiFiClient::getKeepAliveCount () const
{
    return _client->getKeepAliveCount();
}
