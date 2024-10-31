#ifndef PLOTWIDGET_H
#define PLOTWIDGET_H

#include "qcustomplot.h"
#include "solution.h"

#include <QWidget>
#include <QVBoxLayout>

class PlotWidget : public QWidget
{
    Q_OBJECT
private:
    QVBoxLayout *plotMainLayout;
    QCustomPlot *customPlot;
    QCPColorMap *colorMap;

public:
    explicit PlotWidget(QWidget *parent = nullptr);

public slots:
    void replot(Solution data);
    void indicateChange();

};

#endif // PLOTWIDGET_H
