#include "Bsp.hpp"
#include "MainCpp.hpp"
#include "main.h"

#include "AnalyzerExtern.hpp"
#include "Bootloader.hpp"
#include "DacExtern.hpp"
#include "FuncAnalyzer.hpp"
#include "FuncGenerator.hpp"
#include "Lcd.hpp"
#include "SerialConnection.hpp"


#define USE_EXTERN_ADC
#define USE_EXTERN_DAC
#define USE_CORDIC

constexpr uint8_t Major_Version{1};
constexpr uint8_t Minor_Version{0};

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

__attribute__((noreturn)) void MainCpp()
{
	bsp.timPwmPulseCallback = []() { printf("Default TIM PWM Pulse Completed!\n"); };
	bsp.spiTxCallback = []() { printf("Default SPI TX Completed!\n"); };
	bsp.spiRxCallback = []() { printf("Default SPI RX Completed!\n"); };
	bsp.uartTxCallback = []() { printf("Default UART TX Completed!\n"); };
	bsp.uartRxCallback = [](uint8_t data) { printf("Default UART RX Data: %d\n", data); };
	bsp.adcConvCallback = []() { printf("Default ADC Conversion Completed!\n"); };
	bsp.adcHalfConvCallback = []() { printf("Default ADC Half Conversion Completed!\n"); };
	bsp.timPeriodCallback = []() { printf("Default Timer Period Elapsed!\n"); };
	bsp.dacConvCallback = []() { printf("Default DAC Conversion Completed!\n"); };
	bsp.dacHalfConvCallback = []() { printf("Default DAC Half Conversion Completed!\n"); };
	bsp.i2cTxCallback = []() { printf("Default I2C TX Completed!\n"); };
	bsp.i2cRxCallback = []() { printf("Default I2C RX Completed!\n"); };

	ReceivedData data;
	bool dataReceived{false};
	float32_t fftOutput;
	const uint32_t DELAY = 1000;


	bool interface{false};
	do
	{
		Status status = connection.interfaceHandshake(Major_Version, Minor_Version);
		if (status == Status::OK) {
			interface = true;
		}
		bsp.delay(DELAY);

	} while (!interface);


	lcd.init();
	lcd.sendString("LCD Online");

	bsp.watchdogStart();

	while(true)
	{
		if(usbReceivedFlag)
		{
			data = connection.processReceivedData();
			usbReceivedFlag = false;
			dataReceived = true;

			if(data.mode == FUNCTION_GENERATOR_MODE)
			{
				generate.selectWaveform(data.generate.signalType);
				generate.setAmplitude(data.generate.amplitude);
				generate.setFrequency(data.generate.amplitude);
				generate.generateWaveforms();
				generate.startWaveformOutput();
			}
			else if(data.mode == OSCILLOSCOPE_MODE)
			{
				generate.stopWaveformOutput();

				#ifdef USE_EXTERN_DAC
				exDac.noOperation();
				#endif

				analyze.startAnalysing();
			}
			else if(data.mode == UPDATE_MODE)
			{
				printf("DEV_ERROR: UPDATE Mode not implemented!\n");
				dataReceived = false;
			}
			else
			{
				printf("DEV_ERROR: Incorrect mode selected!\n");
				dataReceived = false;
			}
		}
		else if(dataReceived)
		{
			if(data.mode == FUNCTION_GENERATOR_MODE)
			{
				generate.startWaveformOutput();

				#ifdef USE_EXTERN_DAC
				exDac.voltageToCode(3.3, -6, 6);
				#endif
			}
			else if(data.mode == OSCILLOSCOPE_MODE)
			{
				if(data.analyze.stop)
				{
					analyze.stopAnalyzing();
				}
				else if(data.analyze.fft)
				{
					analyze.computeFFT(&fftOutput);

					#ifdef USE_EXTERN_ADC
					exAnalyze.requestFFT();
					#endif
				}
			}
			else if(data.mode == UPDATE_MODE)
			{
				printf("DEV_ERROR: UPDATE Mode not implemented!\n");
			}
			else
			{
				printf("DEV_ERROR: Incorrect mode selected!\n");
			}
		}

		bsp.watchdogRefresh();
	}
}
