#include <address_trans.h>
#include <zephyr/sys/__assert.h>

#define RAT_CTRL(baseAddr, i)       (volatile uint32_t*)(baseAddr + 0x20 + 0x10*(i))
#define RAT_BASE(baseAddr, i)       (volatile uint32_t*)(baseAddr + 0x24 + 0x10*(i))
#define RAT_TRANS_L(baseAddr, i)    (volatile uint32_t*)(baseAddr + 0x28 + 0x10*(i))
#define RAT_TRANS_H(baseAddr, i)    (volatile uint32_t*)(baseAddr + 0x2C + 0x10*(i))

#define CONFIG_ADDR_TRANSLATE_RAT_BASE_ADDR  (0x044200000u)
#define CONFIG_ADDR_TRANSLATE_REGIONS  (4u)

address_trans_Params gAddrTranslateConfig = {
    .numRegions = 0,
    .ratBaseAddr = 0,
    .regionConfig = NULL,
};

static void address_trans_setRegion(uint32_t ratBaseAddr, uint16_t regionNum,
        uint64_t systemAddr, uint32_t localAddr,
        uint32_t size, uint32_t enable)
{
    uint32_t systemAddrL, systemAddrH;
    if(size > address_trans_RegionSize_4G)
    {
        size = address_trans_RegionSize_4G;
    }
    systemAddrL = (uint32_t)(systemAddr & ~( (uint32_t)( ((uint64_t)1 << size) - 1) ));
    systemAddrH = (uint32_t)((systemAddr >> 32 ) & 0xFFFF);
    localAddr = localAddr   & ~( (uint32_t)( ((uint64_t)1 << size) - 1) );

    /* disable RAT region first */
    *RAT_CTRL(ratBaseAddr, regionNum) = 0;
    *RAT_BASE(ratBaseAddr, regionNum) = localAddr;
    *RAT_TRANS_L(ratBaseAddr, regionNum) = systemAddrL;
    *RAT_TRANS_H(ratBaseAddr, regionNum) = systemAddrH;
    /* set size and enable the region */
    *RAT_CTRL(ratBaseAddr, regionNum) = ((enable & 0x1) << 31u) | (size & 0x3F);
}

void address_trans_Params_init(address_trans_Params *params)
{
    params->numRegions = 0;
    params->ratBaseAddr = 0;
    params->regionConfig = NULL;
}

void address_trans_init(address_trans_Params *params)
{
    uint32_t i;

    if(params!=NULL)
    {
        gAddrTranslateConfig = *params;
    }

    __ASSERT(gAddrTranslateConfig.numRegions<address_trans_MAX_REGIONS, "init test");

    for(i=0; i<gAddrTranslateConfig.numRegions; i++)
    {
        __ASSERT(gAddrTranslateConfig.ratBaseAddr!=0, "RATBase test");
        __ASSERT(gAddrTranslateConfig.regionConfig!=NULL, "Region test");
    
        /* enable regions setup by user */
        address_trans_setRegion(
            gAddrTranslateConfig.ratBaseAddr,
            i,
            gAddrTranslateConfig.regionConfig[i].systemAddr,
            gAddrTranslateConfig.regionConfig[i].localAddr,
            gAddrTranslateConfig.regionConfig[i].size,
            1
            );
    }
}

void *address_trans_getLocalAddr(uint64_t systemAddr)
{
    uint32_t found, regionId;
    void *localAddr;

    __ASSERT(gAddrTranslateConfig.numRegions<address_trans_MAX_REGIONS, "getlocaladdr test");

    found = 0;
    uint32_t x = gAddrTranslateConfig.numRegions;
    for(regionId=0; regionId<gAddrTranslateConfig.numRegions; regionId++)
    {
        uint64_t startAddr, endAddr;
        uint32_t sizeMask;

        /* we assume gAddrTranslateConfig.regionConfig[] address and size is aligned */
        sizeMask = ( (uint32_t)( ((uint64_t)1 << gAddrTranslateConfig.regionConfig[regionId].size) - 1) );

        startAddr = gAddrTranslateConfig.regionConfig[regionId].systemAddr;

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
        uint32_t offset = systemAddr - gAddrTranslateConfig.regionConfig[regionId].systemAddr;

        localAddr = (void *) (gAddrTranslateConfig.regionConfig[regionId].localAddr + offset);
    }
    else
    {
        /* no mapping found, set output = input with 32b truncation */
        localAddr = (void *) systemAddr;
    }
    return localAddr;
}