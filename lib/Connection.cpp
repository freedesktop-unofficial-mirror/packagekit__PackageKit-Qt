#include "Connection.h"
#include "constants.h"

namespace PackageKit {

Connection::Connection(QObject *parent) : QObject(parent)
{
	proxy = new DBusProxy(PK_NAME, PK_PATH, QDBusConnection::systemBus(), this);
	connect(QDBusConnection::systemBus().interface(), SIGNAL(serviceOwnerChanged(const QString&, const QString&, const QString&)), this,
									SLOT(ownerChanged(const QString&, const QString&, const QString&)));
}

Connection::~Connection()
{
}

bool Connection::valid()
{
	return proxy->isValid();
}

void Connection::ownerChanged(const QString &name, const QString &oldOwner, const QString &newOwner) {
	if(name != QString(PK_NAME)) return;
	if(oldOwner == "") emit changed(true);
	if(newOwner == "") emit changed(false);
}

} // End namespace PackageKit
