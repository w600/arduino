/**
 * @file    WiFiUDP.h
 *
 * @brief   WiFiUDP Module
 *
 * @author  WinnerMicro
 *
 * Copyright (c) 2019 Winner Microelectronics Co., Ltd.
 */
#ifndef _WIFI_UDP_H_
#define _WIFI_UDP_H_

#include <Udp.h>
#include <slist.h>

#define UDP_TX_PACKET_MAX_SIZE 8192

class UdpContext;

class WiFiUDP : public UDP, public SList<WiFiUDP> {
private:
  UdpContext* _ctx;

public:

/**
 * @defgroup WiFi_library WiFi_library
 * @brief WiFi library
 */

/**
 * @addtogroup WiFi_library
 * @{
 */

/**
 * @defgroup WiFi_library UDP_class
 * @brief UDP class
 */

/**
 * @addtogroup UDP_class
 * @{
 */

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
  WiFiUDP();
  WiFiUDP(const WiFiUDP& other);
  WiFiUDP& operator=(const WiFiUDP& rhs);

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
  ~WiFiUDP();

  operator bool() const { return _ctx != 0; }

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
  virtual uint8_t begin(uint16_t port);	

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
  virtual void stop();

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
  uint8_t beginMulticast(IPAddress interfaceAddr, IPAddress multicast, uint16_t port); 

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
  virtual int beginPacket(IPAddress ip, uint16_t port);

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
  virtual int beginPacket(const char *host, uint16_t port);

  /**
   * @brief      This function is used to start building up a packet to send to the multicast address.
   *
   * @param[in]  multicastAddress   muticast address to send to
   * @param[in]  port               port number
   * @param[in]  interfaceAddress   the local IP address of the interface that should be used,
   *                                use WiFi.localIP() or WiFi.softAPIP() depending on the interface you need
   * @param[in]  ttl                multicast packet TTL (default is 1)
   *
   * @param[out] None
   *
   * @retval     1   successful
   * @retval     0   there was a problem with the supplied IP address or port
   * 
   * @note 
   */
  virtual int beginPacketMulticast(IPAddress multicastAddress, 
                                   uint16_t port, 
                                   IPAddress interfaceAddress, 
                                   int ttl = 1);

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
  virtual int endPacket();

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
  virtual size_t write(uint8_t);

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
  virtual size_t write(const uint8_t *buffer, size_t size);
  
  using Print::write;

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
  virtual int parsePacket();

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
  virtual int available();

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
  virtual int read();

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
  virtual int read(unsigned char* buffer, size_t len);

  /**
   * @brief      Reads UDP data from the specified buffer. 
   *             If no arguments are given, it will return the next character in the buffer.
   *
   * @param[in]  buffer   buffer to hold incoming packets (char*)
   * @param[in]  len      maximum size of the buffer (int)
   *
   * @param[out] None
   *
   * @retval     -1      no buffer is available
   * @retval     other   the size of the buffer
   * 
   * @note 
   */
  virtual int read(char* buffer, size_t len) { return read((unsigned char*)buffer, len); };

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
  virtual int peek();

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
  virtual void flush();

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
  virtual IPAddress remoteIP();

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
  virtual uint16_t remotePort();

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
  IPAddress destinationIP();

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
  uint16_t localPort();

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
  static void stopAll();

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
  static void stopAllExcept(WiFiUDP * exC);

/**
 * @}
 */

/**
 * @}
 */

};


#endif /* _WIFI_UDP_H_ */
