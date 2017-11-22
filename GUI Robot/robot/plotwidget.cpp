#include "plotwidget.h"

PlotWidget::PlotWidget(QWidget *parent) :
    QWidget(parent)
{

    QColor blanc(250,250,250);
    QColor bleu(20,20,250);

    //graphe
    plot = new QwtPlot(this);
    plot->setAxisScale(2,0,2,0.25);
    plot->setAxisScale(0,0,200,20);
    plot->setCanvasBackground(blanc);
    plot->setFixedSize(400,300);

    // grid
    QwtPlotGrid *grid = new QwtPlotGrid;
    grid->enableXMin(true);
    grid->setMajPen(QPen(Qt::gray, 0, Qt::DotLine));
    grid->setMinPen(QPen(Qt::gray, 0 , Qt::DotLine));
    grid->attach(plot);

    /*QPainter * painter = new QPainter;
    painter->setBrush(bleu);*/

    curve = new QwtPlotCurve;
    curve->attach(plot);

    //setLayout(layout);

    for(int i=0;i<CURVE_LEN;i++)
    {
        speedCurve[i]=i/6.666;
        timeVector[i]=i*0.01;
    }
    curve->setSamples(timeVector,speedCurve,CURVE_LEN);
    plot->replot();
}

void PlotWidget::update(Robot* bot)
{
    for(int i=CURVE_LEN-1;i>0;i--)
    {
        speedCurve[i] = speedCurve[i-1]; // décalage de toutes les cases du tableau pour faire évoluer la courbe
    }
    speedCurve[0] = bot->getSpeedWheel(1);
    curve->setSamples(timeVector,speedCurve,CURVE_LEN);//,timeVector,CURVE_LEN);
    plot->replot();
}
