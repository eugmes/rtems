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

#ifndef LIBBSP_ARM_LM3S3749_LM3S3749_H
#define LIBBSP_ARM_LM3S3749_LM3S3749_H
#include <bsp/utility.h>

#define LM3S3749_SC_BASE 0x400fe000

#define LM3S3749_UART_0_BASE 0x4000c000
#define LM3S3749_UART_1_BASE 0x4000d000
#define LM3S3749_UART_2_BASE 0x4000e000

/* AHB apperture is used for GPIO */
#define LM3S3749_GPIO_A_BASE 0x40058000
#define LM3S3749_GPIO_B_BASE 0x40059000
#define LM3S3749_GPIO_C_BASE 0x4005a000
#define LM3S3749_GPIO_D_BASE 0x4005b000
#define LM3S3749_GPIO_E_BASE 0x4005c000
#define LM3S3749_GPIO_F_BASE 0x4005d000
#define LM3S3749_GPIO_G_BASE 0x4005e000
#define LM3S3749_GPIO_H_BASE 0x4005f000

#define LM3S3749_PLL_FREQUENCY 400000000

typedef struct  {
  uint32_t data[256]; /* Masked data registers are included here. */
  uint32_t dir;
  uint32_t is;
  uint32_t ibe;
  uint32_t iev;
  uint32_t im;
  uint32_t ris;
  uint32_t mis;
  uint32_t icr;
  uint32_t afsel;

  uint32_t reserved_0[55];

  uint32_t dr2r;
  uint32_t dr4r;
  uint32_t dr8r;
  uint32_t odr;
  uint32_t pur;
  uint32_t pdr;
  uint32_t slr;
  uint32_t den;
  uint32_t lock;
  uint32_t cr;
  uint32_t amsel;
} lm3s3749_gpio;

typedef struct {
  uint32_t did0;
  uint32_t did1;

  uint32_t dc0;
  uint32_t reserved_0;
  uint32_t dc1;
  uint32_t dc2;
  uint32_t dc3;
  uint32_t dc4;
  uint32_t dc5;
  uint32_t dc6;
  uint32_t dc7;

  uint32_t reserved_1;

#define SCPBORCTL_BORIOR BSP_BIT32(1)
  uint32_t pborctl;

#define SCLDOPCTL_VADJ(val) BSP_FLD32(val, 0, 5)
#define SCLDOPCTL_VADJ_MASK BSP_MSK32(0, 5)
  uint32_t ldopctl;

  uint32_t reserved_2[2];

  uint32_t srcr0;
  uint32_t srcr1;
  uint32_t srcr2;

  uint32_t reserved_3;

#define SCRIS_MOSCPUPRIS BSP_BIT32(8)
#define SCRIS_USBPLLRIS BSP_BIT32(7)
#define SCRIS_PLLLRIS BSP_BIT32(6)
#define SCRIS_BORRIS BSP_BIT32(1)
  uint32_t ris;

#define SCIMC_MOSCPUPIM BSP_BIT32(8)
#define SCIMC_USBPLLLIM BSP_BIT32(7)
#define SCIMC_PLLLIM BSP_BIT32(6)
#define SCIMC_BORIM BSP_BIT32(1)
  uint32_t imc;

#define SCMISC_MOSCPUPMIS BSP_BIT32(8)
#define SCMISC_USBPLLLMIS BSP_BIT32(7)
#define SCMISC_PLLLMIS BSP_BIT32(6)
#define SCMISC_BORMIS BSP_BIT32(1)
  uint32_t misc;

#define SCRESC_MOSCFAIL BSP_BIT32(16)
#define SCRESC_SW BSP_BIT32(4)
#define SCRESC_WDT BSP_BIT32(3)
#define SCRESC_BOR BSP_BIT32(2)
#define SCRESC_POR BSP_BIT32(1)
#define SCRESC_EXT BSP_BIT32(0)
  uint32_t resc;

#define SCRCC_AGC BSP_BIT32(27)
#define SCRCC_SYSDIV(val) BSP_FLD32(val, 23, 26)
#define SCRCC_SYSDIV_MSK BSP_MSK32(23, 26)
#define SCRCC_USESYSDIV BSP_BIT32(22)
#define SCRCC_USEPWMDIV BSP_BIT32(20)
#define SCRCC_PWMDIV(val) BSP_FLD32(val, 17, 19)
#define SCRCC_PWMDIV_MSK BSP_MSK32(17, 19)
#define SCRCC_PWRDN BSP_BIT32(13)
#define SCRCC_BYPASS BSP_BIT32(11)
#define SCRCC_XTAL(val) BSP_FLD32(val, 6, 10)
#define SCRCC_XTAL_10MHZ SCRCC_XTAL(0x10)
#define SCRCC_XTAL_MSK BSP_MSK32(6, 10)
#define SCRCC_OSCSRC(val) BSP_FLD32(val, 4, 5)
#define SCRCC_OSCSRC_MOSC SCRCC_OSCSRC(0x0)
#define SCRCC_OSCSRC_IOSC SCRCC_OSCSRC(0x1)
#define SCRCC_OSCSRC_IOSC_DIV_4 SCRCC_OSCSRC(0x2)
#define SCRCC_OSCSRC_30KHZ SCRCC_OSCSRC(0x3)
#define SCRCC_OSCSRC_MSK BSP_MSK32(4, 5)
#define SCRCC_IOSCDIS BSP_BIT32(1)
#define SCRCC_MOSCDIS BSP_BIT32(0)
  uint32_t rcc;

#define SCPLLCFG_F(val) BSP_FLD32(val, 5, 13)
#define SCPLLCFG_F_MSK BSP_MSK32(5, 13)
#define SCPLLCFG_R(val) BSP_FLD32(val, 0, 4)
#define SCPLLCFG_R_MSK BSP_MSK32(0, 4)
  uint32_t pllcfg;

  uint32_t reserved_4;

#define SCGPIOHBCTL_PORTH BSP_BIT32(7)
#define SCGPIOHBCTL_PORTG BSP_BIT32(6)
#define SCGPIOHBCTL_PORTF BSP_BIT32(5)
#define SCGPIOHBCTL_PORTE BSP_BIT32(4)
#define SCGPIOHBCTL_PORTD BSP_BIT32(3)
#define SCGPIOHBCTL_PORTC BSP_BIT32(2)
#define SCGPIOHBCTL_PORTB BSP_BIT32(1)
#define SCGPIOHBCTL_PORTA BSP_BIT32(0)
  uint32_t gpiohbctl;

#define SCRCC2_USERCC2 BSP_BIT32(31)
#define SCRCC2_SYSDIV2(val) BSP_FLD32(val, 23, 28)
#define SCRCC2_SYSDIV2_MSK(val) BSP_MSK32(23, 28)
#define SCRCC2_USBPWRDN BSP_BIT32(14)
#define SCRCC2_PWRDN2 BSP_BIT32(13)
#define SCRCC2_BYPASS2 BSP_BIT32(11)
#define SCRCC2_OSCSRC2(val) BSP_FLD32(val, 4, 6)
#define SCRCC2_OSCSRC2_MSK BSP_MSK32(4, 6)
  uint32_t rcc2;

  uint32_t reserved_5[2];

#define SCMOSCCTL_CVAL BSP_BIT32(0)
  uint32_t moscctl;

  uint32_t reserved_6[32];

#define SCRCGC0_PWM BSP_BIT32(20)
#define SCRCGC0_ADC BSP_BIT32(16)
#define SCRCGC0_MAXADCSPD(val) BSP_FLD32(val, 8, 9)
#define SCRCGC0_MAXADCSPD_MSK BSP_MSK32(8, 9)
#define SCRCGC0_HIB BSP_BIT32(6)
#define SCRCGC0_WDT BSP_BIT32(3)
  uint32_t rcgc0;

#define SCRCGC1_COMP1 BSP_BIT32(25)
#define SCRCGC1_COMP0 BSP_BIT32(24)
#define SCRCGC1_TIMER3 BSP_BIT32(19)
#define SCRCGC1_TIMER2 BSP_BIT32(18)
#define SCRCGC1_TIMER1 BSP_BIT32(17)
#define SCRCGC1_TIMER0 BSP_BIT32(16)
#define SCRCGC1_I2C1 BSP_BIT32(14)
#define SCRCGC1_I2C0 BSP_BIT32(12)
#define SCRCGC1_QEI0 BSP_BIT32(8)
#define SCRCGC1_SSI1 BSP_BIT32(5)
#define SCRCGC1_SSI0 BSP_BIT32(4)
#define SCRCGC1_UART2 BSP_BIT32(2)
#define SCRCGC1_UART1 BSP_BIT32(1)
#define SCRCGC1_UART0 BSP_BIT32(0)
  uint32_t rcgc1;

#define SCRCGC2_USB0 BSP_BIT32(16)
#define SCRCGC2_UDMA BSP_BIT32(13)
#define SCRCGC2_GPIOH BSP_BIT32(7)
#define SCRCGC2_GPIOG BSP_BIT32(6)
#define SCRCGC2_GPIOF BSP_BIT32(5)
#define SCRCGC2_GPIOE BSP_BIT32(4)
#define SCRCGC2_GPIOD BSP_BIT32(3)
#define SCRCGC2_GPIOC BSP_BIT32(2)
#define SCRCGC2_GPIOB BSP_BIT32(1)
#define SCRCGC2_GPIOA BSP_BIT32(0)
  uint32_t rcgc2;

  uint32_t reserved_7;

  uint32_t scgc0;
  uint32_t scgc1;
  uint32_t scgc2;

  uint32_t reserved_8;

  uint32_t dcgc0;
  uint32_t dcgc1;
  uint32_t dcgc2;

  uint32_t reserved_9[6];

#define SCDSLPCLKCFG_DSDIVORIDE(val) BSP_FLD32(val, 23, 28)
#define SCDSLPCLKCFG_DSDIVORIDE_MSK BSP_MSK32(23, 28)
#define SCDSLPCLKCFG_DSOSCSRC(val) BSP_FLD32(val, 4, 6)
#define SCDSLPCLKCFG_DSOSCSRC_MSK BSP_MSK32(4, 6)
  uint32_t dslpclkcfg;
} lm3s3749_sc;

typedef struct {
#define UARTDR_OE BSP_BIT32(11)
#define UARTDR_BE BSP_BIT32(10)
#define UARTDR_PE BSP_BIT32(9)
#define UARTDR_FE BSP_BIT32(8)
#define UARTDR_DATA(val) BSP_FLD32(val, 0, 7)
  uint32_t dr;

  uint32_t rsr_ecr;
  uint32_t reserved_0[4];

#define UARTFR_TXFE BSP_BIT32(7)
#define UARTFR_RXFF BSP_BIT32(6)
#define UARTFR_TXFF BSP_BIT32(5)
#define UARTFR_RXFE BSP_BIT32(4)
#define UARTFR_BUSY BSP_BIT32(3)
  uint32_t fr;

  uint32_t reserved_1;

  uint32_t ilpr;
  uint32_t ibrd;
  uint32_t fbrd;

#define UARTLCRH_SPS BSP_BIT32(7)
#define UARTLCRH_WLEN(val) BSP_FLD32(val, 5, 6)
#define UARTLCRH_FEN BSP_BIT32(4)
#define UARTLCRH_STP2 BSP_BIT32(3)
#define UARTLCRH_EPS BSP_BIT32(2)
#define UARTLCRH_PEN BSP_BIT32(1)
#define UARTLCRH_BRK BSP_BIT32(0)
  uint32_t lcrh;

#define UARTCTL_RXE BSP_BIT32(9)
#define UARTCTL_TXE BSP_BIT32(8)
#define UARTCTL_LBE BSP_BIT32(7)
#define UARTCTL_SIRLP BSP_BIT32(2)
#define UARTCTL_SIREN BSP_BIT32(1)
#define UARTCTL_UARTEN BSP_BIT32(0)
  uint32_t ctl;

#define UARTIFLS_RXIFLSEL(val) BSP_FLD32(val, 3, 5)
#define UARTIFLS_TXIFLSEL(val) BSP_FLD32(val, 0, 2)
  uint32_t ifls;

#define UARTI_OE BSP_BIT32(10)
#define UARTI_BE BSP_BIT32(9)
#define UARTI_PE BSP_BIT32(8)
#define UARTI_FE BSP_BIT32(7)
#define UARTI_RT BSP_BIT32(6)
#define UARTI_TX BSP_BIT32(5)
#define UARTI_RX BSP_BIT32(4)
  uint32_t im;
  uint32_t ris;
  uint32_t mis;
  uint32_t icr;
} lm3s3749_uart;

#endif /* LIBBSP_ARM_LM3S3749_LM3S3749_H */
