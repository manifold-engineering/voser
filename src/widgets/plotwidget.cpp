#include "widgets/plotwidget.h"

#include<iostream>

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


    //following code was heavily inspired by QCPColorMap example
    //some lines are actually literally copied
    //sorry

    // configure axis rect:
    customPlot->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom); // this will also allow rescaling the color scale by dragging/zooming
    customPlot->axisRect()->setupFullAxesBox(true);
    customPlot->xAxis->setLabel("x [m]");
    customPlot->yAxis->setLabel("y [m]");
    customPlot->yAxis->setScaleRatio(customPlot->xAxis, 1.0);

    // set up the QCPColorMap:
    colorMap = new QCPColorMap(customPlot->xAxis, customPlot->yAxis);


    std::cout << "x: " << x_samples << ", y: " << y_samples << std::endl;
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
    colorMap->rescaleDataRange();

    // make sure the axis rect and color scale synchronize their bottom and top margins (so they line up):
    QCPMarginGroup *marginGroup = new QCPMarginGroup(customPlot);
    customPlot->axisRect()->setMarginGroup(QCP::msBottom|QCP::msTop, marginGroup);
    colorScale->setMarginGroup(QCP::msBottom|QCP::msTop, marginGroup);

    // rescale the key (x) and value (y) axes so the whole color map is visible:
    customPlot->rescaleAxes();


    //debug range replotting
    connect(customPlot, &QCustomPlot::mouseRelease,
            this, &PlotWidget::indicateChange);

}

void PlotWidget::replot(Solution data){
    std::cout << data.getM() << ", " << data.getN() << std::endl;
    //colorMap->data()->setSize(data.getM(), data.getN());
    //colorMap->data()->setRange(QCPRange(-4, 4), QCPRange(-4, 4)); // and span the coordinate range -4..4 in both key (x) and value (y) dimensions
    // now we assign some data, by accessing the QCPColorMapData instance of the color map:
    //double x, y, z;
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
    std::cout << "rozsah preskalovan" << std::endl; //early debug
    //colorMap->rescaleAxes();
    customPlot->replot();
}

void PlotWidget::indicateChange()
{
    std::cout << "graf posunuty"<<std::endl;
    bool rangeFound;
    QCPRange range = colorMap->getKeyRange(rangeFound);
    std::cout << rangeFound <<std::endl;
    std::cout << range.lower << ", " << range.upper <<std::endl;

    //range.upper
}
