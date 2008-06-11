#include "PkAddRm_Model.h"

PkAddRmModel::PkAddRmModel(QObject *parent)
: QAbstractTableModel(parent),
  m_iconDeb("application-x-deb"),
  m_iconRpm("application-x-rpm"),
  m_iconTgz("application-x-compressed-tar"),
  m_iconGeneric("utilities-file-archiver"),
  m_iconBugFix("script-error"),
  m_iconLow("security-high"),
  m_iconImportant("security-low"),
  m_iconEnhancement("ktip"),
  m_iconSecurity("emblem-important"),
  m_iconNormal("security-medium")
{
    rootItem = new PackageItem();
}

int PkAddRmModel::rowCount(const QModelIndex &parent) const
{
    PackageItem *parentItem;
    if (parent.column() > 0)
        return 0;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<PackageItem*>(parent.internalPointer());

    return parentItem->childCount();
}

int PkAddRmModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return static_cast<PackageItem*>(parent.internalPointer())->columnCount();
    else
        return rootItem->columnCount();
}

QVariant PkAddRmModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    PackageItem *item = static_cast<PackageItem*>(index.internalPointer());
    Package *p = item->data();

    switch(role) {
        case Qt::DisplayRole:
            return item->name();
        case Qt::DecorationRole:
	    if ( p->info() == "available" || p->info() == "installed" )
	        if ( p->data() == "debian" )
	            return m_iconDeb;
	        else if ( p->data() == "fedora" )
	            return m_iconRpm;
	        else
	            return m_iconGeneric;
            else if ( p->info() == "bugfix" )
	        return m_iconBugFix;
	    else if ( p->info() == "security-important" )
	        return m_iconImportant;
	    else if ( p->info() == "security-low" )
	        return m_iconLow;
	    else if ( p->info() == "enhancement" )
	        return m_iconEnhancement;
	    else if ( p->info() == "security" )
	        return m_iconSecurity;
	    else if ( p->info() == "normal" )
	        return m_iconNormal;
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

QModelIndex PkAddRmModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    PackageItem *parentItem;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<PackageItem*>(parent.internalPointer());

    PackageItem *childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();
}

QModelIndex PkAddRmModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    PackageItem *childItem = static_cast<PackageItem*>(index.internalPointer());
    PackageItem *parentItem = childItem->parent();

    if (parentItem == rootItem)
        return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
}

Package * PkAddRmModel::package(const QModelIndex &index)
{
    return static_cast<PackageItem*>(index.internalPointer())->data();
}

void PkAddRmModel::addPackage(Package *package)
{
//     qDebug() << package->name() << package->version() << package->arch() << package->data() << package->info() <<  package->summary() ;
    

    // check to see if the list of info has any package
    if (  packages.contains( package->info() ) ) {
	int row = packages.value( package->info() )->childCount();
        beginInsertRows(createIndex(row, 1, packages.value( package->info() ) ), packages.size(), packages.size());
        packages.value( package->info() )->appendChild( new PackageItem(package, packages.value( package->info() ) ) );
    }
    else {
        beginInsertRows(QModelIndex(), packages.size(), packages.size());
        // create the section root 
        packages.insert( package->info(), new PackageItem( new Package( ";;;", package->info(), QString() ), rootItem ) );
	// add the child package
	rootItem->appendChild( packages.value( package->info() ) );
	endInsertRows();
	int row = packages.value( package->info() )->childCount();
	beginInsertRows(createIndex(row, 1, packages.value( package->info() ) ), packages.size(), packages.size());
	packages.value( package->info() )->appendChild( new PackageItem(package, packages.value( package->info() )) );
    }
    endInsertRows();
}

void PkAddRmModel::removePackage(Package *package)
{
    beginRemoveRows(QModelIndex(), 1, 1);
//     packages.removeAt(packages.indexOf(package));
    endRemoveRows();
}

void PkAddRmModel::clear()
{
    layoutChanged();
//     beginRemoveRows(QModelIndex(), 0, packages.size());
//     packages.clear();
//     endRemoveRows();
}
