/**
 * @file Lcd.hpp
 * @brief Declaration of the Lcd class for LCD operations.
 * This class provides methods to initialize the LCD, clear the display, set the cursor position, and send strings or characters to the LCD.
 * It communicates with the LCD via I2C and supports multiple lines.
 * 
 * @author Shayan Eram
 */
#ifndef INC_LCD_HPP_
#define INC_LCD_HPP_

#include "Bsp.hpp"
#include <array>

constexpr int16_t SLAVE_ADDRESS = 0x4E;

class Lcd final {
public:
	explicit Lcd(Bsp& bsp, uint8_t address);
	~Lcd() = default;

    void init();
    void clear();
    void setCursor(int col, int row);
    void sendString(const char* str);
    void sendChar(char ch);

private:
    Bsp& _bsp;

	static constexpr uint8_t LCD_CMD_FUNCTION_SET = 0x28;
	static constexpr uint8_t LCD_CMD_DISPLAY_OFF = 0x08;
	static constexpr uint8_t LCD_CMD_CLEAR_DISPLAY = 0x01;
	static constexpr uint8_t LCD_CMD_ENTRY_MODE_SET = 0x06;
	static constexpr uint8_t LCD_CMD_DISPLAY_ON = 0x0C;
	static constexpr uint8_t LCD_CMD_HOME = 0x80;

	static constexpr uint8_t LCD_LINE_1 = 0x80;
	static constexpr uint8_t LCD_LINE_2 = 0xC0;
	static constexpr uint8_t LCD_LINE_3 = 0x94;
	static constexpr uint8_t LCD_LINE_4 = 0xD4;

	static constexpr uint8_t LCD_ENABLE_BIT = 0x04;
	static constexpr uint8_t LCD_RS_COMMAND = 0x00;
	static constexpr uint8_t LCD_RS_DATA = 0x01;

	uint8_t _address;
	void sendCommand(uint8_t cmd);
	void sendData(uint8_t data);
};





#endif /* INC_LCD_HPP_ */
