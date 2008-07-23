/*
* Copyright (C) 2007 Adrien Bustany <madcat@mymadcat.com>
*
* Licensed under the GNU General Public License Version 2
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 See MA 02111-1307, USA.
*
*/

#ifndef PACKAGE_H
#define PACKAGE_H

#include <QtCore>

#include "Info.h"

namespace PackageKit {

class Package : public QObject {

	Q_OBJECT

public:
	Package(const QString& packageId, QObject *parent = 0);
	Package(const QString& packageId, const Info::Value& info, const QString& summary, QObject *parent = 0);
	const QString id();
	const QString& name();
	const QString& version();
	const QString& arch();
	const QString& data();
	const Info::Value& info();
	const QString& summary();

	bool operator==(const Package &other) const;

private:
	QString _name, _version, _arch, _data, _summary;
	Info::Value _info;
};

}

#endif
