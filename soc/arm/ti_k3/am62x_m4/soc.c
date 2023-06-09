/*
 * Copyright (c) 2023 L Lakshmanan
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/arch/cpu.h>
#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/init.h>
#include <soc.h>
#include <pinctrl_soc.h>

int am62x_m4_init(void)
{
	NMI_INIT();
	RAT_init();
	return 0;
}

SYS_INIT(am62x_m4_init, PRE_KERNEL_1, 0);
