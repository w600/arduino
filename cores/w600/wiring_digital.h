#ifndef _WIRING_DIGITAL_
#define _WIRING_DIGITAL_

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief
 *
 * \param ulPin The number of the pin whose mode you wish to set
 * \param ulMode Either INPUT or OUTPUT
 */

/**
 * @defgroup IO IO
 * @brief Digital Analog and Advanced I/O
 */

/**
 * @addtogroup IO
 * @{
 */

/**
 * @defgroup IO IO
 * @brief Digital Analog and Advanced I/O
 */

/**
 * @addtogroup IO
 * @{
 */

extern void pinMode(uint32_t ulPin, uint32_t ulMode);
extern void digitalWrite(uint32_t ulPin, uint32_t ulVal);
extern int digitalRead(uint32_t ulPin);
extern int analogRead(unsigned char pin);

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
