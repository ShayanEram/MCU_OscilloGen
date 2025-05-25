/*
 * Oscilloscope.hpp
 *
 *  Created on: May 8, 2025
 *      Author: shaya
 */

#ifndef INC_FUNCANALYZER_HPP_
#define INC_FUNCANALYZER_HPP_

#include "Bsp.hpp"
#include "arm_math.h"
#include <array>


class FuncAnalyzer final {
public:
	explicit FuncAnalyzer (Bsp& bsp);
	~FuncAnalyzer() = default;

	void startAnalysing();
	void stopAnalyzing();
    float32_t measurePeakVoltage();
    float32_t measureRMSVoltage();
    float32_t measureDutyCycle();
    void computeFFT(float32_t* fftOutput);
    void applyLowPassFilter(float32_t* output);
    float32_t findMaxPeak();

private:
	Bsp& _bsp;
	static constexpr uint16_t ADC_BUF_SIZE = 4096;
	std::array<uint16_t, ADC_BUF_SIZE>adc_buffer;
};

#endif /* INC_FUNCANALYZER_HPP_ */
