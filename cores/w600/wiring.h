#ifndef _WIRING_H_
#define _WIRING_H_

#include <stdint.h>
#include <stdio.h>

/*
 * C type
 */
#ifdef __cplusplus
extern "C" {
#endif
#include "wiring_constants.h"
#include "wiring_time.h"
#include "wiring_digital.h"
#ifdef __cplusplus
}
#endif

/*
 * C++ type
 */
#ifdef __cplusplus
#include "HardwareSerial.h"
#endif

#endif