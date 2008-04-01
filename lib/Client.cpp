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
	connect(proxy, SIGNAL(ProgressChanged(const QString&, uint, uint, uint, uint)), this,
														SLOT(ProgressChanged_cb(const QString&, uint, uint, uint, uint)));
	connect(proxy, SIGNAL(Description(const QString&, const QString&, const QString&, const QString&, const QString&, const QString&, qulonglong)),
			this, SLOT(Description_cb(const QString&, const QString&, const QString&, const QString&, const QString&, const QString&, qulonglong)));
	connect(proxy, SIGNAL(Files(const QString&, const QString&, const QString&)), this,
														SLOT(Files_cb(const QString&, const QString&, const QString&)));
	connect(proxy, SIGNAL(ErrorCode(const QString&, const QString&, const QString&)), this,
													SLOT(ErrorCode_cb(const QString&, const QString&, const QString&)));
	connect(proxy, SIGNAL(Message(const QString&, const QString&, const QString&)), this,
													SLOT(Message_cb(const QString&, const QString&, const QString&)));
	connect(proxy, SIGNAL(Locked(bool)), this, SIGNAL(Locked(bool)));
	connect(proxy, SIGNAL(AllowCancel(const QString&, bool)), this, SLOT(AllowCancel_cb(const QString&, bool)));
	connect(proxy, SIGNAL(StatusChanged(const QString&, const QString&)), this, SLOT(StatusChanged_cb(const QString&, const QString&)));
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

void Client::searchName(const QString& filter, const QString& name) {
	proxy->SearchName(_tid, filter, name);
}

void Client::searchDetails(const QString& filter, const QString& search) {
	proxy->SearchDetails(_tid, filter, search);
}

void Client::searchGroup(const QString& filter, const QString& group) {
	proxy->SearchGroup(_tid, filter, group);
}

void Client::searchFile(const QString& filter, const QString& file) {
	proxy->SearchFile(_tid, filter, file);
}

void Client::getPackage(const QString& package_id) {
	proxy->GetPackage(package_id);
}

void Client::getDescription(const QString& package_id) {
	proxy->GetDescription(_tid, package_id);
}

void Client::getDescription(Package *p) {
	getDescription(p->id());
}

void Client::getDepends(Package *p, bool recursive) {
	proxy->GetDepends(_tid, p->id(), recursive);
}

void Client::getRequires(Package *p, bool recursive) {
	proxy->GetRequires(_tid, p->id(), recursive);
}

void Client::installPackage(Package *p) {
	proxy->InstallPackage(_tid, p->id());
}

void Client::installFile(const QString& path) {
	proxy->InstallFile(_tid, path);
}

void Client::getUpdates() {
	proxy->GetUpdates(_tid);
}

void Client::updatePackage(Package *p) {
	proxy->UpdatePackage(_tid, p->id());
}

void Client::updateSystem() {
	proxy->UpdateSystem(_tid);
}

void Client::cancel() {
	proxy->Cancel(_tid);
}

void Client::getProgress() {
	uint percentage, subpercentage, elapsed, remaining;
	percentage = proxy->GetProgress(_tid, subpercentage, elapsed, remaining);
	emit ProgressChanged(percentage, subpercentage, elapsed, remaining);
}

void Client::refreshCache(bool force) {
	proxy->RefreshCache(_tid, force);
}

void Client::backendDetails(QString *name, QString *author) {
	QString n, a;
	n = proxy->GetBackendDetail(a);
	name = &n;
	author = &a;
}

QStringList Client::getActions() {
	QString actions = proxy->GetActions();
	return actions.split(";");
}

QStringList Client::getFilters() {
	QString filters = proxy->GetFilters();
	return filters.split(";");
}

QStringList Client::getGroups() {
	QString groups = proxy->GetGroups();
	return groups.split(";");
}

//// Signal callbacks
void Client::AllowCancel_cb(const QString& tid, bool allow_cancel) {
	if(!_promiscuous && tid != _tid) return;
	emit AllowCancel(allow_cancel);
}

void Client::Package_cb(const QString& tid, const QString& info, const QString& package_id, const QString& summary) {
	if(!_promiscuous && tid != _tid) return;
	qDebug() << "tid" << tid << "info" << info << "id" << package_id << "sum" << summary;
	emit newPackage(new Package(package_id, info, summary));
}

void Client::Description_cb(const QString &tid, const QString &package_id, const QString &license, const QString &group,
															const QString &detail, const QString &url, qulonglong size) {
	if(!_promiscuous && tid != _tid) return;
	emit Description(new Package(package_id), license, group, detail, url, size);
}

void Client::Finished_cb(const QString& tid, const QString& status, uint runtime) {
	if(!_promiscuous && tid != _tid) return;
	emit Finished((Exit::Value)EnumFromString<Exit>(status), runtime);
}

void Client::ProgressChanged_cb(const QString& tid, uint percentage, uint subpercentage, uint elapsed, uint remaining) {
	if(!_promiscuous && tid != _tid) return;
	emit ProgressChanged(percentage, subpercentage, elapsed, remaining);
}

void Client::Files_cb(const QString& tid, const QString& package_id, const QString& files) {
	if(!_promiscuous && tid != _tid) return;
	emit Files(new Package(package_id), files.split(";"));
}

void Client::ErrorCode_cb(const QString& tid, const QString& code, const QString& details) {
	if(!_promiscuous && tid != _tid) return;
	emit ErrorCode(code, details);
}

void Client::Message_cb(const QString& tid, const QString& message, const QString& details) {
	if(!_promiscuous && tid != _tid) return;
	emit Message(message, details);
}

void Client::StatusChanged_cb(const QString& tid, const QString& status) {
	if(!_promiscuous && tid != _tid) return;
	emit StatusChanged((Status::Value)EnumFromString<Status>(status));
}
