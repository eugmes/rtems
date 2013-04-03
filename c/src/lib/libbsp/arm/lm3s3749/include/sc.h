#ifndef LIBBSP_ARM_LM3S3749_SC_H
#define LIBBSP_ARM_LM3S3749_SC_H
#include <stdbool.h>

void lm3s3749_sc_enable_gpio_clock(unsigned int port, bool enable);
void lm3s3749_sc_enable_uart_clock(unsigned int port, bool enable);
void lm3s3749_sc_enable_ssi_clock(unsigned int port, bool enable);

#endif
