#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <QtCore>

#include "TransactionProxy.h"
#include "Package.h"

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
	void gotPackage(Package *p);

private slots:
	void Package_cb(const QString &info, const QString &package_id, const QString &summary);

private:
	TransactionProxy *proxy;
	QString _tid;

};

} // End namespace PackageKit

#endif
