#ifndef PACKAGE_H
#define PACKAGE_H

#include <QtCore>

namespace PackageKit {

class Package : public QObject {

	Q_OBJECT

public:
	Package(const QString& packageId, QObject *parent = 0);
	Package(const QString& packageId, const QString& info, const QString& summary, QObject *parent = 0);
	const QString id();
	const QString& name();
	const QString& version();
	const QString& arch();
	const QString& data();
	const QString& info();
	const QString& summary();

private:
	QString _name, _version, _arch, _data, _info, _summary;
};

}

#endif
