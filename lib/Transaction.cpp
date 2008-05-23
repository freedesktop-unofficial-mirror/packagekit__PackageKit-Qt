#include "Transaction.h"
#include "constants.h"

using namespace PackageKit;

Transaction::Transaction(QString tid, QObject *parent) : QObject(parent) {
	_tid = tid;
	proxy = new TransactionProxy(PK_NAME, (tid).toAscii().data() , QDBusConnection::systemBus(), this);
	qDebug() << "trying to create new transaction with path" << (tid).toAscii().data();
	if(!proxy->isValid()) qFatal("Error, cannot create transaction");

	connect(proxy, SIGNAL(Package(const QString&, const QString&, const QString&)), this, SLOT(Package_cb(const QString&, const QString&, const QString&)));
}

Transaction::~Transaction() {
}

void Transaction::cancel() {
	proxy->Cancel();
}

void Transaction::searchName(const QString& filter, const QString& name) {
	qDebug() << "search for " << name;
	proxy->SearchName(filter, name);
}

void Transaction::Package_cb(const QString &info, const QString &package_id, const QString &summary) {
	emit gotPackage(new Package(package_id, info, summary, this));
}
