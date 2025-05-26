/*
 * asmFunc.h
 *
 *  Created on: May 26, 2025
 *      Author: shaya
 */

#ifndef INC_ASMFUNC_H_
#define INC_ASMFUNC_H_

#include <cstdint>

#ifdef __cplusplus
extern "C" {
#endif

extern int16_t firFilterASM(const int16_t* signal, const int16_t* coeffs, int length);

#ifdef __cplusplus
}
#endif

#endif /* INC_ASMFUNC_H_ */
