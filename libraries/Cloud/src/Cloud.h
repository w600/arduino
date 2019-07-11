/**
 * @file Cloud.h
 *
 * @brief   GizCloud Module
 *
 * @author Huang Leilei
 *
 * Copyright (c) 2019 Winner Microelectronics Co., Ltd.
 */
#ifndef _CLOUD_BASE_H_
#define _CLOUD_BASE_H_

extern "C" {
#include "wm_cloud.h"
#include "wm_osal.h"
}

#define DEMO_MSG_WJOIN_FAILD            1
#define DEMO_MSG_WJOIN_SUCCESS          2
#define DEMO_MSG_SOCKET_RECEIVE_DATA    3
#define DEMO_MSG_UART_RECEIVE_DATA      4
#define DEMO_MSG_SOCKET_ERR             5
#define DEMO_MSG_SOCKET_CREATE          6
#define DEMO_MSG_SOCKET_TEST            7
#define DEMO_MSG_OPEN_UART              8
#define DEMO_MSG_UART_CMD_DATA          9
#define DEMO_MSG_KEY                    10

class CloudClass
{
public:
    /**
     * @brief         This function is used to Init Giz Cloud Construct
     *                function to init some arguements or some configuration
     *                before use the object
     * @return 		None 
     * 
     * @note 
     */ 
    CloudClass();
    
    /**
     * @brief         This function is used to Init Giz Cloud method.
     * @return      If the init process is successful, true is returned.
     * 
     * @note This function must be called BEFORE using the object.
     */ 
    bool CloudInit();
    
private:
    CloudInitArg _init_arg;
};

extern CloudClass myCloud;

#endif
