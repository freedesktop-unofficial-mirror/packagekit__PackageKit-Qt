#ifndef KPK_PACKAGEMODEL_H
#define KPK_PACKAGEMODEL_H

#include <QtCore>

#include "Client.h"

using namespace PackageKit;

class PackageModel : public QAbstractListModel {

	Q_OBJECT

public:
	PackageModel(QObject *parent = 0);
	int rowCount(const QModelIndex &parent = QModelIndex());
	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole);

	void addPackage(Package *package);
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
