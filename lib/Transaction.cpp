/*
* Copyright (C) 2007 Adrien Bustany <madcat@mymadcat.com>
*
* Licensed under the GNU General Public License Version 2
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 See MA 02111-1307, USA.
*
*/

#include "Transaction.h"
#include "Daemon.h"
#include "constants.h"
#include "PolkitClient.h"

using namespace PackageKit;

Transaction::Transaction(Daemon *parent) : QObject(parent), parent(parent) {
	_tid = QString();
	proxy = NULL;

	polkit = new PolkitClient(this);
}

Transaction::~Transaction() {
}

bool Transaction::renewTid() {
	if(_tid != QString()) return true;
	_tid = parent->getTid() ;
	proxy = new TransactionProxy(PK_NAME, (_tid).toAscii().data() , QDBusConnection::systemBus(), this);
	qDebug() << "trying to create new transaction with path" << (_tid).toAscii().data();
	if(!proxy->isValid()) {
		emit ErrorCode(Error::Failed_initialization, QString("Failed to get a tid"));
		return false;
	}

	connect(proxy, SIGNAL(Package(const QString&, const QString&, const QString&)), this, SLOT(Package_cb(const QString&, const QString&, const QString&)));
	connect(proxy, SIGNAL(Details(const QString&, const QString&, const QString&, const QString&, const QString&, qulonglong)), this, SLOT(Details_cb(const QString&, const QString&, const QString&, const QString&, const QString&, qulonglong)));
	connect(proxy, SIGNAL(Files(const QString&, const QString&)), this, SLOT(Files_cb(const QString&, const QString&)));
	connect(proxy, SIGNAL(Finished(const QString&, uint)), this, SLOT(Finished_cb(const QString&, uint)));
	connect(proxy, SIGNAL(ProgressChanged(uint, uint, uint, uint)), this, SIGNAL(ProgressChanged(uint, uint, uint, uint)));
	connect(proxy, SIGNAL(UpdateDetail(const QString&, const QString&, const QString&, const QString&, const QString&, const QString&, const QString&, const QString&)), this, SIGNAL(UpdateDetail(const QString&, const QString&, const QString&, const QString&, const QString&, const QString&, const QString&, const QString&)));
	connect(proxy, SIGNAL(RequireRestart(const QString&, const QString&)), this, SIGNAL(RequireRestart(const QString&, const QString&)));
	connect(proxy, SIGNAL(AllowCancel(bool)), this, SIGNAL(AllowCancel(bool)));
	connect(proxy, SIGNAL(ErrorCode(const QString&, const QString&)), this, SLOT(ErrorCode_cb(const QString&, const QString&)));
	connect(proxy, SIGNAL(Message(const QString&, const QString&)), this, SIGNAL(Message(const QString&, const QString&)));
	connect(proxy, SIGNAL(StatusChanged(const QString&)), this, SLOT(StatusChanged_cb(const QString&)));
	connect(proxy, SIGNAL(RepoDetail(const QString&, const QString&, bool)), this, SIGNAL(RepoDetail(const QString&, const QString&, bool)));
	connect(proxy, SIGNAL(Transaction(const QString&, const QString&, bool, const QString&, uint, const QString&)), SLOT(Transaction_cb(const QString&, const QString&, bool, const QString&, uint, const QString&)));
	connect(proxy, SIGNAL(EulaRequired(const QString&, const QString&, const QString&, const QString&)), SLOT(EulaRequired_cb(const QString&, const QString&, const QString&, const QString&)));
	connect(proxy, SIGNAL(RepoSignatureRequired(const QString&, const QString&, const QString&, const QString&, const QString&, const QString&, const QString&, const QString&)), this, SLOT(RepoSignatureRequired_cb(const QString&, const QString&, const QString&, const QString&, const QString&, const QString&, const QString&, const QString&)));
	connect(proxy, SIGNAL(CallerActiveChanged(bool)), this, SIGNAL(CallerActiveChanged(bool)));
	return true;
}

bool Transaction::allowCancel() {
	if(!renewTid()) return false;
	return proxy->GetAllowCancel();
}

void Transaction::cancel() {
	if(proxy)
		proxy->Cancel();
}

Role::Value Transaction::getRole(Package *p) {
	if(!renewTid()) return Role::Unknown;
	QString pid;
	Role::Value role = (Role::Value)EnumFromString<Role>(proxy->GetRole(pid));
	if(p != NULL) p = new Package(pid);
	return role;
}

Status::Value Transaction::getStatus() {
	if(!renewTid()) return Status::Unknown;
	return (Status::Value)EnumFromString<Status>(proxy->GetStatus());
}

void Transaction::searchName(const QString& filter, const QString& name) {
	if(!renewTid()) return;
	proxy->SearchName(filter, name);
}

void Transaction::searchDetails(const QString &filter, const QString& search) {
	if(!renewTid()) return;
	proxy->SearchDetails(filter, search);
}

void Transaction::searchGroup(const QString &filter, const Groups::Value &group) {
	if(!renewTid()) return;
	proxy->SearchGroup(filter, EnumToString<Groups>(group));
}

void Transaction::searchFile(const QString &filter, const QString& file) {
	if(!renewTid()) return;
	proxy->SearchFile(filter, file);
}

void Transaction::getPackages(const QString& filter) {
	if(!renewTid()) return;
	proxy->GetPackages(filter);
}

void Transaction::getDetails(Package *p) {
	if(!renewTid()) return;
	proxy->GetDetails(p->id());
}

void Transaction::getFiles(Package *p) {
	if(!renewTid()) return;
	proxy->GetFiles(p->id());
}

void Transaction::getDepends (const QString& filter, Package *p, bool recursive) {
	if(!renewTid()) return;
	proxy->GetDepends(filter, p->id(), recursive);
}

void Transaction::getRequires ( const QString& filter, Package *p, bool recursive) {
	if(!renewTid()) return;
	proxy->GetRequires(filter, p->id(), recursive);
}

void Transaction::whatProvides(const QString &filter, const Provides::Value &type, const QString& search) {
	if(!renewTid()) return;
	proxy->WhatProvides(filter, EnumToString<Provides>(type), search);
}

void Transaction::resolve(const QString &filter, Package *p) {
	if(!renewTid()) return;
	proxy->Resolve(filter, p->id());
}

bool Transaction::installPackages(const QList<Package*> &packages) {
	if(!renewTid()) return false;
	QStringList pids;
	for(int i = 0 ; i < packages.size() ; ++i) pids << packages.at(i)->id();
	// hopefully do the operation first time
	if ( proxy->InstallPackages(pids).isValid() )
		return true;
	else {
		// ok no lucky...
		if ( polkit->getAuth(AUTH_PACKAGE_INSTALL) )
			return proxy->InstallPackages(pids).isValid();
		else
			return false;
	}
}

bool Transaction::installPackage(Package *p) {
	QList<Package*> packages;
	packages << p;
	return installPackages(packages);
}

bool Transaction::installSignature(const SignatureType::Value &type, const QString &key_id, Package *p) {
	if(!renewTid()) return false;
	// hopefully do the operation first time
	if ( proxy->InstallSignature(EnumToString<SignatureType>(type), key_id, p->id()).isValid() )
		return true;
	else {
		// ok no lucky...
		if ( polkit->getAuth(AUTH_SYSTEM_TRUST_SIGNING_KEY) )
			return proxy->InstallSignature(EnumToString<SignatureType>(type), key_id, p->id()).isValid();
		else
			return false;
	}
}

bool Transaction::updatePackages(const QList<Package*> &packages) {
	if(!renewTid()) return false;
	QStringList pids;
	for(int i = 0 ; i < packages.size() ; ++i) pids << packages.at(i)->id();
	// hopefully do the operation first time
	if ( proxy->UpdatePackages(pids).isValid() )
		return true;
	else {
		// ok no lucky...
		if ( polkit->getAuth(AUTH_SYSTEM_UPDATE) )
			return proxy->UpdatePackages(pids).isValid();
		else
			return false;
	}
}

bool Transaction::updatePackage(Package *p) {
	if(!renewTid()) return false;
	QStringList pids;
	pids << p->id();
	// hopefully do the operation first time
	if ( proxy->UpdatePackages(pids).isValid() )
		return true;
	else {
		// ok no lucky...
		if ( polkit->getAuth(AUTH_SYSTEM_UPDATE) )
			return proxy->UpdatePackages(pids).isValid();
		else
			return false;
	}
}

bool Transaction::installFiles(const QStringList& files, bool trusted) {
	if(!renewTid()) return false;
	// hopefully do the operation first time
	if ( proxy->InstallFiles(trusted, files).isValid() )
		return true;
	else {
		// ok no lucky...
		if ( polkit->getAuth((trusted ? AUTH_PACKAGE_INSTALL : AUTH_PACKAGE_INSTALL_UNTRUSTED)) )
			return proxy->InstallFiles(trusted, files).isValid();
		else
			return false;
	}
}

bool Transaction::removePackages(const QList<Package*> &packages, bool allow_deps, bool autoremove) {
	if(!renewTid()) return false;
	QStringList pids;
	for(int i = 0 ; i < packages.size() ; ++i) pids << packages.at(i)->id();
	// hopefully do the operation first time
	if ( proxy->RemovePackages(pids, allow_deps, autoremove).isValid() )
		return true;
	else {
		// ok no lucky...
		if ( polkit->getAuth(AUTH_PACKAGE_REMOVE) )
			return proxy->RemovePackages(pids, allow_deps, autoremove).isValid();
		else
			return false;
	}
}

bool Transaction::removePackage(Package *p, bool allow_deps, bool autoremove) {
	QList<Package*> packages;
	packages << p;
	return removePackages(packages, allow_deps, autoremove);
}

bool Transaction::updateSystem() {
	if(!renewTid()) return false;
	// hopefully do the operation first time
	if ( proxy->UpdateSystem().isValid() )
		return true;
	else {
		// ok no lucky...
		if ( polkit->getAuth(AUTH_SYSTEM_UPDATE) )
			return proxy->UpdateSystem().isValid();
		else
			return false;
	}
}

bool Transaction::rollback(const QString &tid) {
	if(!renewTid()) return false;
	// hopefully do the operation first time
	if ( proxy->Rollback(tid).isValid() )
		return true;
	else {
		// ok no lucky...
		if ( polkit->getAuth(AUTH_SYSTEM_ROLLBACK) )
			return proxy->Rollback(tid).isValid();
		else
			return false;
	}
}

void Transaction::getUpdates(const QString& filter) {
	if(!renewTid()) return;
	proxy->GetUpdates(filter);
}

void Transaction::getUpdateDetail(const QString& package_id) {
	if(!renewTid()) return;
	proxy->GetUpdateDetail(package_id);
}

bool Transaction::refreshCache(bool force) {
	if(!renewTid()) return false;
	// hopefully do the operation first time
	if ( proxy->RefreshCache(force).isValid() )
		return true;
	else {
		// ok no lucky...
		if ( polkit->getAuth(AUTH_SYSTEM_SOURCES_REFRESH) )
			return proxy->RefreshCache(force).isValid();
		else
			return false;
	}
}

void Transaction::getProgress(uint &percentage, uint &subpercentage, uint &elapsed, uint &remaining) {
	percentage = proxy->GetProgress(subpercentage, elapsed, remaining);
}

void Transaction::getRepoList(const QString &filter) {
	if(!renewTid()) return;
	proxy->GetRepoList(filter);
}

bool Transaction::repoEnable(const QString &repo_id, bool enabled) {
	if(!renewTid()) return false;
	// hopefully do the operation first time
	if ( proxy->RepoEnable(repo_id, enabled).isValid() )
		return true;
	else {
		// ok no lucky...
		if ( polkit->getAuth(AUTH_SYSTEM_SOURCES_CONFIGURE) )
			return proxy->RepoEnable(repo_id, enabled).isValid();
		else
			return false;
	}
}

bool Transaction::repoSetData(const QString &repo_id, const QString &parameter, const QString &value) {
	if(!renewTid()) return false;
	// hopefully do the operation first time
	if ( proxy->RepoSetData(repo_id, parameter, value).isValid() )
		return true;
	else {
		// ok no lucky...
		if ( polkit->getAuth(AUTH_SYSTEM_SOURCES_CONFIGURE) )
			return proxy->RepoSetData(repo_id, parameter, value).isValid();
		else
			return false;
	}
}

bool Transaction::isCallerActive() {
	if(_tid == QString()) return false;
	return proxy->IsCallerActive();
}

void Transaction::getOldTransactions(uint number) {
	if(!renewTid()) return;
	proxy->GetOldTransactions(number);
}

bool Transaction::acceptEula(const QString &id) {
	if(!renewTid()) return false;
	// hopefully do the operation first time
	if ( proxy->AcceptEula(id).isValid() )
		return true;
	else {
		// ok no lucky...
		if ( polkit->getAuth(AUTH_PACKAGE_EULA_ACCEPT) )
			return proxy->AcceptEula(id).isValid();
		else
			return false;
	}
}

// Signal callbacks

void Transaction::Package_cb(const QString &info, const QString &package_id, const QString &summary) {
	emit GotPackage(new Package(package_id, (Info::Value)EnumFromString<Info>(info), summary, this));
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

void Transaction::ErrorCode_cb(const QString &code, const QString &details) {
	emit ErrorCode((Error::Value)EnumFromString<Error>(code), details);
}

void Transaction::StatusChanged_cb(const QString &status) {
	emit StatusChanged((Status::Value)EnumFromString<Status>(status));
}

void Transaction::Transaction_cb(const QString &tid, const QString &timespec, bool succeeded, const QString &role, uint duration, const QString& data) {
	emit OldTransaction(tid, timespec, succeeded, (Role::Value)EnumFromString<Role>(role), duration, data);
}

void Transaction::EulaRequired_cb(const QString &id, const QString &package_id, const QString &vendor_name, const QString &agreement) {
	emit EulaRequired(id, new Package(package_id, this), vendor_name, agreement);
}

void Transaction::RepoSignatureRequired_cb(const QString &package_id, const QString &repository_name, const QString &key_url, const QString &key_userid, const QString &key_id, const QString &key_fingerprint, const QString &key_timestamp, const QString &type) {
	emit RepoSignatureRequired(new Package(package_id), repository_name, key_url, key_userid, key_id, key_fingerprint, key_timestamp, (SignatureType::Value)EnumFromString<SignatureType>(type));
}

