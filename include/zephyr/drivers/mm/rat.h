/*
 * Copyright (c) 2023 Texas Instruments Incorporated
 * Copyright (c) 2023 L Lakshmanan
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef ZEPHYR_INCLUDE_RAT_H_
#define ZEPHYR_INCLUDE_RAT_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define ADDR_TRANSLATE_MAX_REGIONS (16u)
#define RAT_CTRL(base_addr, i)     (volatile uint32_t *)(base_addr + 0x20 + 0x10 * (i))
#define RAT_BASE(base_addr, i)     (volatile uint32_t *)(base_addr + 0x24 + 0x10 * (i))
#define RAT_TRANS_L(base_addr, i)  (volatile uint32_t *)(base_addr + 0x28 + 0x10 * (i))
#define RAT_TRANS_H(base_addr, i)  (volatile uint32_t *)(base_addr + 0x2C + 0x10 * (i))
#ifndef NULL
#define NULL (0)
#endif

/**
 * \brief Enum's to represent different possible region size for the address translate module
 */
typedef enum address_trans_region_size_e {
	address_trans_region_size_1 = 0x0,
	address_trans_region_size_2,
	address_trans_region_size_4,
	address_trans_region_size_8,
	address_trans_region_size_16,
	address_trans_region_size_32,
	address_trans_region_size_64,
	address_trans_region_size_128,
	address_trans_region_size_256,
	address_trans_region_size_512,
	address_trans_region_size_1K,
	address_trans_region_size_2K,
	address_trans_region_size_4K,
	address_trans_region_size_8K,
	address_trans_region_size_16K,
	address_trans_region_size_32K,
	address_trans_region_size_64K,
	address_trans_region_size_128K,
	address_trans_region_size_256K,
	address_trans_region_size_512K,
	address_trans_region_size_1M,
	address_trans_region_size_2M,
	address_trans_region_size_4M,
	address_trans_region_size_8M,
	address_trans_region_size_16M,
	address_trans_region_size_32M,
	address_trans_region_size_64M,
	address_trans_region_size_128M,
	address_trans_region_size_256M,
	address_trans_region_size_512M,
	address_trans_region_size_1G,
	address_trans_region_size_2G,
	address_trans_region_size_4G
} address_trans_region_size;

/**
 * \brief Region config structure
 */
typedef struct address_trans_region_config_ {

	uint64_t system_addr;	/* translated 48b system addr as seen by the SOC, MUST align to
				 * region size
				 */
	uint32_t local_addr; /* start address as seen by the CPU, MUST align to region size */
	uint32_t size;

} address_trans_region_config;

/**
 * \brief Parameters for \ref address_trans_init
 */
typedef struct address_trans_params_s {

	uint32_t num_regions;   /* Number of regions to configure */
	uint32_t rat_base_addr; /* Base address of the RAT HW module */
	address_trans_region_config *region_config;	/*
							 * Pointer to array of region config,
							 * number of array element MUST be >=
							 * num_regions.
							 */
} address_trans_params;

void address_trans_init(address_trans_params *params);
void RAT_init(void *region_config, uint64_t rat_base_addr, uint8_t translate_regions);
void RAT_deinit(void);
void *rat_get_local_addr(uint64_t system_addr);

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* ZEPHYR_INCLUDE_RAT_H_ */

