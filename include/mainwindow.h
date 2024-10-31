#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "solver.h"
#include "sourcestablemodel.h"
#include "widgets/containerwidget.h"

#include <QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT
    //friend class ContainerWidget;
private:
    MultisubSolver *solver;
    SourcesTableModel *model;
    class ContainerWidget *container;
protected slots:
    void compute();

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
};
#endif //MAINWINDOW_H
