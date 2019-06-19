/**
 * @file    Udp.h
 *
 * @brief   UDP Module
 *
 * @author  WinnerMicro
 *
 * Copyright (c) 2019 Winner Microelectronics Co., Ltd.
 */
#ifndef _UDP_H_
#define _UDP_H_

#include "Stream.h"
#include "IPAddress.h"

class UDP : public Stream
{
public:
    /**
     * @brief      This function is used to initializes the UDP library 
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
    virtual uint8_t begin(uint16_t) = 0;

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
    virtual void stop() = 0;

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
    virtual int beginPacket(IPAddress ip, uint16_t port) =0;

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
    virtual int beginPacket(const char *host, uint16_t port) = 0;

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
    virtual int endPacket() = 0;

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
    virtual size_t write(uint8_t) = 0;

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
    virtual size_t write(const uint8_t *buffer, size_t size) = 0;

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
     * @note       parsePacket() must be called before reading the buffer with UDP.read().
     */
    virtual int parsePacket() = 0;

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
     * @note       This function can only be successfully called after UDP.parsePacket().
     *             available() inherits from the Stream utility class.
     */
    virtual int available() = 0;

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
    virtual int read() = 0;

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
    virtual int read(unsigned char *buffer, size_t len) = 0;

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
    virtual int read(char *buffer, size_t len) = 0;

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
    virtual int peek() = 0;

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
    virtual void flush() = 0;

    //virtual char *remoteIP() = 0;

    /**
     * @brief      This function is used to gets the IP address of the remote connection.
     *
     * @param[in]  None
     *
     * @param[out] None
     *
     * @retval     the IP address of the host who sent the current incoming packet(4 bytes)
     * 
     * @note       This function must be called after UDP.parsePacket().
     */
    virtual IPAddress remoteIP() =0;

    /**
     * @brief      This function is used to gets the port of the remote UDP connection.
     *
     * @param[in]  None
     *
     * @param[out] None
     *
     * @retval     The port of the host who sent the current incoming packet
     * 
     * @note       This function must be called after UDP.parsePacket().
     */
    virtual uint16_t remotePort() = 0;
    
protected:
        //uint8_t* rawIPAddress(IPAddress& addr) {
};

#endif
