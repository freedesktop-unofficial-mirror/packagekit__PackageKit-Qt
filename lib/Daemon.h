#ifndef DAEMON_H
#define DAEMON_H

#include <QtCore>

#include "CentralProxy.h"

#include "Transaction.h"

namespace PackageKit {

class Daemon : public QObject {

	friend class Transaction;

	Q_OBJECT

public:
	Daemon(QObject *parent = 0);
	~Daemon();

	// PackageKit functions
	QStringList getActions();
	void getBackendDetails(QString &name, QString &author);
	QStringList getFilters();
	QStringList getGroups();

	bool getNetworkState();
	void suggestQuit();

	Transaction* newTransaction();

protected:
	QString getTid();

private:
	CentralProxy *proxy;

private slots:
	void NetworkStateChanged_cb(const QString &status);

signals:
	void NetworkStateChanged(bool status);

};

} // End namespace PackageKit

#endif
