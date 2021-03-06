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

#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <QtCore>

#include "TransactionProxy.h"
#include "Package.h"
#include "Provides.h"
#include "SignatureType.h"

// Enums
#include "Exit.h"
#include "Role.h"
#include "Status.h"
#include "Error.h"
#include "Groups.h"

namespace PackageKit {

class Daemon;
class PolkitClient;

class Transaction : public QObject {

	Q_OBJECT

public:
	Transaction(Daemon *parent = 0);
	~Transaction();

	// PackageKit functions
	bool allowCancel();
	void cancel();
	Role::Value getRole(Package *p = NULL);
	Status::Value getStatus();

	void searchName(const QString& filter, const QString& name);
	void searchDetails(const QString &filter, const QString& search);
	void searchGroup(const QString &filter, const Groups::Value &group);
	void searchFile(const QString &filter, const QString& file);
	void getPackages(const QString& filter);
	void getDetails(Package *p);
	void getFiles(Package *p);
	void getDepends(const QString &filter, Package *p, bool recursive = true);
	void getRequires( const QString &filter, Package *p, bool recursive = true);
	void whatProvides(const QString &filter, const Provides::Value &type, const QString& search);
	void resolve(const QString &filter, Package *p);

	bool installPackages(const QList<Package*> &packages);
	bool installPackage(Package *p);
	bool installSignature(const SignatureType::Value &type, const QString &key_id, Package *p);
	bool updatePackages(const QList<Package*> &packages);
	bool updatePackage(Package *p);
	bool installFiles(const QStringList& files, bool trusted = false);
	bool removePackages(const QList<Package*> &packages, bool allow_deps = false, bool autoremove = false);
	bool removePackage(Package *p, bool allow_deps = false, bool autoremove = false);

	bool updateSystem();
	bool rollback(const QString &tid);

	void getUpdates(const QString& filter);
	void getUpdateDetail(const QString& package_id);

	bool refreshCache(bool force = false);
	void getProgress(uint &percentage, uint &subpercentage, uint &elapsed, uint &remaining);
	void getRepoList(const QString &filter);
	bool repoEnable(const QString &repo_id, bool enabled);
	bool repoSetData(const QString &repo_id, const QString &parameter, const QString &value);
	bool isCallerActive();
	void getOldTransactions(uint number);
	bool acceptEula(const QString &id);

signals:
	void GotPackage(Package *p);
	void Details(Package *p, const QString &license, const QString &group, const QString &detail, const QString &url, qulonglong size);
	void Files(Package *p, QStringList files);
	void Finished(Exit::Value status, uint runtime);
	void ProgressChanged(uint percentage, uint subpercentage, uint elapsed, uint remaining);
	void UpdateDetail(const QString &package_id, const QString &updates, const QString &obsoletes, const QString &vendor_url, const QString &bugzilla_url, const QString &cve_url, const QString &restart, const QString &update_text);
	void RequireRestart(const QString&, const QString&);
	void AllowCancel(bool allow_cancel);
    void ErrorCode(Error::Value, const QString &details);
    void Message(const QString &message, const QString &details);
	void StatusChanged(Status::Value v);
	void RepoDetail(const QString &repo_id, const QString &details, bool enabled);
	void OldTransaction(const QString &tid, const QString &timespec, bool succeeded, Role::Value role, uint duration, const QString& data);
	void EulaRequired(const QString &id, Package *p, const QString &vendor_name, const QString &agreement);
	void RepoSignatureRequired(Package *p, const QString &repository_name, const QString &key_url, const QString &key_userid, const QString &key_id, const QString &key_fingerprint, const QString &key_timestamp, SignatureType::Value type);
	void CallerActiveChanged(bool active);

private slots:
	void Package_cb(const QString &info, const QString &package_id, const QString &summary);
	void Details_cb(const QString &package_id, const QString &license, const QString &group, const QString &detail, const QString &url, qulonglong size);
	void Files_cb(const QString &pid, const QString &file_list);
	void Finished_cb(const QString& exit, uint runtime);
	void ErrorCode_cb(const QString &code, const QString &details);
	void StatusChanged_cb(const QString& status);
	void Transaction_cb(const QString &tid, const QString &timespec, bool succeeded, const QString &role, uint duration, const QString& data);
	void EulaRequired_cb(const QString &id, const QString &package_id, const QString &vendor_name, const QString &agreement);
	void RepoSignatureRequired_cb(const QString &package_id, const QString &repository_name, const QString &key_url, const QString &key_userid, const QString &key_id, const QString &key_fingerprint, const QString &key_timestamp, const QString &type);

private:
	TransactionProxy *proxy;
	Daemon *parent;
	QString _tid;
	// Get a new TID if needed
	bool renewTid();

	PolkitClient *polkit;

};

} // End namespace PackageKit

#endif
