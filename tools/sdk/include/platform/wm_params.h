/**
 * @file    wm_params.h
 *
 * @brief   param manager Module
 *
 * @author  winnermicro
 *
 * Copyright (c) 2015 Winner Microelectronics Co., Ltd.
 */
#ifndef TLS_PARAMS_H
#define TLS_PARAMS_H

#include "wm_type_def.h"

/***************************************************************************************
	ID								|			Data Type
***************************************************************************************
TLS_PARAM_ID_SSID      				|		  	struct tls_param_ssid ssid
TLS_PARAM_ID_ENCRY      		        	|		  	uint8_t encry
TLS_PARAM_ID_KEY      		          	|		  	struct tls_param_key key
TLS_PARAM_ID_IP      			          	|		  	struct tls_param_ip ipcfg
TLS_PARAM_ID_AUTOMODE               		|		  	uint8_t auto_mode
TLS_PARAM_ID_DEFSOCKET              		|		  	N/A
TLS_PARAM_ID_BSSID                  		|			struct tls_param_bssid bssid
TLS_PARAM_ID_CHANNEL                		|			uint8_t channel
TLS_PARAM_ID_CHANNEL_EN             	|			uint8_t channel_enable
TLS_PARAM_ID_COUNTRY_REGION         	|			uint8_t wireless_region
TLS_PARAM_ID_WPROTOCOL              	|			uint8_t wireless_protocol
TLS_PARAM_ID_ADHOC_AUTOCREATE       |			N/A
TLS_PARAM_ID_ROAMING                		|			uint8_t auto_roam
TLS_PARAM_ID_AUTO_RETRY_CNT         	|			N/A
TLS_PARAM_ID_WBGR                   		|			struct tls_param_bgr wbgr
TLS_PARAM_ID_USRINTF                		|			N/A
TLS_PARAM_ID_AUTO_TRIGGER_LENGTH   |			N/A
TLS_PARAM_ID_DEBUG_MODE             	|			N/A
TLS_PARAM_ID_HARDVERSION            	|			struct tls_param_hardware_version hardware_v
TLS_PARAM_ID_BRDSSID 	              	|			uint8_t ssid_broadcast_enable
TLS_PARAM_ID_DNSNAME                		|			uint8_t local_dnsname[32]
TLS_PARAM_ID_DEVNAME                		|			uint8_t local_device_name[32]
TLS_PARAM_ID_PSM                    		|			uint8_t auto_powersave
TLS_PARAM_ID_ORAY_CLIENT            	|			N/A
TLS_PARAM_ID_UPNP                   		|			N/A
TLS_PARAM_ID_UART                   		|			struct tls_param_uart uart_cfg
TLS_PARAM_ID_WPS                    		|			struct tls_param_wps wps
TLS_PARAM_ID_AUTO_TRIGGER_PERIOD   |			N/A
TLS_PARAM_ID_ESCAPE_CHAR            	|			N/A
TLS_PARAM_ID_ESCAPE_PERIOD	        	|			N/A
TLS_PARAM_ID_IO_MODE                		|			N/A
TLS_PARAM_ID_CMD_MODE               	|			N/A
TLS_PARAM_ID_PASSWORD	              	|			uint8_t PassWord[6]
TLS_PARAM_ID_CHANNEL_LIST           	|			uint16_t channellist
TLS_PARAM_ID_WEBS_CONFIG            	|			struct tls_webs_cfg WebsCfg
TLS_PARAM_ID_ONESHOT_CFG            	|			uint8_t oneshotflag
TLS_PARAM_ID_SHA1                   		|			N/A
TLS_PARAM_ID_ORIGIN_KEY             		|			N/A
TLS_PARAM_ID_ORIGIN_SSID            	|			N/A
TLS_PARAM_ID_AUTO_RECONNECT         	|			uint8_t auto_reconnect
***************************************************************************************/

#define TLS_PARAM_STATUS_OK      (0)
#define TLS_PARAM_STATUS_EINVALID      (1)
#define TLS_PARAM_STATUS_EMEM      (2)
#define TLS_PARAM_STATUS_EIO      (3)
#define TLS_PARAM_STATUS_EPERM      (4)
#define TLS_PARAM_STATUS_EINVALIDID      (5)

/**   MACRO of Magic number initial value   */
#define TLS_PARAM_INIT_MAGIC  (0xffffffff)
/**   MACRO of Magic number valid value   */
#define TLS_PARAM_MAGIC   (0x4947414d)

/**   MACRO of parameter partition number   */
#define TLS_PARAM_PARTITION_NUM      (2)

/**   MACRO of parameter identity   */
#define TLS_PARAM_ID_ALL      (-1)
#define TLS_PARAM_ID_SSID      (0)
#define TLS_PARAM_ID_ENCRY      (1)
#define TLS_PARAM_ID_KEY      (2)
#define TLS_PARAM_ID_IP      (3)
#define TLS_PARAM_ID_AUTOMODE      (4)
#define TLS_PARAM_ID_DEFSOCKET      (5)
#define TLS_PARAM_ID_BSSID      (6)
#define TLS_PARAM_ID_CHANNEL      (7)
#define TLS_PARAM_ID_CHANNEL_EN      (8)
#define TLS_PARAM_ID_COUNTRY_REGION      (9)
#define TLS_PARAM_ID_WPROTOCOL      (10)
#define TLS_PARAM_ID_ADHOC_AUTOCREATE      (11)
#define TLS_PARAM_ID_ROAMING      (12)
#define TLS_PARAM_ID_AUTO_RETRY_CNT      (13)
#define TLS_PARAM_ID_WBGR      (14)
#define TLS_PARAM_ID_USRINTF      (15)
#define TLS_PARAM_ID_AUTO_TRIGGER_LENGTH      (16)
#define TLS_PARAM_ID_DEBUG_MODE      (17)
#define TLS_PARAM_ID_HARDVERSION      (18)
#define TLS_PARAM_ID_BRDSSID      (19)
#define TLS_PARAM_ID_DNSNAME      (20)
#define TLS_PARAM_ID_DEVNAME      (21)
#define TLS_PARAM_ID_PSM      (22)
#define TLS_PARAM_ID_ORAY_CLIENT      (23)
#define TLS_PARAM_ID_UPNP      (24)
#define TLS_PARAM_ID_UART      (26)
#define TLS_PARAM_ID_WPS      (27)
#define TLS_PARAM_ID_AUTO_TRIGGER_PERIOD  (28)
#define TLS_PARAM_ID_ESCAPE_CHAR    (29)
#define TLS_PARAM_ID_ESCAPE_PERIOD	 (30)
#define TLS_PARAM_ID_IO_MODE     (31)
#define TLS_PARAM_ID_CMD_MODE     (32)
#define TLS_PARAM_ID_PASSWORD	  (33)
#define TLS_PARAM_ID_CHANNEL_LIST (34)
#define TLS_PARAM_ID_WEBS_CONFIG   (35)
#define TLS_PARAM_ID_ONESHOT_CFG   (36)
#define TLS_PARAM_ID_SHA1   (37)
#define TLS_PARAM_ID_ORIGIN_KEY	(38)
#define TLS_PARAM_ID_ORIGIN_SSID	(39)
#define TLS_PARAM_ID_AUTO_RECONNECT	(40)
#define TLS_PARAM_ID_QUICK_CONNECT	(41)
#define TLS_PARAM_ID_KEY_CHANGE	    (42)
#define TLS_PARAM_ID_SSID_CHANGE	(43)
#define TLS_PARAM_ID_SOFTAP_SSID	(44)
#define TLS_PARAM_ID_SOFTAP_PSK	    (45)
#define TLS_PARAM_ID_SOFTAP_ENCRY   (46)
#define TLS_PARAM_ID_SOFTAP_KEY     (47)
#define TLS_PARAM_ID_SOFTAP_IP      (48)
#define TLS_PARAM_ID_SOFTAP_CHANNEL (49)
#define TLS_PARAM_ID_SOFTAP_WBGR    (50)

#define TLS_PARAM_ID_SNTP_SERVER1	(51)
#define TLS_PARAM_ID_SNTP_SERVER2	(52)
#define TLS_PARAM_ID_SNTP_SERVER3	(53)
#define TLS_PARAM_ID_TEM_OFFSET	    (54)

#define TLS_PARAM_ID_MAX            (55)
/**   MACRO of Physical moe of Ieee802.11   */
#define TLS_PARAM_PHY_11BG_MIXED      (0)
#define TLS_PARAM_PHY_11B             (1)
#define TLS_PARAM_PHY_11BGN_MIXED     (2)
/**   MACRO of Ieee802.11 Tx Rate for parameter set   */
#define TLS_PARAM_TX_RATEIDX_1M          (0)
#define TLS_PARAM_TX_RATEIDX_2M          (1)
#define TLS_PARAM_TX_RATEIDX_5_5M        (2)
#define TLS_PARAM_TX_RATEIDX_11M         (3)
#define TLS_PARAM_TX_RATEIDX_6M          (4)
#define TLS_PARAM_TX_RATEIDX_9M          (5)
#define TLS_PARAM_TX_RATEIDX_12M         (6)
#define TLS_PARAM_TX_RATEIDX_18M         (7)
#define TLS_PARAM_TX_RATEIDX_24M         (8)
#define TLS_PARAM_TX_RATEIDX_36M         (9)
#define TLS_PARAM_TX_RATEIDX_48M         (10)
#define TLS_PARAM_TX_RATEIDX_54M         (11)
#define TLS_PARAM_TX_RATEIDX_MCS0         (12)
#define TLS_PARAM_TX_RATEIDX_MCS1         (13)
#define TLS_PARAM_TX_RATEIDX_MCS2         (14)
#define TLS_PARAM_TX_RATEIDX_MCS3         (15)
#define TLS_PARAM_TX_RATEIDX_MCS4         (16)
#define TLS_PARAM_TX_RATEIDX_MCS5         (17)
#define TLS_PARAM_TX_RATEIDX_MCS6         (18)
#define TLS_PARAM_TX_RATEIDX_MCS7         (19)
#define TLS_PARAM_TX_RATEIDX_MCS8         (20)
#define TLS_PARAM_TX_RATEIDX_MCS9         (21)
#define TLS_PARAM_TX_RATEIDX_MCS10         (22)
#define TLS_PARAM_TX_RATEIDX_MCS11         (23)
#define TLS_PARAM_TX_RATEIDX_MCS12         (24)
#define TLS_PARAM_TX_RATEIDX_MCS13         (25)
#define TLS_PARAM_TX_RATEIDX_MCS14         (26)
#define TLS_PARAM_TX_RATEIDX_MCS15         (27)
#define TLS_PARAM_TX_RATEIDX_MCS32         (28)


/**   MACRO of SSID Broadcast   */
#define TLS_PARAM_SSIDBRD_DISABLE      (0)
#define TLS_PARAM_SSIDBRD_ENABLE      (1)

#define TLS_PARAM_ROAM_DISABLE      (0)
#define TLS_PARAM_ROAM_ENABLE      (1)

/**   MACRO of Power Saving Mode   */
#define TLS_PARAM_PSM_DISABLE      (0)
#define TLS_PARAM_PSM_ENABLE      (1)

#define TLS_PARAM_DDNS_DISABLE      (0)
#define TLS_PARAM_DDNS_ENABLE      (1)

#define TLS_PARAM_AUTO_CREATE_ADHOC_DISABLE      (0)
#define TLS_PARAM_AUTO_CREATE_ADHOC_ENABLE      (1)

#define TLS_PARAM_WPS_DISABLE      (0)
#define TLS_PARAM_WPS_ENABLE      (1)
#define TLS_PARAM_WPS_MODE_PIN      (0)
#define TLS_PARAM_WPS_MODE_PBC      (1)
#define TLS_PARAM_WPS_FLAG_NEGOTIATED      (1 << 0)

#define TLS_PARAM_UPNP_DISABLE      (0)
#define TLS_PARAM_UPNP_ENABLE      (1)

/**   MACRO of IEEE802.11 Work MODE   */
#define TLS_PARAM_IEEE80211_INFRA      (1)
#define TLS_PARAM_IEEE80211_ADHOC      (2)
#define TLS_PARAM_IEEE80211_SOFTAP     (4)

/**   MACRO of Command or Transparent Mode   */
#define TLS_PARAM_MANUAL_MODE      (0)
#define TLS_PARAM_AUTO_MODE      (1)

#define TLS_PARAM_ALWAYS_ONLINE_ENABLE      (1)
#define TLS_PARAM_ALWAYS_ONLINE_DISABLE      (0)

/**   MACRO of DHCP ENABLE or DISABLE   */
#define TLS_PARAM_DHCP_ENABLE      (1)
#define TLS_PARAM_DHCP_DISABLE      (0)

/**   MACRO of COUNTRY CODE for channel number   */
#define TLS_PARAM_REGION_0_BG_BAND      (0) /* 1-11 */
#define TLS_PARAM_REGION_1_BG_BAND      (1) /* 1-13 */
#define TLS_PARAM_REGION_2_BG_BAND      (2) /* 10-11 */
#define TLS_PARAM_REGION_3_BG_BAND      (3) /* 10-13 */
#define TLS_PARAM_REGION_4_BG_BAND      (4) /* 14 */
#define TLS_PARAM_REGION_5_BG_BAND      (5) /* 1-14 */
#define TLS_PARAM_REGION_6_BG_BAND      (6) /* 3-9 */
#define TLS_PARAM_REGION_7_BG_BAND      (7) /* 5-13 */
#define TLS_PARAM_REGION_MAXIMUM_BG_BAND      TLS_PARAM_REGION_7_BG_BAND

/**   MACRO of ENCRYPT TYPE   */
#define TLS_PARAM_ENCRY_OPEN      (0)
#define TLS_PARAM_ENCRY_WEP64      (1)
#define TLS_PARAM_ENCRY_WEP128      (2)
#define TLS_PARAM_ENCRY_WPA_PSK_TKIP      (3)
#define TLS_PARAM_ENCRY_WPA_PSK_AES      (4)
#define TLS_PARAM_ENCRY_WPA2_PSK_TKIP      (5)
#define TLS_PARAM_ENCRY_WPA2_PSK_AES      (6)

/**   MACRO of USER INTERFACE TYPE   */
#define TLS_PARAM_USR_INTF_LUART      (0)
#define TLS_PARAM_USR_INTF_HUART      (1)
#define TLS_PARAM_USR_INTF_HSPI      (2)
#define TLS_PARAM_USR_INTF_HSDIO	 (3)

/**   MACRO of UART BAUDRATE   */
#define TLS_PARAM_UART_BAUDRATE_B600      (600)
#define TLS_PARAM_UART_BAUDRATE_B1200      (1200)
#define TLS_PARAM_UART_BAUDRATE_B1800      (1800)
#define TLS_PARAM_UART_BAUDRATE_B2400      (2400)
#define TLS_PARAM_UART_BAUDRATE_B4800      (4800)
#define TLS_PARAM_UART_BAUDRATE_B9600      (9600)
#define TLS_PARAM_UART_BAUDRATE_B19200      (19200)
#define TLS_PARAM_UART_BAUDRATE_B38400      (38400)
#define TLS_PARAM_UART_BAUDRATE_B57600      (57600)
#define TLS_PARAM_UART_BAUDRATE_B115200      (115200)
#define TLS_PARAM_HUART_BAUDRATE_B230400      (230400)
#define TLS_PARAM_HUART_BAUDRATE_B460800      (460800)
#define TLS_PARAM_HUART_BAUDRATE_B921600      (921600)
#define TLS_PARAM_HUART_BAUDRATE_B1000000      (1000000)
#define TLS_PARAM_HUART_BAUDRATE_B1250000      (1250000)
#define TLS_PARAM_HUART_BAUDRATE_B1500000      (1500000)
#define TLS_PARAM_HUART_BAUDRATE_B2000000      (2000000)

/**    MACRO of UART PARITY   */
#define TLS_PARAM_UART_PARITY_NONE      (0)
#define TLS_PARAM_UART_PARITY_EVEN      (1)
#define TLS_PARAM_UART_PARITY_ODD      (2)
#define TLS_PARAM_UART_PARITY_MARK      (3)
#define TLS_PARAM_UART_PARITY_SPACE      (4)

/**    MACRO of UART STOP BITS   */
#define TLS_PARAM_UART_STOPBITS_1BITS      (0)
#define TLS_PARAM_UART_STOPBITS_2BITS      (1)

/**   MACRO of UART FLOW CONTROL   */
#define TLS_PARAM_UART_FLOW_DISABLE      (0)
#define TLS_PARAM_UART_FLOW_ENABLE      (1)
#define TLS_PARAM_HSPI_MAX_SCLK      (33000000)
/**    MACRO of SOCKET PARAMETER   */
#define TLS_PARAM_SOCKET_TCP      (0)
#define TLS_PARAM_SOCKET_UDP      (1)
#define TLS_PARAM_SOCKET_CLIENT      (0)
#define TLS_PARAM_SOCKET_SERVER      (1)
#define TLS_PARAM_SOCKET_DEFAULT_PORT      (60000)

/**   Structure of hardware parameter    */
struct tls_param_hardware_version {
	uint8_t mark;
	uint8_t main;
	uint8_t sub;
	uint8_t material;
	uint8_t year;
	uint8_t week;
	uint8_t res[2];
};

/**   Structure of specified BSSID parameter    */
struct tls_param_bssid {
	uint8_t bssid_enable;
	uint8_t res;
	uint8_t bssid[6];
};

/**   Structure of SSID parameter    */
struct tls_param_ssid {
	uint8_t ssid[32];
	uint32_t ssid_len;
};

/**   Structure of TEM parameter    */
struct tls_param_tem_offset {
	uint8_t offset_len;
	int32_t offset;
};

/**   Structure of KEY parameter    */
struct tls_param_key {
	uint8_t psk[64];
	uint8_t key_length;
	uint8_t key_index;
	uint8_t key_format;
	uint8_t res;
};

/**   Structure of original KEY parameter    */
struct tls_param_original_key {
	uint8_t psk[64];
	uint32_t key_length;
};

/**   Structure of SHA1 KEY parameter    */
struct tls_param_sha1{
	uint8_t psk_set;
	uint8_t psk[32];
};

/**   Structure of 802.11 bgn rate parameter    */
struct tls_param_bgr {
	uint8_t bg;
	uint8_t max_rate;
	uint8_t res[2];
};

/**   Structure of IP parameter    */
struct tls_param_ip {
	uint8_t dhcp_enable;
	uint8_t res[3];
	uint8_t ip[4];
	uint8_t netmask[4];
	uint8_t gateway[4];
	uint8_t dns1[4];
	uint8_t dns2[4];
};

/**   Structure of uart parameter    */
struct tls_param_uart {
	uint32_t baudrate;
	uint8_t stop_bits;
	uint8_t parity;
	uint8_t flow;
	uint8_t charsize;
};

/**   Structure of socket parameter    */
struct tls_param_socket {
	uint8_t protocol;
	uint8_t client_or_server;
	uint16_t port_num;
	uint8_t host[32];
};

struct tls_param_wps {
	uint8_t wps_enable;
	uint8_t mode;
	uint8_t flag;
	uint8_t res;
	uint8_t pin[8];
};

/**   Structure of oray client */
struct tls_param_oray_client {
	uint32_t oray_client_enable;
	uint8_t oray_client_user[32];
	uint8_t oray_client_pass[32];
};

/**   Structure of web server parameter    */
struct tls_webs_cfg {
	uint8_t	AutoRun;
	uint8_t	Reserved;
	uint16_t PortNum;
};

/**   Structure of user default parameter    */
typedef struct tls_user_param{

	uint8_t wireless_protocol;
	uint8_t auto_mode;
	uint8_t dhcp_enable;
	uint8_t user_port_mode;

	uint8_t ip[4];
	uint8_t netmask[4];
	uint8_t gateway[4];
	uint8_t dns[4];

	uint32_t baudrate;

	uint8_t socket_protocol;
	uint8_t socket_client_or_server;
	uint16_t socket_port_num;
	uint8_t socket_host[32];
	uint8_t auto_powersave;
	uint8_t PassWord[6];
}ST_Wm_User_Param;

/**
 * @defgroup System_APIs System APIs
 * @brief System APIs
 */

/**
 * @addtogroup System_APIs
 * @{
 */

/**
 * @defgroup Param_APIs Param APIs
 * @brief Param manager APIs
 */

/**
 * @addtogroup Param_APIs
 * @{
 */

/**
 * @brief          This function is used to initialize parameter's manamge module
 *
 * @param[in]      None
 *
 * @retval         TLS_PARAM_STATUS_OK		init success
 * @retval         TLS_PARAM_STATUS_EMEM	memory error
 * @retval         TLS_PARAM_STATUS_EIO		io error
 * @retval         TLS_PARAM_STATUS_EPERM   magic number error
 *
 * @note           None
 */
int tls_param_init(void);

/**
 * @brief          This function is used to load the system's default
 				   parameters
 *
 * @param[in]      None
 *
 * @return         None
 *
 * @note           This function read user defined parameters first,
 				   if wrong, all the parameters restore factory settings
 */
void tls_param_load_factory_default(void);

/**
 * @brief          This function is used to set one system parameter by its id
 *
 * @param[in]      id         param id,from TLS_PARAM_ID_SSID
 						      to (TLS_PARAM_ID_MAX - 1)
 * @param[in]      *argv      store parameters
 * @param[in]      to_flash   whether the parameter is written to flash,
 							  1:write to flash,0:only write memory
 *
 * @retval         TLS_PARAM_STATUS_OK       set success
 * @retval         TLS_PARAM_STATUS_EINVALID invalid param
 *
 * @note           None
 */
int tls_param_set(int id, void *argv, bool to_flash);

/**
 * @brief          This function is used to get one system parameter by its id.
 *
 * @param[in]      id            param id,from TLS_PARAM_ID_SSID
 								 to (TLS_PARAM_ID_MAX - 1)
 * @param[in]      *argv         store parameters
 * @param[in]      from_flash    whether the parameter is readed from flash,
 								 1 read from flash,0 read from memory
 *
 * @retval         TLS_PARAM_STATUS_OK       success
 * @retval         TLS_PARAM_STATUS_EINVALID invalid param
 *
 * @note           None
 */
int tls_param_get(int id, void *argv, bool from_flash);

/**
 * @brief          This function is used to write parameter into flash
 *
 * @param[in]      id    param id,from TLS_PARAM_ID_ALL
                         to (TLS_PARAM_ID_MAX - 1)
 *
 * @retval         TLS_PARAM_STATUS_OK          success
 * @retval         TLS_PARAM_STATUS_EINVALID	invalid param
 * @retval         TLS_PARAM_STATUS_EIO		    read or write flash error
 *
 * @note           None
 */
int tls_param_to_flash(int id);

/**
 * @brief          This function is used to recovery the parameters from
                   the backup area to the parameter area,and load them into ram
 *
 * @param[in]      None
 *
 * @return         None
 *
 * @note           None
 */
void tls_restore_param_from_backup(void);

/**
 * @brief          This function is used to load default parametes into ram

 *
 * @param[in]      None
 *
 * @retval         TLS_PARAM_STATUS_OK       set success
 * @retval         TLS_PARAM_STATUS_EINVALID parameter wrong
 * @retval         TLS_PARAM_STATUS_EIO      read or write falsh error
 *
 * @note           This function read user defined parameters first,
 				   if wrong, all the parameters restore factory settings
 */
int tls_param_to_default(void);

/**
 * @brief          This function is used to write user's parameters into the
                   flash
 *
 * @param[in]      None
 *
 * @retval         TLS_PARAM_STATUS_OK     success
 * @retval         other failed
 *
 * @note           None
 */
int tls_param_save_user_default(void);

/**
 * @brief          This function is used to modify user's default parameters,
                   then write them into flash
 *
 * @param[in]      *user_param
 *
 * @retval         TLS_PARAM_STATUS_OK     success
 * @retval         other failed
 *
 * @note           None
 */
int tls_param_save_user(struct tls_user_param *user_param);

/**
 * @brief          This function is used to get updp mode.(updp:update user
                   default parameters)
 *
 * @param[in]      None
 *
 * @retval         update mode
 *
 * @note           None
 */
uint8_t tls_param_get_updp_mode(void);

/**
 * @brief          This function is used to set updp mode
 *
 * @param[in]      mode
 *
 * @return         None
 *
 * @note           None
 */
void tls_param_set_updp_mode(uint8_t mode);

/**
 * @brief          This function is used to get program param
 *
 * @param[in]      *pBase   pointer to save base address
 *
 * @retval         0        success
 * @retval         other    failed
 *
 * @note           None
 */
int tls_param_get_program_param(uint32_t *pBase);

/**
 * @brief          This function is used to set program base,image len,and
 				   checksum
 *
 * @param[in]      base        base address
 * @param[in]      totallen    total length of the image
 * @param[in]      checksum    checksum value of the image
 *
 * @retval         0     success
 * @retval         other failed
 *
 * @note           None
 */
int tls_param_set_program_param(uint32_t base, uint32_t totallen, uint32_t checksum);

/**
 * @}
 */

/**
 * @}
 */

#endif /* WM_PARAM_H */

