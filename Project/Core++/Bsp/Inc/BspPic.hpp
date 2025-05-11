/*
 * BspPic.hpp
 *
 *  Created on: May 8, 2025
 *      Author: shaya
 */

#ifndef BSP_INC_BSPPIC_HPP_
#define BSP_INC_BSPPIC_HPP_

#include <Bsp.hpp>

class BspPic final : public Bsp {
public:
	explicit BspPic() = default;
	~BspPic() = default;

private:
	void init() override;
};

#endif /* BSP_INC_BSPPIC_HPP_ */
