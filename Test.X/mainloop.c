#include "ALTypes.h"
#include <p33FJ16MC304.h>
#include "mainloop.h"
#include "timer.h"

void mainLoop()
{
    while(1)
    {
        if(waitForSync())
        {
           serialTask();
        }
    }
}