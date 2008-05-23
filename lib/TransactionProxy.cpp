#include "TransactionProxy.h"

/*
 * Implementation of interface class TransactionProxy
 */

TransactionProxy::TransactionProxy(const QString &service, const QString &path, const QDBusConnection &connection, QObject *parent)
    : QDBusAbstractInterface(service, path, staticInterfaceName(), connection, parent)
{
}

TransactionProxy::~TransactionProxy()
{
}

