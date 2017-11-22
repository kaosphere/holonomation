#include <p33FJ16MC304.h>
#include "pll.h"
#include "init.h"
#include "mainloop.h"
#include "timer.h"

_FBS(BSS_NO_FLASH & BWRP_WRPROTECT_OFF)
_FGS(GSS_OFF & GCP_OFF & GWRP_OFF)
_FOSCSEL(FNOSC_FRCPLL & IESO_ON)
_FOSC(FCKSM_CSDCMD & IOL1WAY_OFF & OSCIOFNC_ON & POSCMD_NONE)
//_FOSC( FCKSM_CSDCMD & IOL1WAY_OFF & OSCIOFNC_ON  & POSCMD_XT )
_FWDT(FWDTEN_OFF & WINDIS_OFF)
_FPOR(PWMPIN_OFF & HPOL_ON & LPOL_ON & ALTI2C_OFF & FPWRT_PWR16)
_FICD(ICS_PGD3 & JTAGEN_ON)

// This config bit is not in .h macro ...
// And also the linker script (gld) file has been change
//#define _RESERVED(x) __attribute__((section("__RESERVED.sec,code"))) int _RESERVED = (x);
// FFC1 set pgm3 pcd3 and no debug FF41 for debug this configuration byte is ignored by mplab when programing
// it is for the hex file that is send to the bootloader
//_RESERVED(0xFFC1)

int main(void) {
  initPorts();
  initClock();
  initSerial();
  initTMR1();

  mainLoop();
  
  return 0;
}