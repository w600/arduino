#ifndef WiringPrivate_h
#define WiringPrivate_h

#include <stdio.h>
#include <stdarg.h>

#include "Arduino.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*voidFuncPtr)(void);

void initPins();

#ifdef __cplusplus
} // extern "C"
#endif

#endif
