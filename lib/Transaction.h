#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <QtCore>

#include "TransactionProxy.h"
#include "Package.h"
#include "Exit.h"
#include "Role.h"
#include "Status.h"
#include "Provides.h"
#include "SignatureType.h"

namespace PackageKit {

class Daemon;

class Transaction : public QObject {

	Q_OBJECT

public:
	Transaction(Daemon *parent = 0);
	~Transaction();

	// PackageKit functions
	void renewTid();
	bool allowCancel();
	void cancel();
	Role::Value getRole(Package *p = NULL);
	Status::Value getStatus();

	void searchName(const QString& filter, const QString& name);
	void searchDetails(const QString &filter, const QString& search);
	void searchGroup(const QString &filter, const QString& search);
	void searchFile(const QString &filter, const QString& file);
	void getPackages(const QString& filter);
	void getDetails(Package *p);
	void getFiles(Package *p);
	void getDepends(Package *p, const QString &filter, bool recursive = true);
	void getRequires(Package *p, const QString &filter, bool recursive = true);
	void whatProvides(const QString &filter, const Provides::Value &type, const QString& search);
	void resolve(const QString &filter, Package *p);

	void installPackages(const QList<Package*> &packages);
	void installPackage(Package *p);
	void installSignature(const SignatureType::Value &type, const QString &key_id, Package *p);
	void updatePackages(const QList<Package*> &packages);
	void updatePackage(Package *p);
	void installFiles(const QStringList& files, bool trusted = false);
	void removePackages(const QList<Package*> &packages, bool allow_deps = false, bool autoremove = false);
	void removePackage(Package *p, bool allow_deps = false, bool autoremove = false);

	void updateSystem();
	void rollback(const QString &tid);

	void getUpdates(const QString& filter);
	void getUpdateDetail(const QString& package_id);

	void refreshCache(bool force = false);
	void getProgress(uint &percentage, uint &subpercentage, uint &elapsed, uint &remaining);
	void getRepoList(const QString &filter);
	void repoEnable(const QString &repo_id, bool enabled);
	void repoSetData(const QString &repo_id, const QString &parameter, const QString &value);
	bool isCallerActive();
	void getOldTransactions(uint number);

signals:
	void GotPackage(Package *p);
	void Details(Package *p, const QString& license, const QString& group, const QString& detail, const QString& url, qulonglong size);
	void Files(Package *p, QStringList files);
	void Finished(Exit::Value status, uint runtime);
	void ProgressChanged(uint percentage, uint subpercentage, uint elapsed, uint remaining);
	void UpdateDetail(const QString &package_id, const QString &updates, const QString &obsoletes, const QString &vendor_url, const QString &bugzilla_url, const QString &cve_url, const QString &restart, const QString &update_text);
	void RequireRestart(const QString&, const QString&);
	void AllowCancel(bool allow_cancel);
    void ErrorCode(const QString &code, const QString &details);
    void Message(const QString &message, const QString &details);
	void StatusChanged(Status::Value v);
	void RepoDetail(const QString &repo_id, const QString &details, bool enabled);
	void OldTransaction(const QString &tid, const QString &timespec, bool succeeded, Role::Value role, uint duration, const QString& data);

private slots:
	void Package_cb(const QString &info, const QString &package_id, const QString &summary);
	void Details_cb(const QString &package_id, const QString &license, const QString &group, const QString &detail, const QString &url, qulonglong size);
	void Files_cb(const QString &pid, const QString &file_list);
	void Finished_cb(const QString& exit, uint runtime);
	void StatusChanged_cb(const QString& status);
	void Transaction_cb(const QString &tid, const QString &timespec, bool succeeded, const QString &role, uint duration, const QString& data);

private:
	TransactionProxy *proxy;
	Daemon *parent;
	QString _tid;

};

} // End namespace PackageKit

#endif
