#ifndef KPK_PACKAGEMODEL_H
#define KPK_PACKAGEMODEL_H

#include <QAbstractTableModel>

#include "../../../lib/Client.h"
#include "../../../lib/Package.h"


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
        VersionRole = 32,
        ArchRole,
        SummaryRole
        };

private:
    QList<Package*> packages;

};

#endif
