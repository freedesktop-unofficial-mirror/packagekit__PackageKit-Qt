#ifndef DAEMON_H
#define DAEMON_H

#include <QtCore>

#include "CentralProxy.h"

#include "Transaction.h"

namespace PackageKit {

class Daemon : public QObject {

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

};

} // End namespace PackageKit

#endif
