#include <RAT_module.h>
#include <address_trans.h>

address_trans_RegionConfig gAddrTranslateRegionConfig[ADDR_TRANSLATE_REGIONS] = 
{
    {
        .localAddr = 0x80000000u,
        .systemAddr = 0x0u,
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
void RAT_init(void)
{
    address_trans_Params address_trans_Params;

    address_trans_Params_init(&address_trans_Params);
    address_trans_Params.numRegions = ADDR_TRANSLATE_REGIONS;
    address_trans_Params.ratBaseAddr = ADDR_TRANSLATE_RAT_BASE_ADDR;
    address_trans_Params.regionConfig = &gAddrTranslateRegionConfig[0];

    address_trans_init(&address_trans_Params);
}

void RAT_deinit(void)
{

}