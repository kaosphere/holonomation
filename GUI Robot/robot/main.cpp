#include <QtGui/QApplication>
#include "mainwindow.h"
#include "serialhandler.h"
#include "robot.h"


#include <pthread.h>


// Helper function to bounce into the SerialHandler object
void *startSerialThread(void *sh)
{
    SerialHandler *sHdl = static_cast<SerialHandler *>(sh);
    sHdl->serialTask();
}



//main
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    Robot* bot = new Robot;
    SerialHandler* sh = new SerialHandler(bot);

    QApplication::setStyle("windows");

    w.setMinimumSize(QSize(1300,360));
    w.setMaximumSize(QSize(1300,360));
    w.setWindowTitle("RoBot");
    w.setRobot(bot);

    pthread_t serial;

    if (pthread_create(&serial, NULL, startSerialThread, sh))
    {
        perror("pthread_create");
        exit(EXIT_FAILURE);
    }

    w.show();

    return a.exec();
}
