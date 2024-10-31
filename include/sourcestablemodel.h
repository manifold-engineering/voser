#ifndef SOURCESTABLEMODEL_H
#define SOURCESTABLEMODEL_H

#include "source.h"  //source struct defined there for now

#include <Qt>
#include <QAbstractTableModel>
#include <QObject>


class SourcesTableModel : public QAbstractTableModel
{
private:
    QVector <Source> sourcesVector;
public:
    SourcesTableModel(QObject *parent = nullptr);
    ~SourcesTableModel();

    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    int columnCount(const QModelIndex& parent = QModelIndex()) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;

    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);


    std::vector<Source> exportActiveSources ();
public slots:
    //void append(Source s);
    void append();
    bool removeSources(int position, int rows);
    void clearSources();

};

#endif // SOURCESTABLEMODEL_H
