/*
 * BspStm.cpp
 *
 *  Created on: May 8, 2025
 *      Author: shaya
 */

#include "BspStm.hpp"

void BspStm::init()
{
	printf("Implementations are done in the main.c for STM32!");
}

//PWM--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Status BspStm::pwmStart_IT(TIM_HandleTypeDef *htim, uint32_t Channel)
{
	HAL_StatusTypeDef halStatus = HAL_TIM_PWM_Start_IT(htim, Channel);
	return convertHALStatus(halStatus);
}

Status BspStm::pwmStop_IT(TIM_HandleTypeDef *htim, uint32_t Channel)
{
	HAL_StatusTypeDef halStatus = HAL_TIM_PWM_Stop_IT(htim, Channel);
	return convertHALStatus(halStatus);
}


Status BspStm::pwmStart_DMA(TIM_HandleTypeDef *htim, uint32_t Channel, const uint32_t *pData, uint16_t Length)
{
	HAL_StatusTypeDef halStatus = HAL_TIM_PWM_Start_DMA(htim, Channel, pData, Length);
	return convertHALStatus(halStatus);

}

Status BspStm::pwmStop_DMA(TIM_HandleTypeDef *htim, uint32_t Channel)
{
	HAL_StatusTypeDef halStatus = HAL_TIM_PWM_Stop_DMA(htim, Channel);
	return convertHALStatus(halStatus);
}

//SPI--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Status BspStm::spiTransmit_IT(SPI_HandleTypeDef *hspi, const uint8_t *pData, uint16_t Size)
{
	HAL_StatusTypeDef halStatus = HAL_SPI_Transmit_IT(hspi, pData, Size);
	return convertHALStatus(halStatus);
}

Status BspStm::spiReceive_IT(SPI_HandleTypeDef *hspi, uint8_t *pData, uint16_t Size)
{
	HAL_StatusTypeDef halStatus = HAL_SPI_Receive_IT(hspi, pData, Size);
	return convertHALStatus(halStatus);
}

Status BspStm::spiTransmitReceive_IT(SPI_HandleTypeDef *hspi, const uint8_t *pTxData, uint8_t *pRxData, uint16_t Size)
{
	HAL_StatusTypeDef halStatus = HAL_SPI_TransmitReceive_IT(hspi, pTxData, pRxData, Size);
	return convertHALStatus(halStatus);
}

Status BspStm::spiTransmit_DMA(SPI_HandleTypeDef *hspi, const uint8_t *pData, uint16_t Size)
{
	HAL_StatusTypeDef halStatus = HAL_SPI_Transmit_DMA(hspi, pData, Size);
	return convertHALStatus(halStatus);
}

Status BspStm::spiReceive_DMA(SPI_HandleTypeDef *hspi, uint8_t *pData, uint16_t Size)
{
	HAL_StatusTypeDef halStatus = HAL_SPI_Receive_DMA(hspi, pData, Size);
	return convertHALStatus(halStatus);
}

Status BspStm::spiTransmitReceive_DMA(SPI_HandleTypeDef *hspi, const uint8_t *pTxData, uint8_t *pRxData, uint16_t Size)
{
	HAL_StatusTypeDef halStatus = HAL_SPI_TransmitReceive_DMA(hspi, pTxData, pRxData, Size);
	return convertHALStatus(halStatus);
}

//GPIO--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Status BspStm::gpioWrite(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState)
{
    HAL_GPIO_WritePin(GPIOx, GPIO_Pin, PinState);
    return Status::OK;
}

Status BspStm::gpioRead(const GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, GPIO_PinState GPIO_Pin_status)
{
    if (GPIO_Pin_status == HAL_GPIO_ReadPin(GPIOx, GPIO_Pin))
    	return Status::OK;
    else
    	return Status::ERROR;
}

Status BspStm::gpioToggle(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
    HAL_GPIO_TogglePin(GPIOx, GPIO_Pin);
    return Status::OK;
}


//UART---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Status BspStm::uartTransmit_IT(UART_HandleTypeDef *huart, const uint8_t *pData, uint16_t Size)
{
	HAL_StatusTypeDef halStatus = HAL_UART_Transmit_IT(huart, pData, Size);
	return convertHALStatus(halStatus);
}

Status BspStm::uartReceive_IT(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size)
{
	HAL_StatusTypeDef halStatus = HAL_UART_Receive_IT(huart, pData, Size);
	return convertHALStatus(halStatus);
}

Status BspStm::uartTransmit_DMA(UART_HandleTypeDef *huart, const uint8_t *pData, uint16_t Size)
{
	HAL_StatusTypeDef halStatus = HAL_UART_Transmit_DMA(huart, pData, Size);
	return convertHALStatus(halStatus);
}

Status BspStm::uartReceive_DMA(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size)
{
	HAL_StatusTypeDef halStatus = HAL_UART_Receive_DMA(huart, pData, Size);
	return convertHALStatus(halStatus);
}

//USB-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Status BspStm::usbTransmit(uint8_t* Buf, uint16_t Len)
{
	uint8_t result = CDC_Transmit_HS(Buf, Len);

	if (result != USBD_OK )
		return Status::ERROR;

	return Status::OK;
}

//ADC----------------------------------------------------------------------------------------------------------------------------
Status BspStm::adcCalibrationStart(ADC_HandleTypeDef *hadc, uint32_t CalibrationMode, uint32_t SingleDiff)
{
	HAL_StatusTypeDef halStatus = HAL_ADCEx_Calibration_Start(hadc, CalibrationMode, SingleDiff);
	return convertHALStatus(halStatus);
}

Status BspStm::adcStart_IT(ADC_HandleTypeDef *hadc)
{
	HAL_StatusTypeDef halStatus = HAL_ADC_Start_IT(hadc);
	return convertHALStatus(halStatus);
}

Status BspStm::adcStop_IT(ADC_HandleTypeDef *hadc)
{
	HAL_StatusTypeDef halStatus = HAL_ADC_Stop_IT(hadc);
	return convertHALStatus(halStatus);
}

Status BspStm::adcStart_DMA(ADC_HandleTypeDef *hadc, uint32_t *pData, uint32_t Length)
{
	HAL_StatusTypeDef halStatus = HAL_ADC_Start_DMA(hadc, pData, Length);
	return convertHALStatus(halStatus);
}

Status BspStm::adcStopDMA(ADC_HandleTypeDef *hadc)
{
	HAL_StatusTypeDef halStatus = HAL_ADC_Stop_DMA(hadc);
	return convertHALStatus(halStatus);
}

//TIM----------------------------------------------------------------------------------------------------------------------------
Status BspStm::timStart_IT(TIM_HandleTypeDef *htim)
{
	HAL_StatusTypeDef halStatus = HAL_TIM_Base_Start_IT(htim);
	return convertHALStatus(halStatus);
}

Status BspStm::timStop_IT(TIM_HandleTypeDef *htim)
{
	HAL_StatusTypeDef halStatus = HAL_TIM_Base_Stop_IT(htim);
	return convertHALStatus(halStatus);
}

Status BspStm::timeStart_DMA(TIM_HandleTypeDef *htim, const uint32_t *pData, uint16_t Length)
{
	HAL_StatusTypeDef halStatus = HAL_TIM_Base_Start_DMA(htim, pData, Length);
	return convertHALStatus(halStatus);
}

Status BspStm::timeStopDMA(TIM_HandleTypeDef *htim)
{
	HAL_StatusTypeDef halStatus = HAL_TIM_Base_Stop_DMA(htim);
	return convertHALStatus(halStatus);
}

//DAC----------------------------------------------------------------------------------------------------------------------------
Status BspStm::dacStart_DMA(DAC_HandleTypeDef *hdac, uint32_t Channel, const uint32_t *pData, uint32_t Length, uint32_t Alignment)
{
	HAL_StatusTypeDef halStatus = HAL_DAC_Start_DMA(hdac, Channel, pData, Length, Alignment);
	return convertHALStatus(halStatus);
}

Status BspStm::dacStopDMA(DAC_HandleTypeDef *hdac, uint32_t Channel)
{
	HAL_StatusTypeDef halStatus = HAL_DAC_Stop_DMA(hdac, Channel);
	return convertHALStatus(halStatus);
}

//I2C----------------------------------------------------------------------------------------------------------------------------
Status BspStm::i2cTransmit_Master_IT(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size)
{
	HAL_StatusTypeDef halStatus = HAL_I2C_Master_Transmit_IT(hi2c, DevAddress, pData, Size);
	return convertHALStatus(halStatus);
}

Status BspStm::i2cReceive_Master_IT(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size)
{
	HAL_StatusTypeDef halStatus = HAL_I2C_Master_Receive_IT(hi2c, DevAddress, pData, Size);
	return convertHALStatus(halStatus);
}

Status BspStm::i2cTransmit_Master_DMA(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size)
{
	HAL_StatusTypeDef halStatus = HAL_I2C_Master_Transmit_DMA(hi2c, DevAddress, pData, Size);
	return convertHALStatus(halStatus);
}

Status BspStm::i2cReceive_Master_DMA(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size)
{
	HAL_StatusTypeDef halStatus = HAL_I2C_Master_Receive_DMA(hi2c, DevAddress, pData, Size);
	return convertHALStatus(halStatus);
}

//wdg----------------------------------------------------------------------------------------------------------------------------
Status BspStm::watchdogRefresh(IWDG_HandleTypeDef *hiwdg)
{
	HAL_StatusTypeDef halStatus = HAL_IWDG_Refresh(hiwdg);
	return convertHALStatus(halStatus);
}

//CORDIC-------------------------------------------------------------------------------------------------------------------------
Status BspStm::cordicInit(CORDIC_HandleTypeDef *hcordic, bool cosine = false)
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

	HAL_StatusTypeDef halStatus = HAL_CORDIC_Configure(hcordic, &sCordicConfig);
	return convertHALStatus(halStatus);
}

Status BspStm::cordicCalculate_DMA(CORDIC_HandleTypeDef *hcordic, const int32_t *pInBuff, int32_t *pOutBuff, uint32_t NbCalc, uint32_t DMADirection)
{
	while (HAL_CORDIC_GetState(hcordic) != HAL_CORDIC_STATE_READY);

	HAL_StatusTypeDef halStatus = HAL_CORDIC_Calculate_DMA(hcordic, pInBuff, pOutBuff, NbCalc, DMADirection);
	return convertHALStatus(halStatus);
}

//Extra-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void BspStm::delay(uint32_t Delay)
{
	HAL_Delay(Delay);
}

//PrivateFunctions------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Status BspStm::convertHALStatus(HAL_StatusTypeDef halStatus)
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

Status BspStm::convertUSBStatus(USBD_StatusTypeDef usbStatus)
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
