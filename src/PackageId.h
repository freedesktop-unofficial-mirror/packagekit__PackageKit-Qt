#include <QtCore>

extern "C" {
#include <pk-package-id.h>
}

namespace PackageKit {

class PackageId : public QObject {

	Q_OBJECT

public:
	PackageId(QObject *parent = 0);
	PackageId(QString str, QObject *parent = 0);
	
	static QString build(QString name, QString version, QString arch, QString data);
	QString toString();
	static bool check(QString package_id);

private:
	PkPackageId *id;
};

}
