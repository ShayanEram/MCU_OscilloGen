/**
 * @file MainCpp.cpp
 * @author Shayan Eram
 */

//Includes**************************************
#include "MainCpp.hpp"

#include "AnalyzerExtern.hpp"
#include "DacExtern.hpp"
#include "FuncAnalyzer.hpp"
#include "FuncGenerator.hpp"
#include "Lcd.hpp"
#include "SerialConnection.hpp"

//Defines***************************************
#define USE_EXTERN_ADC
#define USE_EXTERN_DAC
#define USE_CORDIC

constexpr uint8_t Major_Version{2};
constexpr uint8_t Minor_Version{0};

//Global Variables******************************
Bsp& bsp = Bsp::getInstance(); // Singleton!

FuncAnalyzer analyze(bsp);
FuncGenerator generate(bsp);
Lcd lcd(bsp, SLAVE_ADDRESS);
SerialCtn connection(bsp);

#ifdef USE_EXTERN_ADC
AnalyzerExt exAnalyze(bsp);
#endif

#ifdef USE_EXTERN_DAC
Dac exDac(bsp);
#endif

//Handles************************************
osThreadId_t funcGeneratorTaskHandle;
osThreadId_t funcAnalyzerTaskHandle;
osThreadId_t lcdTaskHandle;
osThreadId_t serialConnectionTaskHandle;

osMessageQueueId_t generatorQueue;
osMessageQueueId_t analyzerQueue;
osMessageQueueId_t lcdQueue;

//Init Function*******************************
extern "C" void System_Init(void)
{
	generatorQueue = osMessageQueueNew(4, sizeof(ReceivedData), NULL);
	analyzerQueue  = osMessageQueueNew(4, sizeof(ReceivedData), NULL);
	lcdQueue = osMessageQueueNew(4, sizeof(LcdMode), NULL);

	bsp.watchdogStart();
	bsp.registerDefaultCallbacks();
}

//RTOS Threads**********************************************************************
extern "C" void SerialConnctionTask(void *argument)
{
	MX_USB_DEVICE_Init();

	ReceivedData data;
	bool dataReceived{false};
	const uint32_t DELAY = 1000;
	bool interface{false};

	do
	{
		Status status = connection.interfaceHandshake(Major_Version, Minor_Version);

		if (status == Status::OK)
		{
			interface = true;
		}
		osDelay(pdMS_TO_TICKS(1000));

	} while (!interface);


	while(true)
	{
		bsp.dispatchEvents(); // process callbacks

		if (usbReceivedFlag)
		{
			data = connection.processReceivedData();
			usbReceivedFlag = false;
			dataReceived = true;

			if (data.mode == FUNCTION_GENERATOR_MODE)
			{
				osMessageQueuePut(generatorQueue, &data, 0, 0);

				LcdMode msg = LcdMode::Generator;
				osMessageQueuePut(lcdQueue, &msg, 0, 0);
			}
			else if (data.mode == OSCILLOSCOPE_MODE)
			{
				osMessageQueuePut(analyzerQueue,  &data, 0, 0);

				LcdMode msg = LcdMode::Analyzer;
				osMessageQueuePut(lcdQueue, &msg, 0, 0);
			}

		}

		bsp.watchdogRefresh();
		osDelay(10);
	}
}

extern "C" void FuncGeneratorTask(void *argument)
{
	ReceivedData data;

	while(true)
	{
		if (osMessageQueueGet(generatorQueue, &data, NULL, osWaitForever) == osOK)
		{
			if (data.mode == FUNCTION_GENERATOR_MODE)
			{
				generate.selectWaveform(data.generate.signalType);
				generate.setAmplitude(data.generate.amplitude);
				generate.setFrequency(data.generate.frequency);
				generate.generateWaveforms();
				generate.startWaveformOutput();
			}
			else
			{
				generate.stopWaveformOutput();
			}

		}
	}
}

extern "C" void FuncAnalyzerTask(void *argument)
{
	ReceivedData data;
	float32_t fftOutput;

	while(true)
	{
		if (osMessageQueueGet(analyzerQueue, &data, NULL, osWaitForever) == osOK)
		{
			if (data.mode == OSCILLOSCOPE_MODE)
			{
				if (data.analyze.stop)
				{
					analyze.stopAnalyzing();
				}
				else if (data.analyze.fft)
				{
					analyze.computeFFT(&fftOutput);

					#ifdef USE_EXTERN_ADC
                    	exAnalyze.requestFFT();
                    #endif
				}
				else
				{
					analyze.startAnalysing();
				}
			}
		}
	}
}

extern "C" __attribute__((noreturn)) void LcdTask(void *argument)
{

	lcd.init();
	lcd.sendString("LCD Online");

	LcdMode mode;

	while(true)
	{
		if (osMessageQueueGet(lcdQueue, &mode, NULL, osWaitForever) == osOK)
		{
			lcd.update(mode);
		}
	}
}

















