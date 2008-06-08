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

#ifndef ENUM_H
#define ENUM_H

#include <QtCore>

namespace PackageKit {


template<class T> static int EnumFromString(QString v) {
	// Upper case the first letter of v
	v = v.left(1).toUpper() + v.mid(1);
	v = v.replace("-", "_");
	int id = T::staticMetaObject.indexOfEnumerator("Value");
	QMetaEnum e = T::staticMetaObject.enumerator(id);
	return e.keyToValue(v.toAscii().data());
}

template<class T> static QString EnumToString(int v) {
	int id = T::staticMetaObject.indexOfEnumerator("Value");
	QMetaEnum e = T::staticMetaObject.enumerator(id);
	return QString(e.valueToKey((int)v)).replace("_", "-").toLower();
}

} // End namespace PackageKit

#endif
