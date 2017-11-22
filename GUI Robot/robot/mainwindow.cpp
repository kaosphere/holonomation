#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <stdio.h>
#include <QTimer>
#include <QGroupBox>

MainWindow::MainWindow(QWidget *parent) :
    QFrame(parent)
{
    //ui->setupUi(this);
    QGroupBox *groupBox1 = new QGroupBox(tr("Vitesse roue 1"));
    QGroupBox *groupBox2 = new QGroupBox(tr("Vitesse roue 2"));
    QGroupBox *groupBox3 = new QGroupBox(tr("Vitesse roue 3"));

    QVBoxLayout * vbox1 = new QVBoxLayout;
    QVBoxLayout * vbox2 = new QVBoxLayout;
    QVBoxLayout * vbox3 = new QVBoxLayout;

    //vbox1->addStretch();
    //vbox2->addStretch();
    //vbox3->addStretch();

    speedPlot1 = new PlotWidget(this);
    speedPlot2 = new PlotWidget(this);
    speedPlot3 = new PlotWidget(this);

    vbox1->addWidget(speedPlot1);
    vbox2->addWidget(speedPlot2);
    vbox3->addWidget(speedPlot3);

    groupBox1->setLayout(vbox1);
    groupBox2->setLayout(vbox2);
    groupBox3->setLayout(vbox3);

    QHBoxLayout * layout = new QHBoxLayout;

    layout->addWidget(groupBox1);
    layout->addWidget(groupBox2);
    layout->addWidget(groupBox3);

    setLayout(layout);

    startTimer(10);
}

MainWindow::~MainWindow()
{
    //delete ui;
}

void MainWindow::setRobot(Robot *b)
{
    bot = b;
}


bool MainWindow::isTimerActive()
{
    return timer->isActive();
}

void MainWindow::timerEvent(QTimerEvent *event)
{
    speedPlot1->update(bot);
    speedPlot2->update(bot);
    speedPlot3->update(bot);
}
