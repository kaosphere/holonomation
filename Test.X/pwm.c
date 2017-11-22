#include <p33FJ16MC304.h>
#include "pwm.h"
#include "pll.h"
//#include "serial.h"

#define MAX_PWM (3)
#define FPWM (60000)  //PWM frequency : 60KHz

void initPWM()
{
    P1TCONbits.PTEN = 0;  // disable PWM
    P2TCONbits.PTEN = 0;  // disable PWM
    P1OVDCON = 0x0002;	// Disable all PWM outputs.
    P2OVDCON = 0x0002;	// Disable all PWM outputs.
    P1DTCON1 = 0;	// 0 ns of dead time
    P2DTCON1 = 0;	// 0 ns of dea0d time
    P1TPER = (FCY/(FPWM >> 1)) - 1 ;	// Compute Period based on CPU speed and required PWM frequency (see defines)
    P2TPER = (FCY/(FPWM >> 1)) - 1 ;	// Compute Period based on CPU speed and required PWM frequency (see defines)
    P1DC1 = P1TPER*2+1;	// Initialize as 0 voltage
    P1DC2 = P1TPER*2+1;	// Initialize as 0 voltage
    P1DC3 = P1TPER*2+1;	// Initialize as 0 voltage
    P2DC1 = P2TPER*2+1;	// Initialize as 0 voltage

    PWM1CON1 = 0x0447;
    PWM2CON1 = 0x0010;
    PWM1CON2 = 0x0000;	// 1:1 postscale values on special event
    PWM2CON2 = 0x0000;	// 1:1 postscale values,

    P1SECMPbits.SEVTCMP = P1TPER-3;	// Enable triggering for just at the end of the PWM
    P2SECMPbits.SEVTCMP = 0;	// triggering on 2nd pwm is not use
    P1SECMPbits.SEVTDIR = 0;   // change time base direction for ADC trigger : event on downward counting
    P2SECMPbits.SEVTDIR = 0;   // change time base direction for ADC trigger : event on downward counting

    /* PWM I/O pin controlled by PWM Generator */
    P1OVDCONbits.POVD3H=1;
    P1OVDCONbits.POVD2H=1;
    P1OVDCONbits.POVD1H=1;
    P1OVDCONbits.POVD3L=0;
    P1OVDCONbits.POVD2L=1;
    P1OVDCONbits.POVD1L=1;
    P2OVDCONbits.POVD1H=1;
    P2OVDCONbits.POVD1L=0;


    P1TCON = 0x8002;  // enable PWM
    P2TCON = 0x8002;  // enable PWM
}


void applyPWM(sInt16 pValue, uInt8 motorNumber)
{
// vitesse max : P1DC1 = 0; vitesse min : P1DC1 = P1TPER*2+1;


  sInt16 pwmValue;
  sInt32 PWMMoteur = (sInt32)pValue+(sInt32)32768;

  if(PWMMoteur >= 32768)
  {
    pwmValue = PWMMoteur-32767;
  }
  else
  {
    pwmValue = 32767-PWMMoteur;
  }
  pwmValue = 32768-pwmValue;

  switch(motorNumber)
  {
  case 0 :
    //latb14 => sens du moteur
    if(PWMMoteur >= 32768)
    {
      LATBbits.LATB14=1;
    }
    else
    {
      LATBbits.LATB14=0;
    }
    P1DC1 = ((sInt32)pwmValue*(sInt32)P1TPER)/16384;
    break;
  case 1 :
    //latb12 => sens du moteur
    if(PWMMoteur >= 32768)
    {
      LATBbits.LATB12=1;
    }
    else
    {
      LATBbits.LATB12=0;
    }
    P1DC2 = ((sInt32)pwmValue*(sInt32)P1TPER)/16384;
    break;
  case 2 :
    P1DC3 = ((sInt32)pwmValue*(sInt32)P1TPER)/16384;
    break;
  case 3 :
    P2DC1 = ((sInt32)pwmValue*(sInt32)P2TPER)/16384;
    break;
  default :
    break;
  }
}


/*void pwmTask()
{
  uInt8 i;
  for(i=0;i<MAX_PWM;i++)
  {
    applyPWM(getSerialUInt16(i * 2), i);
    //applyPWM(32000,i);
  }
}*/
