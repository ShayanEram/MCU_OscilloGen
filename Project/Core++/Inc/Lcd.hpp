/*
 * Lcd.hpp
 *
 *  Created on: May 8, 2025
 *      Author: shaya
 */

#ifndef INC_LCD_HPP_
#define INC_LCD_HPP_

#include "BspStm.hpp"
#include <array>

constexpr int16_t SLAVE_ADDRESS = 0x4E;


class Lcd final
{
public:
	explicit Lcd() = default;
	~Lcd() = default;

	void LcdSendCmd(char cmd);
	void LcdSendData(char data);
	void LcdClear();
	void LcdPutCur(int row, int col);

private:
	char dataU;
	char dataL;
	std::array<uint8_t, 4> dataToSend;

};





#endif /* INC_LCD_HPP_ */
