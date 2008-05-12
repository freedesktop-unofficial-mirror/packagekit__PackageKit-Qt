#include "testCallback.h"

using namespace PackageKit;

TestCallback::TestCallback(QObject *parent) : QObject(parent) {
}

void TestCallback::newPackage(Package *p) {
	qDebug() << p->id();
}
