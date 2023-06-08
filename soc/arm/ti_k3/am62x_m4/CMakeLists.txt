# Copyright (c) 2023 L Lakshmanan
#
# SPDX-License-Identifier: Apache-2.0

zephyr_sources_ifdef(soc.c)
zephyr_sources_ifdef(CONFIG_RAT_TI_K3_M4 address_trans.c)
zephyr_sources_ifdef(CONFIG_RAT_TI_K3_M4 RAT_module.c)