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

constexpr uint8_t Major_Version{1};
constexpr uint8_t Minor_Version{0};

Bsp bsp;

FuncAnalyser analyze(bsp);
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
	bool interface{false};
	do
	{
		Status status = connection.interfaceHandshake(Major_Version, Minor_Version);
		if (status == Status::OK) {
			interface = true;
		}
		bsp.delay(1000);

	} while (!interface);

	ReceivedData data = connection.processReceivedData();
	lcd.init();
	lcd.sendString("LCD Online");


	while(true)
	{
		if(usbReceivedFlag)
		{
			data = connection.processReceivedData();
			generate.setAmplitude(data.amplitude);
			generate.setFrequency(data.frequency);
		}
		else
		{
			generate.startWaveformOutput();
			analyze.startAnalysing();

			#ifdef USE_EXTERN_ADC
			exAnalyze.requestFFT();
			#endif

			#ifdef USE_EXTERN_DAC
			exDac.voltageToCode(3.3, -6, 6);
			#endif
		}
	}
}
