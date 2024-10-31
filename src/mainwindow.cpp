#include "mainwindow.h"
#include "sourcestablemodel.h"
#include "solution.h"

#include "globalconfig.h"

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

    compute();
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
    std::vector<double> x = sampleEquiDistant(x_min, x_max, x_samples);
    std::vector<double> y = sampleEquiDistant(y_min, y_max, y_samples);



    double angularFrequency = container->frequencyManager->getAngularFrequency();

    Solution newData = solver->solve(x, y, model->exportActiveSources(), angularFrequency);
    container->plotWidget->replot(newData);
}
