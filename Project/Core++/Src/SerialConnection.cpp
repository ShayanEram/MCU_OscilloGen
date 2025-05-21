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

	// Oscilloscope
	if(dataReceived[0] != 0x00 && dataReceived[3] != 0x00 && dataReceived[6] != 0x00 && dataReceived[9] != 0x00 && dataReceived[13] != 0x00)
	{
		data.stop = true;
		return data;
	}
	// Func generator
	else if (dataReceived[0] != 0x01 || dataReceived[0] != 0x02 || dataReceived[0] != 0x03 || dataReceived[0] != 0x04 || dataReceived[0] != 0x05)
	{
		_bsp.usbTransmit((uint8_t*)"Invalid data\n", 15);
		return {};
	}
	else
	{
		data.type = dataReceived[0];
		std::memcpy(&data.frequency, &dataReceived[1], sizeof(float));
		std::memcpy(&data.amplitude, &dataReceived[5], sizeof(float));
		std::memcpy(&data.offset, &dataReceived[9], sizeof(float));
		data.stop = false;
	}

	return data;
}

void SerialCtn::sendData(const std::array<float, SEND_DATA_SIZE>& data)
{
	std::array<uint8_t, SEND_DATA_SIZE_BYTES> dataToSend;
	std::memcpy(dataToSend.data(), data.data(), SEND_DATA_SIZE_BYTES);

	_bsp.usbTransmit(dataToSend.data(), SEND_DATA_SIZE_BYTES);
}

