/*
 * SerialConnection.hpp
 *
 *  Created on: May 8, 2025
 *      Author: shaya
 */

#ifndef INC_SERIALCONNECTION_HPP_
#define INC_SERIALCONNECTION_HPP_

#include "Bsp.hpp"
#include <array>

using UsbArray = std::array<uint8_t, USB_RX_BUFF_SIZE>;

class SerialCtn
{
public:
	explicit SerialCtn (Bsp& bsp);
	~SerialCtn();

	Status interfaceHandshake(uint8_t major, uint8_t minor);
	void processReceivedData();


private:
	Bsp& _bsp;

	static constexpr uint8_t SINGAL_PARAMS_ID = 0xBB;

	void sendData(UsbArray data);
	UsbArray receiveData();
	void processSignalParams();

};



#endif /* INC_SERIALCONNECTION_HPP_ */
