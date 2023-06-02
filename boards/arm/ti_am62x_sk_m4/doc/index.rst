.. _ti_am62x_sk_m4:

AM62x-SK M4F Core
#################

Overview
********

The AM62x-SK board configuration is used by Zephyr applications that run on
the TI AM62x platform. The board configuration provides support for the ARM
Cortex-M4F MCU core and the following features:

- Nested Vector Interrupt Controller (NVIC)
- System Tick System Clock (SYSTICK)

The board configuration also enables support for the semihosting debugging console.

See the `TI AM62X Product Page`_ for details.

Hardware
********
The AM62x SoC has one MCU domain and the following listed hardware specifications:

- Low-power ARM Cortex-M4F
- Memory

   - 256KB of SRAM

- Debug

   - XDS110 based JTAG

Supported Features
==================

The ti_am62x_sk_m4 configuration supports the following hardware features:

+-----------+------------+-------------------------------------+
| Interface | Controller | Driver/Component                    |
+===========+============+=====================================+
| NVIC      | on-chip    | nested vector interrupt controller  |
+-----------+------------+-------------------------------------+
| SYSTICK   | on-chip    | systick                             |
+-----------+------------+-------------------------------------+

Other hardware features are not currently supported by the port.

The default configuration can be found in the defconfig file:

.. code-block:: console

   boards/arm/ti_am62x_sk_m4/ti_am62x_sk_m4_defconfig


References
**********

.. _TI AM62X Product Page:
   https://www.ti.com/product/AM625


.. _AM62x SK EVM TRM:
   https://www.ti.com/lit/ug/spruiv7/spruiv7.pdf

.. _UniFlash:
   http://processors.wiki.ti.com/index.php/UniFlash_v4_Quick_Guide#Command_Line_Interface

.. _CCS IDE:
   http://www.ti.com/tool/ccstudio

.. _CCS Debug Handbook:
   http://processors.wiki.ti.com/index.php/Debug_Handbook_for_CCS#Cortex_M3.2FM4.2FTiva.2FMSP432

.. _GCC ARM Toolchain Guide:
   http://www.ti.com/lit/ug/slau688b/slau688b.pd
