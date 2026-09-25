/*
 * Copyright (C) 2015 Hardkernel Co,. Ltd
 * Dongjin Kim <tobetter@gmail.com>
 *
 *  This driver has been modified to support ODROID-N2.
 *      Modified by Joy Cho <joy.cho@hardkernel.com>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <common.h>
#include <command.h>
#include <asm/errno.h>
#include <vsprintf.h>
#include <linux/kernel.h>
#include <asm-generic/gpio.h>
#include <../odroid-common/odroid-common.h>

#include "recovery.h"

int boot_device(void)
{
	int dev = get_boot_device();

	if (dev == BOOT_DEVICE_EMMC)
		return 0;
	else if (dev == BOOT_DEVICE_SD)
		return 1;

	return -1;
}

void check_hotkey(void)
{
	// No support for auto-test / recovery boot via hotkey
	setenv("bootmode", "normal");
}


int board_check_recovery(void)
{
	int dev = boot_device();
	int boot_mode = 0;

	if(dev) {
		if (board_check_recovery_image() == 0) {
			run_command("mmc dev 0", 0);
			setenv("bootmode", "recovery");
			printf("bootmode : uSD image is recovery_image \n");
			goto recovery;
		}
	}
	boot_mode = get_bootmode();
	
	if (boot_mode != BOOTMODE_NORMAL) {
		if (board_check_odroidbios(dev) == 0) {
			/* TODO: WHY?
			 * eMMC must be initiated once, otherwise SPI flash memory cannot be
			 * accessible in the Linux kernel.
			 */
			run_command("mmc dev 0", 0);
		} else return -1;
	}
recovery:
	return 0;
}

int get_bootmode(void)
{
	int ret = 0;
	char *pmode = getenv("bootmode");
	
	if (!strcmp("normal", pmode)) ret = BOOTMODE_NORMAL;
	else if (!strcmp("test", pmode)) ret = BOOTMODE_TEST;
	else if (!strcmp("recovery", pmode)) ret = BOOTMODE_RECOVERY;
	else ret = BOOTMODE_NORMAL;

	return ret;
}

