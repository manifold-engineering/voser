#ifndef CONTAINERWIDGET_H
#define CONTAINERWIDGET_H

#include "widgets/sourcesmanagerwidget.h"
#include "widgets/plotwidget.h"
#include "widgets/frequencymanagerwidget.h"
#include "sourcestablemodel.h"
#include "mainwindow.h"

#include <QWidget>
#include <QVBoxLayout>

class ContainerWidget : public QWidget
{
    Q_OBJECT
    friend class MainWindow;
    //friend void SimulatorWindow::compute();
protected:
    SourcesTableModel *model;
    QVBoxLayout *mainLayout;
    SourcesManagerWidget *sourcesManager;
    PlotWidget *plotWidget;
    FrequencyManagerWidget *frequencyManager;


public:
    explicit ContainerWidget(QWidget *parent = nullptr);
    ~ContainerWidget();
    void setModel(SourcesTableModel *newModel);

//signals:

};

#endif // CONTAINERWIDGET_H
