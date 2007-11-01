#include "QPackageKitClient.h"

QPackageKitClient::QPackageKitClient(QObject *parent) : QObject(parent) {
	iface = new QPackageKitInterface(PK_DBUS_SERVICE, PK_DBUS_PATH, QDBusConnection::systemBus());

	connect(iface, SIGNAL(Package(const QString, const QString, const QString, const QString)), this,
				SLOT(proxy_Package(const QString, const QString, const QString, const QString)));

	connect(iface, SIGNAL(Finished(const QString, const QString, uint)), this,
				SLOT(proxy_Finished(const QString, const QString, uint)));
	connect(iface, SIGNAL(ProgressChanged(const QString, uint, uint, uint, uint)), this,
		SLOT(proxy_ProgressChanged(const QString, uint,uint, uint, uint)));
	connect(iface, SIGNAL(Description(const QString&, const QString&, const QString&, const QString&, const QString&, const QString&,
		qulonglong, const QString&)), this, SLOT(proxy_Description(const QString&, const QString&, const QString&, const QString&,
									const QString&,	const QString&, qulonglong, const QString&)));
}

void QPackageKitClient::printErrorMessage() {
	qDebug() << "DBus error : " << iface->lastError().name() << " : " << iface->lastError().message();
}

//! Allocates a transation id. You have to do this in order to be able to follow the progress of
//! your operations, since they're done asynchronously.
//! \return true if we got a tid, false else
QString QPackageKitClient::allocateTid() {
	QDBusReply<QString> reply = iface->GetTid();
	if(reply.isValid()) {
		tids.append(reply.value());
		qDebug() << "Appended tid " << reply.value();
		return reply.value();
	} else {
		printErrorMessage();
		return QString();
	}
}

void QPackageKitClient::Cancel() {
	for(int i = 0 ; i < tids.size() ; ++i)
		iface->Cancel(tids.at(i));
}

//! Searches for a package using its name. You can also provide a filter (see Filter)
//! Each time a package is found, the Package signal will be fired
//! \param name The name of the package
//! \param filter A filter
//! \return true if succeded, false else
bool QPackageKitClient::searchName(QString name, QList<Filter::FilterEnum> filters) {
	QString mytid = allocateTid();
	qDebug() << "Search for " << name << " with tid " << mytid;

	QStringList strFilters;
	for(int i = 0 ; i < filters.size() ; ++i) {
		strFilters.append(Filter::toString(filters.at(i)));
	}

	QDBusReply<void> reply = iface->SearchName(mytid, strFilters.size() > 0 ? strFilters.join(";") : "none", name);
	if(reply.isValid()) {
		return true;
	} else {
		printErrorMessage();
		return false;
	}
}

bool QPackageKitClient::getDescription(QString packageId) {
	QString mytid = allocateTid();

	QDBusReply<void> reply = iface->GetDescription(mytid, packageId);
	if(reply.isValid()) {
		return true;
	} else {
		printErrorMessage();
		return false;
	}
}

bool QPackageKitClient::getDescription(PkPackage *p) {
	return getDescription(p->id());
}

bool QPackageKitClient::installPackage(QString packageId) {
	QString myTid = allocateTid();

	QDBusReply<void> reply = iface->InstallPackage(myTid, packageId);
	if(reply.isValid()) {
		return true;
	} else {
		printErrorMessage();
		return false;
	}
}

bool QPackageKitClient::installPackage(PkPackage *p) {
	return installPackage(p->id());
}

void QPackageKitClient::proxy_Package(const QString &thisTid, const QString &info, const QString &package_id, const QString &summary) {
	// If we're not concerned by this transaction
	if(!tids.contains(thisTid)) return;
	emit Package(info, package_id, summary);
}

void QPackageKitClient::proxy_Finished(const QString &thisTid, const QString &status, uint runtime) {
	// If we're not concerned by this transaction
	if(!tids.contains(thisTid)) return;
	qDebug() << "Transaction " << thisTid << " finished with status " << status << "removing tid " << thisTid;
	tids.removeAt(tids.indexOf(thisTid));
	emit Finished(Exit::fromString(status), runtime);
}


void QPackageKitClient::proxy_ProgressChanged(const QString &thisTid, uint percentage, uint subpercentage, uint elapsed, uint remaining) {
	// If we're not concerned by this transaction
	if(!tids.contains(thisTid)) return;
	
	if(percentage == 101) {
		emit NoProgressUpdates();
	} else {
		emit ProgressChanged(percentage, subpercentage, elapsed, remaining);
	}
}


void QPackageKitClient::proxy_Description(const QString &thisTid, const QString &package_id, const QString &licence, const QString &group,
						const QString &detail, const QString &url, qulonglong size, const QString &file_list) {
	// If we're not concerned by this transaction
	if(!tids.contains(thisTid)) return;

	emit Description(package_id, licence, group, detail, url, size, file_list);
}

