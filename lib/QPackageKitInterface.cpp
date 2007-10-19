#include "QPackageKitInterface.h"

QPackageKitInterface::QPackageKitInterface(const QString &service, const QString &path, const QDBusConnection &connection, QObject *parent)
	: QDBusAbstractInterface(service, path, staticInterfaceName(), connection, parent)
{
}

QPackageKitInterface::~QPackageKitInterface()
{
}

