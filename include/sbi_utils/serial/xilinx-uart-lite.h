/*
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Copyright (c) 2020 Alexander Fasching <fasching.a91@gmail.com>
 *
 */

#ifndef __SERIAL_XILINX_UART_LITE_H__
#define __SERIAL_XILINX_UART_LITE_H__

#include <sbi/sbi_types.h>

void xilinx_uart_lite_putc(char ch);

int xilinx_uart_lite_getc(void);

int xilinx_uart_lite_init(unsigned long base);

#endif
