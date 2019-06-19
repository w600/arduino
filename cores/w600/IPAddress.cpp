/**
 * @file IPAddress.cpp
 *
 * @brief   IPAddress Module
 *
 * @author Huangleilei
 *
 * Copyright (c) 2019 Winner Microelectronics Co., Ltd.
 */
#include "IPAddress.h"
#include "Print.h"

/**
 * @brief         This constructor function is used to construct IPAddress object.
 * @param[in] None
 *
 * @return      None 
 * 
 * @note 
 */ 
IPAddress::IPAddress() {
    _address.dword = 0;
}

/**
 * @brief         This constructor function is used to construct IPAddress object.
 * @param[in] first_oct Specify the first_oct - uint8_t
 * @param[in] sec_oct Specify the sec_oct - uint8_t
 * @param[in] third_oct Specify the third_oct - uint8_t
 * @param[in] fourth_oct Specify the fourth_oct - uint8_t
 *
 * @return      None 
 * 
 * @note 
 */ 
IPAddress::IPAddress(uint8_t first_octet, uint8_t second_octet, uint8_t third_octet, uint8_t fourth_octet) {
    _address.bytes[0] = first_octet;
    _address.bytes[1] = second_octet;
    _address.bytes[2] = third_octet;
    _address.bytes[3] = fourth_octet;
}

/**
 * @brief         This constructor function is used to construct IPAddress object.
 * @param[in] address Specify the address - uint32_t
 *
 * @return      None 
 * 
 * @note 
 */ 
IPAddress::IPAddress(uint32_t address) {
    _address.dword = address;
}

IPAddress::IPAddress(const uint8_t *address) {
    memcpy(_address.bytes, address, sizeof(_address.bytes));
}

/**
 * @brief       This function is used to transform from IPAddress object to String object.
 * @param[in] None
 *
 * @return      the target String object.
 * 
 * @note 
 */ 
String IPAddress::toString() const
{
    char szRet[16];
    sprintf(szRet,"%u.%u.%u.%u",
        _address.bytes[0],
        _address.bytes[1],
        _address.bytes[2],
        _address.bytes[3]);
    return String(szRet);
}

/**
 * @brief       This function is used to create the object from a string buffer.
 * @param[in] address Specify the string buffer.
 *
 * @return      bool 
 * 
 * @note 
 */ 
bool IPAddress::fromString(const char *address) {
    // TODO: add support for "a", "a.b", "a.b.c" formats

    uint16_t acc = 0; // Accumulator
    uint8_t dots = 0;

    while (*address)
    {
        char c = *address++;
        if (c >= '0' && c <= '9')
        {
            acc = acc * 10 + (c - '0');
            if (acc > 255) {
                // Value out of [0..255] range
                return false;
            }
        }
        else if (c == '.')
        {
            if (dots == 3) {
                // Too much dots (there must be 3 dots)
                return false;
            }
            _address.bytes[dots++] = acc;
            acc = 0;
        }
        else
        {
            // Invalid char
            return false;
        }
    }

    if (dots != 3) {
        // Too few dots (there must be 3 dots)
        return false;
    }
    _address.bytes[3] = acc;
    return true;
}

/**
 * @brief       This operator overloading function is used to overloading '=' operator.
 * @param[in] address Sepcify the address - uint8_t *
 *
 * @return      the target IPAddress object.
 * 
 * @note 
 */ 
IPAddress& IPAddress::operator=(const uint8_t *address) {
    memcpy(_address.bytes, address, sizeof(_address.bytes));
    return *this;
}

/**
 * @brief       This operator overloading function is used to overloading '=' operator.
 * @param[in] address Sepcify the address - uint32_t
 *
 * @return      the target IPAddress object.
 * 
 * @note 
 */ 
IPAddress& IPAddress::operator=(uint32_t address) {
    _address.dword = address;
    return *this;
}

/**
 * @brief       This operator overloading function is used to overloading '==' operator.
 * @param[in] addr Sepcify the address - uint8_t*
 *
 * @return      If they are equal, true is return, otherwise, false is return.
 * 
 * @note 
 */ 
bool IPAddress::operator==(const uint8_t* addr) const {
    return memcmp(addr, _address.bytes, sizeof(_address.bytes)) == 0;
}

/**
 * @brief       This virtual function is used to called by print/println function.
 * @param[in] p Specify the Print object.
 *
 * @return      bool 
 * 
 * @note The length of print successfully.
 */ 
size_t IPAddress::printTo(Print &p) const
{
    size_t n = 0;
    for (int i = 0; i < 3; i++)
    {
        n += p.print((unsigned char)(_address.bytes[i]), DEC);
        n += p.print('.');
    }
    n += p.print((unsigned char)(_address.bytes[3]), DEC);
    return n;
}
