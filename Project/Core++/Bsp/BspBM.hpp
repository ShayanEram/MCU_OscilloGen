/**
 * @file BspBM.hpp
 * @brief Bsp class implementation for STM32 using Bare Metal (BM) approach
 * This class provides an interface for various hardware functionalities such as PWM, SPI, GPIO, UART, ADC, TIM, DAC, I2C, and CORDIC operations.
 * 
 * @author Shayan Eram
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
	void spiInit();
	void spiTransmit(const uint8_t *pData, uint16_t Size);
	void spiReceive(uint8_t *pData, uint16_t Size);

	//GPIO-------------------------------------------------------------------------------------------------------------------------
	Status gpioWrite(uint16_t GPIO_Pin, bool PinState) override final;
	bool gpioRead(uint16_t GPIO_Pin) override final;

	//UART--------------------------------------------------------------------------------------------------------------------------
	void uartInit();
	void uartTransmit(const uint8_t *pData, uint16_t Size);
	void uartReceive(uint8_t *pData, uint16_t Size);

	//ADC----------------------------------------------------------------------------------------------------------------------------
	void adcInit();
	void adcStart();
	void adcStop();

	//DAC----------------------------------------------------------------------------------------------------------------------------
	void dacInit();
	void dacStart(const uint32_t *pData, uint32_t Length);
	void dacStop();

	//I2C----------------------------------------------------------------------------------------------------------------------------
	void i2cInit_Master();
	void i2cTransmit_Master(uint16_t DevAddress, uint8_t *pData, uint16_t Size);
	void i2cReceive_Master(uint16_t DevAddress, uint8_t *pData, uint16_t Size);

private:
	static constexpr uint8_t TRIGGER_TIMER_PSC  = 160; // slow clock to 0.1MHz --> 16 MHz/160
	static constexpr uint16_t TRIGGER_TIMER_ARR = 7000; // 70ms --> 0.1MHz * 70ms
	static constexpr uint8_t TRIGGER_TIMER_DC	 = 50;
	static constexpr uint32_t UART_PERIPH_CLOCK =	1000000; // 1MHz
	static constexpr uint32_t UART_BAUDRATE	 =	115200;
};

#endif /* BSP_BSPBM_HPP_ */
