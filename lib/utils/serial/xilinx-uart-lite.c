/*
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Copyright (c) Alexander Fasching <fasching.a91@gmail.com>
 *
 */

#include <sbi/riscv_io.h>
#include <sbi/sbi_console.h>
#include <sbi_utils/serial/xilinx-uart-lite.h>

/* clang-format off */

// Register map
#define UART_LITE_REG_RXFIFO	0
#define UART_LITE_REG_TXFIFO	1
#define UART_LITE_REG_STAT	2
#define UART_LITE_REG_CTRL	3

// Control register
#define UART_LITE_CTRL_RSTTX	0x01
#define UART_LITE_CTRL_RSTRX	0x02
#define UART_LITE_CTRL_INTEN	0x10

// Status register
#define UART_LITE_STAT_RXVALID	    0x01
#define UART_LITE_STAT_RXFULL	    0x02
#define UART_LITE_STAT_TXEMPTY	    0x04
#define UART_LITE_STAT_TXFULL	    0x08
#define UART_LITE_STAT_INTEN	    0x10
#define UART_LITE_STAT_OVERRUNERR   0x20
#define UART_LITE_STAT_FRAMEERR	    0x40
#define UART_LITE_STAT_PARITYERR    0x80

/* clang-format on */

static volatile uint32_t *uart_base;

void xilinx_uart_lite_putc(char ch)
{
	// TODO: Use atomic operations?
	volatile uint32_t *tx = uart_base + UART_LITE_REG_TXFIFO;
	volatile uint32_t *st = uart_base + UART_LITE_REG_STAT;

	while ((*st) & UART_LITE_STAT_TXFULL)
		;
	*tx = ch;
}

int xilinx_uart_lite_getc(void)
{
	volatile uint32_t *rx = uart_base + UART_LITE_REG_RXFIFO;
	volatile uint32_t *st = uart_base + UART_LITE_REG_STAT;

	if ((*st) & UART_LITE_STAT_RXVALID)
		return -1;

	return (*rx) & 0xFF;
}

int xilinx_uart_lite_init(unsigned long base)
{
	uart_base = (volatile uint32_t *)base;

	// TODO: Configure IP in defined state.

	return 0;
}
