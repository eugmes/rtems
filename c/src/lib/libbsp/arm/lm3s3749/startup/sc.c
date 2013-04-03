#include <bsp/sc.h>
#include <bsp/lm3s3749.h>
#include <rtems.h>

static void delay_3_clocks(void)
{
  asm volatile(
      "nop\n\t"
      "nop\n\t"
      "nop");
}

void lm3s3749_sc_enable_gpio_clock(unsigned int port, bool enable)
{
  volatile lm3s3749_sc *sc = LM3S3749_SC;
  uint32_t mask = 1 << port;
  rtems_interrupt_level level;

  rtems_interrupt_disable(level);

  if (enable)
    sc->rcgc2 |= mask;
  else
    sc->rcgc2 &= ~mask;

  delay_3_clocks();

  rtems_interrupt_enable(level);
}

void lm3s3749_sc_enable_uart_clock(unsigned int port, bool enable)
{
  volatile lm3s3749_sc *sc = LM3S3749_SC;
  uint32_t mask = 1 << port;
  rtems_interrupt_level level;

  rtems_interrupt_disable(level);

  if (enable)
    sc->rcgc1 |= mask;
  else
    sc->rcgc1 &= ~mask;

  delay_3_clocks();

  rtems_interrupt_enable(level);
}

void lm3s3749_sc_enable_ssi_clock(unsigned int port, bool enable)
{
  volatile lm3s3749_sc *sc = LM3S3749_SC;
  uint32_t mask = 1 << (port + 4);
  rtems_interrupt_level level;

  rtems_interrupt_disable(level);

  if (enable)
    sc->rcgc1 |= mask;
  else
    sc->rcgc1 &= ~mask;

  delay_3_clocks();

  rtems_interrupt_enable(level);
}
