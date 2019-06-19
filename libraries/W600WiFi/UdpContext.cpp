#if 0
#include "UdpContext.h"

UDP_PCB *_pcb;
pbuf * _rx_buf;
bool _first_buf_taken;
size_t _rx_buff_offset;
int _refcnt;
pbuf *_tx_buf_head;
pbuf *_tx_buf_cur;
size_t _tx_buf_offst;
rxhandler_t _on_rx;
uint16_t _mcast_ttl;

bool UdpContext::new_UdpContext()
{

}

bool UdpContext::delete_UdpContext()
{

}

void UdpContext::ref()
{

}

void UdpContext::unref()
{

}


bool UdpContext::connect(ip_addr_t addr, uint16_t port)
{

}

bool UdpContext::listen(ip_addr_t addr, uint16_t port)
{

}

void UdpContext::disconnect()
{

}

void UdpContext::setMulticastInterface(ip_addr_t addr)
{

}

void UdpContext::setMulticastTTL(int ttl)
{

}

void UdpContext::onRx(rxhandler_t handler)
{

}


size_t UdpContext::getSize() const
{

}

size_t UdpContext::tell() const
{

}

void UdpContext::seek(const size_t pos)
{

}

bool UdpContext::isValidOffset(const size_t pos) const
{

}

uint32_t UdpContext::getRemoteAddress()
{

}
/*
char *UdpContext::getRemoteAddress()
{

}
*/
uint16_t UdpContext::getRemotePort()
{

}

uint32_t UdpContext::getDestAddress()
{

}
/*
char *UdpContext::getDestAddress()
{

}
*/
uint16_t UdpContext::getLocalPort()
{

}

bool UdpContext::next()
{

}

/*
int UdpContext::read()
{

}

size_t UdpContext::read(char *dst, size_t size)
{

}
*/

int UdpContext::peek()
{

}

void UdpContext::flush()
{

}

size_t UdpContext::append(const char *data, size_t size)
{

}

bool UdpContext::send(ip_addr_t *addr, uint16_t port)
{

}


void UdpContext::_reserve(size_t size)
{

}

void UdpContext::_consume(size_t size)
{

}

void UdpContext::_recv(UDP_PCB *upcb, pbuf *pb,
        const ip_addr_t *addr, u16_t port)
{

}

void UdpContext::_s_recv(void *arg,
        UDP_PCB *upcb, pbuf *p, ip_addr_t *addr, u16_t port)
{

}
#endif
