#include <QtGui>

#include "FilterMenu.h"

int main(int argc, char **argv) {
	QApplication app(argc, argv);
	QStringList filters;
	filters << "installed" << "devel" << "gui" << "free" << "basename";
	FilterMenu menu(filters, 0);
	qDebug() << menu.filters();
	menu.show();
	return app.exec();
}
