#include "widgets/containerwidget.h"



ContainerWidget::ContainerWidget(QWidget *parent) : QWidget(parent)
{
    mainLayout = new QVBoxLayout(this);
    sourcesManager = new SourcesManagerWidget(this);
    plotWidget = new PlotWidget(this);
    frequencyManager = new FrequencyManagerWidget(this);


    mainLayout->addWidget(plotWidget);
    mainLayout->addWidget(frequencyManager);
    mainLayout->addWidget(sourcesManager);

    plotWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    //plotWidget->setFixedSize(700, 600);
    //sourcesManager->setFixedHeight(256);
}

ContainerWidget::~ContainerWidget()
{

}

void ContainerWidget::setModel(SourcesTableModel *newModel)
{
    this->model = newModel;
    sourcesManager->setModel(model);
}
