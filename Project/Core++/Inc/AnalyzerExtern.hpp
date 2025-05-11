/*
 * AdcExtern.hpp
 *
 *  Created on: May 9, 2025
 *      Author: shaya
 *
 *      FPGA for processing using UART
 */

#ifndef INC_ANALYZEREXTERN_HPP_
#define INC_ANALYZEREXTERN_HPP_

#include "Bsp.hpp"

class AnalyzerExt
{
public:
	explicit AnalyzerExt(Bsp& bsp);
	~AnalyzerExt() = default;

	uint8_t requestFFT();
	uint8_t requestFiltering();
	uint8_t requestEdgeDetection();
	uint8_t requestModulation();
	uint8_t requestWaveform();

private:
    Bsp& _bsp;
    void sendCommand(uint8_t command);
    uint8_t receiveData();

    static constexpr uint8_t CMD_FFT 		 {0x01};
    static constexpr uint8_t CMD_FILTER 	 {0x02};
    static constexpr uint8_t CMD_EDGE_DETECT {0x03};
    static constexpr uint8_t CMD_MODULATION  {0x04};
    static constexpr uint8_t CMD_WAVEFORM 	 {0x05};
};

#endif /* INC_ANALYZEREXTERN_HPP_ */
