#include <p33Fxxxx.h>
#include "ALTypes.h"
#include "encoder.h"

speedStruct speeds;

sInt16 getSpeed(uInt8 num)
{
    switch(num)
    {
        case 1:
            return speeds.speedWheel1;
        case 2:
            return speeds.speedWheel2;
        case 3:
            return speeds.speedWheel3;
        default:
            break;
    }
}

void initEncoders(void)
{
    //init de la roue 1
    
}