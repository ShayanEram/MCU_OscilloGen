/*
 * IBsp.hpp
 *
 *  Created on: May 8, 2025
 *      Author: shaya
 */

#ifndef BSP_INC_IBSP_HPP_
#define BSP_INC_IBSP_HPP_

#include <cstdint>
#include <stdio.h>
#include <iostream>

class Bsp
{
public:
	virtual ~Bsp() = default;

protected:

#ifdef IBSP
	/*GPIO*/
	virtual void writeGPIO(bool state) = 0;
	virtual void readGPIO() = 0;

	/*ADC*/
	virtual void startADC() = 0;
	virtual void stopADC() = 0;
	virtual uint16_t readADC() = 0;

	/*DAC*/
	virtual void startDAC() = 0;
	virtual void stopDAC() = 0;
	virtual void writeDAC(uint16_t value) = 0;

	/*PWM*/
	virtual void startPWM() = 0;
	virtual void stopPWM() = 0;

	/*UART*/
	virtual void sendUART(uint8_t data) = 0;
	virtual uint8_t receiveUART() = 0;

	/*SPI*/
	virtual uint8_t sendSPI(uint8_t data) = 0;
	virtual uint8_t receiveSPI() = 0;

	/*I2C*/
	virtual void sendI2C(uint8_t address, uint8_t data) = 0;
	virtual uint8_t receiveI2C(uint8_t address) = 0;

	/*DELAY*/
	virtual void delay(uint32_t Delay) = 0;

#endif


};

#endif /* BSP_INC_IBSP_HPP_ */
