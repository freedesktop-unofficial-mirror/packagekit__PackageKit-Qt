#include "PkAddRm_Model.h"

using namespace PackageKit;

PkAddRmModel::PkAddRmModel(QObject *parent)
 : QAbstractTableModel(parent),
m_iconDeb("application-x-deb"), m_iconRpm("application-x-rpm"),
m_iconTgz("application-x-compressed-tar"), m_iconGeneric("utilities-file-archiver")
{

}

PkAddRmModel::PkAddRmModel(const QList<Package*> &packages, QObject *parent)
 : QAbstractTableModel(parent),
m_packages(packages), m_packagesChanges(packages),
m_iconDeb("application-x-deb"), m_iconRpm("application-x-rpm"),
m_iconTgz("application-x-compressed-tar"), m_iconGeneric("utilities-file-archiver")
{

}

int PkAddRmModel::rowCount(const QModelIndex &) const
{
    return m_packages.size();
}

int PkAddRmModel::columnCount(const QModelIndex &) const
{
    return 2;
}

QVariant PkAddRmModel::data(const QModelIndex &index, int role) const
{
    if(index.row() > m_packages.size()) return QVariant();

    Package *p = m_packages.at(index.row());

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
	    if ( p->info() == Info::Available )
	        return false;
            else
	        return true;

        case IdRole:
            return p->id();

	case Qt::CheckStateRole :
	    if ( index.column() == 1 ) {
	        for (int i = 0; i < m_packagesChanges.size(); ++i) {
                    if ( m_packagesChanges.at(i)->id() == package(index)->id() )
                        return Qt::Checked;
                }
	        return Qt::Unchecked;
	    }
	    else
	        return QVariant();

        default:
            return QVariant();
    }
}

bool PkAddRmModel::setData( const QModelIndex &index, const QVariant &value, int role)
{
    if ( role == Qt::CheckStateRole && index.column() == 1 ) {
        // now we check if we need to add or remove from the list
        if ( value.toBool() ) {
            // Add
	    // its good to check if the package isn't already in
	    // this might happen for example if the user installed
	    // 
	    m_packagesChanges.append( package(index) );
	    emit dataChanged(index, index);
	    emit changed( !m_packagesChanges.isEmpty() );
	    return true;
        }
        else {
            //remove
	    for (int i = 0; i < m_packagesChanges.size(); ++i) {
                 if ( m_packagesChanges.at(i)->id() == package(index)->id() )
                     m_packagesChanges.removeAt(i);
            }
	    emit changed( !m_packagesChanges.isEmpty() );
	    emit dataChanged(index, index);
	    return true;
        }
    }
    else
        return false;
}

Qt::ItemFlags PkAddRmModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags defaultFlags = QAbstractTableModel::flags(index);

    if ( index.isValid() && index.column() == 1 )
        return Qt::ItemIsUserCheckable | QAbstractTableModel::flags(index);
    else
        return QAbstractTableModel::flags(index);
}

Package * PkAddRmModel::package(const QModelIndex &index) const
{
    return m_packages.at(index.row());
}

void PkAddRmModel::addPackage(Package *package)
{
//     qDebug() << package->name() << package->version() << package->arch() << package->data() << package->info() <<  package->summary() ;
    beginInsertRows(QModelIndex(), m_packages.size(), m_packages.size());
    m_packages.append(package);
    endInsertRows();
}

void PkAddRmModel::addUniquePackage(Package *package)
{
    for (int i = 0; i < m_packages.size(); ++i)
         if ( m_packages.at(i)->id() == package->id() )
             return;
    beginInsertRows(QModelIndex(), m_packages.size(), m_packages.size());
    m_packages.append(package);
    endInsertRows();
}

void PkAddRmModel::removePackage(Package *package)
{
    beginRemoveRows(QModelIndex(), 1, 1);
    m_packages.removeAt(m_packages.indexOf(package));
    endRemoveRows();
}

void PkAddRmModel::clearPkg()
{
    beginRemoveRows(QModelIndex(), 0, m_packages.size());
    m_packages.clear();
    endRemoveRows();
}

void PkAddRmModel::clearPkgChanges()
{
    qDebug() << "Changes cleared";
    m_packagesChanges.clear();
    emit changed( !m_packagesChanges.isEmpty() );
}
