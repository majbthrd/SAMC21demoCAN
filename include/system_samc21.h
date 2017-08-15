#ifndef _SYSTEM_SAMC21
#define _SYSTEM_SAMC21

/* provide CMSIS prototypes */

#include <stdint.h>

extern uint32_t SystemCoreClock;
void SystemInit(void);
void SystemCoreClockUpdate(void);

#endif

