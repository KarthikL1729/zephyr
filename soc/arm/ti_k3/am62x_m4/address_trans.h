#ifndef ADDRESS_TRANS_H
#define ADDRESS_TRANS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/**
 * \defgroup KERNEL_DPL_ADDR_TRANSLATE APIs for Region based address translation (RAT) module
 * \ingroup KERNEL_DPL
 *
 * For more details and example usage, see \ref KERNEL_DPL_ADDR_TRANSLATE_PAGE
 *
 * @{
 */

/**
 * \brief Maximum regions in the address translate module
 */
#define address_trans_MAX_REGIONS      (16u)

/**
 * \brief Enum's to represent different possible region size for the address translate module
 */
typedef enum address_trans_RegionSize_e {
    address_trans_RegionSize_1 = 0x0,
    address_trans_RegionSize_2,
    address_trans_RegionSize_4,
    address_trans_RegionSize_8,
    address_trans_RegionSize_16,
    address_trans_RegionSize_32,
    address_trans_RegionSize_64,
    address_trans_RegionSize_128,
    address_trans_RegionSize_256,
    address_trans_RegionSize_512,
    address_trans_RegionSize_1K,
    address_trans_RegionSize_2K,
    address_trans_RegionSize_4K,
    address_trans_RegionSize_8K,
    address_trans_RegionSize_16K,
    address_trans_RegionSize_32K,
    address_trans_RegionSize_64K,
    address_trans_RegionSize_128K,
    address_trans_RegionSize_256K,
    address_trans_RegionSize_512K,
    address_trans_RegionSize_1M,
    address_trans_RegionSize_2M,
    address_trans_RegionSize_4M,
    address_trans_RegionSize_8M,
    address_trans_RegionSize_16M,
    address_trans_RegionSize_32M,
    address_trans_RegionSize_64M,
    address_trans_RegionSize_128M,
    address_trans_RegionSize_256M,
    address_trans_RegionSize_512M,
    address_trans_RegionSize_1G,
    address_trans_RegionSize_2G,
    address_trans_RegionSize_4G
} address_trans_RegionSize;

/**
 * \brief Region config structure, this is used by SysConfig and not to be used by end-users directly
 */
typedef struct address_trans_RegionConfig_ {

    uint64_t systemAddr; /**< translated 48b system addr as seen by the SOC, MUST align to region size */
    uint32_t localAddr;  /**< region start address as seen by the CPU, MUST align to region size */
    uint32_t size;       /**< region size, see \ref address_trans_RegionSize */

} address_trans_RegionConfig;

/**
 * \brief Parameters for \ref address_trans_init, this is used by SysConfig and not to be used by end-users directly
 */
typedef struct address_trans_Params_s {

    uint32_t numRegions;             /**< Number of regions to configure */
    uint32_t ratBaseAddr;            /**< Base address of the RAT HW module */
    address_trans_RegionConfig *regionConfig; /**< Pointer to array of region config,
                                                 * number of array element MUST be >= numRegions
                                                 */
} address_trans_Params;


/**
 * \brief Set default value for address translate parameters
 *
 * \param   params  [out] Structure initialized with default parameters
 */
void address_trans_Params_init(address_trans_Params *params);

/**
 * \brief Initialize Address translate sub-system, called by SysConfig, not to be called by end users
 *
 * \param   params  [in] Initialization parameters
 */
void address_trans_init(address_trans_Params *params);

/**
 * \brief Translate from 48b system address to a CPU address as seen via the RAT module
 *
 * \note If no mapping is found then lower 32b are returned as the local address,
 *       i.e no translation is done for 32b address, and address truncation for > 32b input addresses.
 * \note All drivers MUST call this API to translate peripheral MMR base addresses to CPU visible base addr.
 *       It is recommended to call this once to get the base address during driver module init.
 *
 * \param systemAddr    [in] 48b system address or SOC view address
 *
 * \return void * CPU view or local address
 */
void *address_trans_getLocalAddr(uint64_t systemAddr);

/** @} */

#ifdef __cplusplus
}
#endif

#ifndef NULL
#define NULL            (0)
#endif

#endif /* ADDR_TRANSLATEP_H */