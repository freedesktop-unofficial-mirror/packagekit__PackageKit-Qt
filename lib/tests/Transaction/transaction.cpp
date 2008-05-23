#include <QtCore>

#include "../../QPackageKit.h"

using namespace PackageKit;

int main(int argc, char **argv) {
	Daemon d;
	Transaction *t = d.newTransaction();

	return 0;
}
