#include <QtCore>

#include "../../QPackageKit.h"
#include "testCallback.h"

using namespace PackageKit;

int main(int argc, char **argv) {
	QCoreApplication app(argc, argv);
	Daemon d;
	TestCallback tc;
	Transaction *t = d.newTransaction();
	QObject::connect(t, SIGNAL(gotPackage(Package*)), &tc, SLOT(newPackage(Package*)));
	t->searchName("none", "vim");
	return app.exec();
}
