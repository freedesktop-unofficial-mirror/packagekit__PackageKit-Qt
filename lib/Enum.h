#ifndef ENUM_H
#define ENUM_H

#include <QtCore>

namespace PackageKit {


template<class T> static int EnumFromString(QString v) {
	int id = T::staticMetaObject.indexOfEnumerator("Value");
	qDebug() << "Class " << T::staticMetaObject.className() << " has " << T::staticMetaObject.enumeratorCount() << "enums";
	QMetaEnum e = T::staticMetaObject.enumerator(id);
	return e.keyToValue(v.toAscii().data());
}

template<class T> static QString EnumToString(int v) {
	int id = T::staticMetaObject.indexOfEnumerator("Value");
	QMetaEnum e = T::staticMetaObject.enumerator(id);
	return QString(e.valueToKey((int)v)).replace(QString("_"), QString("-"));
}

} // End namespace PackageKit

#endif
