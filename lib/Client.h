#ifndef CLIENT_H
#define CLIENT_H

#include <QtCore>

#include "DBusProxy.h"

namespace PackageKit {

class Client : public QObject {

	Q_OBJECT

public:
	Client(QObject *parent = 0);
	~Client();

	bool setTid(QString newTid);
	bool setPromiscuous(bool enabled);
	const QString& tid();
	bool allowCancel();

private:
	DBusProxy *proxy;
	QString _tid; // TID this instance is tied to. QString() means no tying
	bool _promiscuous; // Weither this instance listens on all transactions or not

};

} // End namespace PackageKit

#endif
