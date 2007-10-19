#include "QPackageKitClient.h"

QPackageKitClient::QPackageKitClient(QObject *parent) : QObject(parent) {
	iface = new QPackageKitInterface(PK_DBUS_SERVICE, PK_DBUS_PATH, QDBusConnection::systemBus());

	connect(iface, SIGNAL(Package(const QString, const QString, const QString, const QString)), this,
				SLOT(newPackage(const QString, const QString, const QString, const QString)));

	connect(iface, SIGNAL(Finished(const QString, const QString, uint)), this,
				SLOT(transactionFinished(const QString, const QString, uint)));
}

void QPackageKitClient::printErrorMessage() {
	qDebug() << "DBus error : " << iface->lastError().name() << " : " << iface->lastError().message();
}

//! Allocates a transation id. You have to do this in order to be able to follow the progress of
//! your operations, since they're done asynchronously.
//! \return true if we got a tid, false else
bool QPackageKitClient::allocateTid() {
	// No need to bother if we already got one
	if(tid != QString()) return false;

	QDBusReply<QString> reply = iface->GetTid();
	if(reply.isValid()) {
		tid = reply.value();
		return true;
	} else {
		printErrorMessage();
		return false;
	}
}

//! Searches for a package using its name. You can also provide a filter (see Filter)
//! Each time a package is found, the Package signal will be fired
//! \param name The name of the package
//! \param filter A filter
//! \return true if succeded, false else
bool QPackageKitClient::searchName(QString name, QList<Filter::FilterEnum> filters) {
	allocateTid();
	qDebug() << "Search for " << name << " with tid " << tid;

	QStringList strFilters;
	for(int i = 0 ; i < filters.size() ; ++i) {
		strFilters.append(Filter::toString(filters.at(i)));
	}

	QDBusReply<void> reply = iface->SearchName(tid, strFilters.size() > 0 ? strFilters.join(";") : "none", name);
	if(reply.isValid()) {
		return true;
	} else {
		printErrorMessage();
		return false;
	}
}

void QPackageKitClient::newPackage(const QString &thisTid, const QString &info, const QString &package_id, const QString &summary) {
	// If we're not concerned by this transaction
	if(tid != thisTid) return;
	emit Package(info, package_id, summary);
}

void QPackageKitClient::transactionFinished(const QString &thisTid, const QString &status, uint runtime) {
	// If we're not concerned by this transaction
	if(tid != thisTid) return;
	qDebug() << "Transaction " << tid << " finished with status " << status;
	emit Finished(Exit::Unknown, runtime);
}
