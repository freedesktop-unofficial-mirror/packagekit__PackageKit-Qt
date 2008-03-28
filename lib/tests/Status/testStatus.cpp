#include <QtCore>
#include <QtDBus>

#include "../../Client.h"

using namespace PackageKit;

int main(int argc, char **argv) {
	QCoreApplication app(argc, argv);
	Client c;
	qDebug() << "We have tid " << c.getTid();
	qDebug() << "Status is " << EnumToString<Status>(c.status());
	return app.exec();
}
