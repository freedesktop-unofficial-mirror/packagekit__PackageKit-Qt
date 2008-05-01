#include "PkAddRm_Model.h"

#include <KIcon>

using namespace PackageKit;

PkAddRmModel::PkAddRmModel(QObject *parent) : QAbstractTableModel(parent)
{

}

int PkAddRmModel::rowCount(const QModelIndex &) const
{
    return packages.size();
}

int PkAddRmModel::columnCount(const QModelIndex &) const
{
    return 1;//for now we have only the name collumn
}

QVariant PkAddRmModel::data(const QModelIndex &index, int role) const
{
    if(index.row() > packages.size()) return QVariant();

    Package *p = packages.at(index.row());

KIcon aaa("application-x-deb");
QIcon xx = aaa;


    switch(role) {
        case Qt::DisplayRole:
            return p->name() + " - " + p->version() + " (" + p->arch() + ")";

        case Qt::DecorationRole:
            return xx;

        case VersionRole:
            return p->summary();

        case ArchRole:
            return p->arch();

        case SummaryRole:
            return p->summary();

        case Qt::EditRole:
            return p->id();

        default:
            return QVariant();
    }
}

void PkAddRmModel::addPackage(Package *package)
{
//     qDebug() << package->name() << package->version() << package->arch() << package->data() << package->info() <<  package->summary() ;
    beginInsertRows(QModelIndex(), packages.size(), packages.size());
    packages.append(package);
    endInsertRows();
}

void PkAddRmModel::removePackage(Package *package)
{
    beginRemoveRows(QModelIndex(), 1, 1);
    packages.removeAt(packages.indexOf(package));
    endRemoveRows();
}

void PkAddRmModel::clear()
{
    beginRemoveRows(QModelIndex(), 0, packages.size());
    packages.clear();
    endRemoveRows();
}
