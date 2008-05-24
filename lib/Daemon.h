#ifndef DAEMON_H
#define DAEMON_H

#include <QtCore>

#include "CentralProxy.h"


namespace PackageKit {

class Transaction;

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

	void suggestQuit();

	Transaction* newTransaction();

private:
	CentralProxy *proxy;
	QString getTid();

};

} // End namespace PackageKit

#endif
