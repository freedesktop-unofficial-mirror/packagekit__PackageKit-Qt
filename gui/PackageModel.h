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

#ifndef PACKAGEMODEL_H
#define PACKAGEMODEL_H

#include <QtCore>
#include <QIcon>

#include <QPackageKitClient.h>

class Package;

class PackageModel : public QAbstractListModel {

	Q_OBJECT;

public:
	PackageModel(QObject *parent = 0);

	// Model functions
	int rowCount(const QModelIndex &parent = QModelIndex()) const;
	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole);
	void sort();

	// Add a package to the list
	void addPackage(PkPackage *p);
	void addPackage(QString package_id, bool installed = false);

	// Remove a package from the list
	void removePackage(PkPackage *p);
	void removePackage(QString package_id);

	// Clear the model
	void clear();

	// Get a package from the list
	PkPackage *packageAtIndex(const QModelIndex &index);

	// Sort related function for the list
	static bool packageNameLessThan(PkPackage *p1, PkPackage *p2);

private:
	QList<PkPackage*> packages;
	
	// How to display the package (eg name version arch...)
	QString formatPackage (PkPackage *p) const;

	// Little package icon
	QIcon installedIcon;
	QIcon packageIcon;
};

#endif
