/*
 * BspBM.cpp
 *
 *  Created on: May 29, 2025
 *      Author: shaya
 */

#include "BspBM.hpp"

#define TRIGGER_TIMER_PSC    160  // slow clock to 0.1MHz --> 16 MHz/160
#define TRIGGER_TIMER_ARR    7000 // 70ms --> 0.1MHz * 70ms
#define TRIGGER_TIMER_DC	 50

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

void BspBM::spiReceive(uint8_t *pData, uint16_t Size) {
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

bool BspBM::gpioRead(uint16_t GPIO_Pin) {
    return (GPIOA->IDR & (1 << GPIO_Pin)) ? true : false;
}


void BspBM::uartTransmit(const uint8_t *pData, uint16_t Size) {
//    for (uint16_t i = 0; i < Size; i++) {
//        while (!(USART2->ISR & USART_ISR_TXE)); // Wait for TX buffer empty
//        USART2->TDR = pData[i]; // Send data
//    }
}


void BspBM::uartReceive(uint8_t *pData, uint16_t Size) {
//    for (uint16_t i = 0; i < Size; i++) {
//        while (!(USART2->ISR & USART_ISR_RXNE)); // Wait for RX buffer full
//        pData[i] = USART2->RDR; // Read received data
//    }
}

// **ADC Start**
void BspBM::adcStart() {
//    ADC1->CR |= ADC_CR_ADSTART; // Start ADC conversion
}

// **ADC Stop**
void BspBM::adcStop() {
//    ADC1->CR |= ADC_CR_ADSTP; // Stop ADC conversion
}

// **Timer Start**
void BspBM::timStart() {
//    TIM2->CR1 |= TIM_CR1_CEN; // Enable timer
}

// **Timer Stop**
void BspBM::timStop() {
//    TIM2->CR1 &= ~TIM_CR1_CEN; // Disable timer
}

// **DAC Start**
void BspBM::dacStart(const uint32_t *pData, uint32_t Length) {
//    for (uint32_t i = 0; i < Length; i++) {
//        DAC1->DHR12R1 = pData[i]; // Load data into DAC register
//    }
//    DAC1->CR |= DAC_CR_EN1; // Enable DAC channel
}

// **DAC Stop**
void BspBM::dacStop() {
//    DAC1->CR &= ~DAC_CR_EN1; // Disable DAC channel
}

// **I2C Transmit (Polling Mode)**
void BspBM::i2cTransmit_Master(uint16_t DevAddress, uint8_t *pData, uint16_t Size) {
//    I2C1->CR2 = (DevAddress << 1) | (Size << 16) | I2C_CR2_START;
//    for (uint16_t i = 0; i < Size; i++) {
//        while (!(I2C1->ISR & I2C_ISR_TXE)); // Wait for TX buffer empty
//        I2C1->TXDR = pData[i]; // Send data
//    }
//    I2C1->CR2 |= I2C_CR2_STOP; // Stop transmission
}

// **I2C Receive (Polling Mode)**
void BspBM::i2cReceive_Master(uint16_t DevAddress, uint8_t *pData, uint16_t Size) {
//    I2C1->CR2 = (DevAddress << 1) | (Size << 16) | I2C_CR2_START | I2C_CR2_RD_WRN;
//    for (uint16_t i = 0; i < Size; i++) {
//        while (!(I2C1->ISR & I2C_ISR_RXNE)); // Wait for RX buffer full
//        pData[i] = I2C1->RXDR; // Read received data
//    }
//    I2C1->CR2 |= I2C_CR2_STOP; // Stop reception
}

// **Watchdog Start**
Status BspBM::watchdogStart() {
//    IWDG->KR = 0x5555; // Unlock IWDG registers
//    IWDG->PR = 0x03;   // Set prescaler
//    IWDG->RLR = 0x0FFF; // Set reload value
//    IWDG->KR = 0xCCCC; // Start watchdog
}

// **Watchdog Refresh**
Status BspBM::watchdogRefresh() {
//    IWDG->KR = 0xAAAA; // Refresh watchdog counter
}

// **Delay (Blocking Mode Using TIM)**
void BspBM::delay(uint32_t Delay) {
//    TIM6->CNT = 0;
//    TIM6->CR1 |= TIM_CR1_CEN;
//    while (TIM6->CNT < Delay);
//    TIM6->CR1 &= ~TIM_CR1_CEN;
}
