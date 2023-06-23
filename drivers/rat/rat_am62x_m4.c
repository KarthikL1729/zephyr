#include "rat_am62x_m4.h"
#include <zephyr/sys/__assert.h>

address_trans_RegionConfig region_config[ADDR_TRANSLATE_REGIONS] = 
{
    {
        .systemAddr = 0x0u,
        .localAddr = 0x80000000u,
        .size = address_trans_RegionSize_512M,
    },
    {
        .localAddr = 0xA0000000u,
        .systemAddr = 0x20000000u,
        .size = address_trans_RegionSize_512M,
    },
    {
        .localAddr = 0xC0000000u,
        .systemAddr = 0x40000000u,
        .size = address_trans_RegionSize_512M,
    },
    {
        .localAddr = 0x60000000u,
        .systemAddr = 0x60000000u,
        .size = address_trans_RegionSize_512M,
    },

    /* 
        Add regions here if you want to map more memory.    
    */
};

address_trans_Params translate_config = {
    .numRegions = ADDR_TRANSLATE_REGIONS,
    .ratBaseAddr = ADDR_TRANSLATE_RAT_BASE_ADDR,
    .regionConfig = &region_config,
};

void *rat_get_local_addr(uint64_t systemAddr)
{
    uint32_t found, regionId;
    void *localAddr;

    __ASSERT(translate_config.numRegions<address_trans_MAX_REGIONS, "Exceeding maximum number of regions");

    found = 0;
    uint32_t x = translate_config.numRegions;
    for(regionId=0; regionId<translate_config.numRegions; regionId++)
    {
        uint64_t startAddr, endAddr;
        uint32_t sizeMask;

        /* we assume translate_config.regionConfig[] address and size is aligned */
        sizeMask = ( (uint32_t)( ((uint64_t)1 << translate_config.regionConfig[regionId].size) - 1) );

        startAddr = translate_config.regionConfig[regionId].systemAddr;

        /* calculate end address */
        endAddr = startAddr + sizeMask;

        /* see if input address falls in this region */
        if(systemAddr >= startAddr && systemAddr <= endAddr)
        {
            /* yes, input address falls in this region, break from loop */
            found = 1;
            break;
        }
    }
    if(found)
    {
        /* translate input address to output address */
        uint32_t offset = systemAddr - translate_config.regionConfig[regionId].systemAddr;

        localAddr = (void *) (translate_config.regionConfig[regionId].localAddr + offset);
    }
    else
    {
        /* no mapping found, set output = input with 32b truncation */
        localAddr = (void *) systemAddr;
    }
    return localAddr;
}