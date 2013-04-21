/*
 * Copyright © 2013 Eugeniy Meshcheryakov <eugen@debian.org>
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rtems.com/license/LICENSE.
 */

#ifndef LIBBSP_ARM_LM3S3749_IO_H
#define LIBBSP_ARM_LM3S3749_IO_H
#include <stdbool.h>

typedef enum {
  LM3S3749_GPIO_DIRECTION_INPUT,
  LM3S3749_GPIO_DIRECTION_OUTPUT
} lm3s3749_gpio_direction;

typedef enum {
  LM3S3749_GPIO_OTYPE_PUSH_PULL,
  LM3S3749_GPIO_OTYPE_OPEN_DRAIN
} lm3s3749_gpio_otype;

typedef enum {
  LM3S3749_GPIO_DRIVE_2MA,
  LM3S3749_GPIO_DRIVE_4MA,
  LM3S3749_GPIO_DRIVE_8MA
} lm3s3749_gpio_drive;

typedef enum {
  LM3S3749_GPIO_NO_PULL,
  LM3S3749_GPIO_PULL_UP,
  LM3S3749_GPIO_PULL_DOWN
} lm3s3749_gpio_pull;

typedef enum {
  LM3S3749_GPIO_DIGITAL_DISABLE,
  LM3S3749_GPIO_DIGITAL_ENABLE,
} lm3s3749_gpio_digital;

typedef enum {
  LM3S3749_GPIO_AF_DISABLE,
  LM3S3749_GPIO_AF_ENABLE
} lm3s3749_gpio_af;

typedef enum {
  LM3S3749_GPIO_ANALOG_DISABLE,
  LM3S3749_GPIO_ANALOG_ENABLE
} lm3s3749_gpio_analog;

typedef enum {
  LM3S3749_GPIO_NO_SLEW_RATE_CONTROL,
  LM3S3749_GPIO_SLEW_RATE_CONTROL
} lm3s3749_gpio_slew_rate_control;

typedef struct {
  unsigned int pin_first : 8;
  unsigned int pin_last : 8;
  unsigned int digital : 1;
  unsigned int alternate : 1;
  unsigned int analog : 1;
  unsigned int dir : 1;
  unsigned int otype : 1;
  unsigned int drive : 2;
  unsigned int pull : 2;
  unsigned int slr : 1;
} lm3s3749_gpio_config;

typedef enum {
  LM3S3749_PORT_A,
  LM3S3749_PORT_B,
  LM3S3749_PORT_C,
  LM3S3749_PORT_D,
  LM3S3749_PORT_E,
  LM3S3749_PORT_F,
  LM3S3749_PORT_G,
  LM3S3749_PORT_H
} lm3s3749_gpio_port;

#define LM3S3749_GPIO_PIN(port, idx) (((port) << 3) | (idx))
#define LM3S3749_GPIO_PORT_OF_PIN(pin) (((pin) >> 3) & 0xf)
#define LM3S3749_GPIO_INDEX_OF_PIN(pin) ((pin) & 0x7)

#define LM3S3749_PIN_UART_TX(port, idx) \
  { \
    .pin_first = LM3S3749_GPIO_PIN(port, idx), \
    .pin_last = LM3S3749_GPIO_PIN(port, idx), \
    .digital = LM3S3749_GPIO_DIGITAL_ENABLE, \
    .alternate = LM3S3749_GPIO_AF_ENABLE, \
    .analog = LM3S3749_GPIO_ANALOG_DISABLE, \
    .dir = LM3S3749_GPIO_DIRECTION_OUTPUT, \
    .otype = LM3S3749_GPIO_OTYPE_PUSH_PULL, \
    .drive = LM3S3749_GPIO_DRIVE_2MA, \
    .pull = LM3S3749_GPIO_NO_PULL, \
    .slr = LM3S3749_GPIO_NO_SLEW_RATE_CONTROL \
  }

#define LM3S3749_PIN_UART_RX(port, idx) \
  { \
    .pin_first = LM3S3749_GPIO_PIN(port, idx), \
    .pin_last = LM3S3749_GPIO_PIN(port, idx), \
    .digital = LM3S3749_GPIO_DIGITAL_ENABLE, \
    .alternate = LM3S3749_GPIO_AF_ENABLE, \
    .analog = LM3S3749_GPIO_ANALOG_DISABLE, \
    .dir = LM3S3749_GPIO_DIRECTION_INPUT, \
    .otype = LM3S3749_GPIO_OTYPE_PUSH_PULL, \
    .drive = LM3S3749_GPIO_DRIVE_2MA, \
    .pull = LM3S3749_GPIO_PULL_UP, \
    .slr = LM3S3749_GPIO_NO_SLEW_RATE_CONTROL \
  }

#define LM3S3749_PIN_LED(port, idx) \
  { \
    .pin_first = LM3S3749_GPIO_PIN(port, idx), \
    .pin_last = LM3S3749_GPIO_PIN(port, idx), \
    .digital = LM3S3749_GPIO_DIGITAL_ENABLE, \
    .alternate = LM3S3749_GPIO_AF_DISABLE, \
    .analog = LM3S3749_GPIO_ANALOG_DISABLE, \
    .dir = LM3S3749_GPIO_DIRECTION_OUTPUT, \
    .otype = LM3S3749_GPIO_OTYPE_PUSH_PULL, \
    .drive = LM3S3749_GPIO_DRIVE_8MA, \
    .pull = LM3S3749_GPIO_NO_PULL, \
    .slr = LM3S3749_GPIO_SLEW_RATE_CONTROL \
  }

#define LM3S3749_PIN_SSI_TX(port, idx) LM3S3749_PIN_UART_TX(port, idx)
#define LM3S3749_PIN_SSI_RX(port, idx) LM3S3749_PIN_UART_RX(port, idx)

void lm3s3749_gpio_set_config(const lm3s3749_gpio_config *config);
void lm3s3749_gpio_set_config_array(const lm3s3749_gpio_config *configs, unsigned int count);
void lm3s3749_gpio_digital_enable(unsigned int pin, bool enable);
void lm3s3749_gpio_analog_mode_select(unsigned int pin, bool enable);

void lm3s3749_gpio_set_pin(unsigned int pin, bool set);
bool lm3s3749_gpio_get_pin(unsigned int pin);

#endif
