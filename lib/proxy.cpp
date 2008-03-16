#include "proxy.h"

namespace PackageKit {

/*
 * Implementation of interface class DBusProxy
 */

DBusProxy::DBusProxy(const QString &service, const QString &path, const QDBusConnection &connection, QObject *parent)
    : QDBusAbstractInterface(service, path, staticInterfaceName(), connection, parent)
{
}

DBusProxy::~DBusProxy()
{
}

} // End namespace PackageKit
