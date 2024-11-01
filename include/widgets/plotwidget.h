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

public slots:
    void onZoomFinished();
    void replot(Solution data);

private slots:
    void onMouseWheel();
    void adjustAxes();


    void indicateChange();
signals:
    void zoomChanged();

};

#endif // PLOTWIDGET_H
