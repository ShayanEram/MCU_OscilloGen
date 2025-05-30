/*
 * BspBM.hpp
 *
 *  Created on: May 29, 2025
 *      Author: shaya
 */

#ifndef BSP_BSPBM_HPP_
#define BSP_BSPBM_HPP_

#include "Bsp.hpp"

extern "C"
{
#include "stm32h7xx.h"
}

class BspBM final: public Bsp {
public:

	explicit BspBM() = default;
	~BspBM() = default;

	//PWM-------------------------------------------------------------------------------------------------------------------------
	void pwmStart();
	void pwmStop();

	//SPI-------------------------------------------------------------------------------------------------------------------------
	void spiTransmit(const uint8_t *pData, uint16_t Size);
	void spiReceive(uint8_t *pData, uint16_t Size);

	//GPIO-------------------------------------------------------------------------------------------------------------------------
	Status gpioWrite(uint16_t GPIO_Pin, bool PinState) override final;
	bool gpioRead(uint16_t GPIO_Pin) override final;

	//UART--------------------------------------------------------------------------------------------------------------------------
	void uartTransmit(const uint8_t *pData, uint16_t Size);
	void uartReceive(uint8_t *pData, uint16_t Size);

	//ADC----------------------------------------------------------------------------------------------------------------------------
	void adcStart();
	void adcStop();

	//TIM----------------------------------------------------------------------------------------------------------------------------
	void timStart();
	void timStop();

	//DAC----------------------------------------------------------------------------------------------------------------------------
	void dacStart(const uint32_t *pData, uint32_t Length);
	void dacStop();

	//I2C----------------------------------------------------------------------------------------------------------------------------
	void i2cTransmit_Master(uint16_t DevAddress, uint8_t *pData, uint16_t Size);
	void i2cReceive_Master(uint16_t DevAddress, uint8_t *pData, uint16_t Size);

	//wdg----------------------------------------------------------------------------------------------------------------------------
	Status watchdogStart() override final;
	Status watchdogRefresh() override final;

	//Extra--------------------------------------------------------------------------------------------------------------------------
	void delay(uint32_t Delay) override;

};

#endif /* BSP_BSPBM_HPP_ */
