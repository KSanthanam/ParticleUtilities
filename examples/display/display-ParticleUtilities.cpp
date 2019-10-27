#include "Particle.h"

#include "ParticleUtilies.h"
#include "Grove_4Digit_Display.h"


const unsigned long TEST_RUN_PERIOD_MS = 10000;
unsigned long lastRun = 0;

#define CLK D2 //pins definitions for TM1637 and can be changed to other ports
#define DIO D3

TM1637 tm1637(CLK, DIO);
ParticleUtilities pu(true,POINT_ON, &tm1637);

void runTest();

void setup() {
	pu.init();	
}

void loop() {
	if (millis() - lastRun >= TEST_RUN_PERIOD_MS) {
		lastRun = millis();
		runTest();
	}
}

void runTest() {
	pu.display(10);
}