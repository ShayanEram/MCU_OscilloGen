/*
 * Signal.hpp
 *
 *  Created on: May 8, 2025
 *      Author: shaya
 */

#ifndef INC_FUNCGENERATOR_HPP_
#define INC_FUNCGENERATOR_HPP_

#include <array>
#include <arm_math.h>
#define ARM_MATH_CM7

constexpr uint8_t DMA_BUFFER_SIZE = 32;
constexpr uint16_t SAMPLE_FREQ = 1000;
constexpr uint16_t MID_POINT = 2048;

class Signal final {
public:
	explicit Signal() = default;
	~Signal()= default;

	void calculateSine();
	void calculateSquare();
	void calculateSaw();
	void calculateTriangle();

private:
	std::array<uint16_t, 2*DMA_BUFFER_SIZE>dmaBuffer;

};

#endif /* INC_FUNCGENERATOR_HPP_ */
