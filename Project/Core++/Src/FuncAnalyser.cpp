/*
 * Oscilloscope.cpp
 *
 *  Created on: May 8, 2025
 *      Author: shaya
 */

#include <FuncAnalyzer.hpp>

FuncAnalyzer::FuncAnalyzer(Bsp& bsp) : _bsp(bsp) {}

void FuncAnalyzer::startAnalysing()
{
	//_bsp.adcStart_DMA(&hadc, reinterpret_cast<uint32_t*>(adc_buffer.data()), ADC_BUF_SIZE);
}

void FuncAnalyzer::stopAnalyzing()
{
	//_bsp.adcStopDMA(hadc);
}

float32_t FuncAnalyzer::measurePeakVoltage() {
	int16_t signed_buffer[ADC_BUF_SIZE];  // Create signed buffer

	// Convert uint16_t ADC data to q15_t signed format
	for (size_t i = 0; i < ADC_BUF_SIZE; i++) {
	    signed_buffer[i] = static_cast<int16_t>(adc_buffer[i] - 2048);  // Convert to signed range
	}

	q15_t maxVal;
	arm_max_q15(signed_buffer, ADC_BUF_SIZE, &maxVal, NULL);

    return (maxVal * 3.3f) / 4096.0f;
}

float32_t FuncAnalyzer::measureRMSVoltage() {
    float32_t rmsValue;
    arm_rms_f32(reinterpret_cast<float32_t*>(adc_buffer.data()), ADC_BUF_SIZE, &rmsValue);
    return rmsValue * (3.3f / 4096.0f);
}

float32_t FuncAnalyzer::measureDutyCycle() {
    uint32_t risingEdge, fallingEdge;
    arm_max_q15(reinterpret_cast<int16_t*>(adc_buffer.data()), ADC_BUF_SIZE, NULL, &risingEdge);
    arm_min_q15(reinterpret_cast<int16_t*>(adc_buffer.data()), ADC_BUF_SIZE, NULL, &fallingEdge);
    return ((float)risingEdge / (risingEdge + fallingEdge)) * 100.0f;
}

void FuncAnalyzer::computeFFT(float32_t* fftOutput) {
    arm_rfft_fast_instance_f32 fftInstance;
    arm_rfft_fast_init_f32(&fftInstance, ADC_BUF_SIZE);
    arm_rfft_fast_f32(&fftInstance, reinterpret_cast<float32_t*>(adc_buffer.data()), fftOutput, 0);
}

void FuncAnalyzer::applyLowPassFilter(float32_t* output) {
    arm_biquad_cascade_df2T_instance_f32 filter;
    float32_t coeffs[5] = {0.2929, 0.5858, 0.2929, -0.0000, -0.1716};
    float32_t state[4] = {0};

    arm_biquad_cascade_df2T_init_f32(&filter, 1, coeffs, state);
    arm_biquad_cascade_df2T_f32(&filter, reinterpret_cast<float32_t*>(adc_buffer.data()), output, ADC_BUF_SIZE);
}

float32_t FuncAnalyzer::findMaxPeak() {
    float32_t maxPeak;
    arm_max_f32(reinterpret_cast<float32_t*>(adc_buffer.data()), ADC_BUF_SIZE, &maxPeak, NULL);
    return maxPeak;
}


