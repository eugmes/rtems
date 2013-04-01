/*
 * Copyright (c) 2011 Sebastian Huber.  All rights reserved.
 *
 *  embedded brains GmbH
 *  Obere Lagerstr. 30
 *  82178 Puchheim
 *  Germany
 *  <rtems@embedded-brains.de>
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rtems.com/license/LICENSE.
 */

#include <bsp.h>
#include <bsp/irq-generic.h>
#include <bsp/lm3s3749.h>
#include <assert.h>

static volatile lm3s3749_sc *get_sc_regs(void)
{
  return (volatile lm3s3749_sc *)LM3S3749_SC_BASE;
}

static void init_main_osc(void)
{
  volatile lm3s3749_sc *sc = get_sc_regs();

  uint32_t sysdiv_val = LM3S3749_PLL_FREQUENCY / LM3S3749_SYSTEM_CLOCK;
  assert(sysdiv_val * LM3S3749_SYSTEM_CLOCK == LM3S3749_PLL_FREQUENCY);
  assert((sysdiv_val >= 4) && (sysdiv_val <= 16));

  uint32_t rcc = sc->rcc;

  rcc = (rcc & ~SCRCC_USESYSDIV) | SCRCC_BYPASS;
  sc->rcc = rcc;

  rcc = (rcc & ~(SCRCC_PWRDN | SCRCC_XTAL_MSK | SCRCC_OSCSRC_MSK)) |
      SCRCC_XTAL_10MHZ | SCRCC_OSCSRC_MOSC;
  sc->rcc = rcc;

  rcc = (rcc & ~SCRCC_SYSDIV_MSK) | SCRCC_SYSDIV(sysdiv_val / 2 - 1) | SCRCC_USESYSDIV;
  sc->rcc = rcc;

  while ((sc->ris & SCRIS_PLLLRIS) == 0)
      /* Wait for PLL lock */;

  rcc &= ~SCRCC_BYPASS;
  sc->rcc = rcc;
}

static void init_uart0_gpio(void)
{
  volatile lm3s3749_sc *sc = get_sc_regs();
  volatile lm3s3749_gpio *gpioa = (volatile lm3s3749_gpio *)LM3S3749_GPIO_A_BASE;

  /* Use AHB for GPIOA port. */
  sc->gpiohbctl |= SCGPIOHBCTL_PORTA;

  /* Enable GPIOA clock. */
  sc->rcgc2 |= SCRCGC2_GPIOA;

  /* Enable UART0 clock. */
  sc->rcgc1 |= SCRCGC1_UART0;

  asm volatile("nop");
  asm volatile("nop");
  asm volatile("nop");

  /* Configure U0TX/PA1 as output, U0RX/PA0 as input. */
  gpioa->dir = (gpioa->dir | (1 << 1)) & ~((uint32_t)1 << 0);

  /* Enable alternate function on PA0-1. */
  gpioa->afsel |= (1 << 1) | (1 << 0);

  /* Enable pull-up on U0RX/PA0. */
  gpioa->pur |= 1 << 0;

  /* Enable digital function on PA0-1. */
  gpioa->den |= (1 << 1) | (1 << 0);
}

void bsp_start(void)
{
  init_main_osc();
  init_uart0_gpio();

  bsp_interrupt_initialize();
}
