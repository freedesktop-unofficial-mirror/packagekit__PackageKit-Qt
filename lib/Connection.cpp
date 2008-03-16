#include "Connection.h"

namespace PackageKit {

Connection::Connection(QObject *parent) : QObject(parent)
{
	// The code here
	proxy = new DBusProxy(DBusProxy::staticInterfaceName(), PK_PATH, QDBusConnection::systemBus(), this);
}

Connection::~Connection()
{
}

bool Connection::valid()
{
	// And here too :-)
}

} // End namespace PackageKit
