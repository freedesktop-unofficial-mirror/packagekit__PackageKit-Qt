#include <QtCore>

#include "../../QPackageKit.h"

using namespace PackageKit;

int main(int argc, char **argv) {
	Daemon d;
	qDebug() << d.getActions();

	return 0;
}
