#include "PkAddRm_Model.h"

using namespace PackageKit;

PkAddRmModel::PkAddRmModel(QObject *parent) : QAbstractTableModel(parent),
m_iconDeb("application-x-deb"), m_iconRpm("application-x-rpm"),
m_iconTgz("application-x-compressed-tar"), m_iconGeneric("utilities-file-archiver")
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

    switch(role) {
        case Qt::DisplayRole:
            return p->name() + " - " + p->version() + " (" + p->arch() + ")";

        case Qt::DecorationRole:
            if ( p->data() == "debian" )
	        return m_iconDeb;
	    else if ( p->data() == "fedora" )
	        return m_iconRpm;
	    else
	        return m_iconGeneric;

        case SummaryRole:
            return p->summary();

        case InstalledRole:
	    if ( p->info() == "available" )
	        return false;
            else
	        return true;

        case IdRole:
            return p->id();

        default:
            return QVariant();
    }
}

Package * PkAddRmModel::package(const QModelIndex &index)
{
    return packages.at(index.row());
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
