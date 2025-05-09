/*
 * Signal.hpp
 *
 *  Created on: May 8, 2025
 *      Author: shaya
 */

#ifndef INC_FUNCGENERATOR_HPP_
#define INC_FUNCGENERATOR_HPP_

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
