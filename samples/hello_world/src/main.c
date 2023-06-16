/*
 * Copyright (c) 2012-2014 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>

typedef struct {
    volatile uint32_t DLL;
    volatile uint32_t DLH;
    volatile uint32_t EFR;
    volatile uint32_t LCR;
    volatile uint32_t XON1_ADDR1;
    volatile uint32_t XON2_ADDR2;
    volatile uint32_t TCR;
    volatile uint32_t TLR;
    volatile uint32_t MDR1;
    volatile uint32_t MDR2;
    volatile uint32_t TXFLL;
    volatile uint32_t TXFLH;
    volatile uint32_t RXFLL;
    volatile uint32_t RXFLH;
    volatile uint32_t UASR;
    volatile uint32_t ACREG;
    volatile uint32_t SCR;
    volatile uint32_t SSR;
    volatile uint32_t EBLR;
    volatile uint8_t  RSVD0[4];
    volatile uint32_t MVR;
    volatile uint32_t SYSC;
    volatile uint32_t SYSS;
    volatile uint32_t WER;
    volatile uint32_t CFPS;
    volatile uint32_t RXFIFO_LVL;
    volatile uint32_t TXFIFO_LVL;
    volatile uint32_t IER2;
    volatile uint32_t ISR2;
    volatile uint32_t FREQ_SEL;
    volatile uint32_t ABAUD_1ST_CHAR;
    volatile uint32_t BAUD_2ND_CHAR;
    volatile uint32_t MDR3;
    volatile uint32_t TX_DMA_THRESHOLD;
} CSL_UartRegs;

CSL_UartRegs *UARTreg;

int main(void)
{
	UARTreg = (CSL_UartRegs *)0x84a00000;
	printk("Hello World! %s\n", CONFIG_BOARD);
	return 0;
}
