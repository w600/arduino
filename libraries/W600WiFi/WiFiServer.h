/**
 * @file WiFiServer.h
 *
 * @brief   WiFiServer Module
 *
 * @author Huang Leilei
 *
 * Copyright (c) 2019 Winner Microelectronics Co., Ltd.
 */
#ifndef _WIFI_SERVER_H_
#define _WIFI_SERVER_H_

extern "C" {
#include "lwip/err.h"
#include "lwip/tcp.h"
}

#include "Server.h"
#include "IPAddress.h"

//class ClientContext;
class WiFiClient;

class WiFiServer : public Server {
  // Secure server needs access to all the private entries here
protected:
  uint16_t _port;
  IPAddress _addr;
  tcp_pcb* _pcb;

  //ClientContext* _unclaimed;
  //ClientContext* _discarded;
  bool _noDelay = false;

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
 * @defgroup WiFi_library Server_class
 * @brief Server class
 */

/**
 * @addtogroup Server_class
 * @{
 */
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
  WiFiServer(IPAddress addr, uint16_t port);
  
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
  WiFiServer(uint16_t port);
  virtual ~WiFiServer() {}
  //WiFiClient available(uint8_t* status = NULL);
  bool hasClient();
  
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
  void begin();
  
  /**
   * @brief         This function is used to start the WiFiServer.
   *
   * @param[in] port Specify the port used by the object.
   *
   * @return      None 
   * 
   * @note 
   */ 
  void begin(uint16_t port);
  
  /**
   * @brief         This function is used to set no-delay flag.
   *
   * @param[in] nodelay Specify the flag of no-delay
   *
   * @return      None 
   * 
   * @note 
   */ 
  void setNoDelay(bool nodelay);
  
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
  bool getNoDelay();
  
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
  virtual size_t write(uint8_t);
  
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
  virtual size_t write(const uint8_t *buf, size_t size);
  
  uint8_t status();
  
  /**
   * @brief         This function is used to close the connection.
   *
   * @param[in] None
   *
   * @return      None 
   * 
   * @note 
   */ 
  void close();
  
  /**
   * @brief         This function is used to close the connection.
   *
   * @param[in] None
   *
   * @return      None 
   * 
   * @note 
   */ 
  void stop();

  //using Print::write;
  long _accept(tcp_pcb* newpcb, long err);
  //void   _discard(ClientContext* client);

  static err_t _s_accept(void *arg, tcp_pcb* newpcb, err_t err);
  //static void _s_discard(void* server, ClientContext* ctx);

/**
 * @}
 */

/**
 * @}
 */

};


#endif
