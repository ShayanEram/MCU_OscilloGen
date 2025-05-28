/*
 * Signal.cpp
 *
 *  Created on: May 8, 2025
 *      Author: shaya
 */

#include <FuncGenerator.hpp>

FuncGenerator::FuncGenerator(Bsp& bsp) : _bsp(bsp)
{
	generateWaveforms();
	activeWaveform = sineWave.data();
}

void FuncGenerator::generateWaveforms()
{
    for (int i = 0; i < SAMPLE_COUNT; i++) {
        float angle = 2.0f * PI * i / SAMPLE_COUNT;

        // Generate Sine Wave
        sineWave[i] = static_cast<uint16_t>(MAX_AMPLITUDE * (0.5f + 0.5f * arm_sin_f32(angle)));

        // Generate Square Wave
        squareWave[i] = (i < SAMPLE_COUNT / 2) ? MAX_AMPLITUDE : 0;

        // Generate Triangle Wave
        triangleWave[i] = static_cast<uint16_t>(MAX_AMPLITUDE * fabs((2.0f * i / SAMPLE_COUNT) - 1.0f));

        // Generate Sawtooth Wave
        sawtoothWave[i] = static_cast<uint16_t>(MAX_AMPLITUDE * (i / static_cast<float>(SAMPLE_COUNT)));
    }
}

void FuncGenerator::setFrequency(uint32_t frequency)
{
    uint32_t timerPeriod = HAL_RCC_GetPCLK1Freq() / (frequency * SAMPLE_COUNT);
    __HAL_TIM_SET_AUTORELOAD(&htim1, timerPeriod);
}

void FuncGenerator::setAmplitude(float amplitude)
{
    updateWaveform(sineWave.data(), amplitude);
    updateWaveform(squareWave.data(), amplitude);
    updateWaveform(triangleWave.data(), amplitude);
    updateWaveform(sawtoothWave.data(), amplitude);
}

void FuncGenerator::updateWaveform(uint16_t* waveform, float amplitude)
{
    for (int i = 0; i < SAMPLE_COUNT; i++) {
        waveform[i] = static_cast<uint16_t>(MAX_AMPLITUDE * amplitude * waveform[i] / MAX_AMPLITUDE);
    }
}

void FuncGenerator::selectWaveform(uint8_t type)
{
    currentWaveform = type;
    switch (type) {
        case SINE:
            activeWaveform = sineWave.data();
            break;
        case SQUARE:
            activeWaveform = squareWave.data();
            break;
        case TRIANGLE:
            activeWaveform = triangleWave.data();
            break;
        case SAWTOOTH:
            activeWaveform = sawtoothWave.data();
            break;
    }
}

void FuncGenerator::startWaveformOutput()
{
    _bsp.dacStart_DMA(reinterpret_cast<uint32_t*>(activeWaveform), SAMPLE_COUNT);
}

void FuncGenerator::stopWaveformOutput()
{
    _bsp.dacStopDMA();
}

std::array<int32_t,128> FuncGenerator::generateWaveformCordic(const std::array<int32_t,128>& inputBuffer)
{
	std::array<int32_t, 128> outputBuffer;
	_bsp.cordicCalculate_DMA(inputBuffer.data(), outputBuffer.data(), 128);
	return outputBuffer;
}


