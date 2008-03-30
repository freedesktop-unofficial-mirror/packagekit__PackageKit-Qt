#ifndef CLIENT_H
#define CLIENT_H

#include <QtCore>

#include "DBusProxy.h"
#include "Status.h"
#include "Role.h"
#include "Exit.h"
#include "Package.h"

namespace PackageKit {

class Client : public QObject {

	Q_OBJECT

public:
	Client(QObject *parent = 0);
	~Client();

	bool setPromiscuous(bool enabled);
	void setTid(QString newTid);
	const QString& tid();
	bool allowCancel();

	Status::Value status();
	Role::Value role(QString &package_id);

	void searchName(QString filter, QString name);
	void searchDetails(QString filter, QString search);
	void searchGroup(QString filter, QString group);
	void cancel();

	void backendDetails(QString *name, QString *author);

signals:
	void newPackage(Package *p);
	void Finished(Exit::Value status, uint runtime);
	void ProgressChanged(uint percentage, uint subpercentage, uint elapsed, uint remaining);

private:
	DBusProxy *proxy;
	QString _tid; // TID this instance is tied to. QString() means no tying
	void getTid();
	bool _promiscuous; // Weither this instance listens on all transactions or not

private slots:
	void Package_cb(const QString& tid, const QString& info, const QString& package_id, const QString& summary);
	void Finished_cb(const QString& tid, const QString& status, uint runtime);
	void ProgressChanged_cb(const QString& tid, uint percentage, uint subpercentage, uint elapsed, uint remaining);

};

} // End namespace PackageKit

#endif
