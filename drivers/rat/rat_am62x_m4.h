#ifndef ZEPHYR_INCLUDE_RAT_TI_AM62X_M4_H_
#define ZEPHYR_INCLUDE_RAT_TI_AM62X_M4_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <address_trans.h>

void *rat_get_local_addr(uint64_t systemAddr);

#ifdef __cplusplus
}
#endif

#endif