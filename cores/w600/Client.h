/**
 * @file    Client.h
 *
 * @brief   Client Module
 *
 * @author  WinnerMicro
 *
 * Copyright (c) 2019 Winner Microelectronics Co., Ltd.
 */
#ifndef _CLIENT_H_
#define _CLIENT_H_

#include "Print.h"
#include "Stream.h"
#include "IPAddress.h"

class Client: public Stream {

    public:
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
        virtual int connect(IPAddress ip, uint16_t port) =0;

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
        virtual int connect(const char *host, uint16_t port) =0;

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
        virtual size_t write(uint8_t) =0;

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
        virtual size_t write(const uint8_t *buf, size_t size) =0;

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
        virtual int available() = 0;

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
        virtual int read() = 0;

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
        virtual int read(uint8_t *buf, size_t size) = 0;

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
        virtual void stop() = 0;

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
        virtual uint8_t connected() = 0;

        virtual operator bool() = 0;
    //protected:
        //uint8_t* rawIPAddress(IPAddress& addr) {
        //    return addr.raw_address();
        //}
        //;
};

#endif/* _CLIENT_H_ */

