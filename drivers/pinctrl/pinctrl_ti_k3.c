/*
 * Copyright (c) 2023 Enphase Energy
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#define DT_DRV_COMPAT ti_k3_pinctrl

#include <zephyr/arch/cpu.h>
#include <zephyr/drivers/pinctrl.h>


#ifdef CONFIG_RAT_TI_K3_M4
#include <address_trans.h>
#define KICK0_UNLOCK_VAL                        (0x68EF3490U)
#define KICK1_UNLOCK_VAL                        (0xD172BC5AU)
#define CSL_MCU_PADCONFIG_LOCK0_KICK0_OFFSET    (0x1008)
#define CSL_MCU_PADCONFIG_LOCK1_KICK0_OFFSET    (0x5008)
#define PADCFG_PMUX_OFFSET                      (0x4000U)

#endif

#define PINCTRL_NODE DT_NODELABEL(pinctrl)

static struct pinctrl_ti_k3_dev_data {
	DEVICE_MMIO_RAM;
} pinctrl_ti_k3_dev;

static struct pinctrl_ti_k3_cfg_data {
	DEVICE_MMIO_ROM;
} pinctrl_ti_k3_cfg = {
	DEVICE_MMIO_ROM_INIT(PINCTRL_NODE)
};

int pinctrl_configure_pins(const pinctrl_soc_pin_t *pins, uint8_t pin_cnt, uintptr_t reg)
{
	ARG_UNUSED(reg);
	const struct device *dev = DEVICE_DT_GET(PINCTRL_NODE);
	uintptr_t virt_reg_base = DEVICE_MMIO_GET(dev);

	#ifdef CONFIG_RAT_TI_K3_M4
	/* Unlocking MMR */
	uint32_t           			 baseAddr;
    volatile uint32_t  			*kickAddr;

	baseAddr = (uint32_t) address_trans_getLocalAddr(virt_reg_base);
	/* Lock 0 */
    kickAddr = (volatile uint32_t *)(baseAddr + CSL_MCU_PADCONFIG_LOCK0_KICK0_OFFSET);
    sys_write32(KICK0_UNLOCK_VAL, (uintptr_t) kickAddr);   /* KICK 0 */
    kickAddr++;
	sys_write32(KICK1_UNLOCK_VAL, (uintptr_t) kickAddr);   /* KICK 1 */

    /* Lock 1 */
    kickAddr = (volatile uint32_t *)(baseAddr + CSL_MCU_PADCONFIG_LOCK1_KICK0_OFFSET);
    sys_write32(KICK0_UNLOCK_VAL, (uintptr_t) kickAddr);   /* KICK 0 */
    kickAddr++;
    sys_write32(KICK1_UNLOCK_VAL, (uintptr_t) kickAddr);   /* KICK 1 */

	/* Writing with address translation */

	baseAddr = (uint32_t) address_trans_getLocalAddr((uint32_t) virt_reg_base + PADCFG_PMUX_OFFSET);
	for (uint8_t i = 0; i < pin_cnt; i++) {
		sys_write32(pins[i].value, (uintptr_t) (baseAddr + pins[i].offset));
	}

	#else
	for (uint8_t i = 0; i < pin_cnt; i++) {
		sys_write32(pins[i].value, virt_reg_base + pins[i].offset);
	}
	#endif

	return 0;
}

static int pinctrl_ti_k3_init(const struct device *dev)
{
	DEVICE_MMIO_MAP(dev, K_MEM_CACHE_NONE);
	return 0;
}

DEVICE_DT_DEFINE(PINCTRL_NODE,
		 pinctrl_ti_k3_init,
		 NULL,
		 &pinctrl_ti_k3_dev,
		 &pinctrl_ti_k3_cfg,
		 PRE_KERNEL_1,
		 CONFIG_KERNEL_INIT_PRIORITY_DEFAULT,
		 NULL);
