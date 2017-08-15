/*
modified:
replaced handler naming conventions
added #include
added support for CMSIS SystemInit
*/
/*
 * Copyright (c) 2016, Alex Taradov <alex@taradov.com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include <samc21.h>

//-----------------------------------------------------------------------------
#define DUMMY __attribute__ ((weak, alias ("irq_handler_dummy")))

//-----------------------------------------------------------------------------
void Reset_Handler(void);
DUMMY void NMI_Handler(void);
DUMMY void HardFault_Handler(void);
DUMMY void SVC_Handler(void);
DUMMY void PendSV_Handler(void);
DUMMY void SysTick_Handler(void);

DUMMY void SYSTEM_Handler(void);
DUMMY void WDT_Handler(void);
DUMMY void RTC_Handler(void);
DUMMY void EIC_Handler(void);
DUMMY void FREQM_Handler(void);
DUMMY void TSENS_Handler(void);
DUMMY void NVMCTRL_Handler(void);
DUMMY void DMAC_Handler(void);
DUMMY void EVSYS_Handler(void);
DUMMY void SERCOM0_Handler(void);
DUMMY void SERCOM1_Handler(void);
DUMMY void SERCOM2_Handler(void);
DUMMY void SERCOM3_Handler(void);
DUMMY void SERCOM4_Handler(void);
DUMMY void SERCOM5_Handler(void);
DUMMY void CAN0_Handler(void);
DUMMY void CAN1_Handler(void);
DUMMY void TCC0_Handler(void);
DUMMY void TCC1_Handler(void);
DUMMY void TCC2_Handler(void);
DUMMY void TC0_Handler(void);
DUMMY void TC1_Handler(void);
DUMMY void TC2_Handler(void);
DUMMY void TC3_Handler(void);
DUMMY void TC4_Handler(void);
DUMMY void ADC0_Handler(void);
DUMMY void ADC1_Handler(void);
DUMMY void AC_Handler(void);
DUMMY void DAC_Handler(void);
DUMMY void SDADC_Handler(void);
DUMMY void PTC_Handler(void);

extern int main(void);

extern void _stack_top(void);
extern unsigned int _etext;
extern unsigned int _data;
extern unsigned int _edata;
extern unsigned int _bss;
extern unsigned int _ebss;

//-----------------------------------------------------------------------------
__attribute__ ((used, section(".vectors")))
void (* const vectors[])(void) =
{
  &_stack_top,                   // 0 - Initial Stack Pointer Value

  // Cortex-M0+ handlers
  Reset_Handler,                 // 1 - Reset
  NMI_Handler,                   // 2 - NMI
  HardFault_Handler,            // 3 - Hard Fault
  0,                             // 4 - Reserved
  0,                             // 5 - Reserved
  0,                             // 6 - Reserved
  0,                             // 7 - Reserved
  0,                             // 8 - Reserved
  0,                             // 9 - Reserved
  0,                             // 10 - Reserved
  SVC_Handler,                   // 11 - SVCall
  0,                             // 12 - Reserved
  0,                             // 13 - Reserved
  PendSV_Handler,                // 14 - PendSV
  SysTick_Handler,               // 15 - SysTick

  // Peripheral handlers
  SYSTEM_Handler,                // 0 - System Controller
  WDT_Handler,                   // 1 - Watchdog Timer
  RTC_Handler,                   // 2 - Real Time Counter
  EIC_Handler,                   // 3 - External Interrupt Controller
  FREQM_Handler,                 // 4 - Frequency Meter
  TSENS_Handler,                 // 5 - Temperature Sensor
  NVMCTRL_Handler,               // 6 - Non-Volatile Memory Controller
  DMAC_Handler,                  // 7 - Direct Memory Access Controller
  EVSYS_Handler,                 // 8 - Event System
  SERCOM0_Handler,               // 9 - Serial Communication Interface 0
  SERCOM1_Handler,               // 10 - Serial Communication Interface 1
  SERCOM2_Handler,               // 11 - Serial Communication Interface 2
  SERCOM3_Handler,               // 12 - Serial Communication Interface 3
  SERCOM4_Handler,               // 13 - Serial Communication Interface 4
  SERCOM5_Handler,               // 14 - Serial Communication Interface 5
  CAN0_Handler,                  // 15 - Control Area Network 0
  CAN1_Handler,                  // 16 - Control Area Network 1
  TCC0_Handler,                  // 17 - Timer/Counter for Control 0
  TCC1_Handler,                  // 18 - Timer/Counter for Control 1
  TCC2_Handler,                  // 19 - Timer/Counter for Control 2
  TC0_Handler,                   // 20 - Timer/Counter 0
  TC1_Handler,                   // 21 - Timer/Counter 1
  TC2_Handler,                   // 22 - Timer/Counter 2
  TC3_Handler,                   // 23 - Timer/Counter 3
  TC4_Handler,                   // 24 - Timer/Counter 4
  ADC0_Handler,                  // 25 - Analog-to-Digital Converter 0
  ADC1_Handler,                  // 26 - Analog-to-Digital Converter 1
  AC_Handler,                    // 27 - Analog Comparator
  DAC_Handler,                   // 28 - Digital-to-Analog Converter
  SDADC_Handler,                 // 29 - Sigma-Delta Analog Digital Converter
  PTC_Handler,                   // 30 - Peripheral Touch Controller
};

//-----------------------------------------------------------------------------
void Reset_Handler(void)
{
  unsigned int *src, *dst;

#ifndef DONT_USE_CMSIS_INIT
  SystemInit();
#endif

  src = &_etext;
  dst = &_data;
  while (dst < &_edata)
    *dst++ = *src++;

  dst = &_bss;
  while (dst < &_ebss)
    *dst++ = 0;

  main();
  while (1);
}

//-----------------------------------------------------------------------------
void irq_handler_dummy(void)
{
  while (1);
}

//-----------------------------------------------------------------------------
void _exit(int status)
{
  (void)status;
  while (1);
}
