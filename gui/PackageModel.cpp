#include "PackageModel.h"

PackageModel::PackageModel(QObject *parent) : QAbstractListModel(parent) {
	// Load the package icon
	packageIcon = QIcon(":/pixmaps/package.svg");
}

int PackageModel::rowCount(const QModelIndex &parent) const {
	Q_UNUSED(parent);
	return packages.size();
}

QVariant PackageModel::data(const QModelIndex &index, int role) const {
	switch (role) {
		case Qt::DisplayRole:
			return formatPackage(packages.at(index.row()));
			break;
		case Qt::DecorationRole:
			return packageIcon;
			break;
		default:
			return QVariant();
	}
}

QVariant PackageModel::headerData(int section, Qt::Orientation orientation, int role) {
	Q_UNUSED(section);
	Q_UNUSED(orientation);

	switch (role) {
		case Qt::DisplayRole:
			return tr("Package");
			break;
		default:
			return QVariant();
	}
}

void PackageModel::sort() {
	qSort(packages.begin(), packages.end(), PackageModel::packageNameLessThan);
}

void PackageModel::addPackage(PkPackage *p) {
	beginInsertRows(QModelIndex(), packages.size() + 1, packages.size() + 1);
	packages.append(p);
	endInsertRows();
}

void PackageModel::addPackage(QString package_id) {
	addPackage(new PkPackage(package_id));
}

void PackageModel::clear() {
	beginRemoveRows(QModelIndex(), 0, packages.size());
	packages.clear();
	endRemoveRows();
}

QString PackageModel::formatPackage(PkPackage *p) const {
	return QString("%1 - %2 - %3").arg(p->name()).arg(p->version()).arg(p->arch());
}

PkPackage* PackageModel::packageAtIndex(const QModelIndex &index) {
	if(index.row() - 1 > packages.size()) return NULL;
	return packages.at(index.row());
}

// Compares the name
bool PackageModel::packageNameLessThan(PkPackage *p1, PkPackage *p2) {
	return p1->name().toLower() < p2->name().toLower();
}
