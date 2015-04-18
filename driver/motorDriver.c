/*
 * motorDriver.c
 *
 * Created: 16.04.2015 19:39:42
 *  Author: befrank
 */ 

void setUp32MhzInternalOsc()
{
    OSC_CTRL |= OSC_RC32MEN_bm; //Setup 32Mhz crystal
     
    while(!(OSC_STATUS & OSC_RC32MRDY_bm));
     
    CCP = CCP_IOREG_gc; //Trigger protection mechanism
    CLK_CTRL = CLK_SCLKSEL_RC32M_gc; //Enable internal  32Mhz crystal
     
     
}

void initMotor() {
	   // Port D4 auf output setzen
	   DDRD   |= (1 << 4);
	   //pwm mode
	   CTRLB  |= TC_WGMODE_SS_gc;
	   // setze prescaler = clk
	   CTRLA |= 1;
	   // zählt bis 1000
	   TCD1.PER = 1000;
	  
	   
}

void setSpeed(int speed) {
	 speed = 500;
	 TCD1.CCA = speed;
}