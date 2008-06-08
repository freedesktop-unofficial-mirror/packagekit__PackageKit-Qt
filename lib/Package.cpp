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

#include "Package.h"

using namespace PackageKit;

Package::Package(const QString& packageId, QObject *parent) : QObject(parent) {
	QStringList tokens = packageId.split(';');
	if(tokens.size() != 4) qWarning("Package : bad package id");
	_name = tokens.at(0);
	_version = tokens.at(1);
	_arch = tokens.at(2);
	_data = tokens.at(3);
}

Package::Package(const QString& packageId, const QString& info, const QString& summary, QObject *parent)
															: QObject(parent), _info(info), _summary(summary) {
	QStringList tokens = packageId.split(';');
	if(tokens.size() != 4) qWarning("Package : bad package id");
	_name = tokens.at(0);
	_version = tokens.at(1);
	_arch = tokens.at(2);
	_data = tokens.at(3);
}

const QString Package::id() {
	return _name + ";" + _version + ";" + _arch + ";" + _data;
}

const QString& Package::name() {
	return _name;
}

const QString& Package::version() {
	return _version;
}

const QString& Package::arch() {
	return _arch;
}

const QString& Package::data() {
	return _data;
}

const QString& Package::info() {
	return _info;
}

const QString& Package::summary() {
	return _summary;
}

bool Package::operator==(const Package &other) const {
	return const_cast<Package*>(this)->id() == const_cast<Package&>(other).id();
}
