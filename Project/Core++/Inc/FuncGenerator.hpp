/*
 * Signal.hpp
 *
 *  Created on: May 8, 2025
 *      Author: shaya
 */

#ifndef INC_FUNCGENERATOR_HPP_
#define INC_FUNCGENERATOR_HPP_

#include <arm_math.h>
#define ARM_MATH_CM7


class Signal final {
public:
	explicit Signal() = default;
	~Signal()= default;

	void calculateSine();
	void calculateSquare();
	void calculateSaw();
	void calculateTriangle();

};

#endif /* INC_FUNCGENERATOR_HPP_ */
