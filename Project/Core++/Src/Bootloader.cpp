/**
 * @file Bootloader.cpp
 * @author Shayan Eram
 */
#include "Bootloader.hpp"

Bootloader::Bootloader() {}

void Bootloader::systemResetToBootloader()
{
	// Variables in main.h
	*dfu_boot_flag = DFU_BOOT_FLAG;
	HAL_NVIC_SystemReset();
}
