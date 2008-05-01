#include <QtCore>

#include "../../Client.h"
#include "Receiver.h"

using namespace PackageKit;

int main(int argc, char **argv) {
	QCoreApplication app(argc, argv);
	Client c;
	Receiver r;
	QObject::connect(&c, SIGNAL(Finished(Exit::Value, uint)), &r, SLOT(callback(Exit::Value, uint)));
	qDebug() << "We have tid " << c.tid();
	c.searchName("none", "vim");
	return app.exec();
}

