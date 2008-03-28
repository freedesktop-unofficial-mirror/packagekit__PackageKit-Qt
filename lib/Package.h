#ifndef PACKAGE_H
#define PACKAGE_H

#include <QtCore>

namespace PackageKit {

class Package : public QObject {

	Q_OBJECT

public:
	Package(QString packageId, QObject *parent = 0);
	const QString& name();
	const QString& version();
	const QString& arch();
	const QString& data();

private:
	QString _name, _version, _arch, _data;
};

}

#endif
