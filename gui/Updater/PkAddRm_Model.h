#ifndef KPK_PACKAGEMODEL_H
#define KPK_PACKAGEMODEL_H

#include <QAbstractTableModel>
#include <KIcon>

#include "pkg_item.h"
#include <QPackageKit>

using namespace PackageKit;

class PkAddRmModel : public QAbstractTableModel
{
Q_OBJECT

public:
    PkAddRmModel(QObject *parent = 0);
    int rowCount(const QModelIndex &/*parent = QModelIndex()*/) const;
    int columnCount(const QModelIndex &) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex &index) const;
public slots:
    void addPackage(Package *package);
public:
    void removePackage(Package *package);
    Package * package(const QModelIndex &index);
    void clear();

    enum {
        SummaryRole = 32,
        InstalledRole,
        IdRole
        };

private:
    QHash<QString, PackageItem*> packages;
    PackageItem *rootItem;
    KIcon m_iconDeb; 
    KIcon m_iconRpm;
    KIcon m_iconTgz;
    KIcon m_iconGeneric;
    KIcon m_iconBugFix;
    KIcon m_iconLow;
    KIcon m_iconImportant;
    KIcon m_iconEnhancement;
    KIcon m_iconSecurity;
    KIcon m_iconNormal;
};

#endif
