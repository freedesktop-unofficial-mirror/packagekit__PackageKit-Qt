#ifndef KPK_PACKAGEMODEL_H
#define KPK_PACKAGEMODEL_H

#include <QAbstractTableModel>
#include <KIcon>

#include "../../lib/QPackageKit.h"

using namespace PackageKit;

class PkAddRmModel : public QAbstractTableModel
{
Q_OBJECT

public:
    PkAddRmModel(QObject *parent = 0);
    PkAddRmModel(const QList<Package*> &packages, QObject *parent = 0);

    int rowCount(const QModelIndex &/*parent = QModelIndex()*/) const;
    int columnCount(const QModelIndex &) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    bool setData( const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    Qt::ItemFlags flags(const QModelIndex &index) const;

    void removePackage(Package *package);
    Package * package(const QModelIndex &index) const;
    void clearPkg();
    void clearPkgChanges();

    QList<Package*> packagesChanges() { return m_packagesChanges; };

    enum {
        SummaryRole = 32,
        InstalledRole,
        IdRole
        };

public slots:
    void addPackage(Package *package);
    void addUniquePackage(Package *package);

signals:
    void changed(bool state);

private:
    QList<Package*> m_packages;
    QList<Package*> m_packagesChanges;
    KIcon m_iconDeb;
    KIcon m_iconRpm;
    KIcon m_iconTgz;
    KIcon m_iconGeneric;
};

#endif
