/*
 * BspPic.hpp
 *
 *  Created on: May 8, 2025
 *      Author: shaya
 */

#ifndef BSP_INC_BSPPIC_HPP_
#define BSP_INC_BSPPIC_HPP_

#include "IBsp.hpp"

#ifdef PIC
#include <xc.h>  // Include PIC MCU registers
#endif

class BspPic final : public Bsp {
public:
	explicit BspPic() = default;
	~BspPic() = default;

#ifdef PIC
	/* GPIO */
	void writeGPIO(bool state) override;
	bool readGPIO() const override;

	/* ADC */
	void startADC() override;
	void stopADC() override;
	uint16_t readADC() const override;

	/* DAC */
	void startDAC() override;
	void stopDAC() override;
	void writeDAC(uint16_t value) override;

	/* PWM */
	void startPWM() override;
	void stopPWM() override;

	/* UART */
	void sendUART(uint8_t data) override;
	uint8_t receiveUART() const override;

	/* SPI */
	uint8_t sendSPI(uint8_t data) override;
	uint8_t receiveSPI() const override;

	/* I2C */
	void sendI2C(uint8_t address, uint8_t data) override;
	uint8_t receiveI2C(uint8_t address) const override;

	/* Delay */
	void delay(uint32_t Delay) override;

#endif

};

#endif /* BSP_INC_BSPPIC_HPP_ */
