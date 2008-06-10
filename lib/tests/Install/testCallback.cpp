#include "testCallback.h"

using namespace PackageKit;

TestCallback::TestCallback(QObject *parent) : QObject(parent) {
	d = new Daemon(this);
	t = d->newTransaction();
	QObject::connect(t, SIGNAL(Finished(Exit::Value, uint)), this, SLOT(finish()));
	qDebug() << "Installing nedit";
	t->installPackage(new Package("nedit;5.5-18.fc9;x86_64;fedora"));
}

void TestCallback::finish() {
	qDebug() << "Installed";
	QCoreApplication::quit();
}
