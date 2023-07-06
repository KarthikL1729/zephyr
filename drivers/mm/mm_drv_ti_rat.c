/*
 * Copyright (c) 2023 Texas Instruments Incorporated
 * Copyright (c) 2023 L Lakshmanan
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/drivers/mm/system_mm.h>
#include <zephyr/drivers/mm/rat.h>
#include <zephyr/sys/__assert.h>

address_trans_params translate_config;

static void address_trans_set_region(uint32_t rat_base_addr, uint16_t region_num,
			uint64_t system_addr, uint32_t local_addr, uint32_t size, uint32_t enable)
{
	uint32_t system_addrL, system_addrH;

	if (size > address_trans_region_size_4G) {
		size = address_trans_region_size_4G;
	}
	system_addrL = (uint32_t)(system_addr & ~((uint32_t)(((uint64_t)1 << size) - 1)));
	system_addrH = (uint32_t)((system_addr >> 32) & 0xFFFF);
	local_addr = local_addr & ~((uint32_t)(((uint64_t)1 << size) - 1));

	/* disable RAT region first */
	*RAT_CTRL(rat_base_addr, region_num) = 0;
	*RAT_BASE(rat_base_addr, region_num) = local_addr;
	*RAT_TRANS_L(rat_base_addr, region_num) = system_addrL;
	*RAT_TRANS_H(rat_base_addr, region_num) = system_addrH;
	/* set size and enable the region */
	*RAT_CTRL(rat_base_addr, region_num) = ((enable & 0x1) << 31u) | (size & 0x3F);
}

static void address_trans_init(address_trans_params *params)
{
	uint32_t i;

	if (params != NULL) {
		translate_config = *params;
	}

	__ASSERT(translate_config.num_regions < ADDR_TRANSLATE_MAX_REGIONS,
		 "Exceeding maximum number of regions");

	for (i = 0; i < translate_config.num_regions; i++) {
		__ASSERT(translate_config.rat_base_addr != 0, "RAT base address cannot be 0");
		__ASSERT(translate_config.region_config != NULL,
			 "RAT region config cannot be NULL");

		/* enable regions setup by user */
		address_trans_set_region(translate_config.rat_base_addr, i,
					 translate_config.region_config[i].system_addr,
					 translate_config.region_config[i].local_addr,
					 translate_config.region_config[i].size, 1);
	}
}

void mm_drv_ti_rat_init(void *region_config, uint64_t rat_base_addr, uint8_t translate_regions)
{
	translate_config.num_regions = translate_regions;
	translate_config.rat_base_addr = rat_base_addr;
	translate_config.region_config = (address_trans_region_config *)region_config;

	address_trans_init(&translate_config);
}

int sys_mm_drv_page_phys_get(void *virt, uintptr_t *phys)
{
	if (virt == NULL) {
		return -EINVAL;
	}
	uint64_t pa = ((uint64_t) (virt));
	uintptr_t *va = phys;

	uint32_t found, regionId;

	__ASSERT(translate_config.num_regions < address_trans_MAX_REGIONS,
		 "Exceeding maximum number of regions");

	found = 0;

	for (regionId = 0; regionId < translate_config.num_regions; regionId++) {
		uint64_t start_addr, end_addr;
		uint32_t size_mask;

		/* we assume translate_config.region_config[] address and size is aligned */
		size_mask =
			((uint32_t)(((uint64_t)1 << translate_config.region_config[regionId].size) -
				    1));

		start_addr = translate_config.region_config[regionId].system_addr;

		/* calculate end address */
		end_addr = start_addr + size_mask;

		/* see if input address falls in this region */
		if (pa >= start_addr && pa <= end_addr) {
			/* yes, input address falls in this region, break from loop */
			found = 1;
			break;
		}
	}
	if (found) {
		/* translate input address to output address */
		uint32_t offset =
			pa - translate_config.region_config[regionId].system_addr;

		*va = (void *)(translate_config.region_config[regionId].local_addr + offset);
	} else {
		/* no mapping found, set output = input with 32b truncation */
		*va = (void *)pa;
	}

	if (va == NULL) {
		return -EFAULT;
	}
	return 0;
}
