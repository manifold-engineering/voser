#include "widgets/sourcesmanagerwidget.h"

#include <QPushButton>
#include <QLineEdit>
#include <iostream>

extern double pi;

SourcesManagerWidget::SourcesManagerWidget(QWidget *parent) : QWidget(parent)
{
    tableView = new QTableView(this);

    SourcesManagerMainLayout = new QVBoxLayout(this);
    SourcesManagerButtonLayout = new QHBoxLayout(this);


    addButton = new QPushButton("Add", this);
    removeButton = new QPushButton("Remove", this);
    clearButton = new QPushButton("Clear", this);


    SourcesManagerButtonLayout->addWidget(addButton);
    SourcesManagerButtonLayout->addWidget(removeButton);
    SourcesManagerButtonLayout->addWidget(clearButton);

    SourcesManagerMainLayout->addWidget(tableView);
    SourcesManagerMainLayout->addLayout(SourcesManagerButtonLayout);



    this->setLayout(SourcesManagerMainLayout);
}

void SourcesManagerWidget::setModel(SourcesTableModel *newModel)

{
    this->model = newModel;
    tableView->setModel(model);

    //this could have been in constructor
    //but I had problems, since model does not exist yet
    connect(addButton, &QPushButton::clicked,
            model, &SourcesTableModel::append);
    connect(removeButton, &QPushButton::clicked,
            this, &SourcesManagerWidget::removeSources);
    connect(clearButton, &QPushButton::clicked,
            model, &SourcesTableModel::clearSources);


    tableView->setColumnWidth(0, 80);
    tableView->setColumnWidth(1, 80);
    tableView->setColumnWidth(2, 80);
    tableView->setColumnWidth(3, 80);
    tableView->setColumnWidth(4, 16);
    tableView->setColumnWidth(5, 16);
}



void SourcesManagerWidget::removeSources()
{
    QModelIndexList indexList = tableView->selectionModel()->selectedIndexes();
    if (indexList.empty())
        return;

    int initial = indexList.at(0).row();
    int row = initial;
    int count = 1;
    foreach (QModelIndex index, indexList) {
        if (row != index.row()){
            ++count;
            std::cout << "initila: " << row <<std::endl;
            row=index.row();
        }
    }
    std::cout << "initial: " << initial << ", count: " << count <<std::endl;
    model->removeSources(initial, count);

}
