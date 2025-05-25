/*
 * SerialConnection.cpp
 *
 *  Created on: May 8, 2025
 *      Author: shaya
 */
#include "SerialConnection.hpp"
#include <algorithm>


uint8_t UsbRxDataBuffer[USB_RX_BUFF_SIZE];

SerialCtn::SerialCtn(Bsp& bsp): _bsp(bsp){}

Status SerialCtn::interfaceHandshake(uint8_t major, uint8_t minor)
{
	char versionStr[18];
	snprintf(versionStr, sizeof(versionStr), "Version: %d.%d", major, minor);
	_bsp.usbTransmit(reinterpret_cast<uint8_t*>(versionStr), strlen(versionStr));

	UsbArray dataReceived = receiveData();

	if(dataReceived[0] != 0xFF && dataReceived[1] != 0xAA && dataReceived[2] != 0xFF)
		return Status::ERROR;

	return Status::OK;
}

UsbArray SerialCtn::receiveData()
{
	// C array into C++ array!
	UsbArray dataReceived = {};
	std::copy(std::begin(UsbRxDataBuffer), std::end(UsbRxDataBuffer), dataReceived.begin());
	return dataReceived;
}

ReceivedData SerialCtn::processReceivedData()
{
	ReceivedData data = {};
	UsbArray dataReceived = receiveData();

	if(dataReceived[0] == 0xAA && dataReceived[1] == 0xFF) // Function generator command
	{
		data.generate.signalType = dataReceived[2];
		std::memcpy(&data.generate.frequency, &dataReceived[3], sizeof(float));
		std::memcpy(&data.generate.amplitude, &dataReceived[7], sizeof(float));
		std::memcpy(&data.generate.offset, &dataReceived[11], sizeof(float));
	}
	else if(dataReceived[0] == 0xFF && dataReceived[1] == 0xC3) // Oscilloscope command
	{
		data.analyze.stop = std::all_of(dataReceived.begin() + 2, dataReceived.end(), [](uint8_t byte) { return byte == 0; });

		if(!data.analyze.stop)
		{
			data.analyze.fft = dataReceived[2];
			data.analyze.filter = dataReceived[3];
		}
	}
	else // Invalid command
	{
		printf("DEV_ERROR: Invalide command was received");
		return {};
	}

	return data;
}

void SerialCtn::sendData(const std::array<float, SEND_DATA_SIZE>& data)
{
	std::array<uint8_t, SEND_DATA_SIZE_BYTES> dataToSend;
	std::memcpy(dataToSend.data(), data.data(), SEND_DATA_SIZE_BYTES);

	_bsp.usbTransmit(dataToSend.data(), SEND_DATA_SIZE_BYTES);
}

