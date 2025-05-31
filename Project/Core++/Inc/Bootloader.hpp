/**
 * @file Bootloader.hpp
 * @brief Declaration of the Bootloader class for firmware management.
 * This class provides methods to run the bootloader, receive firmware, erase flash memory, write to flash, and jump to the application.
 * 
 * @author Shayan Eram
 */
#ifndef INC_BOOTLOADER_HPP_
#define INC_BOOTLOADER_HPP_

#include "Bsp.hpp"

class Bootloader final {
public:
    explicit Bootloader(UART_HandleTypeDef& huart);
    ~Bootloader() = default;

    void run();
    void receiveFirmware();
    void eraseFlash();
    void writeFlash(uint32_t address, uint8_t* data, uint32_t size);
    void jumpToApplication();

private:
    UART_HandleTypeDef& _huart;
    static constexpr uint32_t APP_ADDRESS = 0x08008000;
};



#endif /* INC_BOOTLOADER_HPP_ */
