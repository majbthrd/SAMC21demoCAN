/*
    quick and dirty to plug Atmel's code into a CMSIS-consistent implementation
    this also provides a rudimentary putchar() driver so that printf goes to the SAMC21-XPRO serial port

    Copyright (C) 2017 Peter Lawrence

    Permission is hereby granted, free of charge, to any person obtaining a 
    copy of this software and associated documentation files (the "Software"), 
    to deal in the Software without restriction, including without limitation 
    the rights to use, copy, modify, merge, publish, distribute, sublicense, 
    and/or sell copies of the Software, and to permit persons to whom the 
    Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in 
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL 
    THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER 
    DEALINGS IN THE SOFTWARE.
*/

#include <samc21.h>
#include <stdint.h>
#include <stdbool.h>

#define __SYSTEM_CLOCK (48000000)

uint32_t SystemCoreClock = __SYSTEM_CLOCK;

static void board_cfg_console(uint32_t baudrate)
{
  if (0 == baudrate)
    baudrate = 115200UL;

  PORT->Group[1].DIRSET.reg = PORT_PB10;
  PORT->Group[1].DIRCLR.reg = PORT_PB11;
  PORT->Group[1].PINCFG[10].reg = PORT_PINCFG_INEN | PORT_PINCFG_PMUXEN;
  PORT->Group[1].PINCFG[11].reg = PORT_PINCFG_INEN | PORT_PINCFG_PMUXEN;
  PORT->Group[1].PMUX[10 / 2].reg = PORT_PMUX_PMUXE(3 /* SERCOM-TX D */) | PORT_PMUX_PMUXO(3 /* SERCOM-RX D */); /* have to write odd and even at once */

  GCLK->PCHCTRL[SERCOM4_GCLK_ID_CORE].reg = GCLK_PCHCTRL_CHEN | GCLK_PCHCTRL_GEN_GCLK0;
  MCLK->APBCMASK.reg |= MCLK_APBCMASK_SERCOM4;

  SERCOM4->USART.CTRLA.reg = SERCOM_USART_CTRLA_SWRST;
  while (SERCOM4->USART.SYNCBUSY.reg & SERCOM_USART_SYNCBUSY_SWRST);

  SERCOM4->USART.CTRLB.reg = SERCOM_USART_CTRLB_RXEN | SERCOM_USART_CTRLB_TXEN | SERCOM_USART_CTRLB_CHSIZE(0x0);
  /* inconsistent with the datasheet, CTRLA_SAMPR = 0x1 was needed to get expected operation */
  SERCOM4->USART.CTRLA.reg = SERCOM_USART_CTRLA_DORD | SERCOM_USART_CTRLA_SAMPR(0x1) | SERCOM_USART_CTRLA_RXPO(0x3) | SERCOM_USART_CTRLA_TXPO(0x1) | SERCOM_USART_CTRLA_MODE(0x1);
  SERCOM4->USART.BAUD.reg = __SYSTEM_CLOCK / 16UL / baudrate;
  SERCOM4->USART.CTRLA.reg |= SERCOM_USART_CTRLA_ENABLE;
}

/* Atmel's proprietary convention is to call board_init in the startup code... gosh, that is rather like SystemInit() established with CMSIS */
void board_init(void)
{
  board_cfg_console(0);
}

void SystemInit(void)
{
  /*
  set CPU to 48MHz and adjust flash wait states accordingly: 3 wait states for 3.3V; 1 wait state for 5V
  */
  NVMCTRL->CTRLB.reg = NVMCTRL_CTRLB_READMODE_NO_MISS_PENALTY | NVMCTRL_CTRLB_SLEEPPRM_WAKEUPINSTANT | NVMCTRL_CTRLB_MANW | NVMCTRL_CTRLB_RWS(3);
  MCLK->CPUDIV.reg = MCLK_CPUDIV_CPUDIV_DIV1; /* 48 MHz for CPU+bus */
  OSCCTRL->OSC48MDIV.reg = OSCCTRL_OSC48MDIV_DIV(0); /* 48 MHz for peripheral */
  while (OSCCTRL->OSC48MSYNCBUSY.reg & OSCCTRL_OSC48MSYNCBUSY_OSC48MDIV);

  SystemCoreClock = __SYSTEM_CLOCK;

  /* use this CMSIS standard call to invoke Atmel proprietary convention */
  board_init();
}

void console_example_info(const char *example_name)
{
  (void)example_name;
}

bool console_is_rx_ready(void)
{
  return (SERCOM4->USART.INTFLAG.reg & SERCOM_USART_INTFLAG_RXC);
}

uint8_t console_get_char(void)
{
  return (uint8_t)(SERCOM4->USART.DATA.reg);
}

int __putchar(int c)
{
  while (!(SERCOM4->USART.INTFLAG.reg & SERCOM_USART_INTFLAG_DRE));
  SERCOM4->USART.DATA.reg = (uint8_t)c;
  return c;
}

uint32_t pmc_get_gck_clock(uint32_t id)
{
  (void)id;
  return __SYSTEM_CLOCK;
}
