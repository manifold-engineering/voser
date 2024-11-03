#include "widgets/plotwidget.h"

#include <iostream>
#include <cmath>

extern double x_min;
extern double x_max;
extern double y_min;
extern double y_max;

extern int x_samples;
extern int y_samples;

PlotWidget::PlotWidget(QWidget *parent) : QWidget(parent)
{
    plotMainLayout = new QVBoxLayout(this);
    customPlot = new QCustomPlot(this);
    this->setLayout(plotMainLayout);
    plotMainLayout->addWidget(customPlot);



    // configure axis rect:
    customPlot->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom); // this will also allow rescaling the color scale by dragging/zooming
    customPlot->axisRect()->setupFullAxesBox(true);
    customPlot->xAxis->setLabel("x [m]");
    customPlot->yAxis->setLabel("y [m]");
    //customPlot->yAxis->setScaleRatio(customPlot->xAxis, 1.0);

    // set up the QCPColorMap:
    colorMap = new QCPColorMap(customPlot->xAxis, customPlot->yAxis);


    //std::cout << "x: " << x_samples << ", y: " << y_samples << std::endl;
    colorMap->data()->setSize(x_samples, y_samples);

    colorMap->data()->setRange(QCPRange(x_min, x_max), QCPRange(y_min, y_max)); // and span the coordinate range -4..4 in both key (x) and value (y) dimensions

    // add a color scale:
    QCPColorScale *colorScale = new QCPColorScale(customPlot);
    customPlot->plotLayout()->addElement(0, 1, colorScale); // add it to the right of the main axis rect
    colorScale->setType(QCPAxis::atRight); // scale shall be vertical bar with tick/axis labels right (actually atRight is already the default)
    colorMap->setColorScale(colorScale); // associate the color map with the color scale
    colorScale->axis()->setLabel("SPL [dB]");

    // set the color gradient of the color map to one of the presets:
    QCPColorGradient plotGradient = QCPColorGradient::gpHot;
    plotGradient.setNanHandling(QCPColorGradient::nhNanColor);
    plotGradient.setNanColor(QColor("blue"));
    colorMap->setGradient(plotGradient);

    // we could have also created a QCPColorGradient instance and added own colors to
    // the gradient, see the documentation of QCPColorGradient for what's possible.

    // rescale the data dimension (color) such that all data points lie in the span visualized by the color gradient:
    //colorMap->rescaleDataRange();

    // make sure the axis rect and color scale synchronize their bottom and top margins (so they line up):
    QCPMarginGroup *marginGroup = new QCPMarginGroup(customPlot);
    customPlot->axisRect()->setMarginGroup(QCP::msBottom|QCP::msTop, marginGroup);
    colorScale->setMarginGroup(QCP::msBottom|QCP::msTop, marginGroup);

    // rescale the key (x) and value (y) axes so the whole color map is visible:
    customPlot->rescaleAxes();

    // Set up the timer with a 500ms interval
    zoomTimer = new QTimer(this);
    zoomTimer->setInterval(500);
    zoomTimer->setSingleShot(true); // Only emit timeout once after stopping

    lastXMax =x_max;
    lastXMin =x_min;
    lastYMax =y_max;
    lastYMin =y_min;

    //zooming detection
    connect(customPlot, &QCustomPlot::mouseWheel,
            this, &PlotWidget::onMouseWheel);
    connect(zoomTimer, &QTimer::timeout,
            this, &PlotWidget::onZoomFinished);

    // Set both x and y axes to zoom together
    customPlot->axisRect()->setRangeZoom(Qt::Horizontal | Qt::Vertical);

    // Connect to the mouse wheel event to control zooming behavior
    connect(customPlot, &QCustomPlot::mouseWheel, this, [=](QWheelEvent *event) {
        // Check if the mouse is within the plot area (excluding the axes)
        if (customPlot->viewport().contains(event->position().toPoint()) &&
            customPlot->axisRect()->rect().contains(event->position().toPoint())) {
            // Allow zooming both axes within the plot area
            customPlot->axisRect()->setRangeZoom(Qt::Horizontal | Qt::Vertical);
        } else {
            // Disable zooming on individual axes outside the plot area
            customPlot->axisRect()->setRangeZoom(Qt::Orientations());
        }
    });

    //debug range replotting
    connect(customPlot, &QCustomPlot::mouseRelease,
            this, &PlotWidget::dataRangeChanged);


    connect(this, &PlotWidget::zoomChanged,
            this, &PlotWidget::dataRangeChanged);

}



PlotParameters PlotWidget::getPlotParameters()
{
    PlotParameters parameters;

    QCPRange xRange = customPlot->xAxis->range(); // X-axis visible range
    QCPRange yRange = customPlot->yAxis->range(); // Y-axis visible range

    parameters.xMin = xRange.lower;
    parameters.xMax = xRange.upper;
    parameters.yMin = yRange.lower;
    parameters.yMax = yRange.upper;

    QCPAxisRect *axisRect = colorMap->keyAxis()->axisRect();
    parameters.xPix = axisRect->width();
    parameters.yPix = axisRect->height();

    return parameters;
}

void PlotWidget::replot(Solution data){
    std::cout << data.getM() << ", " << data.getN() << std::endl;
    // now we assign some data, by accessing the QCPColorMapData instance of the color map:

    colorMap->data()->setSize(data.getM(),data.getN());            // Set the grid size
    colorMap->data()->setRange(QCPRange(data.xMin, data.xMax), QCPRange(data.yMin, data.yMax));

    for (unsigned int xIndex=0; xIndex<data.getM(); ++xIndex)
    {
      for (unsigned int yIndex=0; yIndex<data.getN(); ++yIndex)
      {
        //early debug
        //std::cout << xIndex << ", " << yIndex << std::endl;
        colorMap->data()->setCell(xIndex, yIndex, data(xIndex, yIndex));
      }
    }
    //  std::cout << "data do plotu nastavena" << std::endl;    //early debug
    colorMap->rescaleDataRange();
    colorMap->rescaleAxes();
    customPlot->replot();
}

/*
void PlotWidget::indicateChange()
{
    std::cout << "graf posunuty"<<std::endl;
    bool rangeFound;
    QCPRange range = colorMap->getKeyRange(rangeFound);
    std::cout << rangeFound <<std::endl;
    std::cout << range.lower << ", " << range.upper <<std::endl;

    QCPRange xRange = customPlot->xAxis->range(); // X-axis visible range
    QCPRange yRange = customPlot->yAxis->range(); // Y-axis visible range

    double xMin = xRange.lower;
    double xMax = xRange.upper;
    double yMin = yRange.lower;
    double yMax = yRange.upper;



    QCPAxisRect *axisRect = colorMap->keyAxis()->axisRect();
    std::cout << "Velikost: " << axisRect->width() << ", " << axisRect->height() <<std::endl;
    std::cout << "rozsah - X:" << xMin << "-" << xMax <<", Y: " << yMin << "-"<< yMax <<std::endl;

    this->saveRanges();
    //range.upper
}*/




void PlotWidget::saveRanges()
{
    QCPRange xRange = customPlot->xAxis->range(); // X-axis visible range
    QCPRange yRange = customPlot->yAxis->range(); // Y-axis visible range

    lastXMin = xRange.lower;
    lastXMax = xRange.upper;
    lastYMin = yRange.lower;
    lastYMax = yRange.upper;
}

void PlotWidget::adjustAxes()
{
    QCPAxisRect *axisRect = colorMap->keyAxis()->axisRect();
    unsigned int pixX = axisRect->width();
    unsigned int pixY = axisRect->height();
    double k = pixX/(double)pixY;
    //std::cout << "DEBUG: Adjusting axes ranges to ratio " << k << std::endl;

    double xRangeOld = lastXMax - lastXMin;
    double yRangeOld = lastYMax - lastYMin;
    double xRange = std::sqrt(xRangeOld*yRangeOld*k);
    double yRange =xRange/k;

    //std::cout << "DEBUG: new aspect ratio" << xRange/yRange << std::endl;

    //std::cout << "DEBUG: old area" << xRangeOld * yRangeOld << std::endl;
    //std::cout << "DEBUG: new area" << xRange * yRange << std::endl;

    double xMid = (lastXMax+lastXMin)/2;
    double yMid = (lastYMax+lastYMin)/2;


    //std::cout << "DEBUG: old mid" << xMid << ", "<< yMid << std::endl;

    customPlot->xAxis->setRange(xMid - xRange/2, xMid + xRange/2);
    customPlot->yAxis->setRange(yMid - yRange/2, yMid + yRange/2);
    customPlot->replot();
    this->saveRanges();
}

void PlotWidget::dataRangeChanged()
{
    emit requestRecompute();
}

void PlotWidget::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event); // Call base class implementation
    //indicateChange();            // Call indicateChange on resize
    this->adjustAxes();
    this->dataRangeChanged();
}

void PlotWidget::onMouseWheel()
{
    // Restart the timer on every wheel event
    zoomTimer->start();
}
void PlotWidget::onZoomFinished()
{
    emit zoomChanged(); // Emit custom signal after zooming stops
}

