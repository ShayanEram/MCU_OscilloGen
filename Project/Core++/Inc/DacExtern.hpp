/*
 * DacExtern.hpp
 *
 *  Created on: May 8, 2025
 *      Author: shaya
 *
 *      external dac LTC2666
 */

#ifndef INC_DACEXTERN_HPP_
#define INC_DACEXTERN_HPP_

#include "BspStm.hpp"

class Dac final {
public:
    explicit Dac(BspStm& bsp);
    ~Dac()= default;

    void DacTest();
    void DacInit();
    uint16_t voltageToCode(float voltage_decimal, float max_voltage, float min_voltage);
    Status writeN_updateN(uint8_t DAC, uint16_t voltage_hex);
    Status noOperation();
    void test();

private:
    BspStm& _bsp;
    Status sendDataSPI(uint32_t data);
    uint8_t receiveStatusSPI();

    static constexpr uint8_t WRITE_CODE_N 				{0x0};
    static constexpr uint8_t WRITE_CODE_ALL 			{0x8};
    static constexpr uint8_t WRITE_CODE_N_UPDATE_N 		{0x3};
    static constexpr uint8_t WRITE_CODE_N_UPDATE_ALL 	{0x2};
    static constexpr uint8_t WRITE_CODE_ALL_UPDATE_ALL  {0xA};

    static constexpr uint8_t LTC2666_DAC0 {0x0};
    static constexpr uint8_t LTC2666_DAC1 {0x1};
    static constexpr uint8_t LTC2666_DAC2 {0x2};
    static constexpr uint8_t LTC2666_DAC3 {0x3};
    static constexpr uint8_t LTC2666_DAC4 {0x4};
    static constexpr uint8_t LTC2666_DAC5 {0x5};
    static constexpr uint8_t LTC2666_DAC6 {0x6};

    static constexpr uint32_t NO_OPERATION_DAC {0xFFFFFFFF};
};



#endif /* INC_DACEXTERN_HPP_ */
