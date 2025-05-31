/**
 * @file BspBM.cpp
 * @author Shayan Eram
 */
#include "BspBM.hpp"

void BspBM::pwmStart()
{
	// Enable clock access to TIM1
	RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;

	// Ensure TIM1 is disabled
	TIM1->CR1 &= ~TIM_CR1_CEN;

	// Set counting direction (upcounting)
	TIM1->CR1 &= ~TIM_CR1_DIR;

	// Set prescaler
	TIM1->PSC = TRIGGER_TIMER_PSC;

	// Set Auto Reload Value, sets the PRI
	TIM1->ARR = TRIGGER_TIMER_ARR - 1;

	// Set Duty cycle chennel 1
	TIM1->CCR1 = TRIGGER_TIMER_DC;

	// Select PWM mode for channel 1
	TIM1->CCMR1 &= ~TIM_CCMR1_OC1M_Msk; // Clear bits
	TIM1->CCMR1 |= (TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2); // 110 - PWM mode 1

	// Enable output
	TIM1->CCER |= TIM_CCER_CC1E;

	// Enable main output
	TIM1->BDTR |= TIM_BDTR_MOE;

	// Start timer
	TIM1->CR1 |= TIM_CR1_CEN;
}

void BspBM::pwmStop()
{
    TIM1->CCER &= ~TIM_CCER_CC1E; // Disable PWM output
    TIM1->CR1 &= ~TIM_CR1_CEN;    // Stop timer
}

void BspBM::spiInit()
{
	// Enable clock access to SPI1
	RCC->AHB4ENR |= RCC_AHB4ENR_GPIOAEN; //enable clock for GPIOA
	RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;

	// Configure PA5 (SCK), PA6 (MISO), PA7 (MOSI) as alternate function
	GPIOA->MODER &= ~(GPIO_MODER_MODE5 | GPIO_MODER_MODE6 | GPIO_MODER_MODE7);
	GPIOA->MODER |= (GPIO_MODER_MODE5_1 | GPIO_MODER_MODE6_1 | GPIO_MODER_MODE7_1);
	GPIOA->AFR[0] |= (5 << GPIO_AFRL_AFSEL5_Pos) | (5 << GPIO_AFRL_AFSEL6_Pos) | (5 << GPIO_AFRL_AFSEL7_Pos);

	// Configure SPI1 as master
	SPI1->CFG2 |= SPI_CFG2_MASTER; 	// Master mode, software NSS
	SPI1->CFG2 |= SPI_CFG2_SSM;		// Software NSS enabled
	SPI1->CR1 |= SPI_CR1_SSI;		// Internal NSS signal high
	SPI1->CR1 |= SPI_CR1_SPE;		// Enable SPI
}

void BspBM::spiTransmit(const uint8_t *pData, uint16_t Size)
{
	for(uint16_t i= 0; i< Size; ++i)
	{
		while (!(SPI1->SR & SPI_SR_TXP)); // Wait until TX buffer is empty
		SPI1->TXDR = pData[i];
		while (!(SPI1->SR & SPI_SR_RXP)); // Wait until RX buffer is full
		(void)SPI1->RXDR;                 // Clear RX buffer if necessary
	}
}

void BspBM::spiReceive(uint8_t *pData, uint16_t Size)
{
	for (uint16_t i = 0; i < Size; ++i)
	{
		while (!(SPI1->SR & SPI_SR_RXP)); // Wait until received data is available
		pData[i] = SPI1->RXDR;            // Read received data
	}
}

Status BspBM::gpioWrite(uint16_t GPIO_Pin, bool PinState)
{
	if (PinState) GPIOA->ODR |= (1 << GPIO_Pin);
    else GPIOA->ODR &= ~(1 << GPIO_Pin);
	return Status::OK;
}

bool BspBM::gpioRead(uint16_t GPIO_Pin)
{
    return (GPIOA->IDR & (1 << GPIO_Pin)) ? true : false;
}

void BspBM::uartInit()
{
	// Enable clock for USART2 and GPIOA
	RCC->APB1LENR |= RCC_APB1LENR_USART2EN;
	RCC->AHB4ENR |= RCC_AHB4ENR_GPIOAEN;

	// Configure PA2 (TX) and PA3 (RX) as alternate function
	GPIOA->MODER &= ~(GPIO_MODER_MODE2 | GPIO_MODER_MODE3);
	GPIOA->MODER |= (GPIO_MODER_MODE2_1 | GPIO_MODER_MODE3_1);
	GPIOA->AFR[0] |= (7 << GPIO_AFRL_AFSEL2_Pos) | (7 << GPIO_AFRL_AFSEL3_Pos); // AF7 for USART2

	// Configure USART2
	USART2->BRR = UART_PERIPH_CLOCK / UART_BAUDRATE; 	// Baud rate (assuming 4MHz clock)
	USART2->CR1 |= USART_CR1_TE | USART_CR1_RE; 		// Enable TX and RX
	USART2->CR1 |= USART_CR1_UE; 						// Enable USART
}

void BspBM::uartTransmit(const uint8_t *pData, uint16_t Size)
{
	for (uint16_t i = 0; i < Size; ++i)
	{
		while (!(USART2->ISR & USART_ISR_TXFT)); 		// Wait until TX FIFO threshold is met
		USART2->TDR = pData[i]; 						// Send data
	}
}

void BspBM::uartReceive(uint8_t *pData, uint16_t Size) {
    for (uint16_t i = 0; i < Size; i++)
    {
    	while (!(USART2->ISR & USART_ISR_RXFT)); 		// Wait until RX FIFO threshold is met
        pData[i] = USART2->RDR; 						// Read received data
    }
}

void BspBM::adcInit()
{
	// Enable ADC clock
	RCC->AHB1ENR |= RCC_AHB1ENR_ADC12EN;

	// Configure ADC settings
	ADC1->CR &= ~ADC_CR_DEEPPWD; 					// Disable deep power-down mode
	ADC1->CR |= ADC_CR_ADVREGEN; 					// Enable ADC voltage regulator
	for (uint16_t i = 0; i < 1000; ++i); 			// Short delay for stabilization

	// Configure resolution and data alignment
	ADC1->CFGR |= ADC_CFGR_RES_0; 					// 12-bit resolution
	ADC1->CFGR &= ~ADC3_CFGR_ALIGN_Msk; 			// Right-aligned data

	// Select input channel (channel 1)
	ADC1->SQR1 |= (1 << ADC_SQR1_SQ1_Pos); 			// Set channel 1 in sequence

	// Enable ADC
	ADC1->CR |= ADC_CR_ADEN;
	while (!(ADC1->ISR & ADC_ISR_ADRDY)); 			// Wait until ADC is ready
}

void BspBM::adcStart()
{
    ADC1->CR |= ADC_CR_ADSTART; 					// Start ADC conversion
}

void BspBM::adcStop()
{
    ADC1->CR |= ADC_CR_ADSTP; 						// Stop ADC conversion
    while (ADC1->CR & ADC_CR_ADSTP); 				// Wait until stop is complete
}

void BspBM::dacInit()
{
    // Enable DAC clock
    RCC->APB1LENR |= RCC_APB1LENR_DAC12EN; 			// Enable DAC1 clock

    // Configure DAC output pin (example: PA4 for DAC1_OUT1)
    GPIOA->MODER |= GPIO_MODER_MODE4; 				// Set PA4 as analog mode

    // Enable DAC
    DAC1->CR |= DAC_CR_EN1; // Enable DAC channel 1
}

void BspBM::dacStart(const uint32_t *pData, uint32_t Length)
{
    for (uint32_t i = 0; i < Length; i++) {
        DAC1->DHR12R1 = pData[i]; 					// Load data into DAC register
    }
}

void BspBM::dacStop() {
    DAC1->CR &= ~DAC_CR_EN1; 						// Disable DAC channel
}

void BspBM::i2cInit_Master()
{
	// Enable I2C1 and GPIOB clocks
	RCC->APB1LENR |= RCC_APB1LENR_I2C1EN;
	RCC->AHB4ENR |= RCC_AHB4ENR_GPIOBEN;

	// Configure PB6 (SCL) and PB7 (SDA) as alternate function
	GPIOB->MODER &= ~(GPIO_MODER_MODE6 | GPIO_MODER_MODE7);
	GPIOB->MODER |= (GPIO_MODER_MODE6_1 | GPIO_MODER_MODE7_1);
	GPIOB->AFR[0] |= (4 << GPIO_AFRL_AFSEL6_Pos) | (4 << GPIO_AFRL_AFSEL7_Pos); // AF4 for I2C1

	// Configure I2C timing (100kHz standard mode)
	I2C1->TIMINGR = 0x20303E5D; 	// Timing value for 100kHz

	// Enable I2C and configure master mode
	I2C1->CR1 |= I2C_CR1_PE; 		// Enable I2C peripheral
}

void BspBM::i2cTransmit_Master(uint16_t DevAddress, uint8_t *pData, uint16_t Size) {
    I2C1->CR2 = (DevAddress << 1) | (Size << I2C_CR2_NBYTES_Pos) | I2C_CR2_START;

    for (uint16_t i = 0; i < Size; i++)
    {
        while (!(I2C1->ISR & I2C_ISR_TXE)); // Wait for TX buffer empty
        I2C1->TXDR = pData[i]; 				// Send data
    }
    while (!(I2C1->ISR & I2C_ISR_TC)); 		// Wait for transfer complete
    I2C1->CR2 |= I2C_CR2_STOP; 				// Stop transmission
}

void BspBM::i2cReceive_Master(uint16_t DevAddress, uint8_t *pData, uint16_t Size) {
    I2C1->CR2 = (DevAddress << 1) | (Size << I2C_CR2_NBYTES_Pos) | I2C_CR2_START | I2C_CR2_RD_WRN;

    for (uint16_t i = 0; i < Size; i++)
    {
        while (!(I2C1->ISR & I2C_ISR_RXNE)); 	// Wait for RX buffer full
        pData[i] = I2C1->RXDR; 					// Read received data
    }
    while (!(I2C1->ISR & I2C_ISR_TC)); 			// Wait for transfer complete
    I2C1->CR2 |= I2C_CR2_STOP; 					// Stop reception
}
