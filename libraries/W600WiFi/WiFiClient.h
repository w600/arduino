/**
 * @file    WiFiClient.h
 *
 * @brief   WiFiClient Module
 *
 * @author  WinnerMicro
 *
 * Copyright (c) 2019 Winner Microelectronics Co., Ltd.
 */
#ifndef _WIFI_CLIENT_H_
#define _WIFI_CLIENT_H_

#include <memory>
#include "Arduino.h"
#include "Print.h"
#include "Client.h"
#include "IPAddress.h"
#include "slist.h"

#define WIFICLIENT_MAX_PACKET_SIZE 1460

#define TCP_DEFAULT_KEEPALIVE_IDLE_SEC          7200 // 2 hours
#define TCP_DEFAULT_KEEPALIVE_INTERVAL_SEC      75   // 75 sec
#define TCP_DEFAULT_KEEPALIVE_COUNT             9    // fault after 9 failures

class ClientContext;
class WiFiServer;

class WiFiClient : public Client, public SList<WiFiClient> {
protected:
  WiFiClient(ClientContext* client);

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
 * @defgroup WiFi_library Client_class
 * @brief Client class
 */

/**
 * @addtogroup Client_class
 * @{
 */

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
  WiFiClient();
  WiFiClient(const WiFiClient&);
  WiFiClient& operator=(const WiFiClient&);

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
  virtual ~WiFiClient();

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
  uint8_t status();

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
  virtual int connect(IPAddress ip, uint16_t port);

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
  virtual int connect(const char *host, uint16_t port);
  virtual int connect(const String host, uint16_t port);

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
  virtual size_t write(uint8_t);

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
  virtual size_t write(const uint8_t *buf, size_t size);
  virtual size_t write_P(PGM_P buf, size_t size);
  size_t write(Stream& stream);
  size_t write(Stream& stream, size_t unitSize) __attribute__ ((deprecated));

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
  virtual int available();

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
  virtual int read();

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
  virtual int read(uint8_t *buf, size_t size);

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
  virtual size_t peekBytes(uint8_t *buffer, size_t length);
  size_t peekBytes(char *buffer, size_t length) {
    return peekBytes((uint8_t *) buffer, length);
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
  virtual void flush();

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
  virtual void stop();

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
  virtual uint8_t connected();
  
  virtual operator bool();

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
  IPAddress remoteIP();

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
  uint16_t  remotePort();

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
  IPAddress localIP();

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
  uint16_t  localPort();

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
  bool getNoDelay();

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
  void setNoDelay(bool nodelay);

  /**
   * @brief      This function is used to set local port number.
   *
   * @param[in]  port number
   *
   * @param[out] None
   *
   * @return     None
   * 
   * @note
   */
  static void setLocalPortStart(uint16_t port) { _localPort = port; }

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
  size_t availableForWrite();

  friend class WiFiServer;

  using Print::write;

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
  static void stopAll();

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
  static void stopAllExcept(WiFiClient * c);

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
  void     keepAlive (uint16_t idle_sec = TCP_DEFAULT_KEEPALIVE_IDLE_SEC, uint16_t intv_sec = TCP_DEFAULT_KEEPALIVE_INTERVAL_SEC, uint8_t count = TCP_DEFAULT_KEEPALIVE_COUNT);

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
  bool     isKeepAliveEnabled () const;

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
  uint16_t getKeepAliveIdle () const;

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
  uint16_t getKeepAliveInterval () const;

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
  uint8_t  getKeepAliveCount () const;

  /**
   * @brief      This function is used to set disable keep alive.
   *
   * @param[in]  None
   *
   * @param[out] None
   *
   * @return     None
   * 
   * @note
   */
  void     disableKeepAlive () { keepAlive(0, 0, 0); }

/**
 * @}
 */

/**
 * @}
 */

protected:

  static int8_t _s_connected(void* arg, void* tpcb, int8_t err);
  static void _s_err(void* arg, int8_t err);

  int8_t _connected(void* tpcb, int8_t err);
  void _err(int8_t err);

  ClientContext* _client;
  static uint16_t _localPort;
};

#endif
