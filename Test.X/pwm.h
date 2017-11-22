#ifndef PWM
#define PWM

#include "ALTypes.h"


void initPWM();
void applyPWM(sInt16 pValue, uInt8 motorNumber);
void pwmTask();


#endif
