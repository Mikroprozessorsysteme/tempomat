/*
* motorDriver.c
*
* Created: 16.04.2015 19:39:42
* Author: befrank doriemel
*/
#include "motorDriver.h"
#include <avr/io.h>


void setUp32MhzInternalOsc()
{
	//Oszillator auf 32Mhz stellen
	OSC.CTRL |= OSC_RC32MEN_bm;
	// Warten bis der Oszillator bereit ist
	while(!(OSC.STATUS & OSC_RC32MRDY_bm));
	//Schützt I/O Register, Interrupts werden ignoriert
	CCP = CCP_IOREG_gc;
	//aktiviert den internen Oszillator
	CLK.CTRL = (CLK.CTRL & ~CLK_SCLKSEL_gm) | CLK_SCLKSEL_RC32M_gc;
}

void initMotor() {
	// Port D4 auf output setzen
	PORTD.DIR |= (1 << 4);
	
	//pwm mode
	TCD1.CTRLB |= TC_WGMODE_SS_gc;
	// setze prescaler = clk
	TCD1.CTRLA |= TC_CLKSEL_DIV1_gc;
	// zählt bis 1000
	TCD1.PER = 1000;
	// Enable waveform output
	TCD1.CTRLB |= TC1_CCAEN_bm;
}

void setSpeed(int speed) {
	// Set the frequency
	TCD1.CCA = speed;
}

void setbrake(int brake) {
	// Set the frequency
	TCD1.CCB = brake;
}

void odemetrie() {

	PORTB.DIR &= ~(1 << 2);
	TCD0.CTRLD |=  TC_EVACT_CAPT_gc;
	
}
