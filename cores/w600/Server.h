/**
 * @file Server.h
 *
 * @brief   Server Module
 *
 * @author Huang Leilei
 *
 * Copyright (c) 2019 Winner Microelectronics Co., Ltd.
 */
#ifndef _SERVER_H_
#define _SERVER_H_

#include "Print.h"

class Server : public Print
{
public:
    /**
     * @brief         This pure-virtual function is used to start the object.
     *
     * @param[in] none
     *
     * @param[out]
     *
     * @return      None 
     * 
     * @note 
     */ 
    virtual void begin() = 0;
};

#endif