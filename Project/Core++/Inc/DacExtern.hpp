/*
 * DacExtern.hpp
 *
 *  Created on: May 8, 2025
 *      Author: shaya
 */

#ifndef INC_DACEXTERN_HPP_
#define INC_DACEXTERN_HPP_

#include "IBsp.hpp"

constexpr uint8_t WRITE_CODE_N 				{0x0};
constexpr uint8_t WRITE_CODE_ALL 			{0x8};
constexpr uint8_t WRITE_CODE_N_UPDATE_N 	{0x3};
constexpr uint8_t WRITE_CODE_N_UPDATE_ALL 	{0x2};
constexpr uint8_t WRITE_CODE_ALL_UPDATE_ALL {0xA};
constexpr uint8_t NO_OPERATION 				{0xF};

constexpr uint8_t LTC2666_DAC0 {0x0};
constexpr uint8_t LTC2666_DAC1 {0x1};
constexpr uint8_t LTC2666_DAC2 {0x2};
constexpr uint8_t LTC2666_DAC3 {0x3};
constexpr uint8_t LTC2666_DAC4 {0x4};
constexpr uint8_t LTC2666_DAC5 {0x5};
constexpr uint8_t LTC2666_DAC6 {0x6};


class Dac final {
public:
    explicit Dac(Bsp& bsp);
    ~Dac()= default;



private:
    Bsp& _bsp;
};



#endif /* INC_DACEXTERN_HPP_ */
