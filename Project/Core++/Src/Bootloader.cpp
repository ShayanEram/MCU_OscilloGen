/*
 * Bootloader.cpp
 *
 *  Created on: May 8, 2025
 *      Author: shaya
 */

#include "Bootloader.hpp"

Bootloader::Bootloader(UART_HandleTypeDef& huart) : _huart(huart) {}

void Bootloader::run() {
    // TODO: Implement bootloader logic
}

void Bootloader::receiveFirmware() {
    // TODO: Implement firmware reception via UART
}

void Bootloader::eraseFlash() {
    // TODO: Implement Flash erase operation
}

void Bootloader::writeFlash(uint32_t address, uint8_t* data, uint32_t size) {
    // TODO: Implement Flash writing logic
}

void Bootloader::jumpToApplication() {
    // TODO: Implement application jump logic
}


