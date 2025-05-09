/*
 * BspStm.cpp
 *
 *  Created on: May 8, 2025
 *      Author: shaya
 */

#include "BspStm.hpp"

#ifdef STM
/* GPIO */
void BspStm::writeGPIO(bool state) {
//    if (state)
//        GPIOA->BSRR = GPIO_BSRR_BS0;  // Set pin
//    else
//        GPIOA->BSRR = GPIO_BSRR_BR0;  // Reset pin
}

void BspStm::readGPIO() {
//    return (GPIOA->IDR & GPIO_IDR_ID0);
}

/* ADC */
void BspStm::startADC() {
//    ADC1->CR2 |= ADC_CR2_ADON;  // Enable ADC
//    ADC1->CR2 |= ADC_CR2_SWSTART;  // Start conversion
}

void BspStm::stopADC() {
//    ADC1->CR2 &= ~ADC_CR2_ADON;  // Disable ADC
}

uint16_t BspStm::readADC() {
//    while (!(ADC1->SR & ADC_SR_EOC));  // Wait for conversion to complete
//    return ADC1->DR;  // Read ADC value
}

/* DAC */
void BspStm::startDAC() {
//    DAC->CR |= DAC_CR_EN1;  // Enable DAC channel 1
}

void BspStm::stopDAC() {
//    DAC->CR &= ~DAC_CR_EN1;  // Disable DAC channel 1
}

void BspStm::writeDAC(uint16_t value) {
//    DAC->DHR12R1 = value;  // Set DAC output value
}

/* PWM */
void BspStm::startPWM() {
//    TIM2->CR1 |= TIM_CR1_CEN;  // Start PWM timer
}

void BspStm::stopPWM() {
//    TIM2->CR1 &= ~TIM_CR1_CEN;  // Stop PWM timer
}

/* UART */
void BspStm::sendUART(uint8_t data) {
//    while (!(USART1->SR & USART_SR_TXE));  // Wait for TX buffer to be empty
//    USART1->DR = data;
}

uint8_t BspStm::receiveUART() {
//    while (!(USART1->SR & USART_SR_RXNE));  // Wait for RX data
//    return USART1->DR;
}

/* SPI */
uint8_t BspStm::sendSPI(uint8_t data) {
//    while (!(SPI1->SR & SPI_SR_TXE));  // Wait for TX buffer to be empty
//    SPI1->DR = data;
//    while (!(SPI1->SR & SPI_SR_RXNE));  // Wait for RX data
//    return SPI1->DR;
}

uint8_t BspStm::receiveSPI() {
//    while (!(SPI1->SR & SPI_SR_RXNE));  // Wait for RX data
//    return SPI1->DR;
}

/* I2C */
void BspStm::sendI2C(uint8_t address, uint8_t data) {
//    I2C1->CR1 |= I2C_CR1_START;  // Generate START condition
//    while (!(I2C1->SR1 & I2C_SR1_SB));  // Wait for start bit
//    I2C1->DR = address;  // Send address
//    while (!(I2C1->SR1 & I2C_SR1_ADDR));
//    I2C1->DR = data;  // Send data
}

uint8_t BspStm::receiveI2C(uint8_t address) {
//    I2C1->CR1 |= I2C_CR1_START;
//    while (!(I2C1->SR1 & I2C_SR1_SB));
//    I2C1->DR = address | 0x01;  // Read mode
//    while (!(I2C1->SR1 & I2C_SR1_ADDR));
//    while (!(I2C1->SR1 & I2C_SR1_RXNE));
//    return I2C1->DR;
}

/* Delay */
void BspStm::delay(uint32_t Delay) {
    for (volatile uint32_t i = 0; i < Delay * 1000; ++i);  // Simple delay loop
}

#endif
