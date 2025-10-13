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
    explicit Bootloader();
    ~Bootloader() = default;

    void systemResetToBootloader();
};

#endif /* INC_BOOTLOADER_HPP_ */
