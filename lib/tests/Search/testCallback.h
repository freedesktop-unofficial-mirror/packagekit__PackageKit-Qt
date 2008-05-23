#ifndef TESTCALLBACK
#define TESTCALLBACK

#include <QtCore>

#include "../../QPackageKit.h"

namespace PackageKit {

class TestCallback : public QObject {

	Q_OBJECT

public:
	TestCallback(QObject *parent = 0);

public slots:
	void newPackage(Package *p);

};

} // End namespace PackageKit

#endif

