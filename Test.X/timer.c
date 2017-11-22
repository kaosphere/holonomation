 #include <p33Fxxxx.h>
 #include "pll.h"
 #include "ALTypes.h"

 /**
 * Timer 1 init for 1ms interrupt
 */
void initTMR1(void)
{
	T1CON = 0x0020;			// internal Tcy/64 clock
	TMR1 = 0;
	PR1 = FCY/63290;				// 1 ms interrupts for 40 MIPS
	T1CONbits.TON = 1;		// turn on timer 1
	IEC0bits.T1IE = 1; // Enable interrupt
	return;
}

volatile uInt8 gFiftyMsTemp=0;
volatile uInt8 gTime=0;
volatile uInt8 gSync = 0;

/**
 * Timer 1 every ms...
 */
void __attribute__((__interrupt__, __no_auto_psv__)) _T1Interrupt (void)
{
	IFS0bits.T1IF = 0;
	// 1ms tempo
	gFiftyMsTemp += 1;
	if (gFiftyMsTemp == 10)
	{
	  gFiftyMsTemp = 0;
	  gSync = 1;
	}
  gTime++;
}

uInt8 waitForSync(void)
{
  if (gSync)
  {
    gSync = 0;
    return 1;
  }
  return 0;
}


/**
 * Timer 2 init for 1us interrupt
 */
void initTMR2(void)
{
	T2CON = 0x0000;			// internal Tcy/1 clock
	TMR2 = 0;
	PR2 = 40;				// 1 us interrupts for 40 MIPS
	T2CONbits.TON = 1;		// turn on timer 2
	IEC0bits.T2IE = 1; // Enable interrupt
	return;
}
