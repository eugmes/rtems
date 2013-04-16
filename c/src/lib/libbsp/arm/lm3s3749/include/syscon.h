#ifndef LIBBSP_ARM_LM3S3749_SYSCON_H
#define LIBBSP_ARM_LM3S3749_SYSCON_H
#include <stdbool.h>

void lm3s3749_syscon_enable_gpio_clock(unsigned int port, bool enable);
void lm3s3749_syscon_enable_uart_clock(unsigned int port, bool enable);
void lm3s3749_syscon_enable_ssi_clock(unsigned int port, bool enable);
void lm3s3749_syscon_enable_pwm_clock(bool enable);
void lm3s3749_syscon_set_pwmdiv(unsigned int div);

#endif
