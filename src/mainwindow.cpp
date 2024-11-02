#include "mainwindow.h"
#include "sourcestablemodel.h"
#include "solution.h"

#include "globalconfig.h"

#include <algorithm>
#include <QAbstractTableModel>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    model = new SourcesTableModel(this);
    solver = new MultisubSolver();



    container = new ContainerWidget(this);
    setCentralWidget(container);
    container->setModel(model);

    connect(model, &QAbstractTableModel::dataChanged, this, &MainWindow::compute);
    connect(model, &QAbstractTableModel::rowsInserted, this, &MainWindow::compute);
    connect(model, &QAbstractTableModel::rowsRemoved, this, &MainWindow::compute);
    connect(container->frequencyManager, &FrequencyManagerWidget::frequencyChanged,
            this, &MainWindow::compute);
    connect(container->plotWidget, &PlotWidget::requestRecompute, this, &MainWindow::compute);


    this->setWindowTitle("Voser");
    this->setWindowIcon(QIcon(":/resources/icons/icon_32.png"));

    //compute();
}

MainWindow::~MainWindow()
{

    delete solver;
}

std::vector<double> sampleEquiDistant(double min, double max, int samples){
    std::vector<double> result (samples);
    double increment = (max - min)/(samples - 1);
    for(int i = 0; i<samples; ++i){
        result[i] = min+i*increment;
    }
    return result;
}


void MainWindow::compute()
{
    PlotParameters parameters = container->plotWidget->getPlotParameters();

    unsigned int xResolution = std::max(parameters.xPix/2, 1u);
    if (xResolution > 1e4) xResolution = 1;

    unsigned int yResolution = std::max(parameters.yPix/2, 1u);
    if (yResolution > 1e4) yResolution = 1;

    std::vector<double> x = sampleEquiDistant(parameters.xMin, parameters.xMax, xResolution);
    std::vector<double> y = sampleEquiDistant(parameters.yMin, parameters.yMax, yResolution);
    double angularFrequency = container->frequencyManager->getAngularFrequency();
    Solution newData = solver->solve(x, y, model->exportActiveSources(), angularFrequency);
    container->plotWidget->replot(newData);
}

