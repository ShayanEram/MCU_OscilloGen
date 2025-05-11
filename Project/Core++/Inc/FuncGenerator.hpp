/*
 * Signal.hpp
 *
 *  Created on: May 8, 2025
 *      Author: shaya
 */

#ifndef INC_FUNCGENERATOR_HPP_
#define INC_FUNCGENERATOR_HPP_

#include "Bsp.hpp"
#include <array>
#include <arm_math.h>



class FuncGenerator final {
public:
	explicit FuncGenerator();
	~FuncGenerator()= default;

	enum class WaveType { SINE, SQUARE, TRIANGLE, SAWTOOTH };

	void generateWaveforms();
	void setFrequency(uint32_t frequency);
	void setAmplitude(float amplitude);
	void selectWaveform(WaveType type);
	void startWaveformOutput();

private:
	static constexpr uint16_t SAMPLE_COUNT = 128;  // Number of samples per cycle
	static constexpr uint16_t MAX_AMPLITUDE = 4095;  // 12-bit DAC max value

	static constexpr uint8_t DMA_BUFFER_SIZE = 32;
	static constexpr uint16_t SAMPLE_FREQ = 1000;
	static constexpr uint16_t MID_POINT = 2048;

	std::array<uint16_t, 2*DMA_BUFFER_SIZE>dmaBuffer;

    std::array<uint16_t, SAMPLE_COUNT> sineWave;
    std::array<uint16_t, SAMPLE_COUNT> squareWave;
    std::array<uint16_t, SAMPLE_COUNT> triangleWave;
    std::array<uint16_t, SAMPLE_COUNT> sawtoothWave;

    WaveType currentWaveform = WaveType::SINE;
    uint16_t* activeWaveform = nullptr;

    void updateWaveform(uint16_t* waveform, float amplitude);


};

#endif /* INC_FUNCGENERATOR_HPP_ */
