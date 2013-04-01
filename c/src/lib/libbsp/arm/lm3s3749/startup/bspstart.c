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

static const lm3s3749_gpio_config start_config_gpio[] = {
#ifdef LM3S3749_ENABLE_UART_0
  LM3S3749_PIN_USART_RX(LM3S3749_PORT_A, 0),
  LM3S3749_PIN_USART_TX(LM3S3749_PORT_A, 1),
#endif
#ifdef LM3S3749_ENABLE_UART_1
  LM3S3749_PIN_USART_RX(LM3S3749_PORT_B, 0),
  LM3S3749_PIN_USART_TX(LM3S3749_PORT_B, 1),
#endif
#ifdef LM3S3749_ENABLE_UART_2
  LM3S3749_PIN_USART_RX(LM3S3749_PORT_D, 0),
  LM3S3749_PIN_USART_TX(LM3S3749_PORT_D, 1),
#endif
  /* LED pins */
  LM3S3749_PIN_LED(LM3S3749_PORT_D, 6),
  LM3S3749_PIN_LED(LM3S3749_PORT_D, 7),
};

static void init_uart0_gpio(void)
{
  volatile lm3s3749_sc *sc = get_sc_regs();

  /* Use AHB for all gpio ports. */
  sc->gpiohbctl |= SCGPIOHBCTL_PORTA | SCGPIOHBCTL_PORTB | SCGPIOHBCTL_PORTC |
      SCGPIOHBCTL_PORTD | SCGPIOHBCTL_PORTE | SCGPIOHBCTL_PORTF |
      SCGPIOHBCTL_PORTG | SCGPIOHBCTL_PORTH;

  /* Enable GPIOA and GPIOD clocks. */
  // FIXME do this somewhere else
  sc->rcgc2 |= SCRCGC2_GPIOA | SCRCGC2_GPIOD;

  /* Enable UART0 clock. */
  sc->rcgc1 |= SCRCGC1_UART0;

  asm volatile("nop");
  asm volatile("nop");
  asm volatile("nop");

  lm3s3749_gpio_set_config_array(start_config_gpio,
      sizeof(start_config_gpio) / sizeof(start_config_gpio[0]));
}

void bsp_start(void)
{
  init_main_osc();
  init_uart0_gpio();
  bsp_interrupt_initialize();
}
