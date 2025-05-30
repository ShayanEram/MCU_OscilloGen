/*
 * IBsp.hpp
 *
 *  Created on: May 8, 2025
 *      Author: shaya
 */

#ifndef BSP_INC_BSP_HPP_
#define BSP_INC_BSP_HPP_

#define ARM_MATH_CM7

#include "BspInterface.hpp"
#include <functional>

extern "C"
{
#include "main.h"
#include "adc.h"
#include "cordic.h"
#include "dac.h"
#include "dma.h"
#include "i2c.h"
#include "iwdg.h"
#include "memorymap.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "usb_device.h"
#include "usbd_cdc_if.h"
#include "gpio.h"
}

class Bsp final: public BspInterface {
public:
	static Bsp& getInstance();
	~Bsp() = default;

	using FunctionalCallback = std::function<void()>;

	//PWM-------------------------------------------------------------------------------------------------------------------------
	Status pwmStart_IT() override;
	Status pwmStop_IT() override;
	Status pwmStart_DMA(const uint32_t *pData, uint16_t Length) override;
	Status pwmStop_DMA() override;

	//SPI-------------------------------------------------------------------------------------------------------------------------
	Status spiTransmit_IT(const uint8_t *pData, uint16_t Size) override;
	Status spiReceive_IT(uint8_t *pData, uint16_t Size) override;
	Status spiTransmitReceive_IT(const uint8_t *pTxData, uint8_t *pRxData, uint16_t Size) override;
	Status spiTransmit_DMA(const uint8_t *pData, uint16_t Size) override;
	Status spiReceive_DMA(uint8_t *pData, uint16_t Size) override;
	Status spiTransmitReceive_DMA(const uint8_t *pTxData, uint8_t *pRxData, uint16_t Size) override;

	//GPIO-------------------------------------------------------------------------------------------------------------------------
	Status gpioWrite(uint16_t GPIO_Pin, bool PinState) override;
	bool gpioRead(uint16_t GPIO_Pin) override;
	Status gpioToggle(uint16_t GPIO_Pin) override;

	//UART--------------------------------------------------------------------------------------------------------------------------
	Status uartTransmit_IT(const uint8_t *pData, uint16_t Size) override;
	Status uartReceive_IT(uint8_t *pData, uint16_t Size) override;
	Status uartTransmit_DMA(const uint8_t *pData, uint16_t Size) override;
	Status uartReceive_DMA(uint8_t *pData, uint16_t Size) override;

	//USB----------------------------------------------------------------------------------------------------------------------------
	Status usbTransmit(uint8_t* Buf, uint16_t Len) override;

	//ADC----------------------------------------------------------------------------------------------------------------------------
	Status adcCalibrationStart(uint32_t CalibrationMode, uint32_t SingleDiff) override;
	Status adcStart_IT() override;
	Status adcStop_IT() override;
	Status adcStart_DMA(uint32_t *pData, uint32_t Length) override;
	Status adcStopDMA() override;

	//TIM----------------------------------------------------------------------------------------------------------------------------
	Status timStart_IT() override;
	Status timStop_IT() override;
	Status timeStart_DMA(const uint32_t *pData, uint16_t Length) override;
	Status timeStopDMA() override;

	//DAC----------------------------------------------------------------------------------------------------------------------------
	Status dacStart_DMA(const uint32_t *pData, uint32_t Length) override;
	Status dacStopDMA() override;

	//I2C----------------------------------------------------------------------------------------------------------------------------
	Status i2cTransmit_Master_IT(uint16_t DevAddress, uint8_t *pData, uint16_t Size) override;
	Status i2cReceive_Master_IT(uint16_t DevAddress, uint8_t *pData, uint16_t Size) override;
	Status i2cTransmit_Master_DMA(uint16_t DevAddress, uint8_t *pData, uint16_t Size) override;
	Status i2cReceive_Master_DMA(uint16_t DevAddress, uint8_t *pData, uint16_t Size) override;

	//wdg----------------------------------------------------------------------------------------------------------------------------
	Status watchdogStart() override;
	Status watchdogRefresh() override;

	//CORDIC-------------------------------------------------------------------------------------------------------------------------
	Status cordicInit(uint8_t type) override;
	Status cordicCalculate_DMA(const int32_t *pInBuff, int32_t *pOutBuff, uint32_t NbCalc) override;

	//Extra--------------------------------------------------------------------------------------------------------------------------
	void delay(uint32_t Delay) override;

	//Callbacks----------------------------------------------------------------------------------------------------------------------
	FunctionalCallback timPwmPulseCallback;
	FunctionalCallback spiTxCallback;
	FunctionalCallback spiRxCallback;
	FunctionalCallback uartTxCallback;
    std::function<void(uint8_t)> uartRxCallback;
    FunctionalCallback adcConvCallback;
    FunctionalCallback adcHalfConvCallback;
    FunctionalCallback timPeriodCallback;
    FunctionalCallback dacConvCallback;
    FunctionalCallback dacHalfConvCallback;
    FunctionalCallback i2cTxCallback;
    FunctionalCallback i2cRxCallback;

	void handleTimPwmPulseComplete() { if (timPwmPulseCallback) timPwmPulseCallback(); }
	void handleSpiTxComplete() { if (spiTxCallback) spiTxCallback(); }
	void handleSpiRxComplete() { if (spiRxCallback) spiRxCallback(); }
	void handleUartTxComplete() { if (uartTxCallback) uartTxCallback(); }
	void handleUartRxComplete(uint8_t data) { if (uartRxCallback) uartRxCallback(data); }
	void handleAdcConvComplete() { if (adcConvCallback) adcConvCallback(); }
	void handleAdcHalfConvComplete() { if (adcHalfConvCallback) adcHalfConvCallback(); }
	void handleTimPeriodElapsed() { if (timPeriodCallback) timPeriodCallback(); }
	void handleDacConvComplete() { if (dacConvCallback) dacConvCallback(); }
	void handleDacHalfConvComplete() { if (dacHalfConvCallback) dacHalfConvCallback(); }
	void handleI2cTxComplete() { if (i2cTxCallback) i2cTxCallback(); }
	void handleI2cRxComplete() { if (i2cRxCallback) i2cRxCallback(); }

private:
	explicit Bsp() = default;

	Status convertHALStatus(HAL_StatusTypeDef halStatus);
	Status convertUSBStatus(USBD_StatusTypeDef usbStatus);

};

#endif /* BSP_INC_BSP_HPP_ */
