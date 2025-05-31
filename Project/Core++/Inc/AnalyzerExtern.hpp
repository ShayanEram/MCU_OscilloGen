/**
 * @file AnalyzerExtern.hpp
 * @brief Declaration of the AnalyzerExt class for external analyzer operations.
 * This class provides methods to request various analysis operations such as FFT, filtering, edge detection, modulation, and waveform analysis.
 * It communicates with the FPGA via UART.
 * 
 * @author Shayan Eram
 */
#ifndef INC_ANALYZEREXTERN_HPP_
#define INC_ANALYZEREXTERN_HPP_

#include "Bsp.hpp"

class AnalyzerExt final {
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
