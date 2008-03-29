#ifndef CLIENT_H
#define CLIENT_H

#include <QtCore>

#include "DBusProxy.h"
#include "Status.h"
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

	void searchName(QString filter, QString name);

signals:
	void newPackage(Package *p);

private:
	DBusProxy *proxy;
	QString _tid; // TID this instance is tied to. QString() means no tying
	void getTid();
	bool _promiscuous; // Weither this instance listens on all transactions or not

private slots:
	void Package_cb(const QString& tid, const QString& info, const QString& package_id, const QString& summary);

};

} // End namespace PackageKit

#endif
