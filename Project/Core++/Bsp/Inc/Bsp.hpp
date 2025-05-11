/*
 * IBsp.hpp
 *
 *  Created on: May 8, 2025
 *      Author: shaya
 */

#ifndef BSP_INC_BSP_HPP_
#define BSP_INC_BSP_HPP_

#define ARM_MATH_CM7

#include <cstdint>
#include <stdio.h>
#include <iostream>

//Interface BSP-------------------------------
class Bsp
{
public:
	virtual ~Bsp() = default;

protected:
	virtual void init() = 0;
};

#endif /* BSP_INC_BSP_HPP_ */
