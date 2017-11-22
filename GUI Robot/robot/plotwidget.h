#ifndef PLOTWIDGET_H
#define PLOTWIDGET_H

#include <QWidget>
#include "robot.h"
#include <qwt_plot_curve.h>
#include <qwt_plot.h>
#include <qwt_plot_grid.h>

#define CURVE_LEN 200

class PlotWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PlotWidget(QWidget *parent = 0);

    void update(Robot* bot);


private:
    QwtPlotCurve* curve;
    QwtPlot* plot;

    double speedCurve[CURVE_LEN];

    double timeVector[CURVE_LEN];

};

#endif // PLOTWIDGET_H
