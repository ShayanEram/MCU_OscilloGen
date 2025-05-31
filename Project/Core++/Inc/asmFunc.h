/**
 * @file asmFunc.h
 * @brief Declaration of assembly functions for signal processing.
 * This header file declares the `firFilterASM` function, which performs FIR filtering on a signal using assembly language for optimized performance.
 * 
 * @author Shayan Eram
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
