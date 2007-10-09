#include "PackageId.h"
#include "utils.cpp"

using namespace PackageKit;

PackageId::PackageId(QObject *parent) : QObject(parent) {
	id = pk_package_id_new();
}

PackageId::PackageId(QString str, QObject *parent) : QObject(parent) {
	id = pk_package_id_new_from_string(QString2constStr(str));
}

QString PackageId::build(QString name, QString version, QString arch, QString data) {
	return QString(pk_package_id_build(QString2constStr(name), QString2constStr(version), QString2constStr(arch), QString2constStr(data)));	
}

QString PackageId::toString() {
	return QString(pk_package_id_to_string(id));
}

bool PackageId::check(QString package_id) {
	return pk_package_id_check(QString2constStr(package_id));
}
