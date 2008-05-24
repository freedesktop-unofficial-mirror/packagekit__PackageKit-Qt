#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <QtCore>

#include "TransactionProxy.h"
#include "Package.h"
#include "Exit.h"

namespace PackageKit {

class Transaction : public QObject {

	Q_OBJECT

public:
	Transaction(QString tid, QObject *parent = 0);
	~Transaction();

	// PackageKit functions
	void cancel();

	void searchName(const QString& filter, const QString& name);

signals:
	void GotPackage(Package *p);
	void Details(Package *p, const QString& license, const QString& group, const QString& detail, const QString& url, qulonglong size);
	void Finished(Exit::Value status, uint runtime);

private slots:
	void Package_cb(const QString &info, const QString &package_id, const QString &summary);
	void Details_cb(const QString &package_id, const QString &license, const QString &group, const QString &detail, const QString &url, qulonglong size);
	void Finished_cb(const QString& exit, uint runtime);

private:
	TransactionProxy *proxy;
	QString _tid;

};

} // End namespace PackageKit

#endif