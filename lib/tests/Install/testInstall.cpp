#include <QtCore>

#include "../../QPackageKit.h"
#include "testCallback.h"

using namespace PackageKit;

int main(int argc, char **argv) {
	QCoreApplication app(argc, argv);
	TestCallback tc;
	return app.exec();
}
