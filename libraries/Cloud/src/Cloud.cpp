/**
 * @file Cloud.cpp
 *
 * @brief   GizCloud Module
 *
 * @author Huang Leilei
 *
 * Copyright (c) 2019 Winner Microelectronics Co., Ltd.
 */
#include <string.h>

#include "Cloud.h"
#include "Arduino.h"
#include "pins_arduino.h"

extern "C"{
#include "wm_cloud.h"
#include "wm_mem.h"
#include "wm_gpio.h"
extern void oneshot_config(void);
}

#define ACTION_CONTROL_DEVICE       0x01
#define ACTION_READ_DEV_STATUS      0x02
#define ACTION_READ_DEV_STATUS_ACK  0x03
#define ACTION_REPORT_DEV_STATUS    0x04
#define ACTION_W2D_TRANSPARENT_DATA 0x05
#define ACTION_D2W_TRANSPARENT_DATA 0x06

#define TASK_CLOUD_SIZE     1024
#define CLOUD_TASK_PRIO     54
#define DEMO_QUEUE_SIZE	32
static tls_os_queue_t *demo_cloud_q = NULL;
static OS_STK CloudTask[TASK_CLOUD_SIZE];

int red_duty_ratio = 0;
int blue_duty_ratio = 0;
int green_duty_ratio = 0;
bool leds_on = false;

CloudClass myCloud;

int op_all_leds(bool on)
{
    uint32_t level = on ? LOW : HIGH;

    leds_on = on;

    if (on == false
        || (
        on == true
        &&
            (0 == red_duty_ratio
            && 0 == blue_duty_ratio
            && 0 == green_duty_ratio)))
    {
        pinMode(LED_RED, OUTPUT);
        digitalWrite(LED_RED, level);
        pinMode(LED_BLUE, OUTPUT);
        digitalWrite(LED_BLUE, level);
        pinMode(LED_GREEN, OUTPUT);
        digitalWrite(LED_GREEN, level);
    }
    else
    {
        pinMode(LED_RED, OUTPUT);
        analogWrite(LED_RED, 255 - red_duty_ratio);
        pinMode(LED_GREEN, OUTPUT);
        analogWrite(LED_GREEN, 255 - green_duty_ratio);
        pinMode(LED_BLUE, OUTPUT);
        analogWrite(LED_BLUE, 255 - blue_duty_ratio);
    }

    return true;
}

int control_leds(uint8_t * control)
{
    if (1 == control[1] && 0 == control[2])
    {
        // Close all LEDs
        op_all_leds(false);
    }
    else if (1 == control[1] && 1 == control[2])
    {
        // turn on all LEDs
        op_all_leds(true);
    }
    else
    {
        // control[1] == 2, for Query LED state
        if (2 != control[1])
        {
            if (4 == control[1])    // Red
            {
                red_duty_ratio = control[3];
                printf("[%s %s %d] *Red* DutyRatio: %d\n", strrchr(__FILE__, '\\') + 1, __func__, __LINE__, control[3]);
            }
            if (8 == control[1])    //Blue
            {
                blue_duty_ratio = control[4];
                printf("[%s %s %d] *Blue* DutyRatio: %d\n", strrchr(__FILE__, '\\') + 1, __func__, __LINE__, control[4]);
            }
            if (16 == control[1])    //Green
            {
                green_duty_ratio = control[5];
                printf("[%s %s %d] *Green* DutyRatio: %d\n", strrchr(__FILE__, '\\') + 1, __func__, __LINE__, control[5]);
            }
            if (true == leds_on)
            {
                pinMode(LED_RED, OUTPUT);
                analogWrite(LED_RED, 255 - red_duty_ratio);
                pinMode(LED_BLUE, OUTPUT);
                analogWrite(LED_BLUE, 255 - blue_duty_ratio);
                pinMode(LED_GREEN, OUTPUT);
                analogWrite(LED_GREEN, 255 - green_duty_ratio);
            }
            else
            {
                printf("[%s %d] <Cloud> Please Turn ON the leds, but save the value from the Cloud\n", __func__, __LINE__);
            }
        }
        else
        {
            printf("[%s %d] <Cloud> NOT support for queury\n", __func__, __LINE__);
        }
    }

    return true;
}

// tls_cloud_report_data
int report_led_status(uint8_t cmd)
{
    PCloudData txbuf = NULL;

    txbuf = (PCloudData) tls_mem_alloc(sizeof(CloudData));
    if (NULL == txbuf)
    {
        printf("[%s %d] <Cloud> tls_mem_alloc !!!error!!!\n", __func__, __LINE__);
        return false;
    }
    memset(txbuf, 0, sizeof(CloudData));
    txbuf->allbuf = (u8 *)tls_mem_alloc(200 * sizeof(u8));
    if (NULL == txbuf->allbuf)
    {
        printf("[%s %d] <Cloud> tls_mem_alloc !!!error!!!\n", __func__, __LINE__);
        tls_mem_free(txbuf);
        return false;
    }
    memset(txbuf->allbuf, 0, 200 * sizeof(u8));
    txbuf->phead = txbuf->allbuf;
    txbuf->ppayload = txbuf->phead + 20;
    txbuf->ppayload[0] = cmd;

    if (ACTION_READ_DEV_STATUS_ACK == cmd
        || ACTION_REPORT_DEV_STATUS == cmd)
    {
        txbuf->ppayload[1] = (u8)(digitalRead(LED_RED));
        txbuf->pend = txbuf->ppayload + 2;
        txbuf->ppayload[3] = (u8)(red_duty_ratio);
        txbuf->ppayload[4] = (u8)(blue_duty_ratio);
        txbuf->ppayload[5] = (u8)(green_duty_ratio);
        printf("[%s %d] ppayload: (%02d %02d %02d %02d %02d %02d)_10\n", __func__, __LINE__,
            txbuf->ppayload[0], txbuf->ppayload[1], txbuf->ppayload[2],
            txbuf->ppayload[3], txbuf->ppayload[4], txbuf->ppayload[5]);
    }
    txbuf->initiative_report = 0;
    tls_cloud_upload_data(txbuf);
    
    tls_mem_free(txbuf->allbuf);
    tls_mem_free(txbuf);

    return true;
}

int tls_cloud_callback(void *data)
{
    PCloudData rxbuf = (PCloudData)data;
    //printf("[%s %s %d] rxbuf->ppayload[0]: %02d, rxbuf->ppayload[1]: %02d\n",
    //    strrchr(__FILE__, '\\') + 1, __func__, __LINE__,
    //    rxbuf->ppayload[0], rxbuf->ppayload[1]);

    if ( ACTION_READ_DEV_STATUS ==  rxbuf->ppayload[0])
    {
        report_led_status(ACTION_READ_DEV_STATUS_ACK);
    }
    else if ( ACTION_CONTROL_DEVICE == rxbuf->ppayload[0])
    {
        control_leds(rxbuf->ppayload);
    }
    else if (2 == rxbuf->ppayload[1])
    {
        report_led_status(ACTION_CONTROL_DEVICE);
    }

    return true;
}

int cloud_set_cb(void *data)
{
    tls_cloud_callback(data);
    return 0;
}

static void cloud_online_status_changed(int status)
{
	printf("*******cloud online status : %s********\n", status ? "online" : "offline");
}

/*************************************
Key press isr handler
*************************************/
static void demo_key_isr_callback(void *context)
{
	u16 ret;

	ret = tls_get_gpio_irq_status(USER_BTN);
	if(ret)
	{
		tls_clr_gpio_irq_status(USER_BTN);
        tls_os_queue_send(demo_cloud_q,(void *)DEMO_MSG_KEY,0);
	}
}

/*************************************
Key press init with rising edge
*************************************/
static void key_init(void)
{
	tls_gpio_cfg(USER_BTN, WM_GPIO_DIR_INPUT, WM_GPIO_ATTR_PULLLOW);
	tls_gpio_isr_register(USER_BTN, demo_key_isr_callback, NULL);
	tls_gpio_irq_enable(USER_BTN, WM_GPIO_IRQ_TRIG_FALLING_EDGE);
}

static void cloud_net_status_changed_event(u8 status)
{
	u8 auto_reconnect = WIFI_AUTO_CNT_ON;
	switch(status)
	{
		case NETIF_WIFI_JOIN_FAILED:
            //printf("[%s %s %d] NETIF_WIFI_JOIN_FAILED: %d\n", strrchr(__FILE__, '\\') + 1, __func__, __LINE__, NETIF_WIFI_JOIN_FAILED);
			tls_os_queue_send(demo_cloud_q, (void *)DEMO_MSG_WJOIN_FAILD, 0);
			break;
		case NETIF_WIFI_JOIN_SUCCESS:
			tls_os_queue_send(demo_cloud_q, (void *)DEMO_MSG_WJOIN_SUCCESS, 0);
			break;
		case NETIF_IP_NET_UP:

			tls_wifi_auto_connect_flag(WIFI_AUTO_CNT_FLAG_SET, &auto_reconnect);
			tls_os_queue_send(demo_cloud_q, (void *)DEMO_MSG_SOCKET_CREATE, 0);
			break;
		case NETIF_WIFI_DISCONNECTED:
			tls_os_queue_send(demo_cloud_q,(void *)DEMO_MSG_WJOIN_FAILD, 0);
		default:
			break;
	}
}

static void _cloud_task(void *arg)
{
    void *msg;
	int key_state=0;
	int key_count=0;
    
	key_init();
    
    tls_cloud_init((CloudInitArg *)arg);
    tls_cloud_set_callback((cloud_callback)cloud_set_cb);
    tls_cloud_set_online_status_callback(cloud_online_status_changed);
    
    tls_netif_add_status_event(cloud_net_status_changed_event);
    
    for(;;)
    {
        tls_os_queue_receive(demo_cloud_q,(void **)&msg, 0, 0);
        printf("B\n");
        //printf("[%s %s %d] (u32)msg: %d\n", strrchr(__FILE__, '\\') + 1, __func__, __LINE__, (u32)msg);
        switch((u32)msg)
        {
            case DEMO_MSG_WJOIN_SUCCESS:
                break;
            case DEMO_MSG_SOCKET_CREATE:
                break;
            case DEMO_MSG_WJOIN_FAILD:
                //oneshot_config();
                break;
            case DEMO_MSG_SOCKET_ERR:
                printf("\nsocket err\n");
                break;
            case DEMO_MSG_KEY:
                {
                    do
                    {
                        delay(50);
                        key_count++;
                        key_state = tls_gpio_read(USER_BTN);
                    } while (USER_BTN_PRESS == key_state
                                && key_count < 100);

                    if(key_count > 25
                        && key_count <= 100) /*long press key to enter oneshot configure*/
                    {
                        printf("wait oneshot...\n");
                        oneshot_config();
                    }
                    key_count = 0;
                    key_state = 0;

                }
                break;
            default:
                break;
        }
    }
}

bool _set_work_mode_softap()
{
    u8 wi_protocol = 0;
    tls_param_get(TLS_PARAM_ID_WPROTOCOL, (void *)&wi_protocol, true);
    if (TLS_PARAM_IEEE80211_SOFTAP != wi_protocol)
    {
        wi_protocol = TLS_PARAM_IEEE80211_SOFTAP;
        tls_param_set(TLS_PARAM_ID_WPROTOCOL, (void *)&wi_protocol, false);
    }
    return true;
}

/**
 * @brief         This function is used to Init Giz Cloud Construct
 *                function to init some arguements or some configuration
 *                before use the object
 * @return      None 
 * 
 * @note 
 */ 
CloudClass::CloudClass()
{
    memset(&_init_arg, 0, sizeof(CloudInitArg));
	_init_arg.product_key = (char *)"230773a3a96d4e2cba8fdd384403ea8b";
	_init_arg.wifi_soft_ver = (char *)"04020010";
	_init_arg.wifi_hard_ver = (char *)"1H010001";//"000LINUX";
}

/**
 * @brief         This function is used to Init Giz Cloud method.
 * @return      If the init process is successful, true is returned.
 * 
 * @note This function must be called BEFORE using the object.
 */ 
bool CloudClass::CloudInit()
{
    op_all_leds(false);

    tls_os_queue_create(&demo_cloud_q, DEMO_QUEUE_SIZE);

    tls_wifi_disconnect();
    tls_wifi_softap_destroy();
    _set_work_mode_softap();

    tls_os_task_create(
        NULL,
        "Cloud",
        _cloud_task,
        (void *)&_init_arg,
        (u8 *)CloudTask,
        TASK_CLOUD_SIZE * sizeof(u32),
        CLOUD_TASK_PRIO,
        0);

    return true;
}
