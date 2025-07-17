#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "DacExtern.hpp"

// Mock class for Bsp
class MockBsp : public Bsp {
public:
    MOCK_METHOD(Status, spiTransmit_IT, (SPI_HandleTypeDef* hspi, uint8_t* data, uint16_t size), (override));
    MOCK_METHOD(Status, spiReceive_IT, (SPI_HandleTypeDef* hspi, uint8_t* data, uint16_t size), (override));
};

// Test fixture for Dac
class DacTest : public ::testing::Test {
protected:
    MockBsp mockBsp;
    Dac dac{mockBsp};
    SPI_HandleTypeDef hspi1;
};

// Test sendDataSPI
TEST_F(DacTest, SendDataSPI_Success) {
    uint32_t data = 0x12345678;
    EXPECT_CALL(mockBsp, spiTransmit_IT(&hspi1, reinterpret_cast<uint8_t*>(&data), 1))
        .WillOnce(::testing::Return(Status::OK));

    EXPECT_EQ(dac.sendDataSPI(data), Status::OK);
}

TEST_F(DacTest, SendDataSPI_Error) {
    uint32_t data = 0x12345678;
    EXPECT_CALL(mockBsp, spiTransmit_IT(&hspi1, reinterpret_cast<uint8_t*>(&data), 1))
        .WillOnce(::testing::Return(Status::ERROR));

    EXPECT_EQ(dac.sendDataSPI(data), Status::ERROR);
}

// Test receiveStatusSPI
TEST_F(DacTest, ReceiveStatusSPI) {
    uint8_t expectedData = 0xAB;
    EXPECT_CALL(mockBsp, spiReceive_IT(&hspi1, ::testing::_, 1))
        .WillOnce([&](SPI_HandleTypeDef*, uint8_t* data, uint16_t) {
            *data = expectedData;
            return Status::OK;
        });

    uint8_t receivedData = dac.receiveStatusSPI();
    EXPECT_EQ(receivedData, expectedData);
}

// Test voltageToCode
TEST_F(DacTest, VoltageToCode_WithinRange) {
    float voltage = 2.5f;
    float min_voltage = 0.0f;
    float max_voltage = 5.0f;

    uint16_t code = dac.voltageToCode(voltage, min_voltage, max_voltage);
    EXPECT_EQ(code, 32767); // 2.5V is halfway in the range, so the code should be 32767.
}

TEST_F(DacTest, VoltageToCode_AboveRange) {
    float voltage = 6.0f;
    float min_voltage = 0.0f;
    float max_voltage = 5.0f;

    uint16_t code = dac.voltageToCode(voltage, min_voltage, max_voltage);
    EXPECT_EQ(code, 65535); // Voltage above max should be clamped to max.
}

TEST_F(DacTest, VoltageToCode_BelowRange) {
    float voltage = -1.0f;
    float min_voltage = 0.0f;
    float max_voltage = 5.0f;

    uint16_t code = dac.voltageToCode(voltage, min_voltage, max_voltage);
    EXPECT_EQ(code, 0); // Voltage below min should be clamped to min.
}