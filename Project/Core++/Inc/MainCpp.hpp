/**
 * @file MainCpp.hpp
 * @brief Declaration of the MainCpp function.
 * This function serves as the entry point for the C++ application, initializing necessary components and starting the main loop.
 * 
 * @author Shayan Eram
 */
#ifndef INC_MAINCPP_HPP_
#define INC_MAINCPP_HPP_

// INCLUDES
extern "C"
{
#include "main.h"
}

#include "Bsp.hpp"

#ifdef __cplusplus
extern "C" {
#endif

// HANDLES
extern osThreadId_t funcGeneratorTaskHandle;
extern osThreadId_t funcAnalyzerTaskHandle;
extern osThreadId_t lcdTaskHandle;
extern osThreadId_t serialConnectionTaskHandle;

// FUNCTIONS
void System_Init(void);

void FuncGeneratorTask(void *argument);
void FuncAnalyzerTask(void *argument);
void LcdTask(void *argument);
void SerialConnctionTask(void *argument);

#ifdef __cplusplus
}
#endif


#endif /* INC_MAINCPP_HPP_ */
