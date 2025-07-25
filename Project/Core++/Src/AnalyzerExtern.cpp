/**
 * @file AnalyzerExtern.cpp
 * @author Shayan Eram
 */
#include "AnalyzerExtern.hpp"

AnalyzerExt::AnalyzerExt(Bsp& bsp): _bsp(bsp){}

void AnalyzerExt::sendCommand(uint8_t command)
{
	_bsp.uartTransmit_DMA(&command, 1);
}

uint8_t AnalyzerExt::receiveData()
{
	uint8_t data;
	_bsp.uartReceive_DMA(&data, 1);
	return data;
}

uint8_t AnalyzerExt::requestFFT()
{
	sendCommand(CMD_FFT);
	return receiveData();
}
uint8_t AnalyzerExt::requestFiltering()
{
    sendCommand(CMD_FILTER);
    return receiveData();
}
uint8_t AnalyzerExt::requestEdgeDetection()
{
    sendCommand(CMD_EDGE_DETECT);
    return receiveData();
}
uint8_t AnalyzerExt::requestModulation()
{
    sendCommand(CMD_MODULATION);
    return receiveData();
}
uint8_t AnalyzerExt::requestWaveform()
{
    sendCommand(CMD_WAVEFORM);
    return receiveData();
}
