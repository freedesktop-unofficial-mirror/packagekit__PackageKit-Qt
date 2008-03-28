#include <QtCore>

#include "testClient.h"

using namespace PackageKit;

int main(int argc, char **argv) {
	QCoreApplication app(argc, argv);
	testClient client;

	return app.exec();
}
