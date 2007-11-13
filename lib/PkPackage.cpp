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

#include "PkPackage.h"

PkPackage::PkPackage(QObject *parent) : QObject(parent) {

}

PkPackage::PkPackage(QString pkid, QObject *parent) : QObject(parent) {
	QStringList tokens = pkid.split(";");
	p_name = tokens[0];
	p_version = tokens[1];
	p_arch = tokens[2];
	p_data = tokens[3];
	p_installed = false;
}


PkPackage::PkPackage(QString pkid, bool installed, QObject *parent) : QObject(parent) {
	QStringList tokens = pkid.split(";");
	p_name = tokens[0];
	p_version = tokens[1];
	p_arch = tokens[2];
	p_data = tokens[3];
	p_installed = installed;
}

QString PkPackage::name() {
	return p_name;
}

QString PkPackage::version() {
	return p_version;
}

QString PkPackage::arch() {
	return p_arch;
}

QString PkPackage::data() {
	return p_data;
}

QString PkPackage::id() {
	return QString("%1;%2;%3;%4").arg(p_name).arg(p_version).arg(p_arch).arg(p_data);
}

bool PkPackage::installed() {
	return p_installed;
}
