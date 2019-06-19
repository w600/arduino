/**
 * @file WiFiServer.cpp
 *
 * @brief   WiFiServer Module
 *
 * @author Huang Leilei
 *
 * Copyright (c) 2019 Winner Microelectronics Co., Ltd.
 */

#define LWIP_INTERNAL

extern "C" {
//    #include "osapi.h"
//    #include "ets_sys.h"
}

#include "debug.h"
//#include "WiFiClient.h"
#include "WiFiServer.h"
extern "C" {
#include "lwip/opt.h"
#include "lwip/tcp.h"
#include "lwip/inet.h"
}
//#include "include/ClientContext.h"

/**
 * @brief         This constructor is used to init WiFiServer object
 *                with the address and port specify by caller.
 *
 * @param[in] addr Specify the IPv4 address.
 * @param[in] port Specify the port used by the object.
 *
 * @return      None 
 * 
 * @note 
 */ 
WiFiServer::WiFiServer(IPAddress addr, uint16_t port)
: _port(port)
, _addr(addr)
, _pcb(NULL)
{
}

/**
 * @brief         This constructor is used to init WiFiServer object
 *                with port specify by caller.
 *
 * @param[in] port Specify the port used by the object.
 *
 * @return      None 
 * 
 * @note 
 */ 
WiFiServer::WiFiServer(uint16_t port)
{
    _port = port;
    _pcb = NULL;
    memset(&_addr, 0, sizeof(_addr));
}

/**
 * @brief         This function is used to start the WiFiServer.
 *
 * @param[in] none
 *
 * @param[out]
 *
 * @return      None 
 * 
 * @note 
 */ 
void WiFiServer::begin() {
	begin(_port);
}

/**
 * @brief         This function is used to start the WiFiServer.
 *
 * @param[in] port Specify the port used by the object.
 *
 * @return      None 
 * 
 * @note 
 */ 
void WiFiServer::begin(uint16_t port) {
    WiFiServer::close();
	_port = port;
    err_t err;
    tcp_pcb* pcb = tcp_new();

    if (!pcb)
    {
        printf("[%s %d] <WiFiServer> tcp_new error!!!\n", __func__, __LINE__);
        return;
    }

    ip_addr_t local_addr;
    local_addr.addr = (uint32_t) _addr;
    pcb->so_options |= SOF_REUSEADDR;
    err = tcp_bind(pcb, &local_addr, _port);

    if (err != ERR_OK) {
        printf("[%s %d] <WiFiServer> tcp_bind error!!!\n", __func__, __LINE__);
        tcp_close(pcb);
        return;
    }

    tcp_pcb* listen_pcb = tcp_listen(pcb);
    if (!listen_pcb) {
        printf("[%s %d] <WiFiServer> tcp_listen error!!!\n", __func__, __LINE__);
        tcp_close(pcb);
        return;
    }
    _pcb = listen_pcb;
    tcp_accept(listen_pcb, (tcp_accept_fn)(WiFiServer::_s_accept));
    tcp_arg(listen_pcb, (void*) this);
}

/**
 * @brief         This function is used to set no-delay flag.
 *
 * @param[in] nodelay Specify the flag of no-delay
 *
 * @return      None 
 * 
 * @note 
 */ 
void WiFiServer::setNoDelay(bool nodelay) {
    _noDelay = nodelay;
}

/**
 * @brief         This function is used to get no-delay flag.
 *
 * @param[in] None
 *
 * @return      If the no-delay flag is true, return true, 
 *              otherwise return false.
 * 
 * @note 
 */ 
bool WiFiServer::getNoDelay() {
    return _noDelay;
}

bool WiFiServer::hasClient() {
    //if (_unclaimed)
    //    return true;
    return false;
}
/*
WiFiClient WiFiServer::available(byte* status) {
    (void) status;
    if (_unclaimed) {
        WiFiClient result(_unclaimed);
        _unclaimed = _unclaimed->next();
        result.setNoDelay(_noDelay);
        DEBUGV("WS:av\r\n");
        return result;
    }

    optimistic_yield(1000);
    return WiFiClient();
}
*/
uint8_t WiFiServer::status()  {
    if (!_pcb)
        return CLOSED;
    return _pcb->state;
}

/**
 * @brief         This function is used to close the connection.
 *
 * @param[in] None
 *
 * @return      None 
 * 
 * @note 
 */ 
void WiFiServer::close() {
    if (!_pcb) {
      return;
    }
    tcp_close(_pcb);
    _pcb = nullptr;
}

/**
 * @brief         This function is used to close the connection.
 *
 * @param[in] None
 *
 * @return      None 
 * 
 * @note 
 */ 
void WiFiServer::stop() {
    WiFiServer::close();
}

/**
 * @brief         This function is used to send the message (one byte)
 *                to peer.
 *
 * @param[in] b Specify the byte which will be sent to peer.
 *
 * @return      The length of the message sent to peer.
 * 
 * @note 
 */ 
size_t WiFiServer::write(uint8_t b) {
    return WiFiServer::write(&b, 1);
}

/**
 * @brief         This function is used to send the message to peer.
 *
 * @param[in] buf Specify the buffer which will be sent to perr.
 * @param[in] size Specify the length which will be sent.
 *
 * @return      The length of the message sent to peer.
 * 
 * @note 
 */ 
size_t WiFiServer::write(const uint8_t *buffer, size_t size) {
    // write to all clients
    // not implemented
    (void) buffer;
    (void) size;
    return 0;
}

template<typename T>
T* slist_append_tail(T* head, T* item) {
    if (!head)
        return item;
    T* last = head;
    while(last->next())
        last = last->next();
    last->next(item);
    return head;
}

long WiFiServer::_accept(tcp_pcb* apcb, long err) {
    //printf("[%s %s %d]\n", strrchr(__FILE__, '\\') + 1, __func__, __LINE__);
    (void) err;
    //DEBUGV("WS:ac\r\n");
    //ClientContext* client = new ClientContext(apcb, &WiFiServer::_s_discard, this);
    //_unclaimed = slist_append_tail(_unclaimed, client);
    tcp_accepted(_pcb);
    return ERR_OK;
}
/*
void WiFiServer::_discard(ClientContext* client) {
    (void) client;
    // _discarded = slist_append_tail(_discarded, client);
    DEBUGV("WS:dis\r\n");
}
*/
err_t WiFiServer::_s_accept(void *arg, tcp_pcb* newpcb, err_t err) {
    return reinterpret_cast<WiFiServer*>(arg)->_accept(newpcb, err);
}
/*
void WiFiServer::_s_discard(void* server, ClientContext* ctx) {
    reinterpret_cast<WiFiServer*>(server)->_discard(ctx);
}
*/
