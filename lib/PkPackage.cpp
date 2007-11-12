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
