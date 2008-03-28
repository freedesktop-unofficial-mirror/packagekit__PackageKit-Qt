#ifndef CLIENT_H
#define CLIENT_H

#include <QtCore>

#include "DBusProxy.h"
#include "Status.h"

namespace PackageKit {

class Client : public QObject {

	Q_OBJECT

public:
	Client(QObject *parent = 0);
	~Client();

	bool setPromiscuous(bool enabled);
	QString getTid();
	void setTid(QString newTid);
	const QString& tid();
	bool allowCancel();
	Status::Value status();

private:
	DBusProxy *proxy;
	QString _tid; // TID this instance is tied to. QString() means no tying
	bool _promiscuous; // Weither this instance listens on all transactions or not

};

} // End namespace PackageKit

#endif
