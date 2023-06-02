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

Flashing
********

The board cannot be booted using remoteproc, and all tests have been done by flashing the code using CCS.

The testing requires the SOC initialisation binary to be flashed and CCS to be set up with the UART terminal. Refer to `EVM Setup Page`_ and the `CCS Setup Page`_ for details regarding this.

To test the semihosting console with the M4F core, we build the `hello_world` sample with the following command.

.. code-block:: console

   # From the root of the Zephyr repository
   west build -p -b ti_am62x_sk_m4 samples/hello_world

This builds the program and the binary is present in the `build/zephyr` directory as `zephyr.elf`.

Connect to the Cortex BLAZAR_CORTEX_M4_F_1 core through CCS using the debug configurations for the AM62x with the XDS110 probes.

Proceed to load the binary to the core after a CPU reset and run the program.

References
**********

.. _TI AM62X Product Page:
   https://www.ti.com/product/AM625

.. _AM62x SK EVM TRM:
   https://www.ti.com/lit/ug/spruiv7/spruiv7.pdf

.. _EVM Setup Page:
   https://software-dl.ti.com/mcu-plus-sdk/esd/AM62X/08_06_00_18/exports/docs/api_guide_am62x/EVM_SETUP_PAGE.html

.. _CCS Setup Page:
   https://software-dl.ti.com/mcu-plus-sdk/esd/AM62X/08_06_00_18/exports/docs/api_guide_am62x/CCS_SETUP_PAGE.html

.. _CCS IDE:
   http://www.ti.com/tool/ccstudio

.. _CCS Debug Handbook:
   http://processors.wiki.ti.com/index.php/Debug_Handbook_for_CCS#Cortex_M3.2FM4.2FTiva.2FMSP432
