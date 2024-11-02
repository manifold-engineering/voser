#ifndef PLOTWIDGET_H
#define PLOTWIDGET_H

#include "qcustomplot.h"
#include "solution.h"

#include <QWidget>
#include <QVBoxLayout>


struct PlotParameters{
    double xMin, xMax, yMin, yMax;
    unsigned int xPix, yPix;
};


class PlotWidget : public QWidget
{
    Q_OBJECT
private:
    QVBoxLayout *plotMainLayout;
    QCustomPlot *customPlot;
    QCPColorMap *colorMap;
    QTimer *zoomTimer;

    //for keeping view "square"
    double lastXMin;
    double lastXMax;
    double lastYMin;
    double lastYMax;
    void saveRanges();


protected:
    void resizeEvent(QResizeEvent *event) override;

public:
    explicit PlotWidget(QWidget *parent = nullptr);
    PlotParameters getPlotParameters();

public slots:
    void onZoomFinished();
    void replot(Solution data);

private slots:
    void onMouseWheel();
    void adjustAxes();
    void dataRangeChanged();
signals:
    void zoomChanged();
    void requestRecompute();


};

#endif // PLOTWIDGET_H
