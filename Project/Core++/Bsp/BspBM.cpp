/*
 * BspBM.cpp
 *
 *  Created on: May 29, 2025
 *      Author: shaya
 */

#include "BspBM.hpp"

// **PWM Start (Using TIM Register)**
void BspBM::pwmStart() {
//    TIM1->CCER |= TIM_CCER_CC1E; // Enable PWM output
//    TIM1->CR1 |= TIM_CR1_CEN;    // Start timer
}

// **PWM Stop**
void BspBM::pwmStop() {
//    TIM1->CCER &= ~TIM_CCER_CC1E; // Disable PWM output
//    TIM1->CR1 &= ~TIM_CR1_CEN;    // Stop timer
}

// **SPI Transmit (Polling Mode)**
void BspBM::spiTransmit(const uint8_t *pData, uint16_t Size) {
//    for (uint16_t i = 0; i < Size; i++) {
//        while (!(SPI1->SR & SPI_SR_TXE)); // Wait for TX buffer empty
//        SPI1->DR = pData[i];              // Write data
//        while (!(SPI1->SR & SPI_SR_RXNE)); // Wait for RX buffer full
//        (void)SPI1->DR; // Dummy read to clear RXNE flag
//    }
}

// **SPI Receive (Polling Mode)**
void BspBM::spiReceive(uint8_t *pData, uint16_t Size) {
//    for (uint16_t i = 0; i < Size; i++) {
//        while (!(SPI1->SR & SPI_SR_TXE)); // Wait for TX buffer empty
//        SPI1->DR = 0xFF;                   // Dummy write to generate clock
//        while (!(SPI1->SR & SPI_SR_RXNE)); // Wait for RX buffer full
//        pData[i] = SPI1->DR;               // Read received data
//    }
}

// **GPIO Write**
Status BspBM::gpioWrite(uint16_t GPIO_Pin, bool PinState) {
//    if (PinState) GPIOA->ODR |= (1 << GPIO_Pin);
//    else GPIOA->ODR &= ~(1 << GPIO_Pin);
}

// **GPIO Read**
bool BspBM::gpioRead(uint16_t GPIO_Pin) {
//    return (GPIOA->IDR & (1 << GPIO_Pin)) ? true : false;
}

// **UART Transmit**
void BspBM::uartTransmit(const uint8_t *pData, uint16_t Size) {
//    for (uint16_t i = 0; i < Size; i++) {
//        while (!(USART2->ISR & USART_ISR_TXE)); // Wait for TX buffer empty
//        USART2->TDR = pData[i]; // Send data
//    }
}

// **UART Receive**
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
