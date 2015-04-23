/*
* motorDriver.c
*
* Created: 16.04.2015 19:39:42
* Author: befrank doriemel
*/
#include "motorDriver.h"
#include <avr/io.h>
#include <avr/interrupt.h>


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

void setBrake(int brake) {
	// Set the frequency
	TCD1.CCB = brake;
}


void initOdometrie() {
	// interruplevel festlegen
	PORTB.INTCTRL = 0x03;
	//Interrupt an PORTB PIN2 freigeben
	PORTB.INT0MASK = 0x04;
	//Interrupt auf fallende Flanke einstellen
	PORTB.PIN0CTRL = 0x02;
}

void odometrie() {
	
	/* pin 2 portB sollte über eventsystem an timer weitergeleitet werden
	input capture mode
	TCD0.CTRLD |=  TC_EVACT_CAPT_gc; */
}

ISR (PORTB_INT0_vect)
{	
	uint16_t after;
	uint16_t before = blueOsGetUs();
}
