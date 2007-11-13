/*
 * Copyright (C) 2007 Adrien Bustany <madcat@mymadcat.com>
 *
 * Licensed under the GNU General Public License Version 2
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 *
 */

#include "PackageModel.h"

PackageModel::PackageModel(QObject *parent) : QAbstractListModel(parent) {
	// Load the icons
	installedIcon = QIcon(":/pixmaps/ok.svg");
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
			return packages.at(index.row())->installed() ? installedIcon : packageIcon;
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

void PackageModel::addPackage(QString package_id, bool installed) {
	addPackage(new PkPackage(package_id, installed, this));
}

void PackageModel::removePackage(PkPackage *p) {
	beginRemoveRows(QModelIndex(), packages.size() + 1, packages.size() + 1);
	packages.removeAt(packages.indexOf(p));
	endRemoveRows();
}

void PackageModel::removePackage(QString package_id) {
	removePackage(new PkPackage(package_id, this));
}


void PackageModel::clear() {
	beginRemoveRows(QModelIndex(), 0, packages.size()-1);
	packages.clear();
	endRemoveRows();
}

QString PackageModel::formatPackage(PkPackage *p) const {
	return QString("%1 - %2 - %3").arg(p->name()).arg(p->version()).arg(p->arch());
}

PkPackage* PackageModel::packageAtIndex(const QModelIndex &index) {
	qDebug() << packages.size();
	if(index.row() - 1 > packages.size()) return NULL;
	return packages.at(index.row());
}

// Compares the name
bool PackageModel::packageNameLessThan(PkPackage *p1, PkPackage *p2) {
	return p1->name().toLower() < p2->name().toLower();
}
