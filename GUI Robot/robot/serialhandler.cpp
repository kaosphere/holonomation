#include "serialhandler.h"
#include <termios.h>
#include <string>
#include <unistd.h> 	/* UNIX standard function definitions */
#include <stdio.h>
#include <fcntl.h> 		/* File control definitions */
#include <errno.h>

using namespace std;

SerialHandler::SerialHandler()
{
}

SerialHandler::SerialHandler(Robot* b)
{
    bot = b;
}

bool SerialHandler::initSerial()
{
    struct termios options;	// Structure of options for the serial port
    char error[50];
    const char* port = "/dev/ttyUSB0";

    fd = open(port, O_RDWR | O_NOCTTY);

    if (fd == -1)	// Couldn't open the port
    {
            sprintf(error, "initPort: Unable to open %s - ", port);
            perror(error);
    }
    else
    {
            fcntl(fd, F_SETFL, ~O_APPEND | O_NONBLOCK);	// Append data in file descriptor, and make it non blocking
    }

    // Get the current options for the serial port
    tcgetattr(fd, &options);

    /*
     * Control options
     */

    cfsetispeed(&options, B115200);	// Set input baudrate
    cfsetospeed(&options, B115200);	// Set output baudrate

    /*
     * Set options values to get raw mode
     */

    cfmakeraw(&options);

    // Set new options
    tcsetattr(fd, TCSANOW, &options);

    // Flush I/O buffer
    tcflush(fd, TCIOFLUSH);

    printf("\nport well initialized\n");

    return true;
}

void SerialHandler::serialTask()
{
    initSerial();
    //main loop for serial

    //serialSend();
    while(1)
    {
        serialRCV();
    }
}

uInt8 fillNext = 0;

void SerialHandler::serialRCV()
{
    uInt16 cs = 0;
    uInt16 i,j;
    uInt16 tmpX = 0;
    int cnt = 0;

    if(fillNext == 1)
    {
      rcvBuffer[0] = 0x55;
      rcvBuffer[1] = 0xFF;
      rcvBuffer[2] = 0x22;
      rcvBuffer[3] = 0x33;
      cnt = 4;
      fillNext = 0;
    }
    do{
        read(fd, &rcvBuffer[cnt++] , 1);			// Read 1 char from serial port

        if ( cnt == 1 && rcvBuffer[cnt-1] != 0x55){		// Detect SOF first byt
          cnt = 0;}

        if ( cnt == 2 && rcvBuffer[cnt-1] != 0xFF){		// Detect SOF second byte
          cnt = 0;}

        if ( cnt == 3 && rcvBuffer[cnt-1] != 0x22){		// Detect SOF third byte
          cnt = 0;}

        if ( cnt == 4 && rcvBuffer[cnt-1] != 0x33){		// Detect SOF fourth byte
          cnt = 0;}

        if ( cnt > 24 -3 && rcvBuffer[cnt-1] == 0xFF && rcvBuffer[cnt-2] == 0x99 )	// Detect EOF : if counter match frame length byte (globalFrame[2]) and last bytes values are 0x0A 0x0A (end of sensor) or 0x99 0xFF (end of frame), then break
        {
            break;
        }
        if ( cnt > 24 -5 && rcvBuffer[cnt-1] == 0x33 && rcvBuffer[cnt-2] == 0x22 && rcvBuffer[cnt-3] == 0xFF && rcvBuffer[cnt-4] == 0x55 )	// Detect EOF : if counter match frame length byte (globalFrame[2]) and last bytes values are 0x0A 0x0A (end of sensor) or 0x99 0xFF (end of frame), then break
        {
            fillNext = 1;
            break;
        }
    }while(1);
    //verify checksum //TODO: mettre dans une fonction séparée
    cs = 0;
    for(i=4;i<20;i++)
    {
        cs ^= rcvBuffer[i];
        tmpX = cs & 0x8000;
        if(tmpX)
        {
            cs <<= 1;
            cs += 1;
        }
        else
        {
            cs <<= 1;
        }
    }
    if(cs == rcvBuffer[CRC_BYTE1] * 256 + rcvBuffer[CRC_BYTE2])
    {
        j = 0;
        for(i = 4; i < 20; i++)
        {
            //we get only the data in the frame
            rcvData[j] = rcvBuffer[i];
            j++;
        }
        bot->setSpeedWheel(rcvData[0] * 256 + rcvData[1],1);
        bot->setSpeedWheel(rcvData[2] * 256 + rcvData[3],2);
        bot->setSpeedWheel(rcvData[4] * 256 + rcvData[5],3);
    }

}


