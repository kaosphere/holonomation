#include "robot.h"
#include <ALTypes.h>

using namespace std;

//constructeur
Robot::Robot()
{
    speedWheel1 = 0;
    speedWheel2 = 0;
    speedWheel3 = 0;

    posWheel1 = 0;
    posWheel2 = 0;
    posWheel3 = 0;
}

//accesseurs
void Robot::setSpeedWheel(sInt16 speed, uInt8 wheel)
{
    switch (wheel)
    {
        case 1:
            speedWheel1 = speed;
        case 2:
            speedWheel2 = speed;
        case 3:
            speedWheel3 = speed;
        default:
            break;
    }
}

void Robot::setPosWheel(sInt16 pos, uInt8 wheel)
{
    switch (wheel)
    {
        case 1:
            posWheel1 = pos;
        case 2:
            posWheel2 = pos;
        case 3:
            posWheel3 = pos;
        default:
            break;
    }
}

void Robot::setPosX(sInt16 pos)
{
    posX = pos;
}

void Robot::setPosY(sInt16 pos)
{
    posY = pos;
}

sInt16 Robot::getSpeedWheel(uInt8 wheel)
{
    switch (wheel)
    {
        case 1:
            return speedWheel1;
        case 2:
            return speedWheel2;
        case 3:
            return speedWheel3;
        default:
            break;
    }
}

sInt16 Robot::getPosWheel(uInt8 wheel)
{
    switch (wheel)
    {
        case 1:
            return posWheel1;
        case 2:
            return posWheel2;
        case 3:
            return posWheel3;
        default:
            break;
    }
}

sInt16 Robot::getPosX()
{
    return posX;
}

sInt16 Robot::getPosY()
{
    return posY;
}
