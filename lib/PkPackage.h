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
