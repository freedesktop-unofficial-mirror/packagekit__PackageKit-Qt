#include "Transaction.h"
#include "Daemon.h"
#include "constants.h"

using namespace PackageKit;

Transaction::Transaction(Daemon *parent) : QObject(parent), parent(parent) {
	_tid = QString();
	proxy = NULL;
}

Transaction::~Transaction() {
}

void Transaction::renewTid() {
	if(_tid != QString()) return;
	_tid = parent->getTid() ;
	proxy = new TransactionProxy(PK_NAME, (_tid).toAscii().data() , QDBusConnection::systemBus(), this);
	qDebug() << "trying to create new transaction with path" << (_tid).toAscii().data();
	if(!proxy->isValid()) qFatal("Error, cannot create transaction");

	connect(proxy, SIGNAL(Package(const QString&, const QString&, const QString&)), this, SLOT(Package_cb(const QString&, const QString&, const QString&)));
	connect(proxy, SIGNAL(Details(const QString&, const QString&, const QString&, const QString&, const QString&, qulonglong)), this, SLOT(Details_cb(const QString&, const QString&, const QString&, const QString&, const QString&, qulonglong)));
	connect(proxy, SIGNAL(Files(const QString&, const QString&)), this, SLOT(Files_cb(const QString&, const QString&)));
	connect(proxy, SIGNAL(Finished(const QString&, uint)), this, SLOT(Finished_cb(const QString&, uint)));
	connect(proxy, SIGNAL(ProgressChanged(uint, uint, uint, uint)), this, SIGNAL(ProgressChanged(uint, uint, uint, uint)));
	connect(proxy, SIGNAL(UpdateDetail(const QString&, const QString&, const QString&, const QString&, const QString&, const QString&, const QString&, const QString&)), this, SIGNAL(UpdateDetail(const QString&, const QString&, const QString&, const QString&, const QString&, const QString&, const QString&, const QString&)));
	connect(proxy, SIGNAL(RequireRestart(const QString&, const QString&)), this, SIGNAL(RequireRestart(const QString&, const QString&)));
	connect(proxy, SIGNAL(AllowCancel(bool)), this, SIGNAL(AllowCancel(bool)));
	connect(proxy, SIGNAL(ErrorCode(const QString&, const QString&)), this, SIGNAL(ErrorCode(const QString&, const QString&)));
	connect(proxy, SIGNAL(Message(const QString&, const QString&)), this, SIGNAL(Message(const QString&, const QString&)));
	connect(proxy, SIGNAL(StatusChanged(const QString&)), this, SLOT(StatusChanged_cb(const QString&)));
	connect(proxy, SIGNAL(RepoDetail(const QString&, const QString&, bool)), this, SIGNAL(RepoDetail(const QString&, const QString&, bool)));

}

bool Transaction::allowCancel() {
	renewTid();
	return proxy->GetAllowCancel();
}

void Transaction::cancel() {
	if(proxy)
		proxy->Cancel();
}

Role::Value Transaction::getRole(Package *p) {
	renewTid();
	QString pid;
	Role::Value role = (Role::Value)EnumFromString<Role>(proxy->GetRole(pid));
	if(p != NULL) p = new Package(pid);
	return role;
}

Status::Value Transaction::getStatus() {
	renewTid();
	return (Status::Value)EnumFromString<Status>(proxy->GetStatus());
}

void Transaction::searchName(const QString& filter, const QString& name) {
	renewTid();
	proxy->SearchName(filter, name);
}

void Transaction::searchDetails(const QString &filter, const QString& search) {
	renewTid();
	proxy->SearchDetails(filter, search);
}

void Transaction::searchGroup(const QString &filter, const QString& search) {
	renewTid();
	proxy->SearchGroup(filter, search);
}

void Transaction::searchFile(const QString &filter, const QString& file) {
	renewTid();
	proxy->SearchFile(filter, file);
}

void Transaction::getPackages(const QString& filter) {
	renewTid();
	proxy->GetPackages(filter);
}

void Transaction::getDetails(Package *p) {
	renewTid();
	proxy->GetDetails(p->id());
}

void Transaction::getFiles(Package *p) {
	renewTid();
	proxy->GetFiles(p->id());
}

void Transaction::getDepends (Package *p, const QString& filter, bool recursive) {
	renewTid();
	proxy->GetDepends(p->id(), filter, recursive);
}

void Transaction::getRequires (Package *p, const QString& filter, bool recursive) {
	renewTid();
	proxy->GetDepends(p->id(), filter, recursive);
}

void Transaction::whatProvides(const QString &filter, const Provides::Value &type, const QString& search) {
	renewTid();
	proxy->WhatProvides(filter, EnumToString<Provides>(type), search);
}

void Transaction::resolve(const QString &filter, Package *p) {
	renewTid();
	proxy->Resolve(filter, p->id());
}

void Transaction::installPackages(const QList<Package*> &packages) {
	renewTid();
	QStringList pids;
	for(int i = 0 ; i < packages.size() ; ++i) pids << packages.at(i)->id();
	proxy->InstallPackages(pids);
}

void Transaction::installPackage(Package *p) {
	renewTid();
	QStringList pids;
	pids << p->id();
	proxy->InstallPackages(pids);
}

void Transaction::installSignature(const SignatureType::Value &type, const QString &key_id, Package *p) {
	renewTid();
	proxy->InstallSignature(EnumToString<SignatureType>(type), key_id, p->id());
}

void Transaction::updatePackages(const QList<Package*> &packages) {
	renewTid();
	QStringList pids;
	for(int i = 0 ; i < packages.size() ; ++i) pids << packages.at(i)->id();
	proxy->UpdatePackages(pids);
}

void Transaction::updatePackage(Package *p) {
	renewTid();
	QStringList pids;
	pids << p->id();
	proxy->UpdatePackages(pids);
}

void Transaction::installFiles(const QStringList& files, bool trusted) {
	renewTid();
	proxy->InstallFiles(trusted, files);
}

void Transaction::removePackages(const QList<Package*> &packages, bool allow_deps, bool autoremove) {
	renewTid();
	QStringList pids;
	for(int i = 0 ; i < packages.size() ; ++i) pids << packages.at(i)->id();
	proxy->RemovePackages(pids, allow_deps, autoremove);
}

void Transaction::removePackage(Package *p, bool allow_deps, bool autoremove) {
	QStringList pids;
	pids << p->id();
	proxy->RemovePackages(pids, allow_deps, autoremove);
}

void Transaction::updateSystem() {
	renewTid();
	proxy->UpdateSystem();
}

void Transaction::rollback(const QString &tid) {
	renewTid();
	proxy->Rollback(tid);
}

void Transaction::getUpdates(const QString& filter) {
	renewTid();
	proxy->GetUpdates(filter);
}

void Transaction::getUpdateDetail(const QString& package_id) {
	renewTid();
	proxy->GetUpdateDetail(package_id);
}

void Transaction::refreshCache(bool force) {
	renewTid();
	proxy->RefreshCache(force);
}

void Transaction::getProgress(uint &percentage, uint &subpercentage, uint &elapsed, uint &remaining) {
	percentage = proxy->GetProgress(subpercentage, elapsed, remaining);
}

void Transaction::getRepoList(const QString &filter) {
	renewTid();
	proxy->GetRepoList(filter);
}

void Transaction::repoEnable(const QString &repo_id, bool enabled) {
	renewTid();
	proxy->RepoEnable(repo_id, enabled);
}

void Transaction::repoSetData(const QString &repo_id, const QString &parameter, const QString &value) {
	renewTid();
	proxy->RepoSetData(repo_id, parameter, value);
}

bool Transaction::isCallerActive() {
	if(_tid == QString()) return false;
	return proxy->IsCallerActive();
}

// Signal callbacks

void Transaction::Package_cb(const QString &info, const QString &package_id, const QString &summary) {
	emit GotPackage(new Package(package_id, info, summary, this));
}

void Transaction::Details_cb(const QString &package_id, const QString &license, const QString &group, const QString &detail, const QString &url, qulonglong size) {
	emit Details(new Package(package_id), license, group, detail, url, size);
}

void Transaction::Files_cb(const QString &pid, const QString &file_list) {
	emit Files(new Package(pid), file_list.split(";"));
}

void Transaction::Finished_cb(const QString& exit, uint runtime) {
	_tid = QString();
	emit Finished((Exit::Value)EnumFromString<Exit>(exit), runtime);
}

void Transaction::StatusChanged_cb(const QString &status) {
	emit StatusChanged((Status::Value)EnumFromString<Status>(status));
}

