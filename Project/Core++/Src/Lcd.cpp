/*
 * Lcd.cpp
 *
 *  Created on: May 8, 2025
 *      Author: shaya
 */

#include "Lcd.hpp"


Lcd::Lcd(Bsp& bsp, uint8_t address) : _bsp(bsp), _address(address) {}

void Lcd::sendCommand(uint8_t cmd) {
    uint8_t upperNibble = cmd & 0xF0;
    uint8_t lowerNibble = (cmd << 4) & 0xF0;

    uint8_t dataT[4] = {
        upperNibble | LCD_ENABLE_BIT | LCD_RS_COMMAND,
        upperNibble | LCD_RS_COMMAND,
        lowerNibble | LCD_ENABLE_BIT | LCD_RS_COMMAND,
        lowerNibble | LCD_RS_COMMAND
    };

    //_bsp.i2cTransmit_Master_IT(hi2c, _address, dataT, 4);
}

void Lcd::sendData(uint8_t data) {
    uint8_t upperNibble = data & 0xF0;
    uint8_t lowerNibble = (data << 4) & 0xF0;

    uint8_t dataT[4] = {
        upperNibble | LCD_ENABLE_BIT | LCD_RS_DATA,
        upperNibble | LCD_RS_DATA,
        lowerNibble | LCD_ENABLE_BIT | LCD_RS_DATA,
        lowerNibble | LCD_RS_DATA
    };

    //_bsp.i2cTransmit_Master_IT(hi2c, _address, dataT, 4);
}

void Lcd::init() {
    HAL_Delay(50);
    sendCommand(0x30);
    HAL_Delay(5);
    sendCommand(0x30);
    HAL_Delay(1);
    sendCommand(0x30);
    HAL_Delay(10);
    sendCommand(0x20);
    HAL_Delay(10);

    sendCommand(LCD_CMD_FUNCTION_SET);
    sendCommand(LCD_CMD_DISPLAY_OFF);
    sendCommand(LCD_CMD_CLEAR_DISPLAY);
    HAL_Delay(2);
    sendCommand(LCD_CMD_ENTRY_MODE_SET);
    sendCommand(LCD_CMD_DISPLAY_ON);
}

void Lcd::clear() {
    setCursor(0, 0);
    for (int i = 0; i < 80; i++) sendData(' ');
}

void Lcd::setCursor(int col, int row) {
    uint8_t address;
    switch (row) {
        case 0: address = LCD_LINE_1 + col; break;
        case 1: address = LCD_LINE_2 + col; break;
        case 2: address = LCD_LINE_3 + col; break;
        case 3: address = LCD_LINE_4 + col; break;
        default: return;
    }
    sendCommand(address);
}

void Lcd::sendString(const char* str) {
    while (*str) sendData(*str++);
}

void Lcd::sendChar(char ch) {
    sendData(ch);
}


