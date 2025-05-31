/**
 * @file SerialConnection.hpp
 * @brief Declaration of the SerialCtn class for serial communication.
 * This class provides methods to handle serial communication with a device, including sending and receiving data, processing received data, and managing different modes of operation.
 * It uses the USB and defines structures for function generation and oscilloscopes.
 */
#ifndef INC_SERIALCONNECTION_HPP_
#define INC_SERIALCONNECTION_HPP_

#include "Bsp.hpp"
#include <cstring>
#include <array>

using UsbArray = std::array<uint8_t, USB_RX_BUFF_SIZE>;

enum Mode
{
	FUNCTION_GENERATOR_MODE = 0x00,
	OSCILLOSCOPE_MODE       = 0x01,
	UPDATE_MODE				= 0X02
};

enum SignalType
{
	TYPE_NOISE    = 0x00,
	TYPE_SINE     = 0x01,
	TYPE_SQUARE   = 0x02,
	TYPE_TRIANGLE = 0x03,
	TYPE_SAW      = 0x04
};

struct __attribute__((packed)) FunctionGenerator
{
	uint8_t signalType = TYPE_SINE;
	float frequency = 0.0f;
	float amplitude = 0.0f;
	float offset = 0.0f;
};

struct __attribute__((packed)) Oscilloscope
{
	bool stop = false;
	bool fft = false;
	bool filter = false;
};

struct __attribute__((packed)) ReceivedData
{
	uint8_t mode = FUNCTION_GENERATOR_MODE;
	FunctionGenerator generate;
	Oscilloscope analyze;
};

struct StatusBytes
{
	bool ready : 1;
	bool busy  : 1;
	bool fault : 1;
};

class SerialCtn
{
public:
	explicit SerialCtn (Bsp& bsp);
	~SerialCtn() = default;

	Status interfaceHandshake(uint8_t major, uint8_t minor);
	ReceivedData processReceivedData();

private:
	Bsp& _bsp;

	static constexpr uint16_t SEND_DATA_SIZE = 256;
	static constexpr uint16_t SEND_DATA_SIZE_BYTES = 1024;

	void sendData(const std::array<float, SEND_DATA_SIZE>& data);
	UsbArray receiveData();
};

#endif /* INC_SERIALCONNECTION_HPP_ */
