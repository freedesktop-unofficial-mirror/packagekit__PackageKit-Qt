#ifndef KPK_PACKAGEMODEL_H
#define KPK_PACKAGEMODEL_H

#include <QAbstractTableModel>
#include <KIcon>

#include "../../../lib/QPackageKit.h"
// #include "../../../lib/Package.h"

using namespace PackageKit;

class PkAddRmModel : public QAbstractTableModel
{
Q_OBJECT

public:
    PkAddRmModel(QObject *parent = 0);
    int rowCount(const QModelIndex &/*parent = QModelIndex()*/) const;
    int columnCount(const QModelIndex &) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
public slots:
    void addPackage(Package *package);
public:
    void removePackage(Package *package);
    void clear();

    enum {
        SummaryRole = 32,
        InstalledRole,
        IdRole
        };

private:
    QList<Package*> packages;
    KIcon m_iconDeb;
    KIcon m_iconRpm;
    KIcon m_iconTgz;
    KIcon m_iconGeneric;
};

#endif
