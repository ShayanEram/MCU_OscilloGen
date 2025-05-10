/*
 * Oscilloscope.hpp
 *
 *  Created on: May 8, 2025
 *      Author: shaya
 */

#ifndef INC_OSCILLOSCOPE_HPP_
#define INC_OSCILLOSCOPE_HPP_

#include "BspStm.hpp"
#include <array>

constexpr uint16_t ADC_BUF_SIZE = 4096;

class Adc final
{
public:
	explicit Adc(BspStm& bsp);
	~Adc() = default;

private:
	std::array<uint16_t, ADC_BUF_SIZE>adc_buffer;

};

#endif /* INC_OSCILLOSCOPE_HPP_ */
