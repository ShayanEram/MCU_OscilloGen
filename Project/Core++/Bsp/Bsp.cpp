/*
 * BspStm.cpp
 *
 *  Created on: May 8, 2025
 *      Author: shaya
 */

#include "Bsp.hpp"

//PWM--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Status Bsp::pwmStart_IT(TIM_HandleTypeDef *htim, uint32_t Channel)
{
	return convertHALStatus(HAL_TIM_PWM_Start_IT(htim, Channel));
}

Status Bsp::pwmStop_IT(TIM_HandleTypeDef *htim, uint32_t Channel)
{
	return convertHALStatus(HAL_TIM_PWM_Stop_IT(htim, Channel));
}

Status Bsp::pwmStart_DMA(TIM_HandleTypeDef *htim, uint32_t Channel, const uint32_t *pData, uint16_t Length)
{
	return convertHALStatus(HAL_TIM_PWM_Start_DMA(htim, Channel, pData, Length));
}

Status Bsp::pwmStop_DMA(TIM_HandleTypeDef *htim, uint32_t Channel)
{
	return convertHALStatus(HAL_TIM_PWM_Stop_DMA(htim, Channel));
}

//SPI--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Status Bsp::spiTransmit_IT(SPI_HandleTypeDef *hspi, const uint8_t *pData, uint16_t Size)
{
	return convertHALStatus(HAL_SPI_Transmit_IT(hspi, pData, Size));
}

Status Bsp::spiReceive_IT(SPI_HandleTypeDef *hspi, uint8_t *pData, uint16_t Size)
{
	return convertHALStatus(HAL_SPI_Receive_IT(hspi, pData, Size));
}

Status Bsp::spiTransmitReceive_IT(SPI_HandleTypeDef *hspi, const uint8_t *pTxData, uint8_t *pRxData, uint16_t Size)
{
	return convertHALStatus(HAL_SPI_TransmitReceive_IT(hspi, pTxData, pRxData, Size));
}

Status Bsp::spiTransmit_DMA(SPI_HandleTypeDef *hspi, const uint8_t *pData, uint16_t Size)
{
	return convertHALStatus(HAL_SPI_Transmit_DMA(hspi, pData, Size));
}

Status Bsp::spiReceive_DMA(SPI_HandleTypeDef *hspi, uint8_t *pData, uint16_t Size)
{
	return convertHALStatus(HAL_SPI_Receive_DMA(hspi, pData, Size));
}

Status Bsp::spiTransmitReceive_DMA(SPI_HandleTypeDef *hspi, const uint8_t *pTxData, uint8_t *pRxData, uint16_t Size)
{
	return convertHALStatus(HAL_SPI_TransmitReceive_DMA(hspi, pTxData, pRxData, Size));
}

//GPIO--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Status Bsp::gpioWrite(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState)
{
    HAL_GPIO_WritePin(GPIOx, GPIO_Pin, PinState);
    return Status::OK;
}

Status Bsp::gpioRead(const GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, GPIO_PinState GPIO_Pin_status)
{
	return (GPIO_Pin_status == HAL_GPIO_ReadPin(GPIOx, GPIO_Pin)) ? Status::OK : Status::ERROR;
}

Status Bsp::gpioToggle(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
    HAL_GPIO_TogglePin(GPIOx, GPIO_Pin);
    return Status::OK;
}


//UART---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Status Bsp::uartTransmit_IT(UART_HandleTypeDef *huart, const uint8_t *pData, uint16_t Size)
{
	return convertHALStatus(HAL_UART_Transmit_IT(huart, pData, Size));
}

Status Bsp::uartReceive_IT(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size)
{
	return convertHALStatus(HAL_UART_Receive_IT(huart, pData, Size));
}

Status Bsp::uartTransmit_DMA(UART_HandleTypeDef *huart, const uint8_t *pData, uint16_t Size)
{
	return convertHALStatus(HAL_UART_Transmit_DMA(huart, pData, Size));
}

Status Bsp::uartReceive_DMA(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size)
{
	return convertHALStatus(HAL_UART_Receive_DMA(huart, pData, Size));
}

//USB-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Status Bsp::usbTransmit(uint8_t* Buf, uint16_t Len)
{
	return (CDC_Transmit_HS(Buf, Len) == USBD_OK) ? Status::OK : Status::ERROR;
}

//ADC----------------------------------------------------------------------------------------------------------------------------
Status Bsp::adcCalibrationStart(ADC_HandleTypeDef *hadc, uint32_t CalibrationMode, uint32_t SingleDiff)
{
	return convertHALStatus(HAL_ADCEx_Calibration_Start(hadc, CalibrationMode, SingleDiff));
}

Status Bsp::adcStart_IT(ADC_HandleTypeDef *hadc)
{
	return convertHALStatus(HAL_ADC_Start_IT(hadc));
}

Status Bsp::adcStop_IT(ADC_HandleTypeDef *hadc)
{
	return convertHALStatus(HAL_ADC_Stop_IT(hadc));
}

Status Bsp::adcStart_DMA(ADC_HandleTypeDef *hadc, uint32_t *pData, uint32_t Length)
{
	return convertHALStatus(HAL_ADC_Start_DMA(hadc, pData, Length));
}

Status Bsp::adcStopDMA(ADC_HandleTypeDef *hadc)
{
	return convertHALStatus(HAL_ADC_Stop_DMA(hadc));
}

//TIM----------------------------------------------------------------------------------------------------------------------------
Status Bsp::timStart_IT(TIM_HandleTypeDef *htim)
{
	return convertHALStatus(HAL_TIM_Base_Start_IT(htim));
}

Status Bsp::timStop_IT(TIM_HandleTypeDef *htim)
{
	return convertHALStatus(HAL_TIM_Base_Stop_IT(htim));
}

Status Bsp::timeStart_DMA(TIM_HandleTypeDef *htim, const uint32_t *pData, uint16_t Length)
{
	return convertHALStatus(HAL_TIM_Base_Start_DMA(htim, pData, Length));
}

Status Bsp::timeStopDMA(TIM_HandleTypeDef *htim)
{
	return convertHALStatus(HAL_TIM_Base_Stop_DMA(htim));
}

//DAC----------------------------------------------------------------------------------------------------------------------------
Status Bsp::dacStart_DMA(DAC_HandleTypeDef *hdac, uint32_t Channel, const uint32_t *pData, uint32_t Length, uint32_t Alignment)
{
	return convertHALStatus(HAL_DAC_Start_DMA(hdac, Channel, pData, Length, Alignment));
}

Status Bsp::dacStopDMA(DAC_HandleTypeDef *hdac, uint32_t Channel)
{
	return convertHALStatus(HAL_DAC_Stop_DMA(hdac, Channel));
}

//I2C----------------------------------------------------------------------------------------------------------------------------
Status Bsp::i2cTransmit_Master_IT(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size)
{
	return convertHALStatus(HAL_I2C_Master_Transmit_IT(hi2c, DevAddress, pData, Size));
}

Status Bsp::i2cReceive_Master_IT(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size)
{
	return convertHALStatus(HAL_I2C_Master_Receive_IT(hi2c, DevAddress, pData, Size));
}

Status Bsp::i2cTransmit_Master_DMA(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size)
{
	return convertHALStatus(HAL_I2C_Master_Transmit_DMA(hi2c, DevAddress, pData, Size));
}

Status Bsp::i2cReceive_Master_DMA(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size)
{
	return convertHALStatus(HAL_I2C_Master_Receive_DMA(hi2c, DevAddress, pData, Size));
}

//wdg----------------------------------------------------------------------------------------------------------------------------
Status Bsp::watchdogStart(IWDG_HandleTypeDef *hiwdg)
{
	return convertHALStatus(HAL_IWDG_Init(hiwdg));
}

Status Bsp::watchdogRefresh(IWDG_HandleTypeDef *hiwdg)
{
	return convertHALStatus(HAL_IWDG_Refresh(hiwdg));
}

//CORDIC-------------------------------------------------------------------------------------------------------------------------
Status Bsp::cordicInit(CORDIC_HandleTypeDef *hcordic, bool cosine = false)
{
	uint32_t functionType = cosine ? CORDIC_FUNCTION_COSINE : CORDIC_FUNCTION_SINE;

	CORDIC_ConfigTypeDef sCordicConfig;
    sCordicConfig.Function   	   = functionType;
	sCordicConfig.Precision        = CORDIC_PRECISION_6CYCLES;
	sCordicConfig.Scale            = CORDIC_SCALE_0;
	sCordicConfig.NbWrite          = CORDIC_NBWRITE_1;
	sCordicConfig.NbRead           = CORDIC_NBREAD_1;
	sCordicConfig.InSize           = CORDIC_INSIZE_32BITS;
	sCordicConfig.OutSize          = CORDIC_OUTSIZE_32BITS;

	return convertHALStatus(HAL_CORDIC_Configure(hcordic, &sCordicConfig));
}

Status Bsp::cordicCalculate_DMA(CORDIC_HandleTypeDef *hcordic, const int32_t *pInBuff, int32_t *pOutBuff, uint32_t NbCalc, uint32_t DMADirection)
{
	while (HAL_CORDIC_GetState(hcordic) != HAL_CORDIC_STATE_READY);

	return convertHALStatus(HAL_CORDIC_Calculate_DMA(hcordic, pInBuff, pOutBuff, NbCalc, DMADirection));
}

//Extra-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Bsp::delay(uint32_t Delay)
{
	HAL_Delay(Delay);
}

//PrivateFunctions------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Status Bsp::convertHALStatus(HAL_StatusTypeDef halStatus)
{
    switch (halStatus)
    {
        case HAL_OK:
            return Status::OK;
        case HAL_ERROR:
        	return Status::ERROR;
        case HAL_BUSY:
        	return Status::BUSY;
        case HAL_TIMEOUT:
        	return Status::TIMEOUT;
        default:
            return Status::ERROR;
    }
}

Status Bsp::convertUSBStatus(USBD_StatusTypeDef usbStatus)
{
	switch(usbStatus)
	{
		case USBD_OK:
			return Status::OK;
		case USBD_BUSY:
			return Status::BUSY;
		case USBD_EMEM:
			return Status::TIMEOUT;
		case USBD_FAIL:
			return Status::ERROR;
		default:
			return Status::ERROR;
	}
}

/**
 * Use printf/std::cout to send usb data
 * */
extern "C" int _write(int file, char *ptr, int len)
{
	static uint8_t rc = USBD_OK;

	do
	{
		rc = CDC_Transmit_HS((uint8_t*) ptr, len);
	}
	while (USBD_BUSY == rc);

	if (USBD_FAIL == rc) {
		return 0;
	}
	return len;
}
