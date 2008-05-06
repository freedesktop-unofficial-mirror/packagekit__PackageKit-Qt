#include "CentralProxy.h"

using namespace PackageKit;

/*
 * Implementation of interface class CentralProxy
 */

CentralProxy::CentralProxy(const QString &service, const QString &path, const QDBusConnection &connection, QObject *parent)
    : QDBusAbstractInterface(service, path, staticInterfaceName(), connection, parent)
{
}

CentralProxy::~CentralProxy()
{
}

