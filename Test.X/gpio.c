 #include "gpio.h"
 #include "ALTypes.h"
 #include "serial.h"
 #include <p33fxxxx.h>

 void gpioTask(void)
 {
   uInt8 gpio;
   gpio = getSerialUInt8(GPIO_OUT);

   if(gpio & 0b00000001)
   {
   LATAbits.LATA3 = 1;
   }
   if(gpio & 0b00000010)
   {
   LATAbits.LATA2 = 1;
   }
   if(gpio & 0b00000100)
   {
   LATAbits.LATA4 = 1;
   }
   if(gpio & 0b00001000)
   {
   LATAbits.LATA8 = 1;
   }

   if(!(gpio & 0b00000001))
   {
   LATAbits.LATA3 = 0;
   }
   if(!(gpio & 0b00000010))
   {
   LATAbits.LATA2 = 0;
   }
   if(!(gpio & 0b00000100))
   {
   LATAbits.LATA4 = 0;
   }
  if(!(gpio & 0b00001000))
  {
  LATAbits.LATA8 = 0;
  }
 }
