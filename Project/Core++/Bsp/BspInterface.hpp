/*
 * BspInterface.hpp
 *
 *  Created on: May 27, 2025
 *      Author: shaya
 */

#ifndef BSP_BSPINTERFACE_HPP_
#define BSP_BSPINTERFACE_HPP_

#include <cstdint>
#include <stdio.h>
#include <iostream>

enum class Status : uint8_t
{
	OK = 0x00,
	ERROR = 0x01,
	BUSY = 0x02,
	TIMEOUT = 0x03
};

class BspInterface {
protected:

    virtual ~BspInterface() = default;

    // PWM-------------------------------------------------------------------------------------------------------------------------
    virtual Status pwmStart_IT() = 0;
    virtual Status pwmStop_IT() = 0;
    virtual Status pwmStart_DMA(const uint32_t *pData, uint16_t Length) = 0;
    virtual Status pwmStop_DMA() = 0;

    // SPI-------------------------------------------------------------------------------------------------------------------------
    virtual Status spiTransmit_IT(const uint8_t *pData, uint16_t Size) = 0;
    virtual Status spiReceive_IT(uint8_t *pData, uint16_t Size) = 0;
    virtual Status spiTransmitReceive_IT(const uint8_t *pTxData, uint8_t *pRxData, uint16_t Size) = 0;
    virtual Status spiTransmit_DMA(const uint8_t *pData, uint16_t Size) = 0;
    virtual Status spiReceive_DMA(uint8_t *pData, uint16_t Size) = 0;
    virtual Status spiTransmitReceive_DMA(const uint8_t *pTxData, uint8_t *pRxData, uint16_t Size) = 0;

    // GPIO-------------------------------------------------------------------------------------------------------------------------
    virtual Status gpioWrite(uint16_t GPIO_Pin, bool PinState) = 0;
    virtual bool gpioRead(uint16_t GPIO_Pin) = 0;
    virtual Status gpioToggle(uint16_t GPIO_Pin) = 0;

    // UART--------------------------------------------------------------------------------------------------------------------------
    virtual Status uartTransmit_IT(const uint8_t *pData, uint16_t Size) = 0;
    virtual Status uartReceive_IT(uint8_t *pData, uint16_t Size) = 0;
    virtual Status uartTransmit_DMA(const uint8_t *pData, uint16_t Size) = 0;
    virtual Status uartReceive_DMA(uint8_t *pData, uint16_t Size) = 0;

    // USB----------------------------------------------------------------------------------------------------------------------------
    virtual Status usbTransmit(uint8_t* Buf, uint16_t Len) = 0;

    // ADC----------------------------------------------------------------------------------------------------------------------------
    virtual Status adcCalibrationStart(uint32_t CalibrationMode, uint32_t SingleDiff) = 0;
    virtual Status adcStart_IT() = 0;
    virtual Status adcStop_IT() = 0;
    virtual Status adcStart_DMA(uint32_t *pData, uint32_t Length) = 0;
    virtual Status adcStopDMA() = 0;

    // TIM----------------------------------------------------------------------------------------------------------------------------
    virtual Status timStart_IT() = 0;
    virtual Status timStop_IT() = 0;
    virtual Status timeStart_DMA(const uint32_t *pData, uint16_t Length) = 0;
    virtual Status timeStopDMA() = 0;

    // DAC----------------------------------------------------------------------------------------------------------------------------
    virtual Status dacStart_DMA(const uint32_t *pData, uint32_t Length) = 0;
    virtual Status dacStopDMA() = 0;

    // I2C----------------------------------------------------------------------------------------------------------------------------
    virtual Status i2cTransmit_Master_IT(uint16_t DevAddress, uint8_t *pData, uint16_t Size) = 0;
    virtual Status i2cReceive_Master_IT(uint16_t DevAddress, uint8_t *pData, uint16_t Size) = 0;
    virtual Status i2cTransmit_Master_DMA(uint16_t DevAddress, uint8_t *pData, uint16_t Size) = 0;
    virtual Status i2cReceive_Master_DMA(uint16_t DevAddress, uint8_t *pData, uint16_t Size) = 0;

    // Watchdog----------------------------------------------------------------------------------------------------------------------------
    virtual Status watchdogStart() = 0;
    virtual Status watchdogRefresh() = 0;

    // CORDIC-------------------------------------------------------------------------------------------------------------------------
    virtual Status cordicInit(uint8_t type) = 0;
    virtual Status cordicCalculate_DMA(const int32_t *pInBuff, int32_t *pOutBuff, uint32_t NbCalc) = 0;

    // Extra--------------------------------------------------------------------------------------------------------------------------
    virtual void delay(uint32_t Delay) = 0;
};

#endif /* BSP_BSPINTERFACE_HPP_ */
