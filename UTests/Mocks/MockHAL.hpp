#ifndef MOCK_HAL_HPP
#define MOCK_HAL_HPP

#include <stdint.h> // For standard integer types

// Mocked HAL function declarations
extern "C" 
{
    #define CORDIC_FUNCTION_SINE    0x01U
    #define CORDIC_FUNCTION_COSINE  0x02U
    #define CORDIC_PRECISION_6CYCLES 0x03U
    #define CORDIC_SCALE_0          0x04U
    #define CORDIC_NBWRITE_1        0x05U
    #define CORDIC_NBREAD_1         0x06U
    #define CORDIC_INSIZE_32BITS    0x07U
    #define CORDIC_OUTSIZE_32BITS   0x08U
    #define HAL_CORDIC_STATE_READY  0x09U

    typedef enum {
        HAL_OK = 0x00U,
        HAL_ERROR = 0x01U,
        HAL_BUSY = 0x02U,
        HAL_TIMEOUT = 0x03U
    } HAL_StatusTypeDef;

    typedef struct {
        
    } I2C_HandleTypeDef;

    typedef struct {
        
    } IWDG_HandleTypeDef;

    typedef struct {
        
    } CORDIC_HandleTypeDef;

    typedef struct {
        uint32_t Function;
        uint32_t Precision;
        uint32_t Scale;
        uint32_t NbWrite;
        uint32_t NbRead;
        uint32_t InSize;
        uint32_t OutSize;
    } CORDIC_ConfigTypeDef;

    typedef struct {

    } TIM_HandleTypeDef;

    typedef struct {

    } SPI_HandleTypeDef;

    typedef struct {

    } GPIO_TypeDef;

    typedef struct {

    } UART_HandleTypeDef;

    typedef struct {

    } ADC_HandleTypeDef;

    typedef struct {

    } DAC_HandleTypeDef;


    typedef enum
    {
        GPIO_PIN_RESET = 0U,
        GPIO_PIN_SET
    } GPIO_PinState;

    typedef enum
    {
        USBD_OK = 0U,
        USBD_BUSY,
        USBD_EMEM,
        USBD_FAIL,
    } USBD_StatusTypeDef;

    #define DAC_ALIGN_12B_R                    0x00000000U
    #define DAC_CHANNEL_1                      0x00000000U
    #define USB_RX_BUFF_SIZE   15
    #define M_PI       3.14159265358979323846   // pi
    #define CORDIC_DMA_DIR_IN_OUT 2


    ADC_HandleTypeDef hadc1;
    CORDIC_HandleTypeDef hcordic;
    DAC_HandleTypeDef hdac1;
    I2C_HandleTypeDef hi2c1;
    IWDG_HandleTypeDef hiwdg1;
    SPI_HandleTypeDef hspi1;
    TIM_HandleTypeDef htim1;
    UART_HandleTypeDef huart2;






    HAL_StatusTypeDef HAL_IWDG_Init(IWDG_HandleTypeDef* hiwdg);
    HAL_StatusTypeDef HAL_IWDG_Refresh(IWDG_HandleTypeDef* hiwdg);

    uint32_t HAL_CORDIC_GetState(CORDIC_HandleTypeDef* hcordic);
    HAL_StatusTypeDef HAL_CORDIC_Configure(CORDIC_HandleTypeDef* hcordic, CORDIC_ConfigTypeDef* sConfig);
    HAL_StatusTypeDef HAL_CORDIC_Calculate_DMA(CORDIC_HandleTypeDef* hcordic, const int32_t* pInBuff, int32_t* pOutBuff, uint32_t NbCalc, uint32_t DMADirection);
    
    void HAL_Delay(uint32_t Delay);

    // TIM PWM Functions
    HAL_StatusTypeDef HAL_TIM_PWM_Start_IT(TIM_HandleTypeDef* htim, uint32_t Channel);
    HAL_StatusTypeDef HAL_TIM_PWM_Stop_IT(TIM_HandleTypeDef* htim, uint32_t Channel);
    HAL_StatusTypeDef HAL_TIM_PWM_Start_DMA(TIM_HandleTypeDef* htim, uint32_t Channel, const uint32_t* pData, uint32_t Length);
    HAL_StatusTypeDef HAL_TIM_PWM_Stop_DMA(TIM_HandleTypeDef* htim, uint32_t Channel);

    // SPI Functions
    HAL_StatusTypeDef HAL_SPI_Transmit_IT(SPI_HandleTypeDef* hspi, const uint8_t* pData, uint16_t Size);
    HAL_StatusTypeDef HAL_SPI_Receive_IT(SPI_HandleTypeDef* hspi, uint8_t* pData, uint16_t Size);
    HAL_StatusTypeDef HAL_SPI_TransmitReceive_IT(SPI_HandleTypeDef* hspi, const uint8_t* pTxData, uint8_t* pRxData, uint16_t Size);
    HAL_StatusTypeDef HAL_SPI_Transmit_DMA(SPI_HandleTypeDef* hspi, const uint8_t* pData, uint16_t Size);
    HAL_StatusTypeDef HAL_SPI_Receive_DMA(SPI_HandleTypeDef* hspi, uint8_t* pData, uint16_t Size);
    HAL_StatusTypeDef HAL_SPI_TransmitReceive_DMA(SPI_HandleTypeDef* hspi, const uint8_t* pTxData, uint8_t* pRxData, uint16_t Size);

    // GPIO Functions
    void HAL_GPIO_WritePin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState);
    GPIO_PinState HAL_GPIO_ReadPin(const GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
    void HAL_GPIO_TogglePin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);

    // UART Functions
    HAL_StatusTypeDef HAL_UART_Transmit_IT(UART_HandleTypeDef* huart, const uint8_t* pData, uint16_t Size);
    HAL_StatusTypeDef HAL_UART_Receive_IT(UART_HandleTypeDef* huart, uint8_t* pData, uint16_t Size);
    HAL_StatusTypeDef HAL_UART_Transmit_DMA(UART_HandleTypeDef* huart, const uint8_t* pData, uint16_t Size);
    HAL_StatusTypeDef HAL_UART_Receive_DMA(UART_HandleTypeDef* huart, uint8_t* pData, uint16_t Size);

    // USB CDC Function
    HAL_StatusTypeDef CDC_Transmit_HS(uint8_t* Buf, uint16_t Len);

    // ADC Functions
    HAL_StatusTypeDef HAL_ADCEx_Calibration_Start(ADC_HandleTypeDef* hadc, uint32_t CalibrationMode, uint32_t SingleDiff);
    HAL_StatusTypeDef HAL_ADC_Start_IT(ADC_HandleTypeDef* hadc);
    HAL_StatusTypeDef HAL_ADC_Stop_IT(ADC_HandleTypeDef* hadc);
    HAL_StatusTypeDef HAL_ADC_Start_DMA(ADC_HandleTypeDef* hadc, uint32_t* pData, uint32_t Length);
    HAL_StatusTypeDef HAL_ADC_Stop_DMA(ADC_HandleTypeDef* hadc);

    // Timer Base Functions
    HAL_StatusTypeDef HAL_TIM_Base_Start_IT(TIM_HandleTypeDef* htim);
    HAL_StatusTypeDef HAL_TIM_Base_Stop_IT(TIM_HandleTypeDef* htim);
    HAL_StatusTypeDef HAL_TIM_Base_Start_DMA(TIM_HandleTypeDef* htim, const uint32_t* pData, uint32_t Length);
    HAL_StatusTypeDef HAL_TIM_Base_Stop_DMA(TIM_HandleTypeDef* htim);

    // DAC Functions
    HAL_StatusTypeDef HAL_DAC_Start_DMA(DAC_HandleTypeDef* hdac, uint32_t Channel, const uint32_t* pData, uint32_t Length, uint32_t Alignment);
    HAL_StatusTypeDef HAL_DAC_Stop_DMA(DAC_HandleTypeDef* hdac, uint32_t Channel);

    // I2C Functions
    HAL_StatusTypeDef HAL_I2C_Master_Transmit_IT(I2C_HandleTypeDef* hi2c, uint16_t DevAddress, uint8_t* pData, uint16_t Size);
    HAL_StatusTypeDef HAL_I2C_Master_Receive_IT(I2C_HandleTypeDef* hi2c, uint16_t DevAddress, uint8_t* pData, uint16_t Size);
    HAL_StatusTypeDef HAL_I2C_Master_Transmit_DMA(I2C_HandleTypeDef* hi2c, uint16_t DevAddress, uint8_t* pData, uint16_t Size);
    HAL_StatusTypeDef HAL_I2C_Master_Receive_DMA(I2C_HandleTypeDef* hi2c, uint16_t DevAddress, uint8_t* pData, uint16_t Size);

}

#endif // MOCK_HAL_HPP