#include <p33Fxxxx.h>

void initClock(void)
{

	//PLLFBD = 40;
	PLLFBD = 41;
	CLKDIVbits.PLLPOST = 0; // N1 = 2 : 80Mhz

	CLKDIVbits.PLLPRE = 0; // N2 = 2
	OSCTUN = 0;
	RCONbits.SWDTEN = 0; // Disable wath dog...
	while (OSCCONbits.LOCK != 1) {}; // Issue : block the debug ...
}
