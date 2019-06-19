/**
 * @file IPAddress.h
 *
 * @brief   IPAddress Module
 *
 * @author Huangleilei
 *
 * Copyright (c) 2019 Winner Microelectronics Co., Ltd.
 */
#ifndef _IP_ADDRESS_H_
#define _IP_ADDRESS_H_

#include <stdint.h>
#include "Printable.h"
#include "WString.h"

class IPAddress : public Printable
{
private:
    union {
        uint8_t bytes[4];  // IPv4 address
        uint32_t dword;
    } _address;
    uint8_t *raw_address()
    {
        return _address.bytes;
    }

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
 * @defgroup WiFi_library IPAddress_class
 * @brief IPAddress class
 */

/**
 * @addtogroup IPAddress_class
 * @{
 */

    /**
     * @brief         This constructor function is used to construct IPAddress object.
     * @param[in] None
     *
     * @return 		None 
     * 
     * @note 
     */ 
    IPAddress();
    /**
     * @brief         This constructor function is used to construct IPAddress object.
     * @param[in] first_oct Specify the first_oct - uint8_t
     * @param[in] sec_oct Specify the sec_oct - uint8_t
     * @param[in] third_oct Specify the third_oct - uint8_t
     * @param[in] fourth_oct Specify the fourth_oct - uint8_t
     *
     * @return 		None 
     * 
     * @note 
     */ 
    IPAddress(uint8_t first_oct, uint8_t sec_oct, uint8_t third_oct, uint8_t fourth_oct);
    /**
     * @brief         This constructor function is used to construct IPAddress object.
     * @param[in] address Specify the address - uint32_t
     *
     * @return 		None 
     * 
     * @note 
     */ 
    IPAddress(uint32_t address);
    /**
     * @brief         This constructor function is used to construct IPAddress object.
     * @param[in] address Specify the address - uint8_t *
     *
     * @return 		None 
     * 
     * @note 
     */ 
    IPAddress(const uint8_t *address);

    /**
     * @brief       This operator overloading function is used to overloading 'uint32_t' operator.
     * @param[in] None
     *
     * @return      The value of the IPAddress object in uint32_t type.
     * 
     * @note 
     */ 
    operator uint32_t() const {
        return _address.dword;
    }
    /**
     * @brief       This operator overloading function is used to overloading '==' operator.
     * @param[in] addr Sepcify the address - IPAddress
     *
     * @return      bool
     * 
     * @note 
     */ 
    bool operator==(const IPAddress& addr) const {
        return _address.dword == addr._address.dword;
    }
    /**
     * @brief       This operator overloading function is used to overloading '==' operator.
     * @param[in] addr Sepcify the address - uint32_t
     *
     * @return      bool
     * 
     * @note 
     */ 
    bool operator==(uint32_t addr) const {
        return _address.dword == addr;
    }
    /**
     * @brief       This operator overloading function is used to overloading '==' operator.
     * @param[in] addr Sepcify the address - uint8_t*
     *
     * @return      If they are equal, true is return, otherwise, false is return.
     * 
     * @note 
     */ 
    bool operator==(const uint8_t* addr) const;

    // Overloaded index operator to allow getting and setting individual octets of the address
    /**
     * @brief       This operator overloading function is used to overloading '[]' operator.
     * @param[in] index Sepcify the address value of index.
     *
     * @return 	    the target value of IPAddress object.
     * 
     * @note 
     */ 
    uint8_t operator[](int index) const {
        return _address.bytes[index];
    }
    /**
     * @brief       This operator overloading function is used to overloading '[]' operator.
     * @param[in] index Sepcify the address value of index.
     *
     * @return 	    the target value of IPAddress object.
     * 
     * @note 
     */ 
    uint8_t& operator[](int index) {
        return _address.bytes[index];
    }

    // Overloaded copy operators to allow initialisation of IPAddress objects from other types
    /**
     * @brief       This operator overloading function is used to overloading '=' operator.
     * @param[in] address Sepcify the address - uint8_t *
     *
     * @return 	    the target IPAddress object.
     * 
     * @note 
     */ 
    IPAddress& operator=(const uint8_t *address);
    /**
     * @brief       This operator overloading function is used to overloading '=' operator.
     * @param[in] address Sepcify the address - uint32_t
     *
     * @return 	    the target IPAddress object.
     * 
     * @note 
     */ 
    IPAddress& operator=(uint32_t address);
    /**
     * @brief       This function is used to transform from IPAddress object to String object.
     * @param[in] None
     *
     * @return 	    the target String object.
     * 
     * @note 
     */ 
    String toString() const;
    /**
     * @brief       This function is used to create the object from a string buffer.
     * @param[in] address Specify the string buffer.
     *
     * @return 	    bool 
     * 
     * @note 
     */ 
    bool fromString(const char *address);
    /**
     * @brief         This function is used to create the object from a String object.
     * @param[in] address Specify the String object.
     *
     * @return 	    bool 
     * 
     * @note 
     */ 
    bool fromString(const String &address);

    /**
     * @brief         This virtual function is used to called by print/println function.
     * @param[in] p Specify the Print object.
     *
     * @return 	    bool 
     * 
     * @note The length of print successfully.
     */ 
    virtual size_t printTo(Print& p) const;

/**
 * @}
 */

/**
 * @}
 */

};

#endif//_IP_ADDRESS_H_