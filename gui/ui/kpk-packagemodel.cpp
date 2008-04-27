#include "kpk-packagemodel.h"

using namespace PackageKit;

PackageModel::PackageModel(QObject *parent) : QAbstractListModel(parent) {

}

int PackageModel::rowCount(const QModelIndex &parent) {
	return packages.size();
}

QVariant PackageModel::data(const QModelIndex &index, int role) {
	if(index.row() > packages.size()) return QVariant();

	Package *p = packages.at(index.row());

	switch(role) {
		case Qt::DisplayRole:
			return p->name();

		case Qt::DecorationRole:
			// We should return some pixmap here
			return QVariant();

		case VersionRole:
			return p->version();

		case ArchRole:
			return p->arch();

		case SummaryRole:
			return p->summary();

		default:
			return QVariant();
	}
}

void PackageModel::addPackage(Package *package) {
	packages.append(package);
}

void PackageModel::removePackage(Package *package) {
	packages.removeAt(packages.indexOf(package));
}

void PackageModel::clear() {
	packages.clear();
}
