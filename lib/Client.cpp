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

void Client::searchName(QString filter, QString name) {
	qDebug() << "searching for"<< name << "with filters" << filter;
	proxy->SearchName(_tid, filter, name);
}

void Client::Package_cb(const QString& tid, const QString& info, const QString& package_id, const QString& summary) {
	if(!_promiscuous && tid != _tid) return;
	qDebug() << "tid" << tid << "info" << info << "id" << package_id << "sum" << summary;
	emit newPackage(new Package(package_id, info, summary));
}

Role::Value Client::role(QString &package_id) {
	return (Role::Value)EnumFromString<Role>(proxy->GetRole(_tid, package_id));
}
