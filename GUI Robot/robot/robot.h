#ifndef ROBOT_H
#define ROBOT_H

#include <ALTypes.h>

using namespace std;

class Robot
{
    private:
        sInt16 speedWheel1;
        sInt16 speedWheel2;
        sInt16 speedWheel3;

        sInt16 posWheel1;
        sInt16 posWheel2;
        sInt16 posWheel3;

        sInt16 posX;
        sInt16 posY;

    public:
        Robot();
        void setSpeedWheel(sInt16 speed, uInt8 wheel);  //accesseur pour les vitesses
        void setPosWheel(sInt16 pos, uInt8 wheel);      //accesseur pour les positions
        void setPosX(sInt16 pos);
        void setPosY(sInt16);
        sInt16 getSpeedWheel(uInt8 wheel);
        sInt16 getPosWheel(uInt8 wheel);
        sInt16 getPosX();
        sInt16 getPosY();
};


#endif // ROBOT_H
