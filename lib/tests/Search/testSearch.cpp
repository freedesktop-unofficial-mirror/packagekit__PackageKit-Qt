#include <QtCore>

#include "../../Client.h"

using namespace PackageKit;

int main(int argc, char **argv) {
	QCoreApplication app(argc, argv);
	Client c;
	qDebug() << "We have tid " << c.tid();
	c.searchName("none", "vim");
	return app.exec();
}
