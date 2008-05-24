#include <QtCore>

#include "../../QPackageKit.h"

using namespace PackageKit;

int main(int argc, char **argv) {
	Daemon d;
	QString name, author;
	d.getBackendDetails(name, author);
	qDebug() << "We use the backend" << name << ", it was written by" << author;
	qDebug() << "The backend supports the following actions :" << d.getActions();
	qDebug() << "The backend supports the following filters :" << d.getFilters();
	qDebug() << "The backend supports the following groups :" << d.getGroups();

	return 0;
}
