/*
 * BspPic.cpp
 *
 *  Created on: May 8, 2025
 *      Author: shaya
 */

#include "BspPic.hpp"

#ifdef PIC
/* GPIO */
void BspPic::writeGPIO(bool state) {
    if (state)
        LATBbits.LATB0 = 1;  // Set pin
    else
        LATBbits.LATB0 = 0;  // Reset pin
}

bool BspPic::readGPIO() const {
    return PORTBbits.RB0;
}

/* ADC */
void BspPic::startADC() {
    ADCON0bits.ADON = 1;  // Enable ADC
    ADCON0bits.GO = 1;    // Start conversion
}

void BspPic::stopADC() {
    ADCON0bits.ADON = 0;  // Disable ADC
}

uint16_t BspPic::readADC() const {
    while (ADCON0bits.GO);  // Wait until conversion is done
    return (ADRESH << 8) | ADRESL;  // Read ADC value
}

/* DAC */
void BspPic::startDAC() {
    DACCON0bits.DACEN = 1;  // Enable DAC
}

void BspPic::stopDAC() {
    DACCON0bits.DACEN = 0;  // Disable DAC
}

void BspPic::writeDAC(uint16_t value) {
    DACCON1 = value & 0xFF;  // Set DAC output
}

/* PWM */
void BspPic::startPWM() {
    CCP1CONbits.EN = 1;  // Enable PWM module
}

void BspPic::stopPWM() {
    CCP1CONbits.EN = 0;  // Disable PWM module
}

/* UART */
void BspPic::sendUART(uint8_t data) {
    while (!TXSTAbits.TRMT);  // Wait for TX buffer to be empty
    TXREG = data;  // Send data
}

uint8_t BspPic::receiveUART() const {
    while (!PIR1bits.RCIF);  // Wait for RX buffer to be full
    return RCREG;
}

/* SPI */
uint8_t BspPic::sendSPI(uint8_t data) {
    SSPBUF = data;  // Send data
    while (!PIR1bits.SSPIF);  // Wait for SPI transfer complete
    PIR1bits.SSPIF = 0;  // Clear flag
    return SSPBUF;
}

uint8_t BspPic::receiveSPI() const {
    while (!PIR1bits.SSPIF);  // Wait for SPI transfer complete
    PIR1bits.SSPIF = 0;  // Clear flag
    return SSPBUF;
}

/* I2C */
void BspPic::sendI2C(uint8_t address, uint8_t data) {
    SSPBUF = address;  // Send address
    while (!PIR1bits.SSPIF);  // Wait for ACK
    SSPBUF = data;  // Send data
    while (!PIR1bits.SSPIF);
}

uint8_t BspPic::receiveI2C(uint8_t address) const {
    SSPBUF = address | 0x01;  // Send read request
    while (!PIR1bits.SSPIF);
    return SSPBUF;
}

/* Delay */
void BspPic::delay(uint32_t Delay) {
    for (volatile uint32_t i = 0; i < Delay * 1000; i++);
}

#endif
