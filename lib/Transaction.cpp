#include "Transaction.h"
#include "constants.h"

using namespace PackageKit;

Transaction::Transaction(QString tid, QObject *parent) : QObject(parent) {
	_tid = tid;
	proxy = new TransactionProxy(PK_NAME, (tid).toAscii().data() , QDBusConnection::systemBus(), this);
	qDebug() << "trying to create new transaction with path" << (tid).toAscii().data();
	if(!proxy->isValid()) qFatal("Error, cannot create transaction");

	connect(proxy, SIGNAL(Package(const QString&, const QString&, const QString&)), this, SLOT(Package_cb(const QString&, const QString&, const QString&)));
	connect(proxy, SIGNAL(Details(const QString&, const QString&, const QString&, const QString&, const QString&, qulonglong)), this, SLOT(Details_cb(const QString&, const QString&, const QString&, const QString&, const QString&, qulonglong)));
	connect(proxy, SIGNAL(Finished(const QString&, uint)), this, SLOT(Finished_cb(const QString&, uint)));
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

// Signal callbacks

void Transaction::Package_cb(const QString &info, const QString &package_id, const QString &summary) {
	emit GotPackage(new Package(package_id, info, summary, this));
}

void Transaction::Details_cb(const QString &package_id, const QString &license, const QString &group, const QString &detail, const QString &url, qulonglong size) {
	emit Details(new Package(package_id), license, group, detail, url, size);
}

void Transaction::Finished_cb(const QString& exit, uint runtime) {
	emit Finished((Exit::Value)EnumFromString<Exit>(exit), runtime);
}