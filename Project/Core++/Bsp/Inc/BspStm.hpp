/*
 * BspStm.hpp
 *
 *  Created on: May 8, 2025
 *      Author: shaya
 */

#ifndef BSP_INC_BSPSTM_HPP_
#define BSP_INC_BSPSTM_HPP_

#include "IBsp.hpp"

class BspStm: public Bsp {
public:
	BspStm();
	virtual ~BspStm();

#ifdef STM
	/* GPIO */
	void writeGPIO(bool state) override;
	void readGPIO() override;

	/* ADC */
	void startADC() override;
	void stopADC() override;
	uint16_t readADC() override;

	/* DAC */
	void startDAC() override;
	void stopDAC() override;
	void writeDAC(uint16_t value) override;

	/* PWM */
	void startPWM() override;
	void stopPWM() override;

	/* UART */
	void sendUART(uint8_t data) override;
	uint8_t receiveUART() override;

	/* SPI */
	uint8_t sendSPI(uint8_t data) override;
	uint8_t receiveSPI() override;

	/* I2C */
	void sendI2C(uint8_t address, uint8_t data) override;
	uint8_t receiveI2C(uint8_t address) override;

	/* Delay */
	void delay(uint32_t Delay) override;
#endif
};

#endif /* BSP_INC_BSPSTM_HPP_ */
