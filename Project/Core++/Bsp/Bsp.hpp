/*
 * IBsp.hpp
 *
 *  Created on: May 8, 2025
 *      Author: shaya
 */

#ifndef BSP_INC_BSP_HPP_
#define BSP_INC_BSP_HPP_

#define ARM_MATH_CM7

#include <cstdint>
#include <stdio.h>
#include <iostream>

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

enum class Status : uint8_t
{
	OK = 0x00,
	ERROR = 0x01,
	BUSY = 0x02,
	TIMEOUT = 0x03
};

class Bsp final {
public:
	explicit Bsp() = default;
	~Bsp() = default;

	//PWM-------------------------------------------------------------------------------------------------------------------------
	Status pwmStart_IT(TIM_HandleTypeDef *htim, uint32_t Channel);
	Status pwmStop_IT(TIM_HandleTypeDef *htim, uint32_t Channel);
	Status pwmStart_DMA(TIM_HandleTypeDef *htim, uint32_t Channel, const uint32_t *pData, uint16_t Length);
	Status pwmStop_DMA(TIM_HandleTypeDef *htim, uint32_t Channel);

	//SPI-------------------------------------------------------------------------------------------------------------------------
	Status spiTransmit_IT(SPI_HandleTypeDef *hspi, const uint8_t *pData, uint16_t Size);
	Status spiReceive_IT(SPI_HandleTypeDef *hspi, uint8_t *pData, uint16_t Size);
	Status spiTransmitReceive_IT(SPI_HandleTypeDef *hspi, const uint8_t *pTxData, uint8_t *pRxData, uint16_t Size);
	Status spiTransmit_DMA(SPI_HandleTypeDef *hspi, const uint8_t *pData, uint16_t Size);
	Status spiReceive_DMA(SPI_HandleTypeDef *hspi, uint8_t *pData, uint16_t Size);
	Status spiTransmitReceive_DMA(SPI_HandleTypeDef *hspi, const uint8_t *pTxData, uint8_t *pRxData, uint16_t Size);

	//GPIO-------------------------------------------------------------------------------------------------------------------------
	Status gpioWrite(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState);
	Status gpioRead(const GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, GPIO_PinState GPIO_Pin_status);
	Status gpioToggle(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);

	//UART--------------------------------------------------------------------------------------------------------------------------
	Status uartTransmit_IT(UART_HandleTypeDef *huart, const uint8_t *pData, uint16_t Size);
	Status uartReceive_IT(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size);
	Status uartTransmit_DMA(UART_HandleTypeDef *huart, const uint8_t *pData, uint16_t Size);
	Status uartReceive_DMA(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size);

	//USB----------------------------------------------------------------------------------------------------------------------------
	Status usbTransmit(uint8_t* Buf, uint16_t Len);

	//ADC----------------------------------------------------------------------------------------------------------------------------
	Status adcCalibrationStart(ADC_HandleTypeDef *hadc, uint32_t CalibrationMode, uint32_t SingleDiff);
	Status adcStart_IT(ADC_HandleTypeDef *hadc);
	Status adcStop_IT(ADC_HandleTypeDef *hadc);
	Status adcStart_DMA(ADC_HandleTypeDef *hadc, uint32_t *pData, uint32_t Length);
	Status adcStopDMA(ADC_HandleTypeDef *hadc);

	//TIM----------------------------------------------------------------------------------------------------------------------------
	Status timStart_IT(TIM_HandleTypeDef *htim);
	Status timStop_IT(TIM_HandleTypeDef *htim);
	Status timeStart_DMA(TIM_HandleTypeDef *htim, const uint32_t *pData, uint16_t Length);
	Status timeStopDMA(TIM_HandleTypeDef *htim);

	//DAC----------------------------------------------------------------------------------------------------------------------------
	Status dacStart_DMA(DAC_HandleTypeDef *hdac, uint32_t Channel, const uint32_t *pData, uint32_t Length, uint32_t Alignment);
	Status dacStopDMA(DAC_HandleTypeDef *hdac, uint32_t Channel);

	//I2C----------------------------------------------------------------------------------------------------------------------------
	Status i2cTransmit_Master_IT(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size);
	Status i2cReceive_Master_IT(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size);
	Status i2cTransmit_Master_DMA(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size);
	Status i2cReceive_Master_DMA(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size);

	//wdg----------------------------------------------------------------------------------------------------------------------------
	Status watchdogStart(IWDG_HandleTypeDef *hiwdg);
	Status watchdogRefresh(IWDG_HandleTypeDef *hiwdg);

	//CORDIC-------------------------------------------------------------------------------------------------------------------------
	Status cordicInit(CORDIC_HandleTypeDef *hcordic, bool cosine);
	Status cordicCalculate_DMA(CORDIC_HandleTypeDef *hcordic, const int32_t *pInBuff, int32_t *pOutBuff, uint32_t NbCalc, uint32_t DMADirection);

	//Extra--------------------------------------------------------------------------------------------------------------------------
	void delay(uint32_t Delay);


private:
	Status convertHALStatus(HAL_StatusTypeDef halStatus);
	Status convertUSBStatus(USBD_StatusTypeDef usbStatus);

};

#endif /* BSP_INC_BSP_HPP_ */
