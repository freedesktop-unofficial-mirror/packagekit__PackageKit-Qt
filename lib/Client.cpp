#include "Client.h"
#include "constants.h"
#include "Status.h"

using namespace PackageKit;

Client::Client(QObject *parent) : QObject(parent) {
	proxy = new DBusProxy(PK_NAME, PK_PATH, QDBusConnection::systemBus(), this);
	_promiscuous = false; // Don't listen on all signals by default
	getTid();

	connect(proxy, SIGNAL(Package(const QString&, const QString&, const QString&, const QString&)), this,
									SLOT(Package_cb(const QString&, const QString&, const QString&, const QString&)));
	connect(proxy, SIGNAL(Finished(const QString&, const QString&, uint)), this, SLOT(Finished_cb(const QString&, const QString&, uint)));
}

Client::~Client() {

}

bool Client::setPromiscuous(bool enabled) {
	if(_tid != QString()) { // The doc says we can only set promiscuous mode on a tid-less instance
		return false;
	}
	_promiscuous = enabled;
	return true;
}

// Tid related functions

void Client::getTid() {
	_tid = proxy->GetTid().value();
}

void Client::setTid(QString newTid) {
	_tid = newTid;
}

const QString& Client::tid() {
	return _tid;
}

bool Client::allowCancel() {
	if(_tid == QString()) return false;
	return proxy->GetAllowCancel(_tid).value();
}

Status::Value Client::status() {
	return (Status::Value)EnumFromString<Status>(proxy->GetStatus(_tid).value());
}

Role::Value Client::role(QString &package_id) {
	return (Role::Value)EnumFromString<Role>(proxy->GetRole(_tid, package_id));
}

void Client::searchName(QString filter, QString name) {
	proxy->SearchName(_tid, filter, name);
}

void Client::cancel() {
	proxy->Cancel(_tid);
}


void Client::backendDetails(QString *name, QString *author) {
	QString n, a;
	n = proxy->GetBackendDetail(a);
	name = &n;
	author = &a;
}

//// Signal callbacks

void Client::Package_cb(const QString& tid, const QString& info, const QString& package_id, const QString& summary) {
	if(!_promiscuous && tid != _tid) return;
	qDebug() << "tid" << tid << "info" << info << "id" << package_id << "sum" << summary;
	emit newPackage(new Package(package_id, info, summary));
}

void Client::Finished_cb(const QString& tid, const QString& status, uint runtime) {
	if(!_promiscuous && tid != _tid) return;
	emit Finished((Exit::Value)EnumFromString<Exit>(status), runtime);
}

void Client::ProgressChanged_cb(const QString& tid, uint percentage, uint subpercentage, uint elapsed, uint remaining) {
	if(!_promiscuous && tid != _tid) return;
	emit ProgressChanged(percentage, subpercentage, elapsed, remaining);
}
