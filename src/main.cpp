#include <QApplication>

#include "Connection.h"

using namespace PackageKit;

int main(int argc, char **argv) {
	QApplication app(argc, argv);

	// Init glib types system
	g_type_init();

	Connection *c = new Connection();
	QObject::connect(c, SIGNAL(changed(bool)), &app, SLOT(aboutQt()));

	qDebug() << "Valid connection : " << c->valid();



	return app.exec();
}
