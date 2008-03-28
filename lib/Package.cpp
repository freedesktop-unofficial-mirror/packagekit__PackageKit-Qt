#include "Package.h"

using namespace PackageKit;

Package::Package(QString packageId, QObject *parent) : QObject(parent) {
	QStringList tokens = packageId.split(';');
	_name = tokens.at(0);
	_version = tokens.at(1);
	_arch = tokens.at(2);
	_data = tokens.at(3);
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
