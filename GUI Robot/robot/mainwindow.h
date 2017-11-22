#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QVector>
#include <QColor>
#include <QHBoxLayout>
#include "robot.h"
#include <ALTypes.h>
#include "plotwidget.h"


namespace Ui {
    class MainWindow;
}

class MainWindow : public QFrame
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void setRobot(Robot* b);

    void timerEvent(QTimerEvent *event);

    bool isTimerActive();

private:

    //Ui::MainWindow *ui;
    PlotWidget* speedPlot1;
    PlotWidget* speedPlot2;
    PlotWidget* speedPlot3;
    Robot* bot;

    QTimer *timer;
};

#endif // MAINWINDOW_H
