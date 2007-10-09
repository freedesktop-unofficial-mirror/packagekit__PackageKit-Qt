#include "PackageId.h"
#include "utils.cpp"

using namespace PackageKit;

//! Creates a new PackageId object (equivalent to pk_package_id_new)
//! \param parent the parent object, or NULL
PackageId::PackageId(QObject *parent) : QObject(parent) {
	id = pk_package_id_new();
}

//! Creates a new PackageId object from a string (equivalent to pk_package_id_new_from_string)
//! \param str The string used to create the object
//! \param parent the parent object, or NULL
PackageId::PackageId(QString str, QObject *parent) : QObject(parent) {
	id = pk_package_id_new_from_string(QString2constStr(str));
}

//! Builds a package id from its name, version, arch and data
//! \return The built package id
QString PackageId::build(QString name, QString version, QString arch, QString data) {
	return QString(pk_package_id_build(QString2constStr(name), QString2constStr(version), QString2constStr(arch), QString2constStr(data)));	
}

//! Converts the package id to a string
//! \return The id converted to a string
QString PackageId::toString() {
	return QString(pk_package_id_to_string(id));
}

//! Checks the provided package id is correct
//! \param package_id The id to check
//! \return TRUE if the id is valid, FALSE else
bool PackageId::check(QString package_id) {
	return pk_package_id_check(QString2constStr(package_id));
}
