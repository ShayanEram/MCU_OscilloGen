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

	if(dataReceived[0] != 0xBB && dataReceived[1] != 0xCC)
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

void SerialCtn::processReceivedData()
{
	UsbArray dataReceived = receiveData();

	if (dataReceived[0] != 0xAA)
	{
		_bsp.usbTransmit((uint8_t*)"Invalid data\n", 26);
		return;
	}

	uint8_t commandId = dataReceived[1];

	switch (commandId)
	{
		case SINGAL_PARAMS_ID:
			processSignalParams();
			break;

		default:
			_bsp.usbTransmit((uint8_t*)"Invalid command.\n", 27);
			break;
	}
}
