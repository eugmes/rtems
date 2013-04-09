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
#include <bspopts.h>
#include <bsp/irq-generic.h>
#include <bsp/lm3s3749.h>
#include <bsp/io.h>
#include <bsp/sc.h>
#include <assert.h>

static void init_main_osc(void)
{
  volatile lm3s3749_sc *sc = LM3S3749_SC;

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

static const lm3s3749_gpio_config start_config_gpio[] = {
#ifdef LM3S3749_ENABLE_UART_0
  LM3S3749_PIN_UART_RX(LM3S3749_PORT_A, 0),
  LM3S3749_PIN_UART_TX(LM3S3749_PORT_A, 1),
#endif
#ifdef LM3S3749_ENABLE_UART_1
  LM3S3749_PIN_UART_RX(LM3S3749_PORT_B, 0),
  LM3S3749_PIN_UART_TX(LM3S3749_PORT_B, 1),
#endif
#ifdef LM3S3749_ENABLE_UART_2
  LM3S3749_PIN_UART_RX(LM3S3749_PORT_D, 0),
  LM3S3749_PIN_UART_TX(LM3S3749_PORT_D, 1),
#endif
};

static void init_gpio(void)
{
  volatile lm3s3749_sc *sc = LM3S3749_SC;

  /* Use AHB for all gpio ports. */
  sc->gpiohbctl |= SCGPIOHBCTL_PORTA | SCGPIOHBCTL_PORTB | SCGPIOHBCTL_PORTC |
      SCGPIOHBCTL_PORTD | SCGPIOHBCTL_PORTE | SCGPIOHBCTL_PORTF |
      SCGPIOHBCTL_PORTG | SCGPIOHBCTL_PORTH;

  lm3s3749_gpio_set_config_array(start_config_gpio,
      sizeof(start_config_gpio) / sizeof(start_config_gpio[0]));
}

void bsp_start(void)
{
  init_main_osc();
  init_gpio();
  bsp_interrupt_initialize();
}
