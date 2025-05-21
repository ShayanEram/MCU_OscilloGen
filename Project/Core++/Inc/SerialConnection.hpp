/*
 * SerialConnection.hpp
 *
 *  Created on: May 8, 2025
 *      Author: shaya
 */

#ifndef INC_SERIALCONNECTION_HPP_
#define INC_SERIALCONNECTION_HPP_

#include "Bsp.hpp"
#include <cstring>
#include <array>

using UsbArray = std::array<uint8_t, USB_RX_BUFF_SIZE>;

struct __attribute__((packed)) ReceivedData
{
	uint8_t type = 0;
	float frequency = 0.0f;
	float amplitude = 0.0f;
	float offset = 0.0f;
	bool stop = false;
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
