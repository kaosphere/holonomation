#ifndef ENCODER_H
#define ENCODER_H

#include <p33Fxxxx.h>
#include "ALTypes.h"

typedef union __attribute__ ((packed)) {
  uInt8 speeds[6] __attribute__ ((aligned (16)));
  struct {
    sInt16 speedWheel1;
    sInt16 speedWheel2;
    sInt16 speedWheel3;
  };
}speedStruct;

sInt16 getSpeed(uInt8 num);


#endif