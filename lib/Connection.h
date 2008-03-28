#ifndef CONNECTION_H
#define CONNECTION_H

#include <QtDBus>
#include "DBusProxy.h"


namespace PackageKit {

class Connection : public QObject {
	
	Q_OBJECT

public:
	Connection(QObject *parent = 0);
	~Connection();

	bool valid();

signals:
	void changed(bool connected);
private slots:
	void ownerChanged(const QString &name, const QString &oldOwner, const QString &newOwner);

private:
	DBusProxy *proxy;
};

} // End namespace PackageKit

#endif
