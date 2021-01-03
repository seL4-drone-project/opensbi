/*
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Copyright (c) 2020 Western Digital Corporation or its affiliates.
 *
 * Authors:
 *   Anup Patel <anup.patel@wdc.com>
 */

#include <sbi_utils/fdt/fdt_helper.h>
#include <sbi_utils/serial/fdt_serial.h>
#include <sbi_utils/serial/xilinx-uart-lite.h>

static int serial_xilinx_init(void *fdt, int nodeoff,
			      const struct fdt_match *match)
{
	int rc;
	struct platform_uart_data uart;

	rc = fdt_parse_xilinx_uart_lite_node(fdt, nodeoff, &uart);
	if (rc)
		return rc;

	return xilinx_uart_lite_init(uart.addr);
}

static const struct fdt_match serial_xilinx_match[] = {
	{ .compatible = "xlnx,uart-lite" },
	{},
};

struct fdt_serial fdt_serial_xilinx = { .match_table = serial_xilinx_match,
					.init	     = serial_xilinx_init,
					.getc = xilinx_uart_lite_getc,
					.putc = xilinx_uart_lite_putc };
