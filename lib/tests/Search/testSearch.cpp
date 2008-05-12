#include <QtCore>

#include "../../Client.h"
#include "testCallback.h"

using namespace PackageKit;

int main(int argc, char **argv) {
	QCoreApplication app(argc, argv);
	Client c;
	TestCallback tc;
	QObject::connect(&c, SIGNAL(newPackage(Package*)), &tc, SLOT(newPackage(Package*)));
	qDebug() << "We have tid " << c.tid();
	c.searchName("none", "vim");
	return app.exec();
}
