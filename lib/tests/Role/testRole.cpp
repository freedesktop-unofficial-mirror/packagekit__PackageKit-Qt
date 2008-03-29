#include <QtCore>

#include "../../Client.h"
#include "../../Enum.h"

using namespace PackageKit;

int main(int argc, char **argv) {
	QCoreApplication app(argc, argv);
	Client c;
	qDebug() << "We have tid " << c.tid();
	c.searchName("none", "vim");
	QString package;
	qDebug() << "Role" << EnumToString<Role>(c.role(package)) << "on package" << package;
	return app.exec();
}
