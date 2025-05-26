#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "SerialConnection.hpp"

// Mock class for Bsp
class MockBsp : public Bsp {
public:
    MOCK_METHOD(void, usbTransmit, (uint8_t* data, uint16_t size), (override));
};

// Test fixture for SerialCtn
class SerialCtnTest : public ::testing::Test {
protected:
    MockBsp mockBsp;
    SerialCtn serialConnection{mockBsp};
};

// Test interfaceHandshake
TEST_F(SerialCtnTest, InterfaceHandshake_Success) {
    uint8_t major = 1;
    uint8_t minor = 0;

    // Mock usbTransmit
    EXPECT_CALL(mockBsp, usbTransmit(::testing::_, ::testing::_))
        .Times(1);

    // Simulate valid handshake data in UsbRxDataBuffer
    UsbRxDataBuffer[0] = 0xFF;
    UsbRxDataBuffer[1] = 0xAA;
    UsbRxDataBuffer[2] = 0xFF;

    EXPECT_EQ(serialConnection.interfaceHandshake(major, minor), Status::OK);
}

TEST_F(SerialCtnTest, InterfaceHandshake_Error) {
    uint8_t major = 1;
    uint8_t minor = 0;

    // Mock usbTransmit
    EXPECT_CALL(mockBsp, usbTransmit(::testing::_, ::testing::_))
        .Times(1);

    // Simulate invalid handshake data in UsbRxDataBuffer
    UsbRxDataBuffer[0] = 0x00;
    UsbRxDataBuffer[1] = 0x00;
    UsbRxDataBuffer[2] = 0x00;

    EXPECT_EQ(serialConnection.interfaceHandshake(major, minor), Status::ERROR);
}

// Test receiveData
TEST_F(SerialCtnTest, ReceiveData) {
    // Simulate data in UsbRxDataBuffer
    for (size_t i = 0; i < USB_RX_BUFF_SIZE; ++i) {
        UsbRxDataBuffer[i] = static_cast<uint8_t>(i);
    }

    UsbArray receivedData = serialConnection.receiveData();

    // Verify that data was copied correctly
    for (size_t i = 0; i < USB_RX_BUFF_SIZE; ++i) {
        EXPECT_EQ(receivedData[i], static_cast<uint8_t>(i));
    }
}

// Test processReceivedData
TEST_F(SerialCtnTest, ProcessReceivedData_FunctionGeneratorCommand) {
    // Simulate function generator command in UsbRxDataBuffer
    UsbRxDataBuffer[0] = 0xAA;
    UsbRxDataBuffer[1] = 0xFF;
    UsbRxDataBuffer[2] = 0x01; // Signal type
    float frequency = 1000.0f;
    float amplitude = 1.5f;
    float offset = 0.5f;
    std::memcpy(&UsbRxDataBuffer[3], &frequency, sizeof(float));
    std::memcpy(&UsbRxDataBuffer[7], &amplitude, sizeof(float));
    std::memcpy(&UsbRxDataBuffer[11], &offset, sizeof(float));

    ReceivedData receivedData = serialConnection.processReceivedData();

    // Verify that data was processed correctly
    EXPECT_EQ(receivedData.generate.signalType, 0x01);
    EXPECT_FLOAT_EQ(receivedData.generate.frequency, frequency);
    EXPECT_FLOAT_EQ(receivedData.generate.amplitude, amplitude);
    EXPECT_FLOAT_EQ(receivedData.generate.offset, offset);
}