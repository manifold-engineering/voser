#include "sourcestablemodel.h"
#include "source.h"


#include <Qt>

//for debugging output etc.
#include <iostream>
SourcesTableModel::SourcesTableModel(QObject *parent)
{
    this->sourcesVector.append(Source());
}

SourcesTableModel::~SourcesTableModel()
{

}

int SourcesTableModel::rowCount(const QModelIndex &parent) const
{
    return sourcesVector.size();
}

int SourcesTableModel::columnCount(const QModelIndex &parent) const
{
    return 6;
}

QVariant SourcesTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(orientation == Qt::Vertical && role == Qt::DisplayRole)
    {
        return section;
    }
    if (role == Qt::DisplayRole)
    {

        if (orientation == Qt::Horizontal) {
            switch (section)
            {
            case 0:
                return QString("X [m]");
            case 1:
                return QString("Y [m]");
            case 2:
                return QString("gain [dB]");
            case 3:
                return QString("delay [ms]");
            case 4:
                return QString("Ø");
            case 5:
                return QString("active");
            }
        }
    }
    return QVariant();
}

Qt::ItemFlags SourcesTableModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags flags;
    flags.setFlag(Qt::ItemFlag::ItemIsEnabled);
    flags.setFlag(Qt::ItemFlag::ItemIsEditable);
    flags.setFlag(Qt::ItemFlag::ItemIsSelectable);

    if (index.column() == 4 || index.column() == 5){
        flags.setFlag(Qt::ItemFlag::ItemIsUserCheckable);
    }
    else{
    }
    return flags;
}

QVariant SourcesTableModel::data(const QModelIndex &index, int role) const
{
    const Source &source = sourcesVector[index.row()];

    if(role == Qt::CheckStateRole)
           {
                if(index.column() == 4)
                    return source.invert?Qt::Checked:Qt::Unchecked;
                if(index.column() == 5)
                    return source.active?Qt::Checked:Qt::Unchecked;
           }
    if (role == Qt::DisplayRole){
        switch (index.column()) {
            case 0:
                return source.x;
            break;
            case 1:
                return source.y;
            break;
            case 2:
                return source.gain;
            break;
            case 3:
                return source.delay;
            break;
            case 4:
                return QVariant();
            break;
            case 5:
                return QVariant();
            break;
        }
    }
    else
        return QVariant();
    return 666;
}

bool SourcesTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.row() > this->rowCount())
        return false;

    Source &source = sourcesVector[index.row()];

    if (role == Qt::EditRole){
        switch (index.column()) {
            case 0:
                source.x = value.toDouble();
            break;
            case 1:
                source.y = value.toDouble();
            break;
            case 2:
                source.gain = value.toDouble();
            break;
            case 3:
                source.delay = value.toDouble();
            break;
        default:
            return false;
        }
    }
    if (role == Qt::CheckStateRole){
        switch (index.column()) {
            case 4:
                source.invert = value.toInt() == Qt::Checked;
                std::cout <<"zaskrtavam \n" << std::endl;
            break;
            case 5:
                source.active = value.toBool();
                std::cout <<"zaskrtavam \n";
            break;
        default:
            return false;
        }
    }



    emit dataChanged(index,index);
    return true;

}



void SourcesTableModel::append()
{
    Source s;
    //emit dataChanged(this->createIndex(0, 0, this),
    //                 this->createIndex(SourcesVector.size(), 6, this));

    beginInsertRows(QModelIndex(), sourcesVector.size(), sourcesVector.size());

    sourcesVector.append(s);
    endInsertRows();

    //emit this.rowCountChanged();
}

bool SourcesTableModel::removeSources(int position, int rows)
{
    beginRemoveRows(QModelIndex(), position, position+rows-1);

    if (position+rows <= sourcesVector.size())
        sourcesVector.remove(position, rows);

    endRemoveRows();
    return true;
}

void SourcesTableModel::clearSources()
{
    removeSources(0, rowCount());
}

std::vector<Source> SourcesTableModel::exportActiveSources()
{
    std::vector<Source> result;
    //I know, appending into vector is bad, since memory might get reallocated
    //but i assume small number of sources
    //and this operation is done before whole computation
    //which will probably be more time consuming anyway
    for (Source s:sourcesVector){
        if(s.active){
            result.push_back(s);
        }
    }
    return result;
}

