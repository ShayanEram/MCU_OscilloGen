/**
 * @file FuncAnalyzer.hpp
 * @brief Declaration of the FuncAnalyzer class for function analysis.
 * This class provides methods to analyze electrical signals, including measuring peak voltage, RMS voltage, duty cycle, performing FFT, applying low-pass filters, and finding maximum peaks.
 * It uses the Bsp class for hardware interaction and ARM CMSIS DSP library for signal processing.
 * 
 * @author Shayan Eram
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
