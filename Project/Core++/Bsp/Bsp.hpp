/**
 * @file: BspStm.hpp
 * @brief: Bsp class implementation for STM32
 * This class provides an interface for various hardware functionalities such as PWM, SPI, GPIO, UART, USB, ADC, TIM, DAC, I2C, watchdog, and CORDIC operations.
 * 
 * @author: Shayan Eram
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

using FunctionalCallback = std::function<void()>;

class Bsp : public BspInterface {
public:
	static Bsp& getInstance();
	~Bsp() = default;

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
	Status timStart_DMA(const uint32_t *pData, uint16_t Length) override;
	Status timStopDMA() override;

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

    void handleTimPwmPulseComplete();
    void handleSpiTxComplete();
    void handleSpiRxComplete();
    void handleUartTxComplete();
    void handleUartRxComplete(uint8_t data);
    void handleAdcConvComplete();
    void handleAdcHalfConvComplete();
    void handleTimPeriodElapsed();
    void handleDacConvComplete();
    void handleDacHalfConvComplete();
    void handleI2cTxComplete();
    void handleI2cRxComplete();

    void dispatchEvents(); // Dispatch function to be called in main loop

    // Default handlers
    void onTimPwmPulseFinished();
	void onSpiTxComplete();
	void onSpiRxComplete();
	void onUartTxComplete();
	void onUartRx(uint8_t data);
	void onAdcConvComplete();
	void onAdcHalfConvComplete();
	void onTimPeriodElapsed();
	void onDacConvComplete();
	void onDacHalfConvComplete();
	void onI2cTxComplete();
	void onI2cRxComplete();

	void registerDefaultCallbacks(); // Helper to wire default handlers to callbacks

private:
	explicit Bsp() = default;

	Status convertHALStatus(HAL_StatusTypeDef halStatus);
	Status convertUSBStatus(USBD_StatusTypeDef usbStatus);

	// Event flags
	volatile bool timPwmPulseFlag 	= false;
	volatile bool spiTxFlag 		= false;
	volatile bool spiRxFlag 		= false;
	volatile bool uartTxFlag 		= false;
	volatile bool adcConvFlag 		= false;
	volatile bool adcHalfConvFlag 	= false;
	volatile bool timPeriodFlag 	= false;
	volatile bool dacConvFlag 		= false;
	volatile bool dacHalfConvFlag 	= false;
	volatile bool i2cTxFlag 		= false;
	volatile bool i2cRxFlag 		= false;
	volatile bool uartRxFlag 		= false;
	volatile uint8_t uartRxData 	= 0;

};

#endif /* BSP_INC_BSP_HPP_ */
