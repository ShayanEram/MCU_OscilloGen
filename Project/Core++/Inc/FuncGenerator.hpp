/**
 * @file FuncGenerator.hpp
 * @brief Declaration of the FuncGenerator class for function generation.
 * This class provides methods to generate various waveforms (sine, square, triangle, sawtooth), set frequency and amplitude, and manage waveform output.
 * It uses the Bsp class for hardware interaction and ARM CMSIS DSP library for signal processing.
 * 
 * @author Shayan Eram
 */
#ifndef INC_FUNCGENERATOR_HPP_
#define INC_FUNCGENERATOR_HPP_

#include "Bsp.hpp"
#include <array>
#include <arm_math.h>

class FuncGenerator final {
public:
	explicit FuncGenerator(Bsp& bsp);
	~FuncGenerator()= default;

	enum WaveType { SINE, SQUARE, TRIANGLE, SAWTOOTH };

	void generateWaveforms();
	void setFrequency(uint32_t frequency);
	void setAmplitude(float amplitude);
	void selectWaveform(uint8_t type);
	void startWaveformOutput();
	void stopWaveformOutput();
	std::array<int32_t,128> generateWaveformCordic(const std::array<int32_t,128>& inputBuffer);

private:
	Bsp& _bsp;

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

    uint8_t currentWaveform = SINE;
    uint16_t* activeWaveform = nullptr;

    void updateWaveform(uint16_t* waveform, float amplitude);


};

#endif /* INC_FUNCGENERATOR_HPP_ */
