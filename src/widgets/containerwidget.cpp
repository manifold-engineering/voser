#include "widgets/containerwidget.h"


ContainerWidget::ContainerWidget(QWidget *parent) : QWidget(parent)
{
    // Create a main vertical layout
    mainLayout = new QVBoxLayout(this);

    // Create a vertical splitter
    QSplitter *splitter = new QSplitter(Qt::Vertical, this);

    // Instantiate widgets
    plotWidget = new PlotWidget(this);
    frequencyManager = new FrequencyManagerWidget(this);
    sourcesManager = new SourcesManagerWidget(this);

    // Add widgets to the splitter
    splitter->addWidget(plotWidget);
    splitter->addWidget(frequencyManager);
    splitter->addWidget(sourcesManager);

    // Adjust FrequencyManager to take minimal vertical space
    frequencyManager->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    frequencyManager->setFixedHeight(frequencyManager->sizeHint().height());

    // Set initial sizes for each widget in the splitter
    splitter->setStretchFactor(0, 3); // PlotWidget gets 3 parts of space
    splitter->setStretchFactor(1, 0); // FrequencyManager takes minimal space
    splitter->setStretchFactor(2, 1); // SourcesManager gets 1 part of space

    // Set initial sizes to approximate 3/4 for plotWidget and 1/4 for sourcesManager
    QList<int> sizes;
    sizes << 600 << 50 << 200; // Adjust these values based on available space
    splitter->setSizes(sizes);

    // Customize splitter handle
    splitter->setHandleWidth(1);
    splitter->setStyleSheet("QSplitter::handle { background-color: gray; }");

    // Add the splitter to the main layout
    mainLayout->addWidget(splitter);
}

ContainerWidget::~ContainerWidget()
{

}

void ContainerWidget::setModel(SourcesTableModel *newModel)
{
    this->model = newModel;
    sourcesManager->setModel(model);
}
