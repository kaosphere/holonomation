#ifndef SERIALHANDLER_H
#define SERIALHANDLER_H

#include <ALTypes.h>
#include "robot.h"

#define SIZE_FRAME 24
#define DATA_SIZE 16
#define CRC_BYTE1 SIZE_FRAME - 4
#define CRC_BYTE2 SIZE_FRAME - 3

class SerialHandler
{
    private:
        uInt8 sendBuffer[SIZE_FRAME];
        uInt8 rcvBuffer[SIZE_FRAME];
        uInt8 rcvData[DATA_SIZE];

        int fd;			// Serial file descriptor

        Robot* bot;

    public:
        SerialHandler();
        SerialHandler(Robot* b);
        //serial port handle functions
        bool initSerial();
        void serialTask();
        void serialSend();
        void serialRCV();

        //accesseurs pour les buffers
        void setSendBuffer(uInt8* sdBuf);
        uInt8* getSendBuffer();
        void setRcvBuffer(uInt8* rcvBuf);
        uInt8* getRcvdBuffer();
        uInt8* getRcvData();

};

#endif // SERIALHANDLER_H
