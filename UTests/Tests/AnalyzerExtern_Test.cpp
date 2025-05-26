#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "AnalyzerExtern.hpp"

// Mock class for Bsp
class MockBsp : public Bsp {
public:
    MOCK_METHOD(void, uartTransmit_DMA, (UART_HandleTypeDef* huart, uint8_t* data, uint16_t size), (override));
    MOCK_METHOD(void, uartReceive_DMA, (UART_HandleTypeDef* huart, uint8_t* data, uint16_t size), (override));
};

// Test fixture for AnalyzerExt
class AnalyzerExtTest : public ::testing::Test {
protected:
    MockBsp mockBsp;
    AnalyzerExt analyzer{mockBsp};
    UART_HandleTypeDef huart2;
};

// Test sendCommand
TEST_F(AnalyzerExtTest, SendCommand) {
    uint8_t command = 0xA5;
    EXPECT_CALL(mockBsp, uartTransmit_DMA(&huart2, &command, 1)).Times(1);
    analyzer.sendCommand(command);
}

// Test receiveData
TEST_F(AnalyzerExtTest, ReceiveData) {
    uint8_t expectedData = 0x5A;
    EXPECT_CALL(mockBsp, uartReceive_DMA(&huart2, testing::_, 1))
        .WillOnce([&](UART_HandleTypeDef*, uint8_t* data, uint16_t) {
            *data = expectedData;
        });

    uint8_t receivedData = analyzer.receiveData();
    EXPECT_EQ(receivedData, expectedData);
}

// Test requestFFT
TEST_F(AnalyzerExtTest, RequestFFT) {
    uint8_t expectedResponse = 0x01;
    EXPECT_CALL(mockBsp, uartTransmit_DMA(&huart2, testing::_, 1))
        .WillOnce([&](UART_HandleTypeDef*, uint8_t* data, uint16_t) {
            EXPECT_EQ(*data, CMD_FFT);
        });
    EXPECT_CALL(mockBsp, uartReceive_DMA(&huart2, testing::_, 1))
        .WillOnce([&](UART_HandleTypeDef*, uint8_t* data, uint16_t) {
            *data = expectedResponse;
        });

    uint8_t response = analyzer.requestFFT();
    EXPECT_EQ(response, expectedResponse);
}

// Test requestFiltering
TEST_F(AnalyzerExtTest, RequestFiltering) {
    uint8_t expectedResponse = 0x02;
    EXPECT_CALL(mockBsp, uartTransmit_DMA(&huart2, testing::_, 1))
        .WillOnce([&](UART_HandleTypeDef*, uint8_t* data, uint16_t) {
            EXPECT_EQ(*data, CMD_FILTER);
        });
    EXPECT_CALL(mockBsp, uartReceive_DMA(&huart2, testing::_, 1))
        .WillOnce([&](UART_HandleTypeDef*, uint8_t* data, uint16_t) {
            *data = expectedResponse;
        });

    uint8_t response = analyzer.requestFiltering();
    EXPECT_EQ(response, expectedResponse);
}