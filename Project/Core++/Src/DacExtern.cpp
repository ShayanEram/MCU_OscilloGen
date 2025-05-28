/*
 * DacExtern.cpp
 *
 *  Created on: May 8, 2025
 *      Author: shaya
 */

#include "DacExtern.hpp"
#include "arm_math.h"

Dac::Dac(Bsp& bsp): _bsp(bsp){}

Status Dac::sendDataSPI(uint32_t data)
{
	if(_bsp.spiTransmit_IT((uint8_t*)&data, 1) != Status::OK){
        return Status::ERROR;
    }

    return Status::OK;
}

uint8_t Dac::receiveStatusSPI()
{
	uint8_t data = 0;
	_bsp.spiReceive_IT(&data, 1);

	return data;
}

uint16_t Dac::voltageToCode(float voltage_decimal, float min_voltage, float max_voltage)
{
    if (voltage_decimal > max_voltage) {
        voltage_decimal = max_voltage;
    } else if (voltage_decimal < min_voltage) {
        voltage_decimal = min_voltage;
    }

    int32_t range_span = max_voltage - min_voltage;
    float normalized_voltage = (float)(voltage_decimal - min_voltage) / range_span;
    uint16_t code = (uint16_t)(normalized_voltage * 65535);

    return code;
}

Status Dac::writeN_updateN(uint8_t DAC, uint16_t voltage_hex)
{
    uint32_t txData;

    txData = (0xFF << 24) | (WRITE_CODE_N_UPDATE_N << 20) | (DAC << 16) | voltage_hex;
    if(sendDataSPI(txData) != Status::OK){
        return Status::ERROR;
    }

    return Status::OK;
}

Status Dac::noOperation()
{
	uint32_t txData;

    txData = NO_OPERATION_DAC;
    if(sendDataSPI(txData) != Status::OK){
        return Status::ERROR;
    }

    return Status::OK;
}

void Dac::test()
{

    float angle = 0.0;
    float timePerSample = 1.0 / 100; // Time for each sample
    float angleIncrement = 2 * M_PI * timePerSample; // Calculate the angle increment based on the sample rate

    for(uint32_t i = 0; i<100000000; ++i)
    {
    	uint16_t sineValue = (uint16_t)(((arm_sin_f32(angle) * 0x7FFF) + 0x7FFF));
		uint32_t dataToSend = 0xFF300000 | sineValue; // Format the data according to the provided structure
		sendDataSPI(dataToSend);

		angle += angleIncrement;
		if (angle >= (2 * M_PI)) {
			angle -= (2 * M_PI);
		}
	}
}

