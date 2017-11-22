/** 
 * header file for com port communication
 */

#ifndef SERIAL
#define SERIAL

#include "ALTypes.h"

#define PWM1_VALUE (0)
#define PWM2_VALUE (2)
#define PWM3_VALUE (4)
#define PWM4_VALUE (6)
#define PPM1_VALUE (8)
#define PPM2_VALUE (10)
#define GPIO_OUT   (12)
#define GPIO_IN    (12)

void initSerial(void);
void initRcvFrame();
uInt16 checksum(uInt8* data);
void buildFrame();
//void fillADC();
void readFrame();
void serialTask();
uInt16 getSerialUInt16(uInt8 buffPosition);
uInt8 getSerialUInt8(uInt8 buffPosition);

#endif
