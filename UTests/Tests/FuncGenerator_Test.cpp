#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "FuncGenerator.hpp"

// Mock class for Bsp
class MockBsp : public Bsp {
public:
    MOCK_METHOD(uint32_t, HAL_RCC_GetPCLK1Freq, (), (override));
    MOCK_METHOD(void, __HAL_TIM_SET_AUTORELOAD, (TIM_HandleTypeDef* htim, uint32_t value), (override));
};

// Test fixture for FuncGenerator
class FuncGeneratorTest : public ::testing::Test {
protected:
    MockBsp mockBsp;
    FuncGenerator funcGenerator{mockBsp};
};

// Test generateWaveforms
TEST_F(FuncGeneratorTest, GenerateWaveforms) {
    funcGenerator.generateWaveforms();

    // Verify sine wave
    for (int i = 0; i < SAMPLE_COUNT; i++) {
        float angle = 2.0f * PI * i / SAMPLE_COUNT;
        uint16_t expectedValue = static_cast<uint16_t>(MAX_AMPLITUDE * (0.5f + 0.5f * arm_sin_f32(angle)));
        EXPECT_EQ(funcGenerator.sineWave[i], expectedValue);
    }

    // Verify square wave
    for (int i = 0; i < SAMPLE_COUNT; i++) {
        uint16_t expectedValue = (i < SAMPLE_COUNT / 2) ? MAX_AMPLITUDE : 0;
        EXPECT_EQ(funcGenerator.squareWave[i], expectedValue);
    }

    // Verify triangle wave
    for (int i = 0; i < SAMPLE_COUNT; i++) {
        uint16_t expectedValue = static_cast<uint16_t>(MAX_AMPLITUDE * fabs((2.0f * i / SAMPLE_COUNT) - 1.0f));
        EXPECT_EQ(funcGenerator.triangleWave[i], expectedValue);
    }

    // Verify sawtooth wave
    for (int i = 0; i < SAMPLE_COUNT; i++) {
        uint16_t expectedValue = static_cast<uint16_t>(MAX_AMPLITUDE * (i / static_cast<float>(SAMPLE_COUNT)));
        EXPECT_EQ(funcGenerator.sawtoothWave[i], expectedValue);
    }
}

// Test setFrequency
TEST_F(FuncGeneratorTest, SetFrequency) {
    uint32_t frequency = 1000;
    uint32_t pclk1Freq = 80000000; // Example PCLK1 frequency
    EXPECT_CALL(mockBsp, HAL_RCC_GetPCLK1Freq()).WillOnce(::testing::Return(pclk1Freq));
    EXPECT_CALL(mockBsp, __HAL_TIM_SET_AUTORELOAD(&htim1, ::testing::_))
        .WillOnce([](TIM_HandleTypeDef*, uint32_t value) {
            EXPECT_EQ(value, pclk1Freq / (frequency * SAMPLE_COUNT));
        });

    funcGenerator.setFrequency(frequency);
}

// Test setAmplitude
TEST_F(FuncGeneratorTest, SetAmplitude) {
    float amplitude = 0.5f;

    // Mock the updateWaveform function
    EXPECT_CALL(mockBsp, __HAL_TIM_SET_AUTORELOAD).Times(4);

    funcGenerator.setAmplitude(amplitude);

    // Verify that waveforms are updated correctly
    for (int i = 0; i < SAMPLE_COUNT; i++) {
        EXPECT_NEAR(funcGenerator.sineWave[i], amplitude * funcGenerator.sineWave[i], 0.01f);
        EXPECT_NEAR(funcGenerator.squareWave[i], amplitude * funcGenerator.squareWave[i], 0.01f);
        EXPECT_NEAR(funcGenerator.triangleWave[i], amplitude * funcGenerator.triangleWave[i], 0.01f);
        EXPECT_NEAR(funcGenerator.sawtoothWave[i], amplitude * funcGenerator.sawtoothWave[i], 0.01f);
    }
}