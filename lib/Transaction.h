#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <QtCore>

#include "TransactionProxy.h"
#include "Package.h"
#include "Exit.h"
#include "Role.h"
#include "Status.h"

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
	void getPackages(const QString& filter);
	void getDetails(Package *p);
	void getFiles(Package *p);
	void getDepends(Package *p, const QString &filter, bool recursive = true);
	void getRequires(Package *p, const QString &filter, bool recursive = true);

	void installPackages(const QList<Package*> &packages);
	void installPackage(Package *p);
	void removePackages(const QList<Package*> &packages, bool allow_deps = false, bool autoremove = false);
	void removePackage(Package *p, bool allow_deps = false, bool autoremove = false);

	void getProgress(uint &percentage, uint &subpercentage, uint &elapsed, uint &remaining);

signals:
	void GotPackage(Package *p);
	void Details(Package *p, const QString& license, const QString& group, const QString& detail, const QString& url, qulonglong size);
	void Files(Package *p, QStringList files);
	void Finished(Exit::Value status, uint runtime);
	void ProgressChanged(uint percentage, uint subpercentage, uint elapsed, uint remaining);

private slots:
	void Package_cb(const QString &info, const QString &package_id, const QString &summary);
	void Details_cb(const QString &package_id, const QString &license, const QString &group, const QString &detail, const QString &url, qulonglong size);
	void Files_cb(const QString &pid, const QString &file_list);
	void Finished_cb(const QString& exit, uint runtime);

private:
	TransactionProxy *proxy;
	Daemon *parent;
	QString _tid;

};

} // End namespace PackageKit

#endif
