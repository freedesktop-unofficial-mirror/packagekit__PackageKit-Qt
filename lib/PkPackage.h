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

#ifndef PACKAGE_H
#define PACKAGE_H

#include <QtCore>

class PkPackage : public QObject {

	Q_OBJECT

public:
	PkPackage(QObject *parent = 0);
	PkPackage(QString pkid, QObject *parent = 0);
	PkPackage(QString pkid, bool installed, QObject *parent = 0);

	// Getters
	QString name();
	QString version();
	QString arch();
	QString data();
	bool installed();

	// Return the package's id
	QString id();

private:
	QString p_name, p_version, p_arch, p_data;
	bool p_installed;

};

#endif
