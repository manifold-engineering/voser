#ifndef SOUCESMANAGERWIDGET_H
#define SOUCESMANAGERWIDGET_H

#include "sourcestablemodel.h"

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QTableView>
#include <QVBoxLayout>
#include <QHBoxLayout>

class SourcesManagerWidget : public QWidget
{
    Q_OBJECT

private:
    SourcesTableModel *model;
    QTableView *tableView;
    QVBoxLayout *SourcesManagerMainLayout;
    QHBoxLayout *SourcesManagerButtonLayout;

    //buttons in toolbar
    QPushButton *addButton;
    QPushButton *removeButton;
    QPushButton *clearButton;


public:
    explicit SourcesManagerWidget(QWidget *parent = nullptr);
    void setModel(SourcesTableModel *newModel);
    double getAngularFrequency();

public slots:
    void removeSources();
    void frequencyFieldChanged(){emit frequencyChanged();}

signals:
    void frequencyChanged();
};

#endif // SOUCESMANAGERWIDGET_H
