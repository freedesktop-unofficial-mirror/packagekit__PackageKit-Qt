#include "testCallback.h"

using namespace PackageKit;

TestCallback::TestCallback(QObject *parent) : QObject(parent) {
	d = new Daemon(this);
	t = d->newTransaction();
	QObject::connect(t, SIGNAL(GotPackage(Package*)), this, SLOT(newPackage(Package*)));
	QObject::connect(t, SIGNAL(Finished(Exit::Value, uint)), this, SLOT(searchAgain()));
	t->searchName("none", "vim");
}

void TestCallback::newPackage(Package *p) {
	qDebug() << p->id();
}

void TestCallback::searchAgain() {
	t->searchName("none", "vim");
	QObject::connect(t, SIGNAL(Finished(Exit::Value, uint)), this, SLOT(finish()));
}

void TestCallback::finish() {
	QCoreApplication::quit();
}
