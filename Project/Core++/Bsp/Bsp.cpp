/**
 * @file: BspStm.cpp
 * @author: Shayan Eram
 */
#include "Bsp.hpp"

Bsp& Bsp::getInstance() {
    static Bsp instance;
    return instance;
}

//PWM--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Status Bsp::pwmStart_IT()
{
	return convertHALStatus(HAL_TIM_PWM_Start_IT(&htim1, TIM_CHANNEL_1));
}

Status Bsp::pwmStop_IT()
{
	return convertHALStatus(HAL_TIM_PWM_Stop_IT(&htim1, TIM_CHANNEL_1));
}

Status Bsp::pwmStart_DMA(const uint32_t *pData, uint16_t Length)
{
	return convertHALStatus(HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_1, pData, Length));
}

Status Bsp::pwmStop_DMA()
{
	return convertHALStatus(HAL_TIM_PWM_Stop_DMA(&htim1, TIM_CHANNEL_1));
}

extern "C" void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim)
{
	Bsp::getInstance().handleTimPwmPulseComplete();
}

//SPI--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Status Bsp::spiTransmit_IT(const uint8_t *pData, uint16_t Size)
{
	return convertHALStatus(HAL_SPI_Transmit_IT(&hspi1, pData, Size));
}

Status Bsp::spiReceive_IT(uint8_t *pData, uint16_t Size)
{
	return convertHALStatus(HAL_SPI_Receive_IT(&hspi1, pData, Size));
}

Status Bsp::spiTransmitReceive_IT(const uint8_t *pTxData, uint8_t *pRxData, uint16_t Size)
{
	return convertHALStatus(HAL_SPI_TransmitReceive_IT(&hspi1, pTxData, pRxData, Size));
}

Status Bsp::spiTransmit_DMA(const uint8_t *pData, uint16_t Size)
{
	return convertHALStatus(HAL_SPI_Transmit_DMA(&hspi1, pData, Size));
}

Status Bsp::spiReceive_DMA(uint8_t *pData, uint16_t Size)
{
	return convertHALStatus(HAL_SPI_Receive_DMA(&hspi1, pData, Size));
}

Status Bsp::spiTransmitReceive_DMA(const uint8_t *pTxData, uint8_t *pRxData, uint16_t Size)
{
	return convertHALStatus(HAL_SPI_TransmitReceive_DMA(&hspi1, pTxData, pRxData, Size));
}

extern "C" void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi)
{
	Bsp::getInstance().handleSpiTxComplete();
}

extern "C" void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef *hspi)
{
	Bsp::getInstance().handleSpiRxComplete();
}

//GPIO--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Status Bsp::gpioWrite(uint16_t GPIO_Pin, bool PinState)
{
	GPIO_PinState state = (PinState) ? GPIO_PIN_SET : GPIO_PIN_RESET;
	HAL_GPIO_WritePin(GPIOA, GPIO_Pin, state);
    return Status::OK;
}

bool Bsp::gpioRead(uint16_t GPIO_Pin)
{
	return HAL_GPIO_ReadPin(GPIOA, GPIO_Pin) == GPIO_PIN_SET;
}

Status Bsp::gpioToggle(uint16_t GPIO_Pin)
{
    HAL_GPIO_TogglePin(GPIOA, GPIO_Pin);
    return Status::OK;
}

//UART---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Status Bsp::uartTransmit_IT(const uint8_t *pData, uint16_t Size)
{
	return convertHALStatus(HAL_UART_Transmit_IT(&huart2, pData, Size));
}

Status Bsp::uartReceive_IT(uint8_t *pData, uint16_t Size)
{
	return convertHALStatus(HAL_UART_Receive_IT(&huart2, pData, Size));
}

Status Bsp::uartTransmit_DMA(const uint8_t *pData, uint16_t Size)
{
	return convertHALStatus(HAL_UART_Transmit_DMA(&huart2, pData, Size));
}

Status Bsp::uartReceive_DMA(uint8_t *pData, uint16_t Size)
{
	return convertHALStatus(HAL_UART_Receive_DMA(&huart2, pData, Size));
}

extern "C" void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
	Bsp::getInstance().handleUartTxComplete();
}

extern "C" void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	uint8_t receivedData;
	HAL_UART_Receive(huart, &receivedData, 1, 100);
	Bsp::getInstance().handleUartRxComplete(receivedData);
}

//USB-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Status Bsp::usbTransmit(uint8_t* Buf, uint16_t Len)
{
	return (CDC_Transmit_HS(Buf, Len) == USBD_OK) ? Status::OK : Status::ERROR;
}

//ADC----------------------------------------------------------------------------------------------------------------------------
Status Bsp::adcCalibrationStart(uint32_t CalibrationMode, uint32_t SingleDiff)
{
	return convertHALStatus(HAL_ADCEx_Calibration_Start(&hadc1, CalibrationMode, SingleDiff));
}

Status Bsp::adcStart_IT()
{
	return convertHALStatus(HAL_ADC_Start_IT(&hadc1));
}

Status Bsp::adcStop_IT()
{
	return convertHALStatus(HAL_ADC_Stop_IT(&hadc1));
}

Status Bsp::adcStart_DMA(uint32_t *pData, uint32_t Length)
{
	return convertHALStatus(HAL_ADC_Start_DMA(&hadc1, pData, Length));
}

Status Bsp::adcStopDMA()
{
	return convertHALStatus(HAL_ADC_Stop_DMA(&hadc1));
}

extern "C" void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{
	Bsp::getInstance().handleAdcConvComplete();
}

extern "C" void HAL_ADC_ConvHalfCpltCallback(ADC_HandleTypeDef *hadc)
{
	Bsp::getInstance().handleAdcHalfConvComplete();
}

//TIM----------------------------------------------------------------------------------------------------------------------------
Status Bsp::timStart_IT()
{
	return convertHALStatus(HAL_TIM_Base_Start_IT(&htim2));
}

Status Bsp::timStop_IT()
{
	return convertHALStatus(HAL_TIM_Base_Stop_IT(&htim2));
}

Status Bsp::timeStart_DMA(const uint32_t *pData, uint16_t Length)
{
	return convertHALStatus(HAL_TIM_Base_Start_DMA(&htim2, pData, Length));
}

Status Bsp::timeStopDMA()
{
	return convertHALStatus(HAL_TIM_Base_Stop_DMA(&htim2));
}

extern "C" void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	Bsp::getInstance().handleTimPeriodElapsed();
}

//DAC----------------------------------------------------------------------------------------------------------------------------
Status Bsp::dacStart_DMA(const uint32_t *pData, uint32_t Length)
{
	return convertHALStatus(HAL_DAC_Start_DMA(&hdac1, DAC_CHANNEL_1, pData, Length, DAC_ALIGN_12B_R));
}

Status Bsp::dacStopDMA()
{
	return convertHALStatus(HAL_DAC_Stop_DMA(&hdac1, DAC_CHANNEL_1));
}

extern "C" void HAL_DAC_ConvCpltCallbackCh1(DAC_HandleTypeDef *hdac)
{
	Bsp::getInstance().handleDacConvComplete();
}

extern "C" void HAL_DAC_ConvHalfCpltCallbackCh1(DAC_HandleTypeDef *hdac)
{
	Bsp::getInstance().handleDacHalfConvComplete();
}

//I2C----------------------------------------------------------------------------------------------------------------------------
Status Bsp::i2cTransmit_Master_IT(uint16_t DevAddress, uint8_t *pData, uint16_t Size)
{
	return convertHALStatus(HAL_I2C_Master_Transmit_IT(&hi2c1, DevAddress, pData, Size));
}

Status Bsp::i2cReceive_Master_IT(uint16_t DevAddress, uint8_t *pData, uint16_t Size)
{
	return convertHALStatus(HAL_I2C_Master_Receive_IT(&hi2c1, DevAddress, pData, Size));
}

Status Bsp::i2cTransmit_Master_DMA(uint16_t DevAddress, uint8_t *pData, uint16_t Size)
{
	return convertHALStatus(HAL_I2C_Master_Transmit_DMA(&hi2c1, DevAddress, pData, Size));
}

Status Bsp::i2cReceive_Master_DMA(uint16_t DevAddress, uint8_t *pData, uint16_t Size)
{
	return convertHALStatus(HAL_I2C_Master_Receive_DMA(&hi2c1, DevAddress, pData, Size));
}

extern "C" void HAL_I2C_MasterTxCpltCallback(I2C_HandleTypeDef *hi2c)
{
	Bsp::getInstance().handleI2cTxComplete();
}

extern "C" void HAL_I2C_MasterRxCpltCallback(I2C_HandleTypeDef *hi2c)
{
	Bsp::getInstance().handleI2cRxComplete();
}

//wdg----------------------------------------------------------------------------------------------------------------------------
Status Bsp::watchdogStart()
{
	return convertHALStatus(HAL_IWDG_Init(&hiwdg1));
}

Status Bsp::watchdogRefresh()
{
	return convertHALStatus(HAL_IWDG_Refresh(&hiwdg1));
}

//CORDIC-------------------------------------------------------------------------------------------------------------------------
Status Bsp::cordicInit(uint8_t type = 0)
{
	uint32_t functionType;

	switch (type)
	{
		case 0:
			functionType = CORDIC_FUNCTION_COSINE;
			break;
		case 1:
			functionType = CORDIC_FUNCTION_SINE;
			break;
		case 2:
			functionType = CORDIC_FUNCTION_PHASE;
			break;
		case 3:
			functionType = CORDIC_FUNCTION_MODULUS;
			break;
		case 4:
			functionType = CORDIC_FUNCTION_ARCTANGENT;
			break;
		case 5:
			functionType = CORDIC_FUNCTION_HCOSINE;
			break;
		case 6:
			functionType = CORDIC_FUNCTION_HSINE;
			break;
		case 7:
			functionType = CORDIC_FUNCTION_HARCTANGENT;
			break;
		case 8:
			functionType = CORDIC_FUNCTION_NATURALLOG;
			break;
		case 9:
			functionType = CORDIC_FUNCTION_SQUAREROOT;
			break;
		default:
			functionType = CORDIC_FUNCTION_COSINE;
			break;
	}

	CORDIC_ConfigTypeDef sCordicConfig;
    sCordicConfig.Function   	   = functionType;
	sCordicConfig.Precision        = CORDIC_PRECISION_6CYCLES;
	sCordicConfig.Scale            = CORDIC_SCALE_0;
	sCordicConfig.NbWrite          = CORDIC_NBWRITE_1;
	sCordicConfig.NbRead           = CORDIC_NBREAD_1;
	sCordicConfig.InSize           = CORDIC_INSIZE_32BITS;
	sCordicConfig.OutSize          = CORDIC_OUTSIZE_32BITS;

	return convertHALStatus(HAL_CORDIC_Configure(&hcordic, &sCordicConfig));
}

Status Bsp::cordicCalculate_DMA(const int32_t *pInBuff, int32_t *pOutBuff, uint32_t NbCalc)
{
	while (HAL_CORDIC_GetState(&hcordic) != HAL_CORDIC_STATE_READY);

	return convertHALStatus(HAL_CORDIC_Calculate_DMA(&hcordic, pInBuff, pOutBuff, NbCalc, CORDIC_DMA_DIR_IN_OUT));
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
