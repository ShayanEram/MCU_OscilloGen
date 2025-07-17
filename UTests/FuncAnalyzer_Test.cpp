#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "FuncAnalyzer.hpp"


class MockBsp : public Bsp {
public:
    MOCK_METHOD(void, adcStart_DMA, (ADC_HandleTypeDef* hadc, uint32_t* data, uint32_t size), (override));
    MOCK_METHOD(void, adcStopDMA, (ADC_HandleTypeDef* hadc), (override));
};

// Test fixture for FuncAnalyzer
class FuncAnalyzerTest : public ::testing::Test {
protected:
    MockBsp mockBsp;
    FuncAnalyzer funcAnalyzer{mockBsp};
    ADC_HandleTypeDef hadc1;
    std::array<uint16_t, ADC_BUF_SIZE> adc_buffer;
};

// Test startAnalysing
TEST_F(FuncAnalyzerTest, StartAnalysing) {
    EXPECT_CALL(mockBsp, adcStart_DMA(&hadc1, reinterpret_cast<uint32_t*>(adc_buffer.data()), ADC_BUF_SIZE)).Times(1);
    funcAnalyzer.startAnalysing();
}

// Test stopAnalyzing
TEST_F(FuncAnalyzerTest, StopAnalyzing) {
    EXPECT_CALL(mockBsp, adcStopDMA(&hadc1)).Times(1);
    funcAnalyzer.stopAnalyzing();
}

// Test measurePeakVoltage
TEST_F(FuncAnalyzerTest, MeasurePeakVoltage) {
    adc_buffer.fill(2048);  // Simulate ADC buffer with mid-range values
    funcAnalyzer.adc_buffer = adc_buffer;

    float32_t peakVoltage = funcAnalyzer.measurePeakVoltage();
    EXPECT_NEAR(peakVoltage, 0.0f, 0.01f);  // Expect near 0V since all values are mid-range
}

// Test measureRMSVoltage
TEST_F(FuncAnalyzerTest, MeasureRMSVoltage) {
    adc_buffer.fill(2048);  // Simulate ADC buffer with mid-range values
    funcAnalyzer.adc_buffer = adc_buffer;

    float32_t rmsVoltage = funcAnalyzer.measureRMSVoltage();
    EXPECT_NEAR(rmsVoltage, 0.0f, 0.01f);  // Expect near 0V since all values are mid-range
}

// Test measureDutyCycle
TEST_F(FuncAnalyzerTest, MeasureDutyCycle) {
    adc_buffer.fill(2048);  // Simulate ADC buffer with mid-range values
    funcAnalyzer.adc_buffer = adc_buffer;

    float32_t dutyCycle = funcAnalyzer.measureDutyCycle();
    EXPECT_NEAR(dutyCycle, 50.0f, 1.0f);  // Expect 50% duty cycle for mid-range values
}

// Test computeFFT
TEST_F(FuncAnalyzerTest, ComputeFFT) {
    adc_buffer.fill(2048);  // Simulate ADC buffer with mid-range values
    funcAnalyzer.adc_buffer = adc_buffer;

    float32_t fftOutput[ADC_BUF_SIZE];
    funcAnalyzer.computeFFT(fftOutput);

    // Verify FFT output (e.g., check if the first value is non-zero for DC component)
    EXPECT_NEAR(fftOutput[0], 2048.0f, 1.0f);
}